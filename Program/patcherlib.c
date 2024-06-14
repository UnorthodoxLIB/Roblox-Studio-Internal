// This is a library for easy, high-level use of the patcher.
// This is intended to be easily used, & not require routine updating.
// This library should be used Synchronously, parallel calls may cause catastrophic error.

// This library isn't to be used yet, & will only be available one day.
// Added alot of comments to make this more user friendly, since I got some complaints with the old, sorry!

static const char *_ = "Copyright (c) 2024 UnorthodoxLIB\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files(the \"Software\"), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions :\n\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.";

#include "patcherlib.h"

// statically defined stuff for signatures & topatch. If this is outdated, it still serves to function as an allocator & initializer.
unsigned char signatures[] = { 0x41,0x38,0x9e,0x78,0x01,0x00,0x00,0x74,0x05,0xe8 },
                 toPatch[] = { 0x41,0x38,0x9e,0x78,0x01,0x00,0x00,0x90,0x90,0xe8 };


// Compares two arrays.
static long e; // E is only used for the iterator in mco & mcp, to provide a more "static" memory use.
inline __int8 mco(const void* s1, const void* s2, long n) {
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;
    for (e = 0; e < n; e++) { if (p1[e] != p2[e]) { return(p1[e] < p2[e]) ? -1 : 1; } }
    return 0;
}

// Copies an array to dest.
inline void mcp(void* dest, const void* src, long n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (e = 0; e < n; e++) { d[e] = s[e]; }
}


// BR = BytesRead, i = index, wsa = wsa initiated.
unsigned __int8 br = 0, wsa = 0;

static WSADATA wsaData; // WSA Data stuff
static char httpBuffer[4]; // Buffer of 5 characters, so it reads 0x00, then the next from there. Simply removing the , in the program makes this function a-ok.

static struct sockaddr_in ghsa;

// Binary buffer stored on heap. 140 Bytes, * 1024 = 140Kilobytes, * 1024 = 140 Megabytes, (Enough to fit the executable)
unsigned char binary[140 * 1024 * 1024];
// BI = Binary in, BO = Binary out.
FILE* bi, * bo;

// I is used in updating, & patching.
// O is used in patching.
// S is used in patching.
// s = FileSize, i = Index, o = Offset.
long s = 0, i = 0, o = 0;

// initializes WSA, & gets the valid github data. Then assures the function wont update again if called again.
static inline int initWsa() {
    if (wsa == 0) {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
        {
            return -1;
        }
        wsa = 1;
    }
    return 0;
}

// simple get function. Original method was lower level, but it turns out github doesn't like responding to it.

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        // out of memory!
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char* httpGetSync(const char* url) {
    CURL* curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "robloxinternal-agent/1.0");

    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        free(chunk.memory);
        chunk.memory = NULL;
    }

    curl_easy_cleanup(curl_handle);

    curl_global_cleanup();
    return chunk.memory;
}

// array updator
static inline void updateArray(unsigned char* Array, unsigned char* Apple)
{
    static unsigned char AppleOX[40];
    static unsigned __int8 i;
    static unsigned __int8 i2;


    for (i = 0; i < sizeof(*Apple); i+=4, i2++)
    {
        const char Num[4] = { Apple[i], Apple[i+1], Apple[i+2], Apple[i+3] };
        AppleOX[i2] = (char)strtol(&Num, NULL, 16);
    }

    for (i = 0; i < 10; i++)
    {
        Array[i] = AppleOX[i];
    };
}
// updates signatures.
inline void updatePatcherSignatures() {
    static char signaturesEndpoint[] = "https://raw.githubusercontent.com/UnorthodoxLIB/Roblox-Studio-Internal-Patcher/master/Update/signatures.hex";

    const char* stuff = httpGetSync(&signaturesEndpoint);

    updateArray(signatures, stuff);

    printf("Response SIG: ");
    printf("%s",(char*)stuff);
    printf("\n");
    return;
}

// updates patch data.
inline void updatePatcherPatches() {
    static char patchesEndpoint[] = "https://raw.githubusercontent.com/UnorthodoxLIB/Roblox-Studio-Internal-Patcher/master/Update/patches.hex"; // endpoint signature target.
    const char* stuff = httpGetSync(&patchesEndpoint);

    updateArray(toPatch, stuff);

    printf("Response PTC: ");
    printf("%s", (char*)stuff);
    printf("\n");
    return;
}

// updates I guess?
inline void updatePatcherData() {
    updatePatcherSignatures();
    updatePatcherPatches();
}

// Patches.
inline void PatchStudio(const char* studioPath,const char* createInternalAt) 
{
    bi = fopen(studioPath, "rb"); bo = fopen(createInternalAt, "wb");
    fseek(bi, 0, SEEK_END); // moves the pointer.
    s = ftell(bi); // sets filesize to size of bi.
    fseek(bi, 0, SEEK_SET); // moves the pointer.
    fread(&binary, 1, s, bi); // reads & sets to "binary" like a buffer.
    for (i = 0; i < s - sizeof(signatures); ++i)if (mco(&binary[i], signatures, sizeof(toPatch)) == 0) { o = i; break; } // Finds the offset.
    mcp(&binary[o], toPatch, sizeof(toPatch)); // Copies data from toPatch to binary, at the index [o] (starting from)
    fwrite(&binary, 1, s, bo); // Writes
    fclose(bi); fclose(bo); // closes files.
}

/*
Everything's defined as inline.
This doesn't mean it is actually inlined, but rather it may be inlined based on the call.

TODO
Finish the program later.
*/
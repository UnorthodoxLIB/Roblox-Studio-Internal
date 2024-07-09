<<<<<<< HEAD
#pragma once
//#undef _WIN32
#define _WIN64
=======
/*
patcherlib v1.1.0;

Overhauled codebase compared to before.
Supports clang now.
*/
#define CURL_STATICLIB
// #define fopen fopen_s // (MIGRATION INTENDED LATER, TODO!)

>>>>>>> ec172efb65ad64322f94a32342619ac1e81f427d
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <curl/curl.h>

// Prototype funcs.
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
static inline void updateArray(unsigned char *Array, unsigned const char *Apple);
static inline void updatePatcherSignatures();
static inline void updatePatcherPatches();
static inline void updatePatcherData();
static inline char PatchStudio(const char *studioPath, const char *createInternalAt);

#pragma comment(lib, "Ws2_32.lib")

<<<<<<< HEAD
// Updates patcher signatures (Just signatures)
void updatePatcherSignatures();
// Updates patcher Patchs (Just patches)
void updatePatcherPatches();
// Updates patcher data (Signatures & Patches)
void updatePatcherData();
// Patches studio, studio path being the path to RobloxStudioBeta.exe, createInternalAt being where you want the file to be created, & what you want its name to be.
unsigned char PatchStudio(const char* studioPath,const char* createInternalAt);
=======
static unsigned char signatures[10] = { 0x41, 0x38, 0x9e, 0x78, 0x01, 0x00, 0x00, 0x74, 0x05, 0xe8 };
static unsigned char toPatch[10] = { 0x41, 0x38, 0x9e, 0x78, 0x01, 0x00, 0x00, 0x90, 0x90, 0xe8 };

struct MemoryStruct {
    char *memory;
    size_t size;
};

// Global variables
static unsigned char binary[140 * 1024 * 1024];
static FILE *bi, *bo;

// Compares two arrays.
static inline int mco(const void *s1, const void *s2, long n) {
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    for (long e = 0; e < n; e++) {
        if (p1[e] != p2[e]) {
            return (p1[e] < p2[e]) ? -1 : 1;
        }
    }
    return 0;
}

// Copies an array to dest.
static inline void mcp(void *dest, const void *src, long n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (long e = 0; e < n; e++) {
        d[e] = s[e];
    }
}

// Performs a synchronous HTTP GET request.
static char *httpGetSync(const char *url) {
    CURL *curl_handle;
    CURLcode res;
    struct MemoryStruct chunk;
    
    chunk.memory = (char*)malloc(1);
    if (!chunk.memory) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    if (!curl_handle) {
        fprintf(stderr, "Failed to initialize curl.\n");
        free(chunk.memory);
        return NULL;
    }

    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &chunk);
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

// Updates an array with the codes stored on github (40 chars converted to hex array of 10)
static inline void updateArray(unsigned char *Array, unsigned const char *Apple) {
    static unsigned char AppleOX[10];
    for (unsigned char i = 0, i2 = 0; i < 40; i += 4, i2++) {
        const unsigned char Num[4] = { Apple[i], Apple[i+1], Apple[i+2], Apple[i+3] };
        AppleOX[i2] = (char)strtol((const char*)Num, NULL, 16);
    }

    for (unsigned char i = 0; i < 10; i++) {
        Array[i] = AppleOX[i];
    }
}

// Updates signatures.
static inline void updatePatcherSignatures() {
    static const char signaturesEndpoint[] = "https://raw.githubusercontent.com/UnorthodoxLIB/Roblox-Studio-Internal-Patcher/master/Update/signatures.hex";
    unsigned const char *stuff = (unsigned const char*)httpGetSync(signaturesEndpoint);
    if (stuff!=NULL) 
    {
        updateArray(signatures, stuff);
        printf("Response SIG: %s\n", stuff);
    }
}

// Updates patch data.
static inline void updatePatcherPatches() {
    static const char patchesEndpoint[] = "https://raw.githubusercontent.com/UnorthodoxLIB/Roblox-Studio-Internal-Patcher/master/Update/patches.hex";
    unsigned const char *stuff = (unsigned const char*)httpGetSync(patchesEndpoint);
    if (stuff!=NULL) {
        updateArray(toPatch, stuff);
        printf("Response PTC: %s\n", stuff);
    }
}

// Updates data.
static inline void updatePatcherData() {
    updatePatcherSignatures();
    updatePatcherPatches();
}

// Patches.
static inline char PatchStudio(const char *studioPath, const char *createInternalAt) {
    
    bi = fopen(studioPath, "rb"); // TODO fopen_s
    bo = fopen(createInternalAt, "wb"); // TODO fopen_s
    if (!bi) return 1;
    if (!bo) return 2;

    fseek(bi, 0, SEEK_END);
    unsigned long long s = ftell(bi);
    fseek(bi, 0, SEEK_SET);
    fread(binary, 1, s, bi);
    
    for (unsigned long long i = 0; i < s - sizeof(signatures); ++i) {
        if (mco(&binary[i], signatures, sizeof(toPatch)) == 0) {
            long o = i;
            mcp(&binary[o], toPatch, sizeof(toPatch));
            break;
        }
    }

    fwrite(binary, 1, s, bo);
    fclose(bi);
    fclose(bo);

    return 0;
}

// CURL callback for writing received data to memory.

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize); // Fix: Use memcpy
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}
>>>>>>> ec172efb65ad64322f94a32342619ac1e81f427d

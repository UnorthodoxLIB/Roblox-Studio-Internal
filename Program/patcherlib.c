// This is a library for easy, high-level use of the patcher.
// This is intended to be easily used, & not require routine updating.
// This library should be used Synchronously, parallel calls may cause catastrophic error.

// This library isn't to be used yet, & will only be available one day.
// Added alot of comments to make this more user friendly, since I got some complaints with the old, sorry!

static _ = "Copyright (c) 2024 UnorthodoxLIB\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files(the \"Software\"), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions :\n\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.";

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

char signaturesEndpoint[] = "/path/to/signatures"; // endpoint signature target.
char patchesEndpoint[] = "/path/to/patches"; // endpoint patch target.
char githubDomain[] = "github.com"; // github domain name.

// BR = BytesRead, i = index, wsa = wsa initiated.
unsigned __int8 br = 0, wsa = 0;

static WSADATA wsaData; // WSA Data stuff
static char httpBuffer[5]; // Buffer of 5 characters, so it reads 0x00, then the next from there. Simply removing the , in the program makes this function a-ok.

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

// sets GHSA's values, & gets github's IP.
static inline void updateGHSA() {
    ghsa.sin_family = AF_INET;
    ghsa.sin_port = htons(80);
    ghsa.sin_addr.s_addr = *(unsigned __int32*)gethostbyname(githubDomain)->h_addr_list[0];
}

// initializes WSA, & gets the valid github data. Then assures the function wont update again if called again.
static inline int initWsa() {
    if (wsa == 0) {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
        {
            return -1;
        }
        updateGHSA();
        wsa = 1;
    }
    return 0;
}

// updates signatures.
inline void updatePatcherSignatures() {
    if (initWsa() != 0) return;

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

    if (connect(clientSocket, (struct sockaddr*)&ghsa, sizeof(ghsa)) == -1) {
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    char getRequest[256];
    snprintf(getRequest, sizeof(getRequest), "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", signaturesEndpoint, githubDomain);
    send(clientSocket, getRequest, strlen(getRequest), 0);

    i = 0;
    while ((br = recv(clientSocket, httpBuffer, sizeof(httpBuffer), 0)) > 0) {
        for (int j = 0; j < br; j++) {
            toPatch[i++] = httpBuffer[j];
            if (i >= sizeof(toPatch)) break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
}

// updates patch data.
inline void updatePatcherPatches() {
    if (initWsa() != 0) return;

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

    if (connect(clientSocket, (struct sockaddr*)&ghsa, sizeof(ghsa)) == -1) {
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    char getRequest[256];
    snprintf(getRequest, sizeof(getRequest), "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", patchesEndpoint, githubDomain);
    send(clientSocket, getRequest, strlen(getRequest), 0);

    i = 0;
    while ((br = recv(clientSocket, httpBuffer, sizeof(httpBuffer), 0)) > 0) {
        for (int j = 0; j < br; j++) {
            toPatch[i++] = httpBuffer[j];
            if (i >= sizeof(toPatch)) break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
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
#include <windows.h>

const unsigned char signatures[] = { 0x41, 0x38, 0x9e, 0x78, 0x01, 0x00, 0x00, 0x74, 0x05, 0xe8 };
const unsigned char toPatch[] = { 0x41, 0x38, 0x9e, 0x78, 0x01, 0x00, 0x00, 0x90, 0x90, 0xe8 };
unsigned char binary[140 * 1024 * 1024];
long i, o, s, e;
HANDLE bi, bo;
void* v = 0;
inline __int8 mco(const void* s1, const void* s2, size_t n) {
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;
    for (e = 0; e < n; e++) { if (p1[e] != p2[e]) { return(p1[e] < p2[e]) ? -1 : 1; } }
    return 0;
}
inline void mcp(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (e = 0; e < n; e++) { d[e] = s[e]; }
}
int main() {
    bi = CreateFile("RobloxStudioBeta.exe",0x80000000L,0x00000001,v,3,0x00000080,v);
    bo = CreateFile("RobloxStudioInternal.exe",0x40000000L,0,v,2,0x00000080,v);
    {LARGE_INTEGER fileSize; GetFileSizeEx(bi, &fileSize); s = fileSize.QuadPart;}
    ReadFile(bi,&binary,s,v,v);
    for (i=0;i<s -sizeof(signatures);++i)if(mco(&binary[i],signatures,sizeof(toPatch))==0){o=i;break;}
    mcp(&binary[o],toPatch,sizeof(toPatch));
    WriteFile(bo,&binary,s,v,v);
    CloseHandle(bi);CloseHandle(bo);
    return 0;
}
#include <stdio.h>
const unsigned char signatures[]={0x41,0x38,0x9e,0x78,0x01,0x00,0x00,0x74,0x05,0xe8},
                       toPatch[]={0x41,0x38,0x9e,0x78,0x01,0x00,0x00,0x90,0x90,0xe8};
unsigned char binary[140*1024*1024];
long i,o,s,e;FILE*bi,*bo;

inline char mco(const void* s1, const void* s2, size_t n) {
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;
    for (e=0;e<n;e++){if(p1[e]!=p2[e]){return(p1[e]<p2[e])?-1:1;}}
    return 0;
}
inline void mcp(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for(e = 0; e < n; e++){d[e] = s[e];}
}
int main()
{
	bi=fopen("RobloxStudioBeta.exe","rb");bo=fopen("RobloxStudioInternal.exe","wb");
    fseek(bi,0,SEEK_END);
    s=ftell(bi);
    fseek(bi,0,SEEK_SET);
    fread(&binary,1,s,bi);
    for(i=0;i<s-sizeof(signatures);++i)if(mco(&binary[i],signatures,sizeof(toPatch))==0){o=i;break;}
    mcp(&binary[o],toPatch,sizeof(toPatch));
    fwrite(&binary,1,s,bo);
    fclose(bi);fclose(bo);
}
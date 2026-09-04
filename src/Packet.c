#include "common.h"

#include "vu0.h"

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_DispQW);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_DumpPac);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeBoundingBox);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_error);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeNormalStrip);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_getWeight);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeClusterStrip);
extern char D_0054F5C0[];
extern float D_00638C44;
extern float D_00638C48;
extern char D_0067C010[];
extern void debug_StdPrintfDummy__pn(const char *fmt, ...) __asm__("debug_StdPrintfDummy");

void pac_openDmaTag(int a0)
{
    register int mask = 0x0FFFFFFF;
    char *ctx = D_0067C010;
    float f0 = D_00638C44;
    float f1 = D_00638C48;
    *(int *)(ctx + 0x20) = a0 & mask;
    *(int *)(ctx + 0x24) = (a0 + 0x8) & mask;
    *(int *)(ctx + 0x28) = (a0 + 0x10) & mask;
    *(int *)(ctx + 0x2C) = a0 + 0x20;
    *(float *)(ctx + 0x48) = f0;
    *(float *)(ctx + 0x44) = f0;
    *(float *)(ctx + 0x40) = f0;
    *(float *)(ctx + 0x58) = f1;
    *(float *)(ctx + 0x54) = f1;
    *(float *)(ctx + 0x50) = f1;
    debug_StdPrintfDummy__pn(D_0054F5C0, a0 & mask);
}
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_setVifCode);
extern char D_0067C010[];
extern void debug_StdPrintfDummy();

void pac_setVifEndCode(void)
{
    char *ctx = D_0067C010;
    int *p = (int *)*(int *)(ctx + 0x2C);
    *p++ = 0x17000000;
    *(int *)(ctx + 0x2C) = (int)p;
    p[0] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 1);
    p[1] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 2);
    p[2] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 3);
    debug_StdPrintfDummy(p + 3);
}
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_setGifTag);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_closeTag);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_continueTag);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_checkDivide);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_countOneVertexPacketSize);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeStrip);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_setMaterialPacket);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeMaterialTable);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeMaterialTableLine);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_getTextureInfo);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeShapeTable);
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makePacket);
extern void pac_makePacket(void *a0, int a1, int a2);
void pac_MakePacket(char *a0) {
    char *p = *(char **)(a0 + 0x854);
    pac_makePacket(p, *(int *)(*(char **)(a0 + 0x874) + 0xF0), *(signed char *)(p + 0x2F) > 0);
}
extern void pac_DispQW(void *p, void *a2);

void pac_Dump(int *a0, int size)
{
    int *p = a0;
    int count;
    size >>= 4;
    if (size <= 0)
        return;
    count = size;
    do {
        int *arg = p;
        p += 4;
        pac_DispQW(arg, 4);
        count--;
    } while (count != 0);
}
extern int D_0063C154;

void pac_Init(void) {
    D_0063C154 = 0;
}
void pac_DispVu1Memory(int idx, int n, void *a2) {
    char *p = (char *)0x1100C000 + (idx << 4);
    int i;
    for (i = 0; i < n; i++) {
        char *q = p;
        p += 0x10;
        pac_DispQW(q, a2);
    }
}

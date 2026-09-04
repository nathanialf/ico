#include "common.h"

typedef union { long long ll; struct { int lo, hi; } w; } McHdr;

typedef union { long long ll; struct { int lo, hi; } w; } McTestVal;

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrGetInfo);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcHandlerWrite);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcHandlerRead);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrChdirProduct);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrSaveSeg);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrLoadSeg);
extern void iosMcMgrSaveSeg(void *a0, int a1);

void iosMcMgrSaveProductBlock(void *a0) {
    *(int *)((char *)a0 + 0x24) = 0;
    iosMcMgrSaveSeg(a0, 0);
}
extern void iosMcMgrLoadSeg(void *a0, int a1);

void iosMcMgrLoadProductBlock(void *a0) {
    *(int *)((char *)a0 + 0x24) = 0;
    iosMcMgrLoadSeg(a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrGetBlockSaveInfo);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", func_001399A8);
void iosMcTest(void) {}
int iosMcSync(unsigned long *a0)
{
    unsigned long x = *a0;
    char y = x;
    unsigned long z = y & 1ul;
    y = z;
    return -((int)y);
}
extern char D_0029B9E8[];
extern int iosMsgSend(void *a0, void *a1, int a2);

int iosMcGetInfo(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 0;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}
int iosMcFormat(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 3;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}
int iosMcUnformat(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 4;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcGetDir);
extern int D_0029B9E8__pn[] __asm__("D_0029B9E8");

int iosMcDelete(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 2;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
int iosMcSaveIconBlock(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 7;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcSaveProductBlock);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcLoadProductBlock);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcSaveGameBlock);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcLoadGameBlock);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcChdirProduct);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcGetBlockSaveInfo);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", product_write);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", product_read);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", gameblock_write);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", gameblock_read);

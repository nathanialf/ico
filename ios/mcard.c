#include "common.h"

typedef union { long long ll; struct { int lo, hi; } w; } McTestVal;

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcHandlerWrite);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcHandlerRead);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrChdirProduct);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrSaveSeg);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrLoadSeg);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrSaveProductBlock);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrLoadProductBlock);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrGetBlockSaveInfo);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", func_00137E48);

void iosMcManager(void) {}

int iosMcMgrSync(unsigned long *a0)
{
    unsigned long x = *a0;
    char y = x;
    unsigned long z = y & 1ul;
    y = z;
    return -((int)y);
}

extern char D_00280F88[];
extern int iosMsgSend(void *a0, void *a1, int a2);

int iosMcTest(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 0;
    v->ll = v->ll & -2;
    return iosMsgSend(D_00280F88, a0, 0);
}

int iosMcSync(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 3;
    v->ll = v->ll & -2;
    return iosMsgSend(D_00280F88, a0, 0);
}

int iosMcGetInfo(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 4;
    v->ll = v->ll & -2;
    return iosMsgSend(D_00280F88, a0, 0);
}


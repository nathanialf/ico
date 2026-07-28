#include "common.h"

typedef union { long long ll; struct { int lo, hi; } w; } McHdr;



extern void func_00136280();
extern unsigned char D_00280C60[];
extern void iosMcHandlerWrite();
INCLUDE_ASM("asm/nonmatchings/ios/mcdata", iosMcIconWriteIconsys);

extern int D_00280F88[];
extern int iosMsgSend(void *a, void *b, int c);

int iosMcIconWriteIcon(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 2;
    v->ll = v->ll & -2;
    return iosMsgSend(D_00280F88, a0, 0);
}

int _iosMcIconWriteIconsys(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 7;
    v->ll = v->ll & -2;
    return iosMsgSend(D_00280F88, a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_001380B0);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_001380F8);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_00138140);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_00138188);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_001381D0);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_00138218);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_00138260);

int func_00138390(int *self)
{
    int idx = self[0x8 / 4];
    iosMcHandlerWrite((int)self, (int)((char *)D_00280C60 + idx * 0x18C), 0x18C);
    return self[0x10 / 4];
}

int func_001383D8(int a0, int a1)
{
    func_00136280(a0, a1, 0x63FC);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_001383F8);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", func_00138510);


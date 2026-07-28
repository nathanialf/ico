#include "common.h"



extern void func_00136280();
extern unsigned char D_00280C60[];
extern void iosMcHandlerWrite();
INCLUDE_ASM("asm/nonmatchings/ios/mcdata", iosMcIconWriteIconsys);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", iosMcIconWriteIcon);

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", _iosMcIconWriteIconsys);

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


#include "common.h"

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

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcTest);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcSync);

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcGetInfo);


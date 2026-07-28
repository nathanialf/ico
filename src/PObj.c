#include "common.h"


extern int D_00712CC0[];
INCLUDE_ASM("asm/nonmatchings/src/PObj", MakeBoundingBox);

INCLUDE_ASM("asm/nonmatchings/src/PObj", MakePacket);

int AllocPObj(int idx)
{
    return D_00712CC0[idx];
}

INCLUDE_ASM("asm/nonmatchings/src/PObj", InitPObj);

INCLUDE_ASM("asm/nonmatchings/src/PObj", FreePObj);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240C50);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240D40);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240EA0);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240FC8);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_002412D8);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_002413F0);


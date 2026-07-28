#include "common.h"


extern char D_00275850[];
INCLUDE_ASM("asm/nonmatchings/src/windField", InitWindField);

INCLUDE_ASM("asm/nonmatchings/src/windField", drawSenpuukiHaneUnit);

INCLUDE_ASM("asm/nonmatchings/src/windField", drawSenpuuki);

int *ExecWindField(int *a0)
{
    if (a0) *a0 = 0;
    return D_00275850;
}

INCLUDE_ASM("asm/nonmatchings/src/windField", GetWindVector);

INCLUDE_ASM("asm/nonmatchings/src/windField", dummyGetWindVector);

INCLUDE_ASM("asm/nonmatchings/src/windField", getParallelWindVector);

INCLUDE_ASM("asm/nonmatchings/src/windField", getRadiateWindVector);


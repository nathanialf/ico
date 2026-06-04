#include "common.h"

extern int D_00271BD0[];

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", InitWindField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", drawSenpuukiHaneUnit);

extern int (*D_0062BA30)(void);

int drawSenpuuki(void) {
    return D_0062BA30();
}

void *ExecWindField(int *a0) {
    if (a0) {
        *a0 = 0;
    }
    return D_00271BD0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", GetWindVector);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", dummyGetWindVector);

extern int (*D_0062BA30)(void);

void getParallelWindVector(void) {
    D_0062BA30 = ExecWindField;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", getRadiateWindVector);

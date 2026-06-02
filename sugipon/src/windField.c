#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", InitWindField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", drawSenpuukiHaneUnit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", drawSenpuuki);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", ExecWindField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", GetWindVector);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", dummyGetWindVector);

extern void ExecWindField(void);
extern void (*D_0062BA30)(void);

void getParallelWindVector(void) {
    D_0062BA30 = ExecWindField;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", getRadiateWindVector);

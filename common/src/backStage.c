#include "common.h"

extern int D_0062AB2C;

void backStageProcessOutStage(int a0) {
    D_0062AB2C = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageProcessMain);

extern int D_0062AB18;
extern int D_0062AB24;
extern int D_0062AB34;

void routeSetPos(void) {
    D_0062AB18 = 0;
    D_0062AB24 = 0;
    D_0062AB34 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageProcessInStage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageSave);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageProcessInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageDebugTimeZero);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageTsuresariReturn);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", func_0019E5A8);

#include "common.h"

extern int D_0062AB2C;

void backStageProcessOutStage(int a0) {
    D_0062AB2C = a0;
}

extern int D_00271240[];
extern int D_004AEE28[];
extern int D_004B1D90[];
extern void func_001ABE88(int *, int *, int);

void backStageProcessMain(void) {
    if (D_00271240[2] != 0) {
        func_001ABE88(D_004AEE28, D_004B1D90, 0);
        D_00271240[3] = 1;
    }
}

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

extern int D_0062AB50;
extern int D_0062C120;
extern int D_0062C114;
extern int D_0062C134;

void func_0019E5A8(void) {
    D_0062AB50 = 0;
    D_0062C120 = -1;
    D_0062C114 = 0;
    D_0062C134 = 0;
}

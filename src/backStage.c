#include "common.h"





extern int D_00633E44;
extern int D_00633E30;
extern int D_00633E24;
extern int D_00632888;
extern int D_00632850;
extern int D_0063285C;
extern int D_0063286C;
extern int D_004B3B28[];
extern int D_00274EC0[];
extern void func_001AE8F0(int *self, int a1, int a2);
extern int D_004B6A90[];
extern int D_00632864;
void backStageProcessOutStage(int val) {
    D_00632864 = val;
}

void backStageProcessMain(void)
{
    if (D_00274EC0[2]) {
        func_001AE8F0(D_004B3B28, D_004B6A90, 0);
        D_00274EC0[3] = 1;
    }
}

void routeSetPos(void) {
    D_00632850 = 0;
    D_0063285C = 0;
    D_0063286C = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageProcessInStage);

INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageSave);

INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageLoad);

INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageProcessInit);

INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageDebugTimeZero);

INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageTsuresariReturn);

void func_001A1008(void) {
    D_00632888 = 0;
    D_00633E30 = -1;
    D_00633E24 = 0;
    D_00633E44 = 0;
}


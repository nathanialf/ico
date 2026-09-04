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
extern void gamesysMemorySave(int *self, int a1, int a2);
extern int D_004B6A90[];
extern int D_00632864;
void backStageProcessOutStage(int val) {
    D_00632864 = val;
}

void CheckPoint(void)
{
    if (D_00274EC0[2]) {
        gamesysMemorySave(D_004B3B28, D_004B6A90, 0);
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

extern int D_00633E28;
extern int D_00633E2C;
extern int D_00633E34;
extern int D_00633E38;
extern int D_00633E3C;
extern int D_00633E40;
extern int func_001AE1B8(void *, void *, int);

void backStageDebugTimeZero(void *a0) {
    func_001AE1B8(a0, &D_00632888, 4);
    func_001AE1B8(a0, &D_00633E24, 4);
    func_001AE1B8(a0, &D_00633E28, 4);
    func_001AE1B8(a0, &D_00633E2C, 4);
    func_001AE1B8(a0, &D_00633E30, 4);
    func_001AE1B8(a0, &D_00633E34, 4);
    func_001AE1B8(a0, &D_00633E38, 4);
    func_001AE1B8(a0, &D_00633E3C, 4);
    func_001AE1B8(a0, &D_00633E40, 4);
}

extern int gamesysMemoryHandlerRead(void *, void *, int);

void backStageTsuresariReturn(void *a0) {
    gamesysMemoryHandlerRead(a0, &D_00632888, 4);
    gamesysMemoryHandlerRead(a0, &D_00633E24, 4);
    gamesysMemoryHandlerRead(a0, &D_00633E28, 4);
    gamesysMemoryHandlerRead(a0, &D_00633E2C, 4);
    gamesysMemoryHandlerRead(a0, &D_00633E30, 4);
    gamesysMemoryHandlerRead(a0, &D_00633E34, 4);
    gamesysMemoryHandlerRead(a0, &D_00633E38, 4);
    gamesysMemoryHandlerRead(a0, &D_00633E3C, 4);
    gamesysMemoryHandlerRead(a0, &D_00633E40, 4);
}

void func_001A1008(void) {
    D_00632888 = 0;
    D_00633E30 = -1;
    D_00633E24 = 0;
    D_00633E44 = 0;
}


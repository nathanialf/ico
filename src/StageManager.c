#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/StageManager", stop_free_resources);
INCLUDE_ASM("asm/nonmatchings/src/StageManager", stage_initialize);
extern int D_00639D10;
extern int DeleteStreamMotionManager();
extern void backStageProcessOutStage();
extern void gamesysStageExitTimeSet(int idx);
extern void sndBgmReadyNextStage(int *a, int *b);
extern void warpGirlInStage();
extern void warpGirlOutStage();

void exit_stage(int *self)
{
    gamesysStageExitTimeSet(D_00639D10);
    warpGirlOutStage(D_00639D10, 0);
    warpGirlInStage(self);
    backStageProcessOutStage();
    sndBgmReadyNextStage(self, D_00639D10);
    return DeleteStreamMotionManager();
}
INCLUDE_ASM("asm/nonmatchings/src/StageManager", start_stage_Load_thread);
INCLUDE_ASM("asm/nonmatchings/src/StageManager", stgmgrNextStagePreLoad);
INCLUDE_ASM("asm/nonmatchings/src/StageManager", stgmgrNextStagePreLoadEntry);
INCLUDE_ASM("asm/nonmatchings/src/StageManager", func_001A8AA8);
extern void stgmgrForceSwitchWithFadeColor(int a0, int a1, int a2, int a3);

void stgmgrForceSwitchWithFade(int a0) {
    stgmgrForceSwitchWithFadeColor(a0, 0, 0, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/StageManager", stgmgrForceSwitchWithFadeColor);
extern int D_0063ACC8;
extern int D_0063ACCC;
extern int D_0063C34C;

void stgmgrNextStagePreLoadForceStageSet(int val) {
    D_0063C34C = val;
    D_0063ACC8 = 1;
    D_0063ACCC = 0;
}
void stgmgrNextStagePreLoadDistBoyMode(void) {
    D_0063ACC8 = 0;
    D_0063ACCC = 0;
}
void stgmgrNextStagePreLoadForceNoCancel(int val) {
    D_0063ACCC = val;
}
extern int D_0028F4C0[];
extern int D_004DA788[];
extern int D_004DD700[];
extern void gamesysMemorySave(int *self, int a1, int a2);

void CheckPoint(void)
{
    if (D_0028F4C0[2]) {
        gamesysMemorySave(D_004DA788, D_004DD700, 0);
        D_0028F4C0[3] = 1;
    }
}
extern int D_0063ACB8;
extern int D_0063ACC4;
extern int D_0063ACD4;

void stgmgrNextStagePreLoadDiskNotReady(void) {
    D_0063ACB8 = 0;
    D_0063ACC4 = 0;
    D_0063ACD4 = 0;
}

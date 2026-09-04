#include "common.h"

typedef struct { unsigned char _0[0xA0]; short ent[0x18]; unsigned char _d0[0xC4]; } StgPre;
typedef struct { int f0; unsigned char _4[0x24]; } StgFile;
typedef struct { int f0; unsigned char _4[0xC]; int f10; unsigned char _14[0xC]; } StgSlot;

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
extern StgSlot D_004D9A30[];
extern StgFile D_0055C53C[];
extern StgPre D_005F5D50[];
extern char D_00619128[];
extern int D_0063ACB8;
extern int D_0063ACBC;
extern int D_0063ACC0;
extern int D_0063ACC4;
extern int D_0063ACC8;
extern int D_0063ACD0;
extern int D_0063ACD4;
extern int D_0063ACD8;
extern int D_0063ACEC;
extern int PositionOfExit();
extern int iosCdvdBackGroundMgrAdd();
extern int iosCdvdBackGroundMgrNotDiskReadyPauseSet();
extern void stgmgrNextStagePreLoad(void);
extern void stgmgrNextStagePreLoadDiskNotReady(void);

void stgmgrNextStagePreLoadEntry(int stage) {
    StgPre *pre = &D_005F5D50[stage];
    int i;
    int ret;

    D_0063ACEC = 0;
    for (i = 0; i < 15; i++) {
        short s = pre->ent[i];
        if (s != 0) {
            int count = D_0063ACEC;
            D_004D9A30[count].f0 = D_0055C53C[s].f0;
            if (PositionOfExit(&D_004D9A30[count].f10, i + 1) == 0) {
                D_0063ACEC = D_0063ACEC + 1;
            }
        }
    }
    ret = iosCdvdBackGroundMgrAdd(D_00619128, stgmgrNextStagePreLoad, 0, stgmgrNextStagePreLoadDiskNotReady, 0, 0, 0, 0);
    D_0063ACD0 = ret;
    iosCdvdBackGroundMgrNotDiskReadyPauseSet(ret, 1);
    D_0063ACB8 = 0;
    D_0063ACD8 = 0;
    D_0063ACD4 = 0;
    D_0063ACBC = 0;
    D_0063ACC0 = 0;
    D_0063ACC4 = 0;
    D_0063ACC8 = 0;
}
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

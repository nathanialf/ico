#include "common.h"

typedef struct { unsigned char _0[0xA0]; short ent[0x18]; unsigned char _d0[0xC4]; } StgPre;
typedef struct { int f0; unsigned char _4[0x24]; } StgFile;
typedef struct { int f0; unsigned char _4[0xC]; int f10; unsigned char _14[0xC]; } StgSlot;

INCLUDE_ASM("asm/nonmatchings/src/StageManager", stop_free_resources);
INCLUDE_ASM("asm/nonmatchings/src/StageManager", stage_initialize);
extern int stage_no;
extern int DeleteStreamMotionManager();
extern void backStageProcessOutStage();
extern void gamesysStageExitTimeSet(int idx);
extern void sndBgmReadyNextStage(int *a, int *b);
extern void warpGirlInStage();
extern void warpGirlOutStage();

void exit_stage(int *self)
{
    gamesysStageExitTimeSet(stage_no);
    warpGirlOutStage(stage_no, 0);
    warpGirlInStage(self);
    backStageProcessOutStage();
    sndBgmReadyNextStage(self, stage_no);
    return DeleteStreamMotionManager();
}
INCLUDE_ASM("asm/nonmatchings/src/StageManager", start_stage_Load_thread);
INCLUDE_ASM("asm/nonmatchings/src/StageManager", stgmgrNextStagePreLoad);
extern StgSlot stageExitData[];
extern StgFile D_0055C53C[];
extern StgPre D_005F5D50[];
extern char D_00619128[];
extern int stagePreLoadStageNo;
extern int stagePreLoadReadOffset;
extern int stagePreLoad2ndReadOffset;
extern int D_0063ACC4;
extern int D_0063ACC8;
extern int D_0063ACD0;
extern int stagePreLoadLsn;
extern int stagePreLoadSectorCnt;
extern int stageExitDataCnt;
extern int PositionOfExit();
extern int iosCdvdBackGroundMgrAdd();
extern int iosCdvdBackGroundMgrNotDiskReadyPauseSet();
extern void stgmgrNextStagePreLoad(void);
extern void stgmgrNextStagePreLoadDiskNotReady(void);

void stgmgrNextStagePreLoadEntry(int stage) {
    StgPre *pre = &D_005F5D50[stage];
    int i;
    int ret;

    stageExitDataCnt = 0;
    for (i = 0; i < 15; i++) {
        short s = pre->ent[i];
        if (s != 0) {
            int count = stageExitDataCnt;
            stageExitData[count].f0 = D_0055C53C[s].f0;
            if (PositionOfExit(&stageExitData[count].f10, i + 1) == 0) {
                stageExitDataCnt = stageExitDataCnt + 1;
            }
        }
    }
    ret = iosCdvdBackGroundMgrAdd(D_00619128, stgmgrNextStagePreLoad, 0, stgmgrNextStagePreLoadDiskNotReady, 0, 0, 0, 0);
    D_0063ACD0 = ret;
    iosCdvdBackGroundMgrNotDiskReadyPauseSet(ret, 1);
    stagePreLoadStageNo = 0;
    stagePreLoadSectorCnt = 0;
    stagePreLoadLsn = 0;
    stagePreLoadReadOffset = 0;
    stagePreLoad2ndReadOffset = 0;
    D_0063ACC4 = 0;
    D_0063ACC8 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/StageManager", func_001A8AA8);
INCLUDE_ASM("asm/nonmatchings/src/StageManager", func_001A8D98);
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
extern int stagePreLoadStageNo;
extern int D_0063ACC4;
extern int stagePreLoadLsn;

void stgmgrNextStagePreLoadDiskNotReady(void) {
    stagePreLoadStageNo = 0;
    D_0063ACC4 = 0;
    stagePreLoadLsn = 0;
}

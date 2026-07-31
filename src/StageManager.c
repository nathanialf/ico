#include "common.h"

typedef struct { unsigned char _0[0xA0]; short ent[0x18]; unsigned char _d0[0xC4]; } StgPre;
typedef struct { int f0; unsigned char _4[0x24]; } StgFile;
typedef struct { int f0; unsigned char _4[0xC]; int f10; unsigned char _14[0xC]; } StgSlot;



extern int D_00632864;
extern int D_00632860;
extern int D_00633E20;
extern void func_00180BC0();
extern void backStageProcessInStage();
extern void sndManager(int *a, int *b);
extern void AttackCheckHit();
extern int D_00631990;
extern int _transRingBuf();
extern void ExitIcoMisc(int idx);
INCLUDE_ASM("asm/nonmatchings/src/StageManager", stop_free_resources);

void stage_initialize(int *self)
{
    ExitIcoMisc(D_00631990);
    func_00180BC0(D_00631990, 0);
    AttackCheckHit(self);
    backStageProcessInStage();
    sndManager(self, D_00631990);
    return _transRingBuf();
}

INCLUDE_ASM("asm/nonmatchings/src/StageManager", exit_stage);

INCLUDE_ASM("asm/nonmatchings/src/StageManager", start_stage_Load_thread);

extern StgSlot D_004B2DF0[];
extern StgFile D_0056194C[];
extern StgPre D_005F2FB8[];
extern char D_006127E8[];
extern int D_00632850;
extern int D_00632854;
extern int D_00632858;
extern int D_0063285C;
extern int D_00632868;
extern int D_0063286C;
extern int D_00632870;
extern int D_00632884;
extern int func_00168C88();
extern int iosCdvdBackGroundMgrSeek();
extern int iosCdvdChgFileName();
extern void routeSetPos(void);
extern void start_stage_Load_thread(void);

void stgmgrNextStagePreLoad(int stage) {
    StgPre *pre = &D_005F2FB8[stage];
    int i;
    int ret;

    D_00632884 = 0;
    for (i = 0; i < 15; i++) {
        short s = pre->ent[i];
        if (s != 0) {
            int count = D_00632884;
            D_004B2DF0[count].f0 = D_0056194C[s].f0;
            if (func_00168C88(&D_004B2DF0[count].f10, i + 1) == 0) {
                D_00632884 = D_00632884 + 1;
            }
        }
    }
    ret = iosCdvdChgFileName(D_006127E8, start_stage_Load_thread, 0, routeSetPos, 0, 0, 0, 0);
    D_00632868 = ret;
    iosCdvdBackGroundMgrSeek(ret, 1);
    D_00632850 = 0;
    D_00632870 = 0;
    D_0063286C = 0;
    D_00632854 = 0;
    D_00632858 = 0;
    D_0063285C = 0;
    D_00632860 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/StageManager", stgmgrNextStagePreLoadEntry);

typedef struct StgMsg {
    int f0;
    int stage;
    int f8;
    float fC;
    float f10;
    unsigned char f14, f15, f16;
} StgMsg;

extern StgMsg D_002757D0;
extern char D_004B2DC0[];
extern int D_00631A10;
extern void iosMsgSend(void *q, void *msg, int a2);

void func_0019FF68(int a0) {
    D_002757D0.stage = a0;
    D_002757D0.f0 = 0;
    D_00631A10 = 1;
    D_002757D0.fC = 0.0f;
    return iosMsgSend(D_004B2DC0, &D_002757D0, 0);
}

extern void stgmgrForceSwitch(int a0, int a1, int a2, int a3);

void StageManager(int a0) {
    stgmgrForceSwitch(a0, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/StageManager", stgmgrForceSwitch);

void stgmgrForceSwitchWithFade(int val) {
    D_00633E20 = val;
    D_00632860 = 1;
    D_00632864 = 0;
}

void stgmgrForceSwitchWithFadeColor(void) {
    D_00632860 = 0;
    D_00632864 = 0;
}


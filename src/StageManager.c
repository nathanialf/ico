#include "common.h"



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

INCLUDE_ASM("asm/nonmatchings/src/StageManager", stgmgrNextStagePreLoad);

INCLUDE_ASM("asm/nonmatchings/src/StageManager", stgmgrNextStagePreLoadEntry);

INCLUDE_ASM("asm/nonmatchings/src/StageManager", func_0019FF68);

INCLUDE_ASM("asm/nonmatchings/src/StageManager", StageManager);

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


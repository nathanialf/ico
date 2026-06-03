#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stop_free_resources);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stage_initialize);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", exit_stage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", start_stage_Load_thread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stgmgrNextStagePreLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stgmgrNextStagePreLoadEntry);

extern void stgmgrForceSwitch(int a0, int a1, int a2, int a3);

void StageManager(int a0) {
    stgmgrForceSwitch(a0, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stgmgrForceSwitch);

extern int D_0062C110;
extern int D_0062AB28;
extern int D_0062AB2C;

void stgmgrForceSwitchWithFade(int a0) {
    D_0062C110 = a0;
    D_0062AB28 = 1;
    D_0062AB2C = 0;
}

extern int D_0062AB28;
extern int D_0062AB2C;

void stgmgrForceSwitchWithFadeColor(void) {
    D_0062AB28 = 0;
    D_0062AB2C = 0;
}

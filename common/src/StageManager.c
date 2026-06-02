#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stop_free_resources);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stage_initialize);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", exit_stage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", start_stage_Load_thread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stgmgrNextStagePreLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stgmgrNextStagePreLoadEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", StageManager);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stgmgrForceSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", stgmgrForceSwitchWithFade);

extern int D_0062AB28;
extern int D_0062AB2C;

void stgmgrForceSwitchWithFadeColor(void) {
    D_0062AB28 = 0;
    D_0062AB2C = 0;
}

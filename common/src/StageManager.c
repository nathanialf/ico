#include "common.h"

extern void func_0013F480(void);
extern void debug_assertMessage(char *a0);
extern void func_0010ED88(void);
extern void func_00104CF0(void);
extern void SetDarkVolumeEffect(void);
extern void gsb_StageSettingTool(void);
extern void func_0010F058(void);
extern void debug_Load(void);
extern void func_001AB108(void);
extern void func_00100A70(int a0);
extern char D_0060B178[], D_0060B188[], D_0060B1A0[], D_0060B1B0[];
extern char D_0060B1C8[], D_0060B1D8[], D_0060B1F0[];

void stop_free_resources(void)
{
    func_0013F480();
    debug_assertMessage(D_0060B178);
    func_0010ED88();
    debug_assertMessage(D_0060B188);
    func_00104CF0();
    SetDarkVolumeEffect();
    debug_assertMessage(D_0060B1A0);
    gsb_StageSettingTool();
    debug_assertMessage(D_0060B1B0);
    func_0010F058();
    debug_assertMessage(D_0060B1C8);
    debug_Load();
    debug_assertMessage(D_0060B1D8);
    func_001AB108();
    debug_assertMessage(D_0060B1F0);
    return func_00100A70(2);
}

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


void stgmgrForceSwitchWithFadeColor(void) {
    D_0062AB28 = 0;
    D_0062AB2C = 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
    char               f_14;  /* 0x14 */
    char               f_15;  /* 0x15 */
    char               f_16;  /* 0x16 */
} S_00271B50;

/* end struct shapes */

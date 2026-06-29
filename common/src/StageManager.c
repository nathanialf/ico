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

extern int D_00629C90;
extern void ExitIcoMisc(int a0);
extern void func_0017E160(int a0, int a1);
extern void AttackCheckHit(int a0);
extern void backStageProcessInStage(void);
extern void sndManager(int a0, int a1);
extern void _transRingBuf(void);

void stage_initialize(int a0) {
    ExitIcoMisc(D_00629C90);
    func_0017E160(D_00629C90, 0);
    AttackCheckHit(a0);
    backStageProcessInStage();
    sndManager(a0, D_00629C90);
    _transRingBuf();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", exit_stage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", start_stage_Load_thread);

typedef struct { unsigned char _0[0xA0]; short ent[0x18]; unsigned char _d0[0xC0]; } StgPre;   /* 0x190 */
typedef struct { int f0; unsigned char _4[0x24]; } StgFile;                       /* 0x28 */
typedef struct { int f0; unsigned char _4[0xC]; int f10; unsigned char _14[0xC]; } StgSlot;  /* 0x20 */

extern StgPre D_005EBC48[];
extern StgFile D_0055A2FC[];
extern StgSlot D_004AE0F0[];
extern char D_0060B258[];
extern int func_00166AB8();
extern void start_stage_Load_thread(void);
extern void routeSetPos(void);
extern int iosCdvdChgFileName();
extern int iosCdvdBackGroundMgrSeek();
extern int D_0062AB18, D_0062AB1C, D_0062AB20, D_0062AB24, D_0062AB28;
extern int D_0062AB30, D_0062AB34, D_0062AB38, D_0062AB4C;

void stgmgrNextStagePreLoad(int stage) {
    StgPre *pre = &D_005EBC48[stage];
    int i;
    int ret;

    D_0062AB4C = 0;
    for (i = 0; i < 15; i++) {
        short s = pre->ent[i];
        if (s != 0) {
            int count = D_0062AB4C;
            D_004AE0F0[count].f0 = D_0055A2FC[s].f0;
            if (func_00166AB8(&D_004AE0F0[count].f10, i + 1) == 0) {
                D_0062AB4C = D_0062AB4C + 1;
            }
        }
    }
    ret = iosCdvdChgFileName(D_0060B258, start_stage_Load_thread, 0, routeSetPos, 0, 0, 0, 0);
    D_0062AB30 = ret;
    iosCdvdBackGroundMgrSeek(ret, 1);
    D_0062AB18 = 0;
    D_0062AB38 = 0;
    D_0062AB34 = 0;
    D_0062AB1C = 0;
    D_0062AB20 = 0;
    D_0062AB24 = 0;
    D_0062AB28 = 0;
}


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

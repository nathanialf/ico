#include "common.h"

extern void func_0013F480(void);
extern void debug_assertMessage(char *a0, ...);
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

extern void light_getAmbientLight(void *a0, int a1, int a2, int a3);
extern void func_0023EB60(int a0, int a1);
extern void func_0019CB28(void);
extern int func_0013D4B0(int a0);
extern void ClipStormByCamera(int a0);
extern void iosThreadWakeup(void *a0, int a1, void *a2, void *a3, int a4, long long a5, int a6);
extern void iosThreadJoin(void *a0);
extern void func_0023E168(void);
extern void func_00240AB8(void);
extern int func_00240B78(int a0);
extern void func_001ACA38(void);

extern char D_0060B200[], D_0060B210[];
extern unsigned char D_00271270[];
extern int D_00271594_a[] __asm__("D_00271594");
extern int D_00629CA0;
extern void *D_00629DE4, *D_00629DE8;
extern int D_00629E14, D_00629D20;
extern int D_0062A300, D_0062AAF8, D_0062AAFC, D_0062AB08;

typedef struct { unsigned char _0[0x14]; int f_14; int f_18; } S_00271240;
extern S_00271240 D_00271240;
typedef struct { unsigned char _0[0x3c]; unsigned int f_3c; } S_006DE080;
extern S_006DE080 D_006DE080;

void exit_stage(int a0) {
    unsigned long long flag;
    D_00629CA0 = D_00629C90;
    D_00629C90 = a0;
    light_getAmbientLight(D_00271270, 1, 1, 1);
    func_0023EB60(0, 0);
    D_0062AB08 = 1;
    func_0019CB28();
    if (D_0062AAF8 != 0) {
        func_0013F480();
        func_0023E168();
        func_00240AB8();
        func_00240B78(1);
        D_0062AAFC = 1;
        D_00271240.f_14 = 0;
        D_00271240.f_18 = 0;
        D_00629DE8 = 0;
        D_00629DE4 = 0;
        D_0062AB08 = 0;
        return;
    } /* keep goto-equivalent CFG */
    stop_free_resources();
    D_0062AB08 = 0;
    func_0013D4B0(0);
    ClipStormByCamera(D_00271594_a[0]);
    D_00629E14 = a0;
    iosThreadWakeup(&D_006DE080, 1, func_001ACA38, &D_00629C90, D_0062A300, 0x18000, 0x1B);
    iosThreadJoin(&D_006DE080);
    flag = D_006DE080.f_3c;
    debug_assertMessage(D_0060B200, (long long)(int)flag & 1);
    D_00629D20 = 1;
    debug_assertMessage(D_0060B210);
}


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

void StageManager(int a0) {
    stgmgrForceSwitch(a0, 0, 0, 0);
}

extern void iosMsgSend(void *a0, void *a1, int a2, int a3);
extern int D_004AE0C0[];
extern int D_0062AB04;
extern int D_00629D10;
typedef struct {
    int   f_0;   /* 0x00 */
    int   f_4;   /* 0x04 */
    char  _8[4]; /* 0x08 */
    float f_C;   /* 0x0C */
    float f_10;  /* 0x10 */
    char  f_14;  /* 0x14 */
    char  f_15;  /* 0x15 */
    char  f_16;  /* 0x16 */
} T_00271B50;
extern T_00271B50 D_00271B50;

/* NEAR-MISS (rc19, fan-1 convergence). LOGIC + STRUCTURE + ALL VALUES recovered.
 * Dev shape (byte-exact ops/values, only whole-function register coloring differs):
 *   void stgmgrForceSwitch(int a0,int a1,int a2,int a3,float f4,float f5){
 *       unsigned char b1=a1,b2=a2,b3=a3;
 *       D_00271B50.f_4=a0;
 *       D_0062AB04=((b3<<16)|b1)|((b2<<8)|0x80000000);
 *       D_00271B50.f_0=1; D_00629D10=1;
 *       D_00271B50.f_C=f5; D_00271B50.f_10=f4;
 *       D_00271B50.f_14=b1; D_00271B50.f_15=b2; D_00271B50.f_16=b3;
 *       iosMsgSend(D_004AE0C0,&D_00271B50,0,b3); }
 * StageManager tail-calls this with 4 int args (implicit decl, floats passthrough);
 * float args arrive in $f12(f4)/$f13(f5); f_C=f5, f_10=f4. The tail call is `j
 * iosMsgSend(D_004AE0C0,&D_00271B50,0,b3)`.
 * RESIDUAL (rc19, pure regalloc, NO value/structure diffs): ROM REUSES the dead
 * argument registers -- b3 stays in $7(a3, = iosMsgSend arg3, no move), 0x80000000
 * in $5(a1), %hi(D_00271B50) in $6(a2), and the struct base &D_00271B50 in $2(v0)
 * with the packed word in a temp ($8/t0). ee-gcc instead allocates FRESH t-regs
 * ($8-$11) for the masked bytes + &D and puts the pack in v0, then emits `move
 * $7,$9` (a3=b3) and `move $5,$8` before the tail call. 7 variants tried (b-temp vs
 * compound-mask-in-place a3&=0xFF, struct-pointer p=&D, pack-early vs pack-late,
 * ROM vs flat OR grouping) -- gcc never reuses the arg regs and never puts &D in
 * v0; the pack always grabs v0/v1 (born first). This is the dead-arg-reg-reuse +
 * base-in-v0 coloring convergence (cookbook dead_arg_reg / regalloc-swap). NEXT
 * LEVER: force &D_00271B50's base allocno to v0 and the 3 masked bytes to reuse
 * $5/$6/$7 (make_regs_eqv copy-preference from the params) so the pack falls to a
 * temp. NOT a floor. rc19. */
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

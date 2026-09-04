#include "common.h"

extern void func_0013F480(void);
extern void debug_StdPrintfDummy(char *a0, ...);
extern void InitTableSin(void);
extern void func_00104CF0(void);
extern void SetDarkVolumeEffect(void);
extern void gsb_StageSettingTool(void);
extern void p2o_TransMicroProgram(void);
extern void debug_Load(void);
extern void func_001AB108(void);
extern void func_00100A70(int a0);
extern char D_0060B178[], D_0060B188[], D_0060B1A0[], D_0060B1B0[];
extern char D_0060B1C8[], D_0060B1D8[], D_0060B1F0[];

void stop_free_resources(void)
{
    func_0013F480();
    debug_StdPrintfDummy(D_0060B178);
    InitTableSin();
    debug_StdPrintfDummy(D_0060B188);
    func_00104CF0();
    SetDarkVolumeEffect();
    debug_StdPrintfDummy(D_0060B1A0);
    gsb_StageSettingTool();
    debug_StdPrintfDummy(D_0060B1B0);
    p2o_TransMicroProgram();
    debug_StdPrintfDummy(D_0060B1C8);
    debug_Load();
    debug_StdPrintfDummy(D_0060B1D8);
    func_001AB108();
    debug_StdPrintfDummy(D_0060B1F0);
    return func_00100A70(2);
}

extern int D_00629C90;
extern void gamesysStageExitTimeSet(int a0);
extern void func_0017E160(int a0, int a1);
extern void AttackCheckHit(int a0);
extern void backStageProcessInStage(void);
extern void sndManager(int a0, int a1);
extern void _transRingBuf(void);

void stage_initialize(int a0) {
    gamesysStageExitTimeSet(D_00629C90);
    func_0017E160(D_00629C90, 0);
    AttackCheckHit(a0);
    backStageProcessInStage();
    sndManager(a0, D_00629C90);
    _transRingBuf();
}

extern void light_getAmbientLight(void *a0, int a1, int a2, int a3);
extern void sceGsSyncPath(int a0, int a1);
extern void func_0019CB28(void);
extern int func_0013D4B0(int a0);
extern void ClipStormByCamera(int a0);
extern void iosThreadWakeup(void *a0, int a1, void *a2, void *a3, int a4, long long a5, int a6);
extern void iosThreadJoin(void *a0);
extern void sceGsResetPath(void);
extern void sceVpu0Reset(void);
extern int sceDmaReset(int a0);
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
    sceGsSyncPath(0, 0);
    D_0062AB08 = 1;
    func_0019CB28();
    if (D_0062AAF8 != 0) {
        func_0013F480();
        sceGsResetPath();
        sceVpu0Reset();
        sceDmaReset(1);
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
    debug_StdPrintfDummy(D_0060B200, (long long)(int)flag & 1);
    D_00629D20 = 1;
    debug_StdPrintfDummy(D_0060B210);
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/StageManager", start_stage_Load_thread);

typedef struct { unsigned char _0[0xA0]; short ent[0x18]; unsigned char _d0[0xC0]; } StgPre;   /* 0x190 */
typedef struct { int f0; unsigned char _4[0x24]; } StgFile;                       /* 0x28 */
typedef struct { int f0; unsigned char _4[0xC]; int f10; unsigned char _14[0xC]; } StgSlot;  /* 0x20 */

extern StgPre D_005EBC48[];
extern StgFile D_0055A2FC[];
extern StgSlot D_004AE0F0[];
extern char D_0060B258[];
extern int PositionOfExit();
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
            if (PositionOfExit(&D_004AE0F0[count].f10, i + 1) == 0) {
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

void stgmgrForceSwitchWithFade(int a0) {
    stgmgrForceSwitch(a0, 0, 0, 0);
}

extern void iosMsgSend(void *a0, void *a1, int a2);
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

/* MATCHED rc0 (fan-1 convergence, 2026-07-24; byte-identical, was rc4/rc10/rc19).
 * The whole-function register allocation is now BYTE-EXACT to ROM. Two coupled
 * levers cracked the rc4 near-miss:
 *
 * 1. FLAT OR term order (not a pre-grouped hi/lo split). ROM packs the 32-bit
 *    value with a NON-adjacent byte grouping -- HI=(b3<<16)|b1, LO=(b2<<8)|signbit
 *    -- which is what ee-gcc's reassociation produces from the FLAT expression
 *    `(b3<<16) | b1 | 0x80000000 | (b2<<8)`. The rc4 pre-grouped `hi|lo` / `lo|hi`
 *    split forms are STRUCTURALLY unable to reach ROM: they couple base<->hi so
 *    that base=v0 forces hi=v1 (lo|hi, rc4) and hi=t0 forces base=v1 (hi|lo, rc18+).
 *    A 15120-config real-differ sweep proved base=v0 AND hi=t0 AND lo=v1 (ROM's
 *    coloring) is reachable ONLY with this flat term order -- 252 hits, all
 *    `...(b3<<16)|b1|0x80000000|(b2<<8)...` (the const combined via `|`, NOT `+`
 *    which regresses to `subu`). Mechanism: the flat form lets base(r101, refs8)
 *    win v0 in global find_reg while the hi accumulator still coalesces to t0 with
 *    the pack store-value; the pre-split forms fuse base's fate to the final-OR's
 *    op1 (see [two_allocno_tie_nearmisses]).
 * 2. Sub-OR operand order: ROM's `or $8,$8,$9` has hi_raw as op1, so the flat
 *    expression must lead with `(b3<<16)` before `b1` (leading with `b1` emits
 *    `or $8,$9,$8`, the last rc1 residual).
 * Statement order (a full-body real-differ sweep picked the rc0 order below):
 * f_4=a0; f_0=1; f_C=f5; f_10=f4; D_00629D10=1; byte stores; pack; call.
 * Crutch-free: no pins, barriers, or inline asm. */
void stgmgrForceSwitch(int a0, int a1, int a2, int a3, float f4, float f5)
{
    unsigned char b1 = a1, b2 = a2, b3 = a3;
    D_00271B50.f_4 = a0;
    D_00271B50.f_0 = 1;
    D_00271B50.f_C = f5;
    D_00271B50.f_10 = f4;
    D_00629D10 = 1;
    D_00271B50.f_14 = b1;
    D_00271B50.f_15 = b2;
    D_00271B50.f_16 = b3;
    D_0062AB04 = (b3 << 16) | b1 | 0x80000000 | (b2 << 8);
    iosMsgSend(D_004AE0C0, &D_00271B50, 0);
}

extern int D_0062C110;
extern int D_0062AB28;
extern int D_0062AB2C;

void stgmgrNextStagePreLoadForceStageSet(int a0) {
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

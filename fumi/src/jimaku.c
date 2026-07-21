#include "common.h"

/* jimaku 0x164 actor-state view (local) */
typedef struct { char _0[0x3A4]; int f_3A4; } JSub678;
typedef struct { char _0[0x30]; int f_30; char _pad34[0x308]; int f_33C; char _pad340[0x338]; JSub678 *p_678; } JimakuState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", display_texture);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", iosCdvdBackGroundReadJimaku);

extern void BoxBarSoundOn(int a0, int a1);
extern void _ACTWait(int a0);

void func_00173538(volatile int a0) {
    for (;;) {
        BoxBarSoundOn(a0, 0x13A);
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173568);

extern void debug_assertMessage(void *a0);
extern char D_00553730[];
extern int D_00629DE4;
extern int D_0062A4DC;
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern void ACTLookTargetSystem_Exec(void);

void func_00173610(volatile int a0) {
    debug_assertMessage(D_00553730);
    iosOmBeforeFuncStandard(D_00629DE4, 0x58, D_0062A4DC);
    ACTLookTargetSystem_Exec();
}

extern void debug_assertMessage(void *a0);
extern char D_00553790[], D_00553760[];
extern void func_001736D0(volatile int a0);
void jimakuHandler(volatile int a0) {
    int *gobj = *(int **)(a0 + 0x164);
    debug_assertMessage(D_00553790);
    gobj[0x30 / 4] = 0x50;
    gobj[0x14 / 4] = (int)func_001736D0;
    gobj[0xC0 / 4] = 0;
    while ((gobj[0xC0 / 4] & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_assertMessage(D_00553760);
    for (;;) {
        BoxBarSoundOn(a0, 0x5D);
        _ACTWait(1);
    }
}

void func_001736D0(volatile int a0) {
    debug_assertMessage(D_00553730);
    iosOmBeforeFuncStandard(D_00629DE4, 0x5D, D_0062A4DC);
    ACTLookTargetSystem_Exec();
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrBegin);

void func_00173790(volatile int a0) {
    debug_assertMessage(D_00553730);
    iosOmBeforeFuncStandard(D_00629DE4, 0x62, D_0062A4DC);
    ACTLookTargetSystem_Exec();
}

/* NEAR-MISS (rc11, W3 convergence). LOGIC + STRUCTURE fully recovered; residual
 * is a whole-function 3-way register coloring + return-0 funnel. Dev shape:
 *   extern void *D_00629DE8; extern unsigned char D_00284740[];
 *   int jimakuMgrNext(void) {
 *       JimakuState *s = *(JimakuState **)((char *)D_00629DE8 + 0x164);
 *       if (((*(unsigned long long *)((char *)s + 0x18) >> 36) & 1) == 0)
 *           return 1;
 *       if (s->f_30 == 0x45 && D_00284740[0x5D] != 0)
 *           return (D_00284740[0x58] == 0);
 *       return 0;
 *   }
 * All matched byte-exact: gp-rel chase, ld+dsrl32(4)+andi(1) bit-36 test (UNSIGNED
 * => dsrl32 not dsra32), bnel bit36-check with s->f_30 load in its delay, bne
 * f_30!=0x45, lbu D[0x5D] beqz, lbu D[0x58] sltiu(==0). Only diffs = REGISTER
 * COLORING + the return-0 funnel:
 *   ROM: v0 reserved for the return; `daddu v0,zero,zero` (v0=0 default) sits in
 *        the `bne f_30,0x45` DELAY slot (reorg-stolen from a SHARED exit .L7381C
 *        `jr;nop`); the compared loads (f_30, D[0x5D]) go to a0, base ptrs (s,&D)
 *        to v1 -> a genuine 3-register (v0/v1/a0) coloring, no final move.
 *   ours: gcc uses only 2 registers (v0/v1): loads->v1, consts/base->v0, and the
 *        two return paths do NOT merge to a shared `jr;nop` exit (v0=0 ends up in
 *        a trailing separate jr-delay, not the bne-delay). greg -dg confirms: our
 *        allocnos land only in v0/v1 (never a0); ROM spans 3.
 * The accumulator form (`int rv; ...; return rv`) DOES force 3 regs but colors rv
 * to a0 with a trailing `daddu v0,a0,zero` move (rc12). ~7 source forms (seq
 * returns, goto-funnel §8.3, ternary, if/else rv, nested-if, rv=1 default) all
 * collapse to the same rc11 2-reg form or the rc12 move form. NEXT LEVER: recover
 * the dev shape that makes gcc reserve v0 for the return AND cross-jump the exits
 * to a shared jr;nop so reorg steals v0=0 into the bne delay (v0-copy-preference
 * on the return without keeping a live rv across the compares). NOT a floor.
 *
 * SHARPENED (fan-1 convergence, greg -dg + reorg.c proof): the ACCUMULATOR is
 * the dev shape (confirmed). Form:
 *   int rv; if(bit36==0) return 1; rv=0;
 *   if(s->f_30==0x45) rv=(D[0x5D]==0)?0:(D[0x58]==0);  return rv;
 * reproduces ROM's structure EXACTLY -- `rv=0` (daddu $2,$0,$0) SIMPLE-filled into
 * the `bne f_30,0x45` delay, success falls through to the shared exit -- EXCEPT a
 * pure 3-CYCLE REGISTER ROTATION: ROM {rv=v0, base=v1, cmp-loads=a0}; ours
 * {rv=a0, base=v0, cmp-loads=v1} + a trailing `move $2,$4` (rc11/12).
 * ROOT (greg -dg): rv is a LONG-lived pseudo (reg 86, live_length=18, refs=3 =>
 * allocno pri floor_log2(3)*3/18*1e4 = 1666) that loses v0 to the shorter success
 * value (reg 94, ll=8, pri 3750, prefers v0). rv would WIN v0 at refs>=4
 * (floor_log2 jumps 1->2 => pri ~4444) but no source shape yields a 4th rv ref
 * without gcc folding it. The deeper cause is local-vs-global alloc ORDER: the &D
 * base is a pass-1 LOCAL allocno and grabs v0 (lowest available) BEFORE rv (a
 * pass-2 global) is colored; ROM's &D reuses the just-freed `s` register (v1),
 * leaving v0 for rv. 12 source variants (accumulator, ternary, goto-ret0 funnel,
 * rv=1-unified, reused-pointer b/s, explicit else rv=0, &D[i] addr-expr, char*
 * cast) all leave &D in v0 -> rv in a0. NEXT LEVER: force the &D base allocno to
 * v1 (make it a global allocno w/ a v1 copy-preference from dead `s`, WITHOUT
 * extending its live range across the bit36 branch). NOT a floor.
 */
extern void *D_00629DE8;
extern unsigned char D_00284740[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrNext);

void jimakuMgrJump(int a0) {
    if (D_00629DE8) {
        JimakuState *p = *(JimakuState **)((char *)D_00629DE8 + 0x164);
        JSub678 *q = p->p_678;
        q->f_3A4 = a0;
    }
}

void jimakuMgrEnd(void) {
    if (D_00629DE8) {
        JimakuState *p = *(JimakuState **)((char *)D_00629DE8 + 0x164);
        JSub678 *q = p->p_678;
        q->f_3A4 = 0;
    }
}

extern void _ACTWait(int a0);

void jimakuBegin(volatile int a0) {
    JimakuState *p = *(JimakuState **)(a0 + 0x164);
    p->f_33C = 0;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuNext);

void func_00173948(volatile int a0) {
    JimakuState *p = *(JimakuState **)(a0 + 0x164);
    p->f_33C = 0;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuJump);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173A84);

int jimakuEnd(void *a0, void *a1) {
    return (int)(*(float *)((char *)a0 + 0x20) - *(float *)((char *)a1 + 0x20));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuDisp);

extern void ACTLookTargetSystem_Exec(void);
extern void debug_assertMessage(void *a0);
extern void Vibration_ShotDecode(int a0);
extern char D_00553BE0[];

void jimakuManager(int a0) {
    volatile int home = a0;
    ACTLookTargetSystem_Exec();
    debug_assertMessage(D_00553BE0);
    Vibration_ShotDecode(7);
}

void jimakuUndisp(void *a0) {
    void *volatile q = a0;
    int *p = *(int **)((char *)q + 0x15C);
    *(int *)((char *)p + 0x624) = 0;
}

extern char D_00553DD8[];

void func_00173D00(volatile unsigned int a0)
{
    volatile int local;
    int *new_var;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    debug_assertMessage(D_00553DD8);
    s0 = new_var;
    s0[0x30 / 4] = 0x4;
    _ACTWait(0);
}

extern void ACTLookTargetSystem_Exec(void);
void func_00173D48(void *a0) {
    void *volatile q = a0;
    ACTLookTargetSystem_Exec();
}

extern int D_00629DE4;

int func_00173D68(int a0, int a1)
{
    int p = D_00629DE4;
    int q = (int)D_00629DE8;
    if ((a0 == p && a1 == q) || (a0 == q && a1 == p)) {
        JimakuState *obj = *(JimakuState **)(q + 0x164);
        if (obj->f_30 == 0x4E)
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173DB0);

extern void inflate_codes(int a0, int a1, int a2);
extern void huft_build(void *a0, int a1);

void func_00173F48(int self, int a1, int size)
{
    int large = size + 0x7FE;
    int v1 = size - 1;
    int neg_one = -1;
    if (neg_one < v1) large = v1;
    large = ((large >> 11) + 1) << 11;
    inflate_codes(self, a1, large);
    huft_build((void *)self, *(int *)((char *)self + 0x110) + size);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173FA8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_001741B0);

struct jNode {
    char  _0[4];
    int   status;
    int   field8;
    int   fieldC;
    char  _10[4];
    int   field14;
};

struct jWayGroup {  /* D_006A5900 element, stride 0x18 */
    int   f0;
    int   f4;
    int   f8;
    char  _c[4];
    struct jNode *node;
    char  _14[4];
};

struct jSub {       /* sub-object at offset 0xC of the argument */
    char  _0[0x2C];
    int   field2C;
    int   n;
    int   field34;
    char  _38[4];
    void *field3C;
    void *field40;
};

struct jArg {
    char  _0[0xC];
    struct jSub sub;
};

struct jBig { char _[0x8C40]; };

extern struct jWayGroup D_006A5900[];
extern struct jBig D_006A5980[];
extern char D_006C8A80[];
extern char D_006C8AB8[];
extern char D_006C8AF0[];
extern char D_00553E58[];
extern char D_00553E68[];
extern char D_00553E78[];
extern int D_00629D00;
extern int D_0062A7F4;
extern unsigned int D_0062C688[];
extern int  func_0013D5E8(void *);
extern int  func_00261188(void *buf, const char *fmt, int n);
extern int  func_0012FC08(void *buf, int x);
extern int  func_0012FCE0(int);
extern void func_0012FD10(int, int, int);
extern int  func_001AAD00(const char *, int);
extern int  func_00260380(const char *, int, void *);
extern void tex_printTexture(int);

void func_001743B8(struct jArg *p)
{
    char buf[16];
    struct jSub *q = &p->sub;
    struct jWayGroup *wg = &D_006A5900[q->n];
    int ww;

    while (wg->node->status != 4) {
        if (func_0013D5E8(D_006C8A80) < 0) return;
    }
    if (func_0013D5E8(D_006C8A80) < 0) return;

    wg->node->status = 1;
    func_00261188(buf, D_00553E58, (q->n + 1) % 4);
    ww = func_0012FC08(buf, wg->node->field14);
    wg->node->field8 = ww;
    func_0012FD10(func_0012FCE0(ww), 1, 1);
    wg->node->fieldC = D_00629D00;
    if (wg->node->field8 == -1) {
        debug_assertMessage(D_00553E68);
        func_001AAD00(D_00553E78, 0x272);
        func_00260380(D_00553E78, 0x272, D_0062C688);
    }

    q->n = (q->n + 1) % 4;
    if (func_0013D5E8(D_006C8AB8) < 0) return;

    wg->f4 = 2;
    if (wg->f8 >= 0) {
        tex_printTexture(wg->f8);
    }

    D_0062A7F4 = 1;
    q->field3C = &D_006A5980[q->n];
    do { } while (0); /* required: epilogue ld-ra scheduling */
}

void func_00174580(struct jArg *p)
{
    struct jSub *q = &p->sub;
    int m;

    huft_build(q->field40, q->field2C * 0x8800);
    m = (q->field34 = (q->n + 1) % 4);
    while (m != q->n) {
        D_006A5900[m].f0 = -1;
        D_006A5900[m].f4 = 3;
        D_006A5900[m].f8 = -1;
        m = (m + 1) % 4;
    }
    func_001743B8(p);
}

extern void iosCdvdBackGroundMgrEntryNum(int val);
extern void func_0013D570(char *p);

void func_00174650(int *p)
{
    int val = p[0x4C / 4];
    if (val != 0) {
        iosCdvdBackGroundMgrEntryNum(val);
    }
    func_0013D570(D_006C8AF0);
    func_0013D570(D_006C8AB8);
    func_0013D570(D_006C8A80);
}

extern int D_00286810[];
extern void iosMsgSend(void *a0, void *a1, int a2);

void func_00174698(void *a0) {
    *(int *)a0 = 0;
    iosMsgSend(D_00286810, a0, 1);
}

extern int D_00271268[];

void func_001746B8(int *a0) {
    if (D_00271268[0]) {
        a0[0] = 1;
        iosMsgSend(D_00286810, a0, 0);
    }
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_006A5900;  /* stride 0x18 */

/* end struct shapes */

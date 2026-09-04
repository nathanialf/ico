#include "common.h"

extern int D_006A4428[];

typedef struct { char _0[0x1B8]; int f1B8; } WishC;
typedef struct { char _0[0x670]; WishC *f670; } WishB;
typedef struct { char _0[0x164]; WishB *f164; } WishA;
extern int InitMultiBgaManager(int a0);

void ACTGetWish_FromPad(WishA *a0) {
    int v = InitMultiBgaManager(1);
    a0->f164->f670->f1B8 = v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_00149F60);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", ActGame_GetOrientQ);

/* NEAR-MISS (rc12, W3 convergence). LOGIC + STRUCTURE fully recovered; residual is
 * a callee-saved s0/s1 register-swap tie coupled with the 2nd jal delay-slot fill.
 * Dev shape:
 *   extern void memset(void *dst, int val, int n);
 *   extern void sceVu0ApplyMatrix(void *a0, int a1, void *a2);
 *   void _GetRootObjectOrient(void *a0, char *a1) {
 *       float buf[4];
 *       memset(buf, 0, 0x10);            // memset-like, 16 bytes
 *       buf[2] = 1.0f;                          // swc1 1.0 at sp+8
 *       sceVu0ApplyMatrix(a0, *(int *)(*(int *)(a1 + 0x15C) + 0xC), buf);
 *   }
 * Matched: frame 0x40 with s0/s1/ra saves, first call args (buf,0,0x10) with buf
 * in the jal delay, 1.0f build (lui 0x3f80;mtc1) + swc1 at sp+8, 2nd call (a0,
 * (a1->f_15C)->f_C, buf). VALUES all correct. Only residual (register names +
 * one delay slot):
 *   ROM: a0->s0, a1->s1 (`daddu s1,a1` emitted first, then `daddu s0,a0`); the
 *        2nd jal delay = `lw a1,12(v0)` (arg1 load), swc1 emitted BEFORE the jal.
 *   ours: gcc assigns a0->s1, a1->s0 (saves a0 first) and fills the 2nd jal delay
 *        with the swc1 instead, moving the arg1 load before the jal.
 * The s0/s1 pick is a symmetric allocno tie: both params are single-use, live
 * across the first call; gcc saves a0 first (->s1) where ROM saves a1 first
 * (->s1). Confirmed: routing a0 THROUGH the first call (`memset(a0,...)`)
 * flips it to a0->s0, so it is purely a first-use-order tie. ~4 forms (p-temp,
 * t-block, val-late, volatile carrier) don't flip it. NEXT LEVER: the dev shape
 * that makes gcc save a1 before a0 (a1 first-use earlier, or a0 lower allocno
 * priority) so a0 lands s0 and the swc1/lw arg pair reschedules. NOT a floor.
 *
 * SHARPENED (fan-1 convergence, QTY_CMP_PRI + dbr + local-alloc.c proof): the
 * s0/s1 swap and the delay-slot swap are ONE coupled root. local-alloc's
 * QTY_CMP_PRI = floor_log2(n_refs)*n_refs*size/(death-birth)*1e4 gives a1 (reg 85,
 * ll=6 => 3333) a HIGHER priority than a0 (reg 84, ll=8 => 2500), so a1 is colored
 * first and takes s0 (lowest callee-save); a0 gets s1. ROM wants a0->s0, which
 * requires a0's live range <= a1's. a0 outlives a1 ONLY because sched2 schedules
 * the longer arg1 dependency chain (lw 0x15C -> lw 0xC) BEFORE the single arg0
 * move (critical-path INSN_PRIORITY), so a1 dies (at 0x15C) one slot before a0
 * dies (at arg0). ROM instead schedules arg0 first AND defers the final arg1 load
 * (lw 0xC) into the 2nd jal's delay slot -- which shortens the arg1 chain's pre-
 * jal critical path so arg0 can lead. dbr then fills our delay with the swc1
 * (nearest pre-jal insn) instead of the arg1 load. Every variant that flips
 * a0->s0 (explicit 0x15C temp, void* p, int c=..., a1 int-param) does so ONLY by
 * hoisting the 0x15C load BEFORE the first call (a1 dies early), which ROM does
 * NOT do (ROM keeps a1 live across memset and loads 0x15C after). NEXT
 * LEVER: make sched2 defer the final arg1 load (lw 0xC) to the jal delay while
 * keeping 0x15C after the first call -- i.e. lower the arg1 chain's pre-jal
 * priority so arg0 leads and a0 wins s0. NOT a floor. rc12. */
extern void memset(void *dst, int val, int n);
extern void sceVu0ApplyMatrix(void *a0, int a1, void *a2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", _GetRootObjectOrient);

extern void avoidInsideOfWall(void *p);

void func_0014A110(int *a0) {
    volatile int *o = (volatile int *)a0[0x59];
    void *p = (void *)o[0x58];
    if (p != 0) {
        avoidInsideOfWall(p);
        o[0x59] = 0;
        o[0x58] = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", ACTCheckCollis_VIEW);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", ACTCheckViewClDetail);

void func_0014A3E0(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    *(float *)((char *)q + 0x58) = 1.0f;
    q[0x15] = 0;
}

extern char D_0055DA10_a[] __asm__("D_0055DA10");
extern int D_00629DE8;
extern float GetHeightOfCliffFromGObj(void *a0, float a1);

float func_0014A400(int *a0) {
    int *p = (int *)a0[0x164 / 4];
    char *sub = (char *)p[0x670 / 4];
    unsigned int state = *(unsigned int *)(sub + 0x54);
    int flag = 0;
    float f12 = 1.0f;
    char *e;
    if (state < 3) {
        flag = (a0 == (int *)D_00629DE8);
    }
    if (state == 1) {
        e = D_0055DA10_a + ((int *)a0[0x15C / 4])[0x490 / 4] * 0x190;
        if ((*(unsigned int *)(e + 0x188) >> 22) & 1) {
            f12 = *(float *)(sub + 0x58);
            flag = 0;
        }
    } else {
        e = D_0055DA10_a + ((int *)a0[0x15C / 4])[0x490 / 4] * 0x190;
        if (((*(unsigned int *)(e + 0x188) >> 21) & 1) == 0) {
            f12 = *(float *)(sub + 0x58);
        }
    }
    if (flag != 0) {
        f12 = 1.0f;
    }
    return GetHeightOfCliffFromGObj(a0, f12);
}

extern int DispIcoMisc(int *buf);
extern void queen_barrier_anim(int a0, int a1, int a2, int *buf);
extern int D_00629C90;

void GetGirlPositionAtThisStage(int a0)
{
    int buf[4];
    int v0 = DispIcoMisc(buf);
    queen_barrier_anim(a0, D_00629C90, v0, buf);
}

extern int D_002E0100[][37];
extern int D_005CA4B0[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_0014A510);


extern int D_002E0100[][37];

void func_0014A668(int *unused)
{
    int *dst = D_006A4428;
    char *src = (char *)D_002E0100;
    int i = 0x46;
    (void)unused;
    do {
        *dst = *(int *)src;
        i--;
        src += 0x94;
        dst++;
    } while (i >= 0);
}

extern int D_006A4428[];

void *func_0014A6A8(void) {
    return D_006A4428;
}

int func_0014A6B8(int a0, int a1) {
    int r = a0 ? 9 : 1;
    int t = r | 4;
    return a1 ? t : r;
}

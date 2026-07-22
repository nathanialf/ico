#include "common.h"

void huft_build(int *a0, int a1) {
    a0[68] = a1;
}

typedef struct {
    char pad[0x108];
    unsigned int f108;
    int f10C;
    int f110;
    int f114;
} InfCodes;

extern void func_002498E0(int, int, int, void *);
extern int func_002490C0(int);
extern int func_00249CB0(void);
extern void debug_assertMessage();
extern int D_0062A258;
extern int D_0062A268;
extern char D_00550E48[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_codes);


extern void func_00249AC0(int, int, int, void *);
extern char D_00550E68[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_stored);


extern int D_0062BF84;

int inflate_fixed(void) {
    return D_0062BF84;
}

extern int func_00249E10(void);
extern int func_00249CB0(void);

void inflate_dynamic(void *a0) {
    int *p = (int *)a0;
    p[3] = 0;
    if (func_00249E10() == 0) {
        p[3] = func_00249CB0();
    }
}

extern int func_00249E48(int a0, int a1, int a2, void *a3);
extern char D_00550E88[];

/* MATCHED. The stale-comment "rc5 scheduling/coloring floor" was solved by
 * recovering the real dev idiom: the assert PRINTS the error value, i.e.
 * `debug_assertMessage(D_00550E88, local)` passes `local` as arg1. That single
 * change resolves BOTH residuals at once:
 *  - COLORING: `local` is an outgoing arg1, so gcc colors the reload into $5 (a1)
 *    via the arg-reg copy-preference -- and since it is already in $5 the assert
 *    needs no extra move (ROM sets only $4 for the message).
 *  - SCHEDULE: the reload now feeds the assert call, which lifts the local-load
 *    above the result-stash sll so the load emits first; the un-issued sll then
 *    sinks into the beq delay slot (ROM's `sll s0,v0,11`), leaving `daddu v0,s0`
 *    (move $2,$16) as the BB2 return. Verified byte-identical (real_count 0).
 * a0 is unused; local@sp+0 is func_00249E48's out-param; *a3 is the 0/1 status. */
int inflate_start(int a0, int a1, int a2, int *a3) {
    int local, result;
    *a3 = 0;
    result = func_00249E48(a2 >> 11, a1, 1, &local) << 11;
    if (local != 0) { debug_assertMessage(D_00550E88, local); *a3 = 1; }
    return result;
}

/* MATCHED (fan-1 convergence). a2 is a CdvdReq*; 0x138=fileSize (int), 0x24=read
 * position. n = min((unsigned)(fileSize - pos), a1) bytes to transfer, read into
 * buffer a0 via iosCdvdManager(handle, buf, n).
 *
 * The whole-function coloring is driven by three coupled decisions that ROM makes
 * together and every "obvious" spelling breaks:
 *  1. The clamped count crosses the call (return value), so it lives in s0. It is
 *     DImode (`long long`): ROM stores it with a plain `daddu s0,v0` (zero-extended
 *     diff, NOT sign-canonical) and re-sign-extends only at the `int` call arg
 *     (`dsll32/dsra32 a2`). An `int`/`unsigned int` n instead sign-extends at STORE
 *     and passes the arg plainly (mirror-image, wrong bytes).
 *  2. Returning `long long` (not `(int)n`) keeps n a single DImode pseudo in s0 with
 *     a single tail. Any `(int)n` truncation splits n's live range into a transient
 *     DImode min (caller-saved) + a persistent SImode home, giving a two-tail diamond.
 *  3. Computing the compare flag (`lt = d < a1`) BEFORE the `n = d` copy forces the
 *     slt to reference the diff in its own caller-saved reg (v0), so gcc emits the
 *     real `daddu s0,v0` copy and reuses v0 for the slt — matching ROM. Folding the
 *     copy (n = d; if (d >= a1) ...) lets cse target the dsrl32 straight at s0 and
 *     read s0 in the slt (fused, one insn short, swapped load order).
 * (move->daddu and dsll/dsll32 are the always-on ROM-encoding rewrites.) */
extern void iosCdvdManager(int *a0, void *buf, int n);

long long close_inflate_handler(void *a0, int a1, int *a2, int a3) {
    long long d = (unsigned int)(a2[0x4E] - a2[9]);
    int lt = d < a1;
    long long n = d;
    if (!lt) n = a1;
    if (n) iosCdvdManager(a2, a0, (int)n);
    return n;
}

typedef struct { char f0; char pad[0x12B]; } InfEntry;
extern InfEntry D_0069F800[];

void inflate(void) {
    int i;
    for (i = 6; i >= 0; i--) {
        D_0069F800[i].f0 = 0;
    }
    D_0062BF84 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", open_inflate_handler);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", fill_inbuf);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", huft_free);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00134550);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001347B0);

extern void new_segment(void *a0);

void func_001350C8(void *a0)
{
    int *w = (int *)((char *) a0 + 0x18000);
    w[0x78 / 4] = -1;
    w[0x48 / 4] = 0;
    *(long long *)((char *) w + 0x68) = 0;
    *(long long *)((char *) w + 0x70) = 0;
    w[0x50 / 4] = 0;
    w[0x4C / 4] = 0;
    w[0x54 / 4] = 0;
    w[0x58 / 4] = 0;
    w[0x7C / 4] = 0;
    w[0x84 / 4] = 0;
    w[0x80 / 4] = 0;
    w[0x88 / 4] = 0;
    new_segment((char *) a0 + 0x18098);
}

extern void iosMallocCheckLeak2(void *p);
extern void strdup_mblock(void *p);
extern void iosMallocClearPartition(int a0);
extern int D_0062A33C;

/* MATCHED. Frees two NULL-terminated mblock lists (heads at +0x18058 / +0x18054
 * of a0's 0x18000 sub-object), zeroes both heads, then re-inits. Levers:
 *  - a0 stays in s1 and the +0x18000 offset is rematerialized per use (do NOT
 *    cache w=a0+0x18000 in a callee-saved reg, or the frame grows a reg).
 *  - free-loop idiom copied from the matched sibling ios_init_plus: capture
 *    node=p and do the next-load BEFORE the free call, so the loop head is the
 *    arg-move and the assembler fills the jal delay with `lw next` (not the move).
 *  - void return + trailing statement call => the final iosMallocClearPartition
 *    is a void-tail `j` (an `int return f()` would emit jal+jr instead). */
void func_00135118(void *a0)
{
    char *p;
    if (*(int *)((char *)a0 + 0x18054) != 0) {
        p = *(char **)((char *)a0 + 0x18058);
        if (p != 0) {
            p -= 8;
            for (;;) {
                char *node = p;
                p = *(char **)(p + 4);
                iosMallocCheckLeak2(node);
                if (p == 0) break;
                p -= 8;
            }
        }
        p = *(char **)((char *)a0 + 0x18054);
        if (p != 0) {
            p -= 8;
            for (;;) {
                char *node = p;
                p = *(char **)(p + 4);
                iosMallocCheckLeak2(node);
                if (p == 0) break;
                p -= 8;
            }
        }
        *(int *)((char *)a0 + 0x18054) = 0;
        *(int *)((char *)a0 + 0x18058) = 0;
    }
    strdup_mblock((char *)a0 + 0x18098);
    iosMallocCheckLeak2(a0);
    iosMallocClearPartition(D_0062A33C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001351E0);

extern int iosFree(int a0, int a1, const char *fmt, int line);
extern void func_001350C8(void *p);
extern void debug_assertMessage();
extern int D_0062A33C;
extern int D_0062A348;

extern char D_00550EA0[];

extern char D_00550EF0[];

extern int D_0062A328;

int func_001356A8(int a0, int a1)
{
    int g = D_0062A328;
    int *s1;
    D_0062A33C = g;
    D_0062A348 = 0;
    s1 = (int *) iosFree(g, 0x180A8, D_00550EA0, 0x2E3);
    func_001350C8(s1);
    s1[0] = a1;
    if (a0 == 0)
    {
        debug_assertMessage(D_00550EF0);
    }
    else
    {
        s1[0x4 / 4] = a0;
    }
    return (int) s1;
}

/* NEAR-MISS (fan-1). DATA MODEL + PURPOSE fully recovered; residual is a
 * single whole-function coloring tie plus arg-schedule. This is the exact
 * recovered dev C -- it builds to ~36 diff sites, dominated by one a0<->w
 * register-color flip:
 *
 *   typedef int (*InfFp)(void *, unsigned int, int);
 *   int func_00135738(void *a0) {
 *       int *w = (int *)((char *)a0 + 0x18000);
 *       int count;
 *       w[0x4C/4] = 0;
 *       for (;;) {
 *           int ret;
 *           count = w[0x4C/4];
 *           ret = ((InfFp)((int*)a0)[1])((char*)a0 + count + 0x10008,
 *                     (unsigned)(0x8000 - count), ((int*)a0)[0]);
 *           if (ret == -1 || ret == 0) break;      // beql (ret in {-1,0})
 *           count = w[0x4C/4] + ret;               // RE-READ w[0x4C], not cache
 *           w[0x4C/4] = count;
 *           if ((unsigned)count > 0x7FFF) break;   // sltu 0x7FFF < count
 *       }
 *       if (w[0x4C/4] == 0) return -1;
 *       w[0x50/4] = 1;
 *       return *(unsigned char *)((char*)a0 + 0x10010);
 *   }
 *
 * CORRECT so far: frame 0x60 (re-read count so it does NOT cross the jalr);
 * constants 0x10008/0x8000/0x7FFF hoisted to s2/s4/s3; two-exit loop.
 * RESIDUAL (verified via -dg): ROM colors a0->s0, w->s1; ee-gcc colors w->s0,
 * a0->s1 because allocno_compare ranks w (refs~8/live~21 => ~1.14) above a0
 * (refs~10/live~33 => ~0.91). Need a0's priority > w's: either raise a0 refs
 * or shorten w's live range WITHOUT the goto-CFG rewrite (that un-hoists the
 * constants and shrinks the frame). Also pending: arg-eval order (len zero-ext
 * placement around the jalr) and the final lbu reusing the 0x10008 base (+8)
 * instead of 0x10000+0x10. NOT a floor. */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00135738);

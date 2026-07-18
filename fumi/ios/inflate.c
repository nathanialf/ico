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

/* NEAR-MISS (rc5, W3 convergence). LOGIC + STRUCTURE recovered; residual is a
 * register/schedule coupling on the result shift. Dev shape:
 *   extern int func_00249E48(int a0, int a1, int a2, void *a3);
 *   int inflate_start(int a0, int a1, int a2, int *a3) {   // a0 unused (ROM overwrites $4)
 *       int local, ret;
 *       *a3 = 0;
 *       ret = func_00249E48(a2 >> 11, a1, 1, &local);      // out-param `local`
 *       if (local != 0) { debug_assertMessage(D_00550E88); *a3 = 1; }
 *       return ret << 11;
 *   }
 * Matched: frame, `sra a0,a2,11` arg0, func_00249E48(a2>>11, a1, 1, &local) with
 * *a3=0 in the jal delay, the local!=0 branch, assert + *a3=1, return ret<<11.
 * Residual (rc5): ROM reads `local` into a1 ($5, dead after the call), keeps ret in
 * v0, and computes `sll s0,v0,11` (result=ret<<11) IN the beq delay slot (result in
 * s0 survives the assert, ret dies there); return = `daddu v0,s0`. gcc instead
 * copies ret->s0 EARLY (`daddu s0,v0`), reads local into v0, and duplicates the
 * `sll` (once in the beq delay, once at the return) — because it freed v0 for local
 * by shifting early. Both `return ret<<11` and `int result=ret<<11` forms give the
 * same rc5. NEXT LEVER: make gcc read `local` into a1 (not v0) so ret stays in v0
 * and the single sll lands in the beq delay (bias local's alloc off v0, or keep ret
 * live in v0 until the delay). NOT a floor. */
extern int func_00249E48(int a0, int a1, int a2, void *a3);
extern char D_00550E88[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_start);

/* NEAR-MISS (rc11, W3 convergence). LOGIC + STRUCTURE fully recovered; residual is
 * a §5.11 low-32 sign/zero-extend routing + a2 keep-vs-copy (auto-memory flags this
 * class as permuter-domain, which convergence forbids). Dev shape (zlib flush):
 *   extern void iosCdvdManager(int *a0, void *buf, int n);
 *   int close_inflate_handler(void *a0, int a1, int *a2, int a3) {
 *       unsigned int n = a2[0x4E] - a2[9];      // f_138 - f_24, UNSIGNED (zero-ext)
 *       if ((long long)n >= a1) n = a1;         // min via signed 64-bit slt + movz
 *       if (n != 0) iosCdvdManager(a2, a0, n);
 *       return n;
 *   }
 * Matched: frame (s0/ra save), lw f_138(v0)+f_24(v1), subu, zero-extend
 * dsll32/dsrl32, slt(diff,a1) SIGNED + movz s0,a1 (min), beqz skip, 3-arg call
 * (a2, a0, n) with a3=a0 saved in the beqz delay + a1=a0 in the jal delay, return
 * s0. TWO residual diffs, both §5.11 low-32 canon:
 *  (1) arg2: ROM sign-extends s0 -> arg (`dsll32 a2,s0; dsra32`) because ROM's s0
 *      is the ZERO-extended diff (`daddu s0, v0_zeroext`), so passing it to the
 *      `int` 3rd param re-sign-extends. gcc here keeps s0 = the RAW subu (already
 *      sign-extended) and zero-extends into a scratch only for the slt, so the
 *      arg pass is a bare `daddu a2,s0` (no re-extend). Need s0 to BE the
 *      zero-extended value.
 *  (2) a2: ROM keeps the param a2 live (loads f_138/f_24 into v0/v1, uses a2 for
 *      call arg0); gcc reuses a2 for the diff and pre-copies `daddu a3,a2` to
 *      preserve it -> one extra move + cascaded v0/a2 coloring.
 * ~6 type/shape variants (int vs unsigned n, long long param, if vs ternary min,
 * explicit (long long) arg cast) all keep s0=raw (no re-extend) + the a2 copy.
 * NEXT LEVER: the s511_permuter recipe (route the low-32 through an unsigned-int
 * carrier so gcc materializes s0 as the zero-extended value) done in clean C. NOT
 * a floor. */
extern void iosCdvdManager(int *a0, void *buf, int n);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", close_inflate_handler);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00135118);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001351E0);

extern int iosFree(int a0, int a1, const char *fmt, int line);
extern void func_001350C8(void *p);
extern void debug_assertMessage();
extern int D_0062A33C;
extern int D_0062A348;

extern char D_00550EA0[];

extern char D_00550EF0[];

extern char D_0062A328[];

/* parked: needs real matching. See tough_nuts/func_001356A8/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001356A8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00135738);

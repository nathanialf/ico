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

/* NEAR-MISS (rc11, W3+W(fan-3) convergence). LOGIC + STRUCTURE fully recovered.
 * Dev shape (zlib inflate flush):
 *   extern void iosCdvdManager(int *a0, void *buf, int n);
 *   int close_inflate_handler(void *a0, int a1, int *a2, int a3) {
 *       unsigned int n = a2[0x4E] - a2[9];   // f_138 - f_24, uInt
 *       if ((long long)n >= a1) n = a1;      // min via 64-bit signed slt + movz
 *       if (n != 0) iosCdvdManager(a2, a0, n);
 *       return n;
 *   }
 * SHARPENED (fan-3): the entire rc11 is ONE coupled register-allocation tie with
 * two mutually-exclusive gcc dispositions, neither of which is ROM's:
 *  - `unsigned int n` (rc11): n born directly in s0 (movz s0 EARLY, correct min
 *    structure), BUT gcc pre-stashes the base param a2 into the DEAD arg reg a3
 *    (`daddu a3,a2` at entry) and reuses a2 as the first-load scratch -> extra
 *    move; and s0 = the RAW subu (sign-extended) so the `int` call-arg pass is a
 *    bare `daddu a2,s0` with NO re-extend. ROM keeps a2 as base throughout (loads
 *    into v0/v1), so s0 = the ZERO-extended diff (`daddu s0,v0` after dsll32/dsrl32)
 *    and the arg re-sign-extends (`dsll32 a2,s0; dsra32`).
 *  - `long long n` (rc15): KEEPS a2 as base (loads v0/v1, zero-extends) — fixes the
 *    a2-stash — BUT now gcc does the min in caller-saved v0 (movz v0) and copies to
 *    s0 LATE as a sign-extended value, and swaps the sd/lw order.
 * So a2-keep wants the 64-bit (long long) value-flow; s0-early wants the 32-bit
 * (unsigned int) flow; they conflict. Tried: unsigned/ull/ll n, a1 as long long,
 * &0xFFFFFFFFLL mask, two-var (n,m) split, explicit int load temps — all land on
 * one of the two dispositions above (rc11/15/22/23). To LAND: bias gcc to keep the
 * base allocno in a2 (not the dead a3) via find_reg copy-preference while the diff
 * is born in v0 and zero-ext-copied to s0 — needs the global.c/local-alloc source
 * lever that stops gcc grabbing the dead $7 as an early stash. NOT a floor.
 * SHARPENED (this session, minimal-TU + -dg): the coupling is EXACT and tight —
 * `movz` min  <=>  `subu` lands DIRECTLY in s0 ($16)  <=>  a2 stashed to $7. Any
 * form with movz (unsigned int n, intermediate `d` temp, int hi/lo temps, signed n,
 * unsigned-compare) ALL give STASH; `unsigned long long n` is the ONLY thing that
 * keeps a2 in $6 AND computes the diff in caller-saved $2 with the zero-ext IN $2
 * (ROM's exact first half) — but it forces a BRANCH min (not movz) and a two-tail
 * return. greg order: n(r88,crosses call)->s0 FIRST, then a2(r86,ptr) gets $7 not
 * $6 even though $6 is free — find_reg rejects $6 (load-scratch conflict) and $4
 * (a0 conflict) and takes $7. ROOT: the FIRST load coalesces into $6 (freeing it
 * needs a2 out), so a2->$7; ROM instead loads into $2/$3 keeping a2 in $6, which
 * then forces a0's arg1-shuffle through $7 (ROM's `daddu $7,$4`... `daddu $5,$7`).
 * NEXT LEVER: stop the first load from coalescing into $6 (bias load->$2), OR make
 * a0's shuffle claim $7 BEFORE a2 is allocated. Read global.c find_reg $6-rejection
 * (why $6 conflicts) via -dg on the u.l.l. vs unsigned-int variants side by side. */
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

#include "common.h"

struct E24_pe { char pad[0x14]; int *f14; };

/* NEAR-MISS (rc10). STRUCTURE RECOVERED. Dev shape (below): e = base +
 * idx*0x50; e->0x40 = -1; MatrixDrive_TurnObjectMatrix(e+0x10, a2);
 * MatrixDrive_TurnObjectMatrix(e+0x20, D_00271BD0);
 * GetInverseQuaternion(e+0x30, D_002724B0); e->0x0 = 0.
 * KEY RECOVERY: &D_002724B0 must be a LOCAL loaded EARLY (`char *q = ...`)
 * so gcc holds it in callee-saved s1 across the 3 calls (frame 0x30, sd/ld
 * $17) exactly like ROM -- referencing it only at the GetInverseQuaternion
 * call site loads it late (frame 0x20, no $17). MatrixDrive_TurnObjectMatrix
 * takes 2 args here (ROM sets a1=a2 / a1=&D_00271BD0 before the calls);
 * execParticleEffect's 1-arg call matches only coincidentally.
 * RESIDUAL (rc10) = coupled coloring/schedule ties: (a) the mult dest
 * idx*0x50 -- ROM a3, ours v1; ROM's -1 const is materialized EARLY (before
 * the `addu s0,mult,base`) so it holds v1 and forces the mult to a3, while
 * gcc schedules the -1 (addiu) AFTER the addu so the mult and -1 reuse v1
 * sequentially. (b) the first jal delay -- ROM fills it with the a0-setup
 * (addiu a0,s0,0x10) and does the -1 store before the call; gcc fills it
 * with the -1 store. (c) the callee-saved sd $16/$17 emission order. Tried
 * early neg1 local (sunk), swap_addu e-form -- neither moves the -1 ahead
 * of the addu. Sched1/reorg tie; NOT a floor.
 *   char *q = D_002724B0;
 *   char *e = base + idx * 0x50;
 *   *(int *)(e + 0x40) = -1;
 *   MatrixDrive_TurnObjectMatrix(e + 0x10, a2);
 *   MatrixDrive_TurnObjectMatrix(e + 0x20, D_00271BD0);
 *   GetInverseQuaternion(e + 0x30, q);
 *   *(int *)(e + 0x0) = 0;                                                */
INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", setParticleEffectGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", setParticleEffect);

extern void MatrixDrive_TurnObjectMatrix(int a0);
extern int GetInverseQuaternion(int a0, int a1);

void execParticleEffect(int a0, int a1, int a2)
{
    MatrixDrive_TurnObjectMatrix(a0);
    GetInverseQuaternion(a0 + 0x10, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", dispParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectUpperLimit);

extern char D_007030C0[];
extern void debug_assertMessage(char *fmt, ...);
extern char D_00612830[];

struct PE_elem { int f0; char pad[0x10]; int f14; };

extern struct PE_elem D_007030C0a[] __asm__("D_007030C0");

void ExecParticleEffects(int a0, int a1, int a2) {
    if (a0 >= 0) {
        if (D_007030C0a[a0].f0 == 0) {
            debug_assertMessage(D_00612830);
        } else {
            execParticleEffect(D_007030C0a[a0].f14, a1, a2);
        }
    }
}
extern void SetParticleEffect(int *p);

void ResetParticleEffectPackages(int a0, float f)
{
    struct E24_pe *new_var;
    int *p;
    if (a0 < 0) return;
    new_var = (struct E24_pe *)D_007030C0;
    new_var = (struct E24_pe *)((char *)new_var - (-(a0 * 0x18)));
    p = new_var->f14;
    p[0x38 / 4] = 1;
    *(float *)((char *)p + 0x3C) = f;
    SetParticleEffect(p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectPackage);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", DispParticleEffects);

typedef struct { long long q[20]; } PE160;
extern PE160 D_004C2030;
extern char D_00612870[];
extern unsigned char D_00703CC0[];
extern void func_002604B8(void *dst, int *a1, int a2);

void InitParticleEffects(int a0, int *a1, int a2) {
    *(PE160 *)&D_00703CC0[a0 * 0xA0] = D_004C2030;
    if (*(int *)&D_004C2030 != *a1) {
        debug_assertMessage(D_00612870, *a1);
    }
    func_002604B8(&D_00703CC0[a0 * 0xA0], a1, a2);
}


extern struct E24_pe D_004C2010;

void DeleteParticleEffect(void) {
    struct E24_pe *p = (struct E24_pe *)D_007030C0;
    struct E24_pe *end = (struct E24_pe *)(D_007030C0 + 0xC00);
    do {
        *p = D_004C2010;
        p++;
    } while ((int)p < (int)end);
}

extern void SetParticleEffectGeometry(int);

void SetParticleEffectActiveSensing(void)
{
    char *p = D_007030C0;
    char *end = p + 0xC00;
    do {
        if (*(int *)p != 0) {
            SetParticleEffectGeometry(*(int *)(p + 0x14));
        }
        p += 0x18;
    } while ((int)p < (int)end);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", GetParticleEffectPackage);

/* NEAR-MISS (rc5). STRUCTURE FULLY RE-RECOVERED (supersedes the old rc8 note,
 * which had the WRONG call shape). Correct dev shape:
 *
 *   struct PEelem24 { int f0, f4, f8, fC, f10, f14; };   // stride 0x18
 *   extern struct PEelem24 D_007030C0e[] __asm__("D_007030C0");
 *   int DeleteParticleEffectsByPackage(int a0, int a1, int a2) {
 *       int idx = SetParticleEffectUpperLimit(a0);       // 1-ARG call
 *       if (idx != -1) {
 *           D_007030C0e[idx].f8  = 1;                     // store order: f8,fC,f10
 *           D_007030C0e[idx].fC  = a1;
 *           D_007030C0e[idx].f10 = a2;
 *       }
 *       return idx;
 *   }
 *
 * This matches the ENTIRE prologue, the s0/s1 coloring (a1->s0, a2->s1), the
 * jal delay-slot fill (daddu s0,a1), the -1 guard/beq CFG, mult idx*0x18, the
 * const-1 materialization in a1, the 0x8 const store, and the return -- rc8->rc5.
 *
 * KEY RECOVERIES vs the old note:
 *  - The call is 1-ARG: SetParticleEffectUpperLimit(a0). ROM never rewrites $5/$6,
 *    so a1,a2 sit unused in the arg regs across the call; passing them (2-arg) is a
 *    phantom that gives a1 an extra ref and mis-fills the jal delay slot (a2 copy
 *    instead of a1). The prior "int idx=...(a0)" with 2/3-arg speculation was wrong.
 *  - Coloring a1->s0 is NOT ref-driven here: with the 1-arg call a1,a2 tie at
 *    refs=2, live_length=17 (verified in the .greg dump, allocnos 85=a1 / 86=a2);
 *    the tie breaks by allocno number (85<86) so a1->s0. This only holds when a1's
 *    store (fC) precedes a2's store (f10) in source order -- hence store order
 *    f8,fC,f10 (const first keeps the const-1 in a1 like ROM).
 *
 * RESIDUAL (rc5, block-converged) = ONE 6-insn store region. EVERY other block is
 * byte-exact (prologue, 1-arg jal + daddu s0,a1 delay, a3=v0, -1 guard/beq, mult
 * idx*0x18 with prod=$3, const-1 in $5, const-24=$3 in delay slot, return, epi).
 *   ROM:  addu a2($6),v0,v1  (root); daddu a0,a2; sw s1,0x10(a2); daddu v0,a0;
 *         sw a1_const1,0x8(a0); sw s0,0xC(v0)   ->  f8:$4  fC:$2  f10:$6(root)
 *   ours: addu a0($4),v0,v1  (root); sw const1,0x8(a0); daddu a2,a0; daddu v0,a0;
 *         sw s0,0xC(a2); sw s1,0x10(v0)          ->  f8:$4  fC:$6  f10:$2(root)
 * f8->$4 is IDENTICAL; only fC and f10 swap their $6/$2 homes (and which is root).
 *
 * MECHANISM (confirmed from gcc-2.95.3 local-alloc.c + .lreg/.greg dumps, 2026-07-24):
 *  - gcse emits 3 separate `base+prod` adds (reg98=f8, reg109=fC, reg119=f10), each
 *    feeding one store; a later pass collapses them to 1 add + 2 daddu copies.
 *  - REG_ALLOC_ORDER lists $4 before $6; find_free_reg returns the LOWEST free
 *    caller-saved reg. The FIRST-born base add (== first store in source order) wins
 *    the root and gets $4. reg109(fC, born 2nd) -> $6; reg119(f10, born 3rd) -> $2.
 *  - To make f10 the root in $6, its add must be BORN FIRST, i.e. f10 stored first.
 *    But storing f10(a2) before fC(a1) shortens a2's live_length below a1's, so the
 *    allocno-priority tie (refs=2 each) breaks on live_length instead of allocno
 *    number -> a2 wins s0 -> FLIPS the s0/s1 block (daddu s0,a2 / s1,a1). VERIFIED:
 *    store order f8,f10,fC gives the ROM base regs (f10:$6,fC:$2) but wrong s0/s1.
 *  The base-reg swap and the s0/s1 coloring are MUTUALLY EXCLUSIVE across every
 *  crutch-free source shape (swept ~25: all 6 store orders, pointer/char-ptr/int-arr bases,
 *  3-ptr-temps, decoupled f10-addr temps, a2 copy-routing, unsigned/short idx,
 *  volatile idx, do-while(0)/goto/comma/early-return CFGs -- all >= rc5, none swap
 *  fC/f10 without breaking s0/s1 or collapsing the 3 bases to one reg).
 *  - DIAGNOSTIC: -fno-schedule-insns (sched1 OFF) DOES yield root=$6, proving the
 *    $4 pick is a sched1 birth-order effect -- but sched1-off then mis-homes
 *    const-24/prod to $5 and const-1 to $3 (ROM has prod=$3,const1=$5, a sched1-ON
 *    trait). So ROM was built with sched1 ON; the $6 root is not reachable by any
 *    flag we own, only by a birth order our sched1 won't produce for this shape.
 *  - No $6 copy-preference anchor exists: a2 is the only $6-homed value and it is
 *    saved to s1 before block 1; routing a2 through a temp does not seed the base a
 *    hard_reg_copy_pref for $6 (find_free_reg copy-suggestion path).
 * NOT a re-spelling floor: this is the coupled birth-order/live-length tie above,
 * i.e. a sched1 build-order delta (cf. func_00159138_parked_rc3), not a gcc "floor."
 *
 * SESSION 2026-07-24 (fan-1) RE-VERIFICATION -- deepened the mechanism and CLOSED
 * the "give a2 a later use" escape the handoff proposed:
 *  - ROOT PROOF of the coupling: in the array-index store form, each `.fN=` store
 *    emits its OWN base+prod add (offset kept in the store), so base-add BIRTH ORDER
 *    == source STORE ORDER, unbreakably. The local-alloc tie between fCbase(reg109)
 *    and f10base(reg119) then breaks purely on their live_length, which is set by
 *    that same store order -- so base-reg homes and a1/a2 s0/s1 lifetimes move as ONE
 *    knob. (Taking `&...f10` into a temp to decouple FOLDS +0x10 into the symbol
 *    -> base becomes D_007030C0+16, offsets -8/-4/0, breaks the whole block. A single
 *    struct/flat pointer COLLAPSES the 3 bases to 1 add -- fewer insns than ROM.)
 *  - ALL 6 store orders re-swept via .greg + real_count: f8,fC,f10 = rc5 (s0/s1 OK,
 *    fC/f10 bases swapped); f8,f10,fC = rc7 (base HOMES right f8:$4/f10:$6/fC:$2 but
 *    ROOT is $4 not $6, store order within block wrong, AND s0/s1 flipped); the other
 *    4 put a base in $3/$5 or flip s0/s1. rc5 is the crutch-free minimum. CFG (goto,
 *    early-return, comma), guard polarity (>=0, >-1, -1!=idx), unsigned idx, and a
 *    value-temp (int t=a2) were all re-tried in rc5 order: byte-identical to rc5.
 *  - HANDOFF PREMISE DISPROVEN: a2 has NO genuine use after its f10 store. ROM is 27
 *    insns (call+guard+3 stores+return); a2($17) is dead after E5E0C except the ld
 *    restore; the function returns idx, never a2. So no "second store/return/compare"
 *    keeps a2 live -- the only lever that could let f10 be stored first WITHOUT
 *    flipping s0/s1 does not exist here. ROM equalizes a1/a2 live_length instead by
 *    scheduling a2-save BEFORE the call and a1-save IN the jal delay (a1 born 3 later
 *    to offset dying 3 later) -- a sched1 param-save ordering our ee-gcc 2.9-991111
 *    will not emit for any crutch-free shape (it always saves a1 first at RTL gen).
 *  Confirms: genuine sched1 knife-edge, mutually-exclusive at the alloc-time
 *  live_length level. rc0 unreachable crutch-free.
 * SESSION 2026-07-24-B (fan-1, worker) -- FRESH-DUMP re-proof; CLOSED the handoff's
 * "a2 = D_002724B0 global-load" lever and re-confirmed the coupling with new .greg:
 *  - a2 IS a genuine incoming arg ($6). The caller (pool.c:145) passes (int)D_002724B0
 *    AS the a2 argument; inside DeleteParticleEffectsByPackage a2 is the $6 param, NOT
 *    a load. So "load D_002724B0 early/late to reorder its save" does not apply here --
 *    that global is the CALLER's business. Lever CLOSED by inspection.
 *  - The param-save schedule is ALREADY byte-exact at rc5 (verified: daddu s1,a2 before
 *    the call, daddu s0,a1 in the jal delay; a1->s0, a2->s1). It is NOT the residual.
 *    The rc5 residual is ONLY the fC/f10 base-home swap in the 6-insn store block.
 *  - MECHANISM re-proven from three fresh .greg dumps (this session):
 *      store f8,fC,f10 (rc5): allocnos 85(a1) & 86(a2) BOTH live_length=17 -> TIE ->
 *        breaks on allocno number 85<86 -> a1->s0,a2->s1 (ROM-correct). Base homes
 *        f8:$4, fC:$6, f10:$2 (fC/f10 SWAPPED vs ROM).
 *      store f8,f10,fC: base homes become ROM-correct (f8:$4, fC:$2, f10:$6) BUT
 *        86(a2) live_length=16, 85(a1)=18 -> no tie -> shorter a2 sorts first -> a2->s0
 *        -> s0/s1 FLIPPED.
 *    ONE store-order knob sets BOTH the base-add birth order (local-alloc) AND the
 *    a1/a2 live_length (global-alloc tie). s0/s1-correct needs fC-before-f10; base-
 *    homes-correct needs f10-before-fC. Mutually exclusive -- confirmed across all 6
 *    store orders + the flip mechanism now has exact live_length numbers.
 *  - ROOT=$6 unreachable: ROM's first-born base lives in $6 (used by f10) with copies
 *    $6->$4->$2; OUR first-born base always takes the lowest-free $4 (f8's). Swept all
 *    6 store orders (first base -> $4 every time) and -fno-schedule-insns{,2} combos:
 *    sched1-off does give a root in $6 but it is f8's, with const1->$3/prod->$5 (ROM has
 *    prod=$3,const1=$5) -- NOT ROM. No store-order x schedule-flag combo yields ROM's
 *    f8:$4/fC:$2/f10:$6 + root=$6(f10). ROM's find_free_reg gave the first base $6 not
 *    the lowest-free $4 -- a REG_ALLOC_ORDER/find_free_reg build-level trait we can't
 *    reach crutch-free. CONFIRMED func_00159138_parked_rc3 param-save/live-length class.
 * Kept as INCLUDE_ASM (build-green); shipping the rc5 C would break the SHA gate,
 * and the dead `daddu $6` seed that forces the root is a CRUTCH (forbidden).      */
INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", DeleteParticleEffectsByPackage);

extern unsigned char D_00703CC0[];

void *DeleteParticleEffectsByID(int a0) {
    return &D_00703CC0[a0 * 0xA0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", GetParticleEffectData);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
} S_007030C0;  /* stride 0x18 */

/* end struct shapes */

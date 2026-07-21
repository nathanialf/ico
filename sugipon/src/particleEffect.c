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

/* NEAR-MISS (rc8). STRUCTURE FULLY RECOVERED via direct-index (below):
 * matches the call, idx-in-a3 (`daddu a3,v0`), the -1 guard, mult idx*0x18,
 * the DUAL-ADDR 3-base-copy store pattern (elem copied into 3 regs, one per
 * store), store EMISSION order 0x10,0x8,0xC, and the return of idx. Residual
 * = a coupled arg/base allocno-coloring tie:
 *   ROM:  a2->s1, a1->s0 (a1 saved in the call's DELAY slot); elem base first
 *         materialized in a2, const-1 in a1.
 *   ours: a1->s1, a2->s0; elem base in a0, const-1 in a2.
 * MECHANISM (-dg): the two callee-saved arg copies (a1=reg85 live=18,
 * a2=reg86 live=14) tie on refs=2; a2's SHORTER live-range wins higher
 * allocno priority so it is allocated first -> s0. ROM allocates a1 first
 * (->s0) despite a1 living longer, which requires a1 to have +1 ref or a2 to
 * live longer than a1 -- neither reachable from this func's semantics (a1/a2
 * are each stored exactly once; a2 at 0x10 emitted first => a2 dies first).
 * Passing a1 to the call (SetParticleEffectUpperLimit(a0,a1)) DOES flip the
 * tie to ROM's s0/s1, but ROM's call is (a0)-only (a1's save sits in the
 * call delay slot => a1 not referenced at the call), so that is a phantom
 * arg, not the dev shape; and it regresses the base/const coloring to rc9.
 * The base/const regs (a2/a1 in ROM vs a0/a2 ours) are downstream of the
 * same freed-arg-reg ordering. Two-allocno-tie class; needs the confirmed
 * ee-gcc2.9 order-of-allocation source, not a re-spelling. NOT a floor.
 * Best honest shape (rc8):
 *   struct PEelem24 { int f0,f4,f8,fC,f10,f14; };
 *   extern struct PEelem24 D_007030C0e[] __asm__("D_007030C0");
 *   int DeleteParticleEffectsByPackage(int a0, int a1, int a2) {
 *       int idx = SetParticleEffectUpperLimit(a0);
 *       if (idx != -1) { D_007030C0e[idx].f10 = a2;
 *           D_007030C0e[idx].f8 = 1; D_007030C0e[idx].fC = a1; }
 *       return idx;
 *   } */
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

#include "common.h"

/* weapon 0x7F0 view (local) */
typedef struct { int f_0, f_4, f_8, f_C; char _pad10[0x40]; int f_50; char _pad54[0x4C]; int f_A0; } WGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", torchOnOfWeaponSE);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void torchOffOfWeaponSE(char *a0, int a1, int a2, int a3) {
    char *sub = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    MatrixDrive_TurnObjectMatrix(a1, sub + 0x20);
    MatrixDrive_TurnObjectMatrix(a2, sub + 0x30);
    MatrixDrive_TurnObjectMatrix(a3, sub + 0x40);
}

extern void DemoMotionGeo(int a0, int a1, int a2, int a3);

void weaponHitReactionSE(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int x = *(int *)((char *)p + 0x7F0);
    DemoMotionGeo(a1, x + 0x20, x + 0x30, x + 0x40);
}

extern void func_001EF3B0(int a0);

void weaponFumbleSE(int a0) {
    func_001EF3B0(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", weaponStickSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", ReleaseWeaponWithFumbleTargetPos);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", ReleaseWeaponWithFumbleSequential);

extern void torchOnOfWeaponSE(void *a0);
extern void weaponStickSE(void *a0);

void calcDynamicPathGeometry(void *a0) {
    torchOnOfWeaponSE(a0);
    weaponStickSE(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", calcDynamicGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", getGeometry);

extern int DebugDisp1CollisionWithColor(char *a0, int a1);

void WeaponCurPos(void *a0, char *a1, int a2)
{
    WGeo *q = *(WGeo **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    q->f_8 = (int)a1;
    q->f_C = DebugDisp1CollisionWithColor(a1, a2);
    *(int *)(*(int *)((char *)a1 + 0x15C) + 0x620) = (int)a0;
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern void GetRootMatrixByDObj(void *buf, void *obj);

void *WeaponHitEffect(void *a0, float radius) {
    int buf[4];
    float thresh2 = radius * radius;
    void *best = 0;
    char *obj;

    obj = (char *)isysGObjSearchFromObjLayoutID(0xE);
    GetRootMatrixByDObj(buf, a0);
    while (obj != 0) {
        if (obj != (char *)a0) {
            char *sub = *(char **)(obj + 0x15C);
            char *p = *(char **)(sub + 0x7F0);
            if (*(int *)p != 0 && *(int *)(p + 8) == 0 && *(int *)(obj + 0x16C) != 0) {
                char *m = *(char **)(sub + 0xC) + 0x30;
                float d2;
                register float rd __asm__("$f0");
                __asm__ __volatile__(
                    "lqc2 $vf1, 0x0($29)\n"
                    "lqc2 $vf2, 0x0(%1)\n"
                    "vsub.xyzw $vf3, $vf1, $vf2\n"
                    "vmul.xyz $vf3, $vf3, $vf3\n"
                    "vaddy.x $vf3, $vf3, $vf3y\n"
                    "vaddz.x $vf3, $vf3, $vf3z\n"
                    "qmfc2.ni $2, $vf3\n"
                    "mtc1 $2, $f0\n"
                    : "=f"(rd) : "r"(m) : "$2", "memory");
                d2 = rd;
                if (d2 < thresh2) {
                    thresh2 = d2;
                    best = obj;
                }
            }
        }
        obj = (char *)isysGObjSearchFromObjKindID_begin(obj);
    }
    return best;
}

void ExecWeaponHitReaction(void *a0) {
    WGeo *p = *(WGeo **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    int x = p->f_8;
    if (x != 0) {
        *(int *)(*(char **)((char *)x + 0x15C) + 0x620) = 0;
    }
    p->f_8 = 0;
    p->f_C = -1;
    p->f_4 = 0;
}

int checkHit(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WGeo *q = *(WGeo **)((char *)p + 0x7F0);
    return q->f_0;
}

extern void func_001EF378(int a0);
extern void func_001EE9A8(int a0);
/* NEAR-MISS (rc3, fan-1 convergence). BYTE-IDENTICAL TWIN of InitWeaponGeo (same
 * offsets/callees/structure) -- see that function's note for the full mechanism.
 * Same residual: guard1's branch delay (ROM fills with the loop-counter init i=0;
 * ee-gcc folds the epilogue `ld ra` because guard1's i=0 sits across the
 * func_001EF378 call). do-while required. NOT a floor. rc3. */
INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", initializeQueenzSword);

extern void func_001EF378(int a0);
extern void func_001EE9A8(int a0);
/* NEAR-MISS (rc3, fan-1 convergence). LOGIC + STRUCTURE + VALUES fully recovered.
 * Dev shape (byte-exact except ONE branch-delay fill):
 *   void InitWeaponGeo(void *a0) {
 *       char *s1 = *(char**)(*(int*)((char*)a0+0x15C)+0x7F0);
 *       int i;
 *       if (*(int*)(s1+0x50) == 0) return;              // guard1: beqz f50
 *       func_001EF378((*(int**)(s1+0x54))[0]);          // call element[0]
 *       if (*(int*)(s1+0x50) <= 0) return;              // guard2: blez f50 (reloaded)
 *       i = 0;
 *       do { func_001EE9A8((*(int**)(s1+0x54))[i]); i++; } while (i < *(int*)(s1+0x50));
 *   }
 * do-while (not for) was required for the loop bnel + guard2's i=0 delay-fill.
 * RESIDUAL (rc3): guard1's branch delay. ROM fills BOTH guard delays with the
 * loop-counter init `daddu s0,zero` (i=0, rematerialized); guard2 matches, but for
 * guard1 ee-gcc FOLDS the epilogue `ld ra` into the delay and branches past the
 * shared epilogue's ld ra (+0x68 vs ROM's +0x64), because guard1's fall-through
 * i=0 sits ACROSS the func_001EF378 call (reorg won't thread-steal it past a call,
 * only simple-fills guard2 where i=0 is adjacent). `int i=0` hoisted to entry
 * REGRESSES to rc15 (i goes callee-saved live across both calls). Flat-return and
 * nested-if both give rc3. NEXT LEVER: make reorg rematerialize i=0 into guard1's
 * delay across the call instead of folding ld ra (cookbook epilogue-in-delay /
 * §8.2 unfold). NOT a floor. rc3. */
INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", InitWeaponGeo);

extern void func_001EEB10();

void WeaponGeo(char *a0) {
    char *sub = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    int i;
    for (i = 0; i < *(int *)(sub + 0x50); i++) {
        func_001EEB10(*(int *)(*(int *)(sub + 0x54) + i * 4));
    }
}

int dispInsectNet(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WGeo *q = *(WGeo **)((char *)p + 0x7F0);
    if (q->f_50) {
        return **(int **)((char *)q + 0x54);
    }
    return 0;
}

/* m2c scaffold from asm/aug6/nonmatchings/sugipon/src/weapon/WeaponDL.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern void GetInverseQuaternion(void *a0, void *a1);

void WeaponDL(void *a0, void *a1, void *a2) {
    char *base = *(char **)((char *)a0 + 0x15C);
    char *r = base + 0xA0;
    WGeo *sub = *(WGeo **)(base + 0x7F0);
    int one = 1;
    int x = sub->f_8;
    if (x != 0) {
        x = *(int *)((char *)x + 0x15C);
        *(int *)(x + 0x620) = 0;
    }
    sub->f_4 = one;
    sub->f_C = -1;
    sub->f_8 = 0;
    if (a2 != 0) {
        GetInverseQuaternion(base + 0x140, a2);
    }
    MatrixDrive_TurnObjectMatrix(base + 0x120, a1);
    *(int *)(r + 0x8C) = 0;
}


int PickupWeapon(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WGeo *q = *(WGeo **)((char *)p + 0x7F0);
    q->f_A0 = 0;
    return 1;
}

typedef struct { char _0[0xC]; int f_C; char _10[0x14]; } WeaponEntry;
extern WeaponEntry D_0060AF70[];

float CheckSwapableWeapon(void *a0) {
    WGeo *p = *(WGeo **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    int idx = p->f_0;
    return (float)D_0060AF70[idx].f_C;
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern void IsTorchLightOn(int a0, void *a1);

void ReleaseWeapon(void *a0) {
    char *g = isysGObjSearchFromObjLayoutID(0xE);
    if (g != 0) {
        do {
            char *s1 = *(char **)(*(char **)(g + 0x15C) + 0x7F0);
            if (*(int *)s1 == 1) {
                int i;
                for (i = 0; i < *(int *)(s1 + 0x50); i++) {
                    int *base = *(int **)(s1 + 0x54);
                    IsTorchLightOn(base[i], a0);
                }
            }
            g = isysGObjSearchFromObjKindID_begin(g);
        } while (g != 0);
    }
}

extern void *iosFree(int a0, int a1, char *a2, int a3);
extern void ReleaseWeaponWithFumbleTargetPos(void *a0, int a1, int a2);
extern int D_0062A310;
extern char D_00613220[];
extern char D_004C2330[];

typedef struct { long long w[22]; } WeaponBlob;

void *CheckWeaponKind(void *a0, int a1) {
    void *p = iosFree(D_0062A310, 0xB0, D_00613220, 0x2F3);
    char *m = *(char **)((char *)a0 + 0x15C);
    int i;

    *(void **)(m + 0x7F0) = p;
    *(WeaponBlob *)p = *(WeaponBlob *)D_004C2330;
    for (i = 0; i < *(int *)(*(char **)((char *)a0 + 0x15C) + 0x8); i++) {
        ReleaseWeaponWithFumbleTargetPos(a0, i, a1);
    }
    return p;
}

void LightTorchOnOfWeapon(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int v = p[0x1D];
    int *r = *(int **)((char *)q + 0x5C);
    r[0x5B] = v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", LightTorchOnOfWeaponWithNoSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", LightTorchOffOfWeapon);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_14;  /* 0x14 */
    unsigned char      f_18;  /* 0x18 */
    unsigned char      f_19;  /* 0x19 */
    unsigned char      f_1A;  /* 0x1A */
    unsigned char      f_1B;  /* 0x1B */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
} S_0060AF70;  /* stride 0x24 */

/* end struct shapes */

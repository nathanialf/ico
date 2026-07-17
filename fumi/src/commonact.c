#include "common.h"

/* commonact 0x164 actor-state view (local) */
typedef struct { char _0[0xBC]; unsigned int f_BC; char _padc0[0x144]; int f_204; char _pad208[0x48]; int f_250; } CBrain670;
typedef struct { char _0[0x30]; int f_30; unsigned int f_34; char _pad38[0x638]; CBrain670 *p_670; char _pad674[4]; void *p_678; } CommonActState;

extern void weaponFumbleSE(void *);
extern char *D_00629DE4;

void ACTSetPositionWithFitting(char *self) {
    char *s164 = *(char **)(self + 0x164);
    int *p2C = *(int **)(s164 + 0x2C);
    int a1;
    if (p2C != 0) {
        a1 = *p2C;
    } else {
        a1 = *(int *)(s164 + 0x5D0);
    }
    if (self == D_00629DE4) {
        char *p130 = *(char **)(s164 + 0x130);
        if (p130 != 0) {
            char *p15C = *(char **)(p130 + 0x15C);
            *(int *)(p15C + 0x5E4) = a1;
            weaponFumbleSE(p130);
        }
    }
}

extern void func_001EF4F0(int a0);
extern int isysGObjSearchFromObjLayoutID(int a0);
extern int iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern int D_00629C90, D_0062B058;
void ACTSetPositionNodeWithFitting(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    int v = *(int *)(p + 0x130);
    void *obj;
    if (v != 0) {
        func_001EF4F0(v);
        *(int *)(p + 0x130) = 0;
    }
    if (D_00629C90 == 0x53 || D_0062B058 != 0) {
        obj = (void *)isysGObjSearchFromObjLayoutID(0x35);
        if (obj != 0) {
            iosOmBeforeFuncStandard(obj, 0xD, a0);
        }
    }
}

extern int GetChainHangRange(void *a0, int *a1);
extern int InitMailAdditionalData(int a0);
extern void func_00191DB8(void *a0, float a1);
extern float func_00191E30(void *a0);
extern int func_00192160(int a0);
extern void func_00260568(void *a0, int a1, int a2);
extern float D_00628F24;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ChangeMailInLadder);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _ACTCorrectMsg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTGetOrientFromIntrK);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00154FE8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00155138);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00155288);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_001555B4);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00155738);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTRunIntrCorrect);

extern void IsWallLeverStatus(void *a, void *b, int c);
extern void func_001BDE70(void *a, void *b, int c);

void func_00155FF8(void *a0, void *a1)
{
    int n = *(int *)((char *)a1 + 0xC);
    if (n >= 0x16) {
        if (n >= 0x18) {
            if (n < 0x1A) {
                func_001BDE70(a1, a0, 0x16);
            }
        } else {
            IsWallLeverStatus(a1, a0, 0x16);
        }
    }
}

extern void *ContinueCorrectPosition(void *a0);
extern void CylinderCollision(void *a0, void *a1);

void WithMailFunc_WayBeginPosError(void *a0, void *a1) {
    void *ret = ContinueCorrectPosition(a0);
    *(float *)((char *)a1 + 4) = *(float *)((char *)ret + 4);
    CylinderCollision(a0, a1);
}

extern void SetRootMatrixWithTransOffsetByDObj(void *a0, int a1, void *a2, float a3);
extern void WallLeverGeo(void *a0, void *a1);
extern void _ACTWait(int a0);
extern void pushStartSE(void *a0, void *a1);
extern void dispPlane(void *a0, void *a1);
extern void func_00240038_p(void *a0, int a1, float f) __asm__("func_00240038");
extern int D_00271240[];
extern float D_00628F40;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_AttackFail);


extern void func_0018F2A0(void *a0);

void func_001561E8(void *a0, int a1) {
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        func_0018F2A0(a0);
}

extern char *D_00629DE8;
extern void debug_assertMessage();
extern void func_001561E8(void *a0, int a1);
extern void UpdatePointBlur(void *a0, void *a1, void *a2);
extern char D_0062C450[];
void WithMailFunc_AttackRejectInQueen(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    int v;
    debug_assertMessage(D_0062C450);
    if (a0 != (void *)D_00629DE8) {
        char *q = *(char **)((char *)a0 + 0x164);
        *(float *)(p + 0x1D0) -= (float)*(int *)(q + 0x1C0);
    }
    v = *(int *)((char *)a0 + 0xC);
    if (v == 4) {
        char *s;
        func_001561E8(a0, 5);
        s = *(char **)(*(char **)((char *)a0 + 0x164) + 0x670);
        UpdatePointBlur(a0, s + 0xE0, s + 0xF0);
    }
}

extern void WithMailFunc_AttackRejectInQueen(void *a0);

void GetCorrectOrientOfChain(void *a0)
{
    WithMailFunc_AttackRejectInQueen(a0);
    if (*(int *)((char *)a0 + 0xC) == 1) {
        void *p = *(void **)((char *)a0 + 0x164);
        func_001561E8(*(void **)((char *)p + 0x1A0), 6);
    }
}

/* CollisCheckInRope: NEAR-MATCH (real_count 8, 5 sites; body structurally
 * correct). Recovered dev C:
 *   extern void func_0017F450(float a0);
 *   extern void WithMailFunc_FallDead(volatile int a0);
 *   extern char D_00552BF0[];
 *   void CollisCheckInRope(volatile int a0) {
 *       char buf[0x10];
 *       void *s16 = *(void **)(a0 + 0x164);       // held across assert
 *       debug_assertMessage(D_00552BF0);
 *       *(void **)((char *)s16 + 0x18) = (void *)WithMailFunc_FallDead;  // bne delay
 *       if ((char *)a0 == D_00629DE4) func_0017F450(1000.0f);
 *       if ((char *)a0 == D_00629DE8) {
 *           func_00240038_p(buf, (int)((char *)*(void **)(a0+0x164)+0x1B0), -1.0f);
 *           dispPlane((void *)a0, buf);
 *       } else {
 *           dispPlane((void *)a0, (char *)*(void **)(a0+0x164)+0x1B0);
 *       }
 *       GetCorrectOrientOfChain((void *)a0);
 *       for (;;) {
 *           if (*(int *)(a0 + 0xC) != 4)
 *               *(char *)((char *)*(void **)(a0+0x164)+0x1CA) = 1;   // s16=1,s17=4 hoisted
 *           BoxBarSoundOn((void *)a0, 0xB4);
 *           _ACTWait(1);
 *       }
 *   }
 * RESIDUAL: first `a0 == D_00629DE4` compare — ROM loads the volatile a0-home
 * into the arg reg EARLY and D_00629DE4 late (bne a0,v1) with the WithMailFunc
 * store filling the bne delay; ee-gcc defers the volatile a0 read and loads DE4
 * (non-volatile) first (bne v1,a0), leaving the delay empty. Temp-hoisting the
 * a0 read and reversing the compare operands did not move it (real_count stays 8).
 * NEXT ANGLE: get the volatile a0 read scheduled before the DE4 global load in
 * the compare (volatile-vs-nonvolatile sched order), which cascades the rest. */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", CollisCheckInRope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_001563E8);

typedef struct {
    int f[3];   /* 0x00,0x04,0x08 */
    float fC;   /* 0x0C */
    float f10;  /* 0x10 */
    float f14;  /* 0x14 */
    int f18;    /* 0x18 */
    int f1C;    /* 0x1C */
    int f20;    /* 0x20 */
} RopeEntry;    /* 0x24 */
extern RopeEntry D_0029AF08[];
extern char D_00552B60[];
extern char D_00552C20[];
extern void func_0010E448(void *a0, int a1);
extern void func_0010E4E8(void *a0, int a1);
extern void func_0010E588(void *a0, int a1);
extern void GetHeightOfFieldPlaneDifference(void *, int, int, int, void *, float, float, float, float);
extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);

extern float pac_DispQW(void);
extern void ACTParaStatus_Exec(void *a0);

void actCommonRope(int self) {
    volatile int *ps = &self;
    int func_00156750(int idx, int a1) {
        float buf[4];
        int i;
        RopeEntry *e = &D_0029AF08[idx];
        func_00260568(buf, 0, 0x10);
        buf[3] = 1.0f;
        if ((unsigned int)idx >= 15) {
            func_001AAD00(D_00552B60, 0x9BE);
            func_00260380(D_00552B60, 0x9BE, D_00552C20);
        }
        for (i = 0; i < 3; i++) {
            int q = (e->f[i] << 15) / 180;
            if (q != 0) {
                switch (i) {
                case 0: func_0010E448(buf, (short)q); break;
                case 1: func_0010E4E8(buf, (short)q); break;
                case 2: func_0010E588(buf, (short)q); break;
                }
            }
        }
        GetHeightOfFieldPlaneDifference((void *)self, a1, e->f18, e->f20, buf,
                                        e->fC, e->f10, e->f14, 1.0f);
        return e->f1C;
    }
    float f;
    int val;
    int rem;
    void *sa;
    f = pac_DispQW();
    rem = (int)(f * 10.0f) % 15;
    sa = (void *)self;
    val = *(int *)(*(int *)(*(int *)(*ps + 0x164) + 0x670) + 0x214);
    *(int *)(*(int *)(*(int *)(*ps + 0x164) + 0x670) + 0x218) = val;
    ACTParaStatus_Exec(sa);
    func_00156750(rem, val);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", motCommonRopeTurnR);

extern void SetCageFixGeometry(void *a0);
extern void darkVolume(void *a0);
extern void actBoyHangG3M(void *a0, void *a1);
extern void func_00191FD0(void *a0, void *a1, void *a2);
extern int D_0062B320;
extern int D_0062A894;

void func_00156AB8(volatile int a0) {
    char buf10[0x10];
    char buf20[0x10];
    if (*(int *)(*(int *)(a0 + 0x164) + 0xB8) == 0x22) {
        SetCageFixGeometry((void *)a0);
        darkVolume(buf10);
        func_00191FD0(buf20, buf10, ContinueCorrectPosition((void *)a0));
        dispPlane((void *)a0, buf20);
    } else {
        actBoyHangG3M((void *)a0, ContinueCorrectPosition((void *)a0));
        dispPlane((void *)a0, (char *)*(void **)(a0 + 0x164) + 0x1B0);
        *(int *)(a0 + 0x50) = 0;
    }
    D_0062B320 = 0;
    D_0062A894 = 1;
    _ACTWait(0x12C);
    func_0015B4C8();
    _ACTWait(0);
}

extern void traceLine(int a0, int a1, int a2, void *a3, int a4);
extern void ActPara_GetDefTbl(int a0, int a1);
extern char D_00552C78[], D_00552C88[];
extern void actCommonOne(volatile int a0);
extern void func_0015B4C8(void);
extern int D_0062AF84;
extern void BoxBarSoundOn(void *a0, int a1);

void motCommonRopeTurnL(volatile int self) {
    char *s164 = *(char **)(self + 0x164);
    char *o0 = *(char **)(*(char **)(self + 0x164) + 0x670);
    *(int *)(s164 + 0x14) = (int)actCommonOne;
    *(int *)(o0 + 0x2A0) = 0;
    for (;;) {
        if (D_0062AF84 & 1) {
            traceLine(0xA, 0xAA, 0x0FFFFFFF, D_00552C78,
                      *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0xCC));
            if (D_0062AF84 & 1) {
                traceLine(0xA, 0xB4, 0x0FFFFFFF, D_00552C88,
                          *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C));
            }
        }
        {
            int st = *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C);
            if (st < 0) goto tbl22;
            if (st < 2) goto after;
            if (st != 2) goto tbl22;
            ActPara_GetDefTbl(self, 0x21);
            goto after;
        tbl22:
            ActPara_GetDefTbl(self, 0x22);
        after:;
        }
        if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0xCC) < 0) {
            BoxBarSoundOn((void *)self, 0xB4);
            *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C) = 0;
        }
        if (*(int *)(s164 + 0x48) >= 0x3D) {
            if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C) >= 3) {
                func_0015B4C8();
                _ACTWait(0);
            }
        }
        BoxBarSoundOn((void *)self, 0x68);
        _ACTWait(1);
    }
}

extern void BoxGeoRestore(int a0, int a1);
extern void RotObjectGeo(int a0);

void func_00156D18(void *a0) {
    CommonActState *s = *(CommonActState **)((char *)a0 + 0x164);
    int x = s->f_30;
    if (x == 0x31) goto h1;
    if (x == 0x33) goto h2;
    return;
h1:
    BoxGeoRestore(*(int *)((char *)s + 0x138), *(int *)((char *)s + 0x34));
    return;
h2:
    RotObjectGeo(*(int *)((char *)s + 0x5E8));
}

extern void BoxExtGeoRestore(void *a0);
extern void getRootMatrix(void *a0);

void actCommonRopeClimbEnd1(void *a0) {
    CommonActState *s = *(CommonActState **)((char *)a0 + 0x164);
    int state = s->f_30;
    if (state == 0x31) goto l1;
    if (state == 0x33) goto l2;
    return;
l1:
    BoxExtGeoRestore(*(void **)((char *)s + 0x138));
    return;
l2:
    getRootMatrix(*(void **)((char *)s + 0x5E8));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRopeCliff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", TestCageUpDown);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00157338);

extern void dispPlane(void *a0, void *a1);

extern void ACTParaStatus_Clear(int a0);
void actCommonRopeSpecial(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    void *x = p->p_678;
    dispPlane(a0, (char *)x + 0x350);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", lever_nego1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", SetDirectRootPositionXZ);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_001579EC);

extern void func_00104D20(void);
extern void func_00105068(void);
extern int func_00105078(void);
extern void func_001050A8(void *a0);
extern void func_0010F9D0(void);
extern void func_00118AA0(int a0);
extern void func_001D1DF0(int *a0, int *a1, int *a2, int *a3, int a4);
extern void gif_SpriteOffset(int a0);
extern void reg_dispBoxLine(void *a0, int a1, int a2, float a3);
extern int D_0027E730[];

typedef struct { float x, y, z, w; } __attribute__((aligned(8))) Vec4;
typedef struct { Vec4 a, b; } Vec4Pair;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00157E70);


extern void func_00104D20(void);
extern int func_00105078(void);
extern void func_00118AA0(int a0);
extern void gif_SpriteOffset(int a0);
extern void func_001050A8(void *a0);
extern void reg_dispBoxLine(void *a0, int a1, int a2, float f);
extern void func_0010F9D0(void);
extern void func_00105068(void);

void actCommonLever(void *a0, void *a1, float f) {
    func_00104D20();
    func_00118AA0(func_00105078());
    gif_SpriteOffset(0xB);
    func_001050A8(a0);
    reg_dispBoxLine(a1, 4, 4, f);
    func_0010F9D0();
    func_00105068();
}

extern void func_00104DC0(int a0);
extern void func_00105108(float a, float b, float c);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern int ClipWallBoxStop(void *a0);
extern void ChangeFieldCollisionDebugMode(void *a0);
extern void _TransposeRotationCurrentMatrix(void *a0, void *a1, void *a2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", EBRAIN_SEND_MES);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", DamageFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", DownFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDown);

/* func_00159138: NEAR-MATCH. CFG byte-correct; residual is ONE if-conversion
 * tie on the s16 select. Recovered dev C (all verified against ROM except the
 * flagged residual):
 *
 *   extern char boss_effect_check_parts[];
 *   extern int EnemyBrainStatus_Girl(void *a0, int *a1);
 *   extern int actEnemyFlagCheckDead(void *a0);
 *   extern void ReviveEnemyParticle(void *a0, int a1);
 *   extern int D_0062B07C;
 *   void func_00159138(volatile int a0) {
 *       int local4 = 0, s16, r2;
 *       int c1 = a0, c2 = a0;               // volatile a0 hoisted (getLandOffset vein)
 *       *(void **)(*(int *)(c1 + 0x164) + 0x18) = boss_effect_check_parts;
 *       *(int *)(*(int *)(c2 + 0x15C) + 0x5E8) = 0;
 *       r2 = EnemyBrainStatus_Girl((void *)a0, &local4);
 *       s16 = local4;
 *       if (r2 != 0) goto revive;
 *       if (actEnemyFlagCheckDead((void *)a0)) {
 *           s16 = (int)D_00629DE4;
 *           if (D_00629DE4 != 0) goto revive;   // BRANCH (not diamond: DE8 block follows)
 *       }
 *       s16 = (int)D_00629DE8;
 *       if (D_00629DE8 != 0) goto revive;        // <== gcc IF-CONVERTS -> movz (ROM: bnez+daddu)
 *       s16 = (int)D_00629DE4;
 *   revive:
 *       ReviveEnemyParticle((void *)a0, 0);
 *       { int flag = 0; char *p = D_00629DE8;
 *         void *e = p ? *(void **)((char *)p + 0x164) : 0;
 *         if ((p != 0 && *(int *)((char *)e + 0x30) == 0x6B &&
 *              *(int *)((char *)e + 0x124) == (int)a0) || D_0062B07C != 0) flag = 1;
 *         actCommonDown((void *)a0, s16, flag); }
 *   }
 *
 * SOLVED: flag block matches ROM's beql/bnel byte-for-byte via the single
 * `if ((A && ...) || B) flag = 1;` short-circuit form (the nested-if form gives
 * sltu). Prologue matches via the c1/c2 volatile-read hoist.
 *
 * RESIDUAL (blocker): the terminal `s16 = DE8; if (DE8) goto revive; s16 = DE4;`
 * is a clean 1-insn-arm diamond with condition == value1 (DE8). ee-gcc's
 * jump-pass if-conversion turns it into `movz s0,v0,s0`; ROM keeps a branch
 * (`lw $5,DE8; bnez $5,L; daddu $16,$5; lw $16,DE4`). Calibration (minimal-TU):
 * ee-gcc if-converts EVERY such diamond where the condition equals a merge value
 * (i4: A==A -> movn) and only BRANCHES when the condition is a memory load
 * INDEPENDENT of both merge values (i3: cond P[1], vals P[0]/P[2] -> branch).
 * ~30 source forms (goto/label/temp/pointer/comma/ternary/two-goto) all reproduce
 * the movz or flip to beql. The flag `||` lever does NOT transfer (s16 is a value
 * select, not a 0/1 flag). NEXT ANGLE: find the dev spelling that makes the DE8
 * presence-CONDITION independent of the DE8 VALUE without a second load (CSE folds
 * a re-read), or a compiler-behavior angle explaining why ROM's identical diamond
 * did not if-convert. Residual is exactly the 5 s16/movz insns. */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00159138);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDie);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_001597E8);

extern void debug_assertMessage();
extern char D_00552F88[];
extern char D_0062C478[];
extern char D_0062C480[];
void Cling(char *a0, void *a1, char *a2) {
    char *str = D_00552F88;
    void *p = *(void **)(a0 + 0x164);
    char *arg5;
    char *arg6;
    *(int *)((char *)p + 0xC0) |= 2;
    arg5 = (a2 == D_00629DE4) ? D_0062C478 : D_0062C480;
    arg6 = (a0 == D_00629DE4) ? D_0062C478 : D_0062C480;
    debug_assertMessage(str, arg5, arg6);
}

extern void debug_assertMessage();
extern char D_00552FA0[];
extern char D_0062C478[];
extern char D_0062C480[];
void actCommonCling(char *a0, void *a1, char *a2) {
    char *str = D_00552FA0;
    void *p = *(void **)(a0 + 0x164);
    char *arg5;
    char *arg6;
    *(int *)((char *)p + 0xC0) |= 8;
    arg5 = (a2 == D_00629DE4) ? D_0062C478 : D_0062C480;
    arg6 = (a0 == D_00629DE4) ? D_0062C478 : D_0062C480;
    debug_assertMessage(str, arg5, arg6);
}

extern void debug_assertMessage();
extern char D_00552FB8[];
extern char D_0062C478[];
extern char D_0062C480[];
void actCommonSlip(char *a0, void *a1, char *a2) {
    char *str = D_00552FB8;
    void *p = *(void **)(a0 + 0x164);
    char *arg5;
    char *arg6;
    *(int *)((char *)p + 0xC0) |= 0x10;
    arg5 = (a2 == D_00629DE4) ? D_0062C478 : D_0062C480;
    arg6 = (a0 == D_00629DE4) ? D_0062C478 : D_0062C480;
    debug_assertMessage(str, arg5, arg6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonStoneDead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonStone);

void BoxBarSoundOn(void *a0, int a1) {
    char *p = *(char **)((char *)a0 + 0x164);
    if ((a1 == 0xA6 || a1 == 0xAB) && *(int *)((char *)a0 + 0xC) == 1) {
        unsigned long long f470 = *(unsigned long long *)(p + 0x470);
        if ((unsigned int)(f470 >> 60) & 1) {
            if ((unsigned int)(*(unsigned long long *)(p + 0x480) >> 60) & 1) {
                a1 = 0xA7;
                goto done;
            }
        }
        if ((unsigned int)(f470 >> 58) & 1) {
            if ((unsigned int)(*(unsigned long long *)(p + 0x480) >> 58) & 1)
                a1 = 0xA8;
        }
    }
done:
    iosOmBeforeFuncStandard(a0, a1, a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", BoxBarSoundOff);

void *subCommonIdle(char *a0);
extern int HandCameraCorrect(void *a0, void *a1);
extern void func_00191DB8(void *a0, float a1);
extern float D_00628FB4;

int _boxbar_set_sound(char *a0) {
    float buf[3];
    int v;
    buf[0] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x170)) + 0x0);
    buf[1] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x170)) + 0x4);
    buf[2] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x170)) + 0x8);
    func_00191DB8(buf, D_00628FB4);
    return HandCameraCorrect(subCommonIdle(a0), buf) < 0
               ? -HandCameraCorrect(subCommonIdle(a0), buf) < 0x2D
               : HandCameraCorrect(subCommonIdle(a0), buf) < 0x2D;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBox);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015A990);

extern void traceLine(int a0, int a1, int a2, void *a3, int a4);
extern void _OrientXZGV(void *a0, void *a1, void *a2, float a3, float a4);
extern char D_005530A8[];
extern int D_0062AF84;

extern void func_0023FE98(void *a0, void *a1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015AF10);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBar);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015B250);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015B398);

extern int D_00629DF4;
extern void lt_fade_status(int a0);

void func_0015B4C8(void) {
    if (D_00629DF4 == 0) {
        D_00629DF4 = 1;
        lt_fade_status(0x3A);
    }
}

extern void setNodePursueParticleEffectWithUpperLimit(int a0, int a1, float a2);

void funcCommonJumpDircorrect(int a0, int a1) {
    setNodePursueParticleEffectWithUpperLimit(a0, a1, 30.0f);
}

extern char D_0055DA10_a[] __asm__("D_0055DA10");
extern int actCommonStoneDead(void *a0, float *a1, float a2);

typedef union { float f; int i; } FI;

int funcCommonFallDircorrect(void *a0, float *pos) {
    char *s164 = *(char **)((char *)a0 + 0x164);
    char *rec = D_0055DA10_a;
    ((FI *)(s164 + 0x100))->f = pos[0];
    ((FI *)(s164 + 0x104))->f = pos[1];
    ((FI *)(s164 + 0x108))->f = pos[2];
    rec = rec - (-(*(int *)(*(char **)((char *)a0 + 0x15C) + 0x490) * 0x190));
    return actCommonStoneDead(a0, pos, (float)*(int *)(rec + 0x138));
}


typedef struct { int _0, _4, _8, _C, _10; } ChainEntry;
extern ChainEntry D_00288FD0[];
typedef struct { int w[6]; } SlowrunRec;
extern SlowrunRec D_0028E680[];

/* correctJumpOrientByChain: MATCHED. Two structural keys cracked it from rc29:
 *  (1) direct-index D_00288FD0[idx]._N (NOT a cached ce pointer) makes ee-gcc
 *      recompute base+idx*20 per field, collapsing to 1 addu + 3 star-copies of
 *      ce and reusing the copy regs as load dests (lw v1,4(v1)) like ROM.
 *  (2) the e8 store is UNCONDITIONAL (in the beq delay slot in ROM = both paths),
 *      NOT nested inside the eC<e10 guard; the guard covers only the loop. This
 *      pairs the two mults (auto-mult1) and fixes the branch shape.
 *  (3) the loop must be a `while` (i=eC; while(i<e10){...i++}) not a `for`, so eC
 *      lands in a1 and gets saved to a2 early like ROM (the final coloring flip). */
void correctJumpOrientByChain(void *a0) {
    char *s164 = *(char **)((char *)a0 + 0x164);
    char *s15C = *(char **)((char *)a0 + 0x15C);
    int v = *(int *)(s15C + 0x490);
    int idx = *(int *)(s164 + 0x44);
    int e4 = D_00288FD0[idx]._4;
    int e8 = D_00288FD0[idx]._8;
    int eC = D_00288FD0[idx]._C;
    int e10 = D_00288FD0[idx]._10;
    int i;
    if (v != 0x440) {
        D_0028E680[e4].w[2] = v;
        D_0028E680[e8].w[2] = v;
        i = eC;
        while (i < e10) {
            D_0028E680[i].w[0] = v;
            i++;
        }
    }
}


void actCommonJump(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    CBrain670 *q = p->p_670;
    q->f_204--;
}

extern void func_0023FE98(void *a0, void *a1);
extern float MatrixDrive_GetTurnYAngleXZ(float a0);
extern int func_00260340(float a0);
extern int func_0025F4A0(int a0, double a1);

void actCommonFall(int self) {
    float buf[3];
    int sub = *(int *)(self + 0x15C);
    int r;

    buf[0] = *(float *)(sub + 0x1C0);
    buf[1] = *(float *)(sub + 0x1C4);
    buf[2] = *(float *)(sub + 0x1C8);
    func_0023FE98(buf, buf);
    r = func_00260340(MatrixDrive_GetTurnYAngleXZ(buf[0] * buf[0] + buf[2] * buf[2]));
    if (func_0025F4A0(r, 0.3) > 0) {
        buf[1] = 0.0f;
        func_0023FE98(buf, buf);
        dispPlane((void *)self, buf);
    }
}

extern char D_00552C60[];
extern void ACTParaStatus_Exec(void *a0);
extern void ResetEnemyEye(void *a0);
extern void isExistEnemyParticle(char *a0);
extern void actCommonPlay();

void debugDispFlyLimit(volatile int a0) {
    char *s0 = *(char **)(a0 + 0x164);
    debug_assertMessage(D_00552C60);
    ACTParaStatus_Exec((void *)a0);
    {
        void *self = (void *)a0;
        *(int *)(s0 + 0x14) = (int)actCommonPlay;
        CylinderCollision(self, s0 + 0x150);
    }
    isExistEnemyParticle((char *)a0);
    for (;;) {
        ResetEnemyEye((void *)a0);
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

void func_0015B740(volatile int a0) {
    CylinderCollision((void *)a0, *(char **)(a0 + 0x164) + 0x150);
    isExistEnemyParticle((char *)a0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xCF);
        _ACTWait(1);
    }
}


extern char D_00552BC0[];

void func_0015B790(volatile int a0) {
    debug_assertMessage(D_00552BC0);
    _ACTWait(0);
}


void debugDispSphere(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    if (*(int *)(s164 + 0xB8) == 0x17E && (*(int *)(s164 + 0x118) & 1)) {
        int q = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
        *(short *)(s164 + 0x11A) = q * 5;
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}


void func_0015B850(volatile int a0) {
    _ACTWait(0);
}


void getLandOffset(volatile int a0) {
    void *obj = *(void **)(a0 + 0x164);
    CylinderCollision((void *)a0, (char *)obj + 0x5A0);
    {
        int c1 = a0, c2 = a0, c3 = a0;
        int t = *(int *)((char *)obj + 0x60C);
        *(int *)(*(int *)(*(int *)(c1 + 0x164) + 0x670) + 0x250) = 0;
        *(int *)((char *)obj + 0x140) = t;
        *(int *)(*(int *)(*(int *)(c2 + 0x164) + 0x670) + 0x258) = 0;
        *(int *)(*(int *)(*(int *)(c3 + 0x164) + 0x670) + 0x25C) = 0;
    }
    for (;;) {
        int *pa = (int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670));
        int *pb = (int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670));
        if (*(int *)((char *)pb + 0x254) < *(int *)((char *)pa + 0x250)) {
            BoxBarSoundOn((void *)a0, 0x6B);
        }
        {
            int *p = (int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670));
            *(int *)((char *)p + 0x250) += 1;
        }
        _ACTWait(1);
    }
}

extern int GetDifferenceFromWallUpperPlane(void *a0);
extern void initializeQueenzSword(int a0);
void func_0015B938(volatile int a0) {
    char *s0 = *(char **)(a0 + 0x164);
    int flag = 0;
    dispPlane((void *)a0, s0 + 0x4C0);
    for (;;) {
        if (GetDifferenceFromWallUpperPlane((void *)a0) && flag == 0) {
            initializeQueenzSword(*(int *)(s0 + 0x130));
            flag = 1;
        }
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

extern void func_001EE9A8(int a0);
void func_0015B9B0(volatile int a0) {
    char *s0 = *(char **)(a0 + 0x164);
    int flag = 0;
    dispPlane((void *)a0, s0 + 0x4C0);
    for (;;) {
        if (GetDifferenceFromWallUpperPlane((void *)a0) && flag == 0) {
            func_001EE9A8(*(int *)(s0 + 0x604));
            flag = 1;
        }
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

void func_0015BA28(volatile int a0) {
    char *s0 = *(char **)(a0 + 0x164);
    int flag = 0;
    dispPlane((void *)a0, s0 + 0x4D0);
    for (;;) {
        if (GetDifferenceFromWallUpperPlane((void *)a0) && flag == 0) {
            func_001EE9A8(*(int *)(s0 + 0x608));
            flag = 1;
        }
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

void func_0015BAA0(volatile int a0) {
    _ACTWait(0x28);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

void func_0015BAD8(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    funcCommonJumpDircorrect(a0, (int)s->p_678 + 0x7C0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

extern char D_00552E80[];

void func_0015BB20(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    debug_assertMessage(D_00552E80);
    dispPlane((void *)a0, s + 0x4B0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BB70);

extern int ForMotionViewer_GetCurrentMotion(void *a0, int a1);

void func_0015BCA8(volatile int a0) {
    for (;;) {
        if (ForMotionViewer_GetCurrentMotion((void *)a0, 0x3000) == 0 &&
            ForMotionViewer_GetCurrentMotion((void *)a0, 0x400) == 0) {
            BoxBarSoundOn((void *)a0, 0xCF);
        }
        _ACTWait(1);
    }
}

void func_0015BD00(volatile int a0) {
    for (;;) {
        float v;
        BoxBarSoundOn((void *)a0, 0x136);
        v = *(float *)(*(char **)(a0 + 0x15C) + 0x5D8);
        if (250.0f < -v) {
            BoxBarSoundOn((void *)a0, 0x18);
        }
        _ACTWait(1);
    }
}

extern char D_00552EC8[];
extern void actBoyBelift(void *a0, void *a1, void *a2);
extern void func_00191FD0(void *a0, void *a1, void *a2);
extern void GetOrientOfCliffOfGObj(void *a0, void *a1, float f0, float f1);

void func_0015BD60(volatile int a0) {
    int local20 = 0;
    char buf[0x10];
    void *s17 = *(void **)(a0 + 0x164);
    debug_assertMessage(D_00552EC8);
    if (*(int *)(a0 + 0xC) == 1) {
        actBoyBelift((void *)a0, &local20, buf);
    } else {
        void *r1 = ContinueCorrectPosition(D_00629DE4);
        void *r2v = ContinueCorrectPosition((void *)a0);
        func_00191FD0((char *)s17 + 0x100, r1, r2v);
        dispPlane((void *)a0, (char *)s17 + 0x100);
    }
    for (;;) {
        if (local20 != 0) {
            GetOrientOfCliffOfGObj((void *)a0, buf, 10.0f, 90.0f);
        }
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

extern void actBoyBelift(void *a0, void *a1, void *a2);
extern void func_00191FD0(void *a0, void *a1, void *a2);

void func_0015BE38(volatile int a0) {
    int local20 = 0;
    int local10[3];
    char *s1 = *(char **)(a0 + 0x164);
    if (*(int *)(a0 + 0xC) == 1) {
        actBoyBelift((void *)a0, &local20, local10);
    } else {
        void *r1, *r2;
        s1 += 0x100;
        r1 = ContinueCorrectPosition(D_00629DE4);
        r2 = ContinueCorrectPosition((void *)a0);
        func_00191FD0(s1, r1, r2);
        dispPlane((void *)a0, s1);
    }
    for (;;) {
        _ACTWait(1);
    }
}

extern char D_00552EE0[];
extern void func_00149F60(void *a0);
extern void actBoyHangG3M(void *a0, void *a1);

void func_0015BEC8(volatile int a0) {
    char *base = *(char **)(a0 + 0x164);
    debug_assertMessage(D_00552EE0);
    dispPlane((void *)a0, *(char **)(a0 + 0x164) + 0x1B0);
    if (*(int *)(a0 + 0xC) == 4) {
        func_001561E8((void *)a0, 6);
        func_00149F60((void *)a0);
    }
    iosOmBeforeFuncStandard(D_00629DE4, 0x109, (void *)a0);
    if (*(int *)(base + 0xB8) == 0x107) {
        actBoyHangG3M((void *)a0, ContinueCorrectPosition((void *)a0));
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

extern void func_0017F450(float a0);
extern void brainInitGirlSet(void);
void func_0015BF88(volatile int a0) {
    if ((char *)a0 == D_00629DE4) {
        func_0017F450(1000.0f);
    }
    for (;;) {
        if ((char *)a0 == D_00629DE4 && D_00629DE8 != 0) {
            brainInitGirlSet();
            iosOmBeforeFuncStandard(D_00629DE8, 0x39, (void *)a0);
        }
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

extern char D_00552BD8[];
void func_0015C000(volatile int a0) {
    debug_assertMessage(D_00552BD8);
    dispPlane((void *)a0, *(char **)(a0 + 0x164) + 0x1B0);
    WithMailFunc_AttackRejectInQueen((void *)a0);
    if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x1DC) == 3) {
        _ACTWait(0x168);
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

extern char D_00552EA0[];

void func_0015C080(volatile int a0) {
    debug_assertMessage(D_00552EA0);
    _ACTWait(0);
}

extern char D_00552EB0[];

void getAvoidCollisionFlyLevel(volatile int a0) {
    debug_assertMessage(D_00552EB0);
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C0D8);

static __inline__ void func_0015C818_disp(int obj) {
    int buf[4];
    func_00240038_p(buf, (int)(*(char **)(obj + 0x164) + 0x4A0), -1.0f);
    dispPlane((void *)obj, buf);
}

void func_0015C1D0(volatile int a0) {
    char *base = *(char **)(a0 + 0x164);
    int s17val = *(int *)(base + 0x5EC);
    WithMailFunc_WayBeginPosError((void *)a0, base + 0x590);
    func_0015C818_disp(a0);
    for (;;) {
        if (s17val) {
            (void)a0;
            if (*(int *)(*(char **)(a0 + 0x15C) + 0x5F0)) {
                func_00155FF8((void *)a0, (void *)s17val);
            }
        }
        _ACTWait(1);
    }
}

void func_0015C268(volatile int a0) {
    char *s1 = *(char **)(a0 + 0x164);
    for (;;) {
        if ((0x3C - D_00271240[0] * 0xA) / D_00271240[1] / 2 <
            *(int *)(s1 + 0x48)) {
            BoxBarSoundOn((void *)a0, 0x9C);
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C300);

void func_0015C3F8(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}

/* func_0015C418: inline `probe` helper keeps the two buf-arg addresses off
 * callee-saved regs (frame 0x120, s0/s1/s2 + f20). The v0/v1 coloring of
 * `value` (buf+0x94) vs `hit` follows ROM because ChangeFieldCollisionDebugMode
 * is void: with no dead int-return pseudo occupying v0, the value load takes v0
 * and the global `hit` flag is pushed to v1 (matches ROM's lw v0 / bnez v0). */
extern void ActOrientTest(void *a0, void *a1, int a2);
static __inline__ int func_0015C418_probe(char *buf, char *obj) {
    ActOrientTest(buf, obj, 0x2C);
    ActOrientTest(buf + 0x10, obj, 0x33);
    *(float *)(buf + 0x14) -= 5.0f;
    ChangeFieldCollisionDebugMode(buf);
    return *(int *)(buf + 0x94) != 0;
}
void func_0015C418(volatile int a0) {
    char buf[0xC0];
    for (;;) {
        char *obj = (char *)a0;
        int hit;
        char *rec = D_0055DA10_a +
            *(int *)(*(char **)(obj + 0x15C) + 0x490) * 0x190;
        if (!(*(int *)(rec + 0x188) & 1)) goto no;
        if (func_0015C418_probe(buf, obj)) { hit = 1; goto test; }
      no:  hit = 0;
      test:
        if (hit) BoxBarSoundOn((void *)a0, 0x9B);
        _ACTWait(1);
    }
}

void func_0015C4D8(volatile int a0) {
    if (*(int *)(*(int *)(a0 + 0x164) + 0xB8) == 0x99) {
        int t0 = a0, t1 = a0, t2 = a0;
        *(int *)(*(int *)(t0 + 0x15C) + 0x120) = 0;
        *(int *)(*(int *)(t1 + 0x15C) + 0x124) = 0;
        *(int *)(*(int *)(t2 + 0x15C) + 0x128) = 0;
    }
    _ACTWait(0);
}

void emergencyCheck(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (1) {
        BoxBarSoundOn((void *)buf[0], 0xAE);
        _ACTWait(1);
    }
}

void func_0015C568(volatile int a0) {
    _ACTWait(0);
}

void flyCoreLoop(volatile int a0) {
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

extern void func_00149C20(void *a0, int a1, int a2, float f);

void func_0015C5B8(volatile int a0) {
    int buf[4];
    func_00240038_p(buf, (int)subCommonIdle((char *)a0), -1.0f);
    dispPlane((void *)a0, buf);
    for (;;) {
        func_00149C20((void *)a0, 3, 0, -1.0f);
        _ACTWait(1);
    }
}

void func_0015C620(volatile int a0) {
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}

extern void *ExecMotionOrient(void *a0, void *a1, void *a2);
extern void func_00104548(void *a0, void *a1);

void func_0015C650(volatile int a0) {
    int buf[4];
    char *base = *(char **)(a0 + 0x164);
    int prev = *(int *)(base + 0x3C);
    for (;;) {
        int cur = *(int *)(base + 0x3C);
        char *o;
        int r, ar;
        if (cur != 0xEB) {
            prev = cur;
        } else {
            *(void **)(base + 0x110) =
                ExecMotionOrient((void *)a0, (void *)prev, base + 0x610);
        }
        func_00104548(buf, (void *)a0);
        o = *(char **)(a0 + 0x164);
        r = HandCameraCorrect(*(char **)(o + 0x678) + 0x3B0, buf);
        ar = (r < 0) ? -r : r;
        if (ar < 0xF) {
            BoxBarSoundOn((void *)a0, 0xE2);
        }
        _ACTWait(1);
    }
}

extern void func_00104548(void *a0, void *a1);

void func_0015C708(volatile int a0) {
    int buf[4];
    char *p = *(char **)(a0 + 0x164) + 0x5B0;
    for (;;) {
        int r, ar;
        func_00104548(buf, (void *)a0);
        r = HandCameraCorrect(p, buf);
        ar = (r < 0) ? -r : r;
        if (ar < 0xF) {
            BoxBarSoundOn((void *)a0, 0xE1);
        }
        _ACTWait(1);
    }
}

void func_0015C778(volatile int a0) {
    _ACTWait(0);
}

void actCommonFly(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}

extern void boss_effect_process(int a0);

void func_0015C7B8(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    *(int *)(s164 + 0x14) = (int)boss_effect_process;
    _ACTWait(0);
}


extern char D_00552F58[];

void actCommonLadder(volatile int a0) {
    debug_assertMessage(D_00552F58);
    for (;;) {
        _ACTWait(1);
    }
}

void func_0015C818(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 1;
    for (;;) {
        func_0015C818_disp(a0);
        _ACTWait(1);
    }
}

void func_0015C870(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 0xFFFFFFFF;
    for (;;) {
        func_0015C818_disp(a0);
        _ACTWait(1);
    }
}

void func_0015C8D0(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 1;
    _ACTWait(0);
}

extern void _ACTWait(int a0);

void actCommonDodge(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 0xFFFFFFFF;
    _ACTWait(0);
}

void actCommonEdgeHang(volatile int a0) {
    char *s1 = *(char **)(a0 + 0x164);
    for (;;) {
        char *o = *(char **)(*(char **)(a0 + 0x164) + 0x670);
        *(int *)(s1 + 0x34) = 1;
        switch (*(int *)(o + 0x290)) {
        case 1:
            BoxBarSoundOn((void *)a0, 0x80);
        case 2:
            BoxBarSoundOn((void *)a0, 0x81);
            break;
        }
        _ACTWait(1);
    }
}

void func_0015C9B8(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    for (;;) {
        char *o = *(char **)(*(char **)(a0 + 0x164) + 0x670);
        s->f_34 = 0xFFFFFFFF;
        switch (*(int *)(o + 0x294)) {
        case 1:
            BoxBarSoundOn((void *)a0, 0x80);
        case 2:
            BoxBarSoundOn((void *)a0, 0x81);
            break;
        }
        _ACTWait(1);
    }
}

void func_0015CA48(volatile int a0) {
    char *s16 = *(char **)(a0 + 0x164);
    for (;;) {
        long long v = *(long long *)(s16 + 0x470);
        if (((int)(v >> 9) & 1) &&
            ((int)(*(long long *)(s16 + 0x480) >> 9) & 1))
            goto wait;
        if (((int)(v >> 10) & 1) &&
            ((int)(*(long long *)(s16 + 0x480) >> 10) & 1))
            goto wait;
        BoxBarSoundOn((void *)a0, 0xB4);
    wait:
        _ACTWait(1);
    }
}

void func_0015CAE0(volatile int a0) {
    char *p = *(char **)(a0 + 0x164) + 0x190;
    for (;;) {
        dispPlane((void *)a0, p);
        _ACTWait(1);
    }
}

extern char D_00552EF8[];

void func_0015CB20(volatile int a0) {
    debug_assertMessage(D_00552EF8);
    _ACTWait(0);
}

extern void debug_assertMessage(void *a0);
extern void _ACTWait(int a0);
extern char D_00552F18[];
extern char D_00552F38[];

void funcCommonBeginReady(volatile int a0) {
    debug_assertMessage(D_00552F18);
    _ACTWait(0);
}

void funcCommonEndReady(volatile int a0) {
    debug_assertMessage(D_00552F38);
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonEndExec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015CD08);

extern char D_0062C490[];

void func_0015CE60(volatile int a0) {
    char *state = *(char **)(a0 + 0x164);
    int v = *(int *)(state + 0x5EC);
    _ACTWait(6);
    CanWallLeverPull(v, 0);
    debug_assertMessage(D_0062C490);
    _ACTWait(0);
}

extern int CanWallLeverPull(int a0, int a1);
extern char D_0062C498[];
extern char D_0062C4A0[];

void funcCommonError(volatile int a0) {
    char *state = *(char **)(a0 + 0x164);
    int v = *(int *)(state + 0x5EC);
    _ACTWait(0x1E);
    CanWallLeverPull(v, -1);
    debug_assertMessage(D_0062C498);
    _ACTWait(0);
}

void SetMotionDirectionSmooze(volatile int a0) {
    char *state = *(char **)(a0 + 0x164);
    int v = *(int *)(state + 0x5EC);
    _ACTWait(0x1E);
    CanWallLeverPull(v, 1);
    debug_assertMessage(D_0062C4A0);
    _ACTWait(0);
}

void _ACTDebugPrint(int **a0, int a1, int a2) {
    int *p = a0[0x59];
    p[0x60] = a2;
}

extern int isBottomOfChain(int a0, int a1);
extern char D_00552B48[];
void ACTSendMailCorrect(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    int self;
    debug_assertMessage(D_00552B48);
    isBottomOfChain(*(int *)(s + 0x180), a0);
    self = a0;
    *(int *)(s + 0x184) = *(int *)(s + 0x180);
    *(int *)(*(int *)(self + 0x15C) + 0x410) = 0;
}


void _ACTCommonMailTest(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}


extern void *D_0062A4DC;

void func_0015CFF0(volatile int a0) {
    if (D_00629DE8 != 0) {
        iosOmBeforeFuncStandard((void *)D_00629DE8, 0x3F, D_0062A4DC);
    }
    for (;;) {
        _ACTWait(1);
    }
}


extern int D_0062A7E8;

void func_0015D028(int a0) {
    if (a0 == (int)D_00629DE8) {
        D_0062A7E8 = 1;
    }
}


void E3_LeverCheck(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    CBrain670 *q = p->p_670;
    q->f_250 = 0;
}

extern void *ExecMotionOrient(void *a0, void *a1, void *a2);

int actCommonBecarry(void *a0, void *a1) {
    char *s = *(char **)((char *)a0 + 0x164);
    void *r = ExecMotionOrient(a0, a1, s + 0x610);
    *(void **)(s + 0x110) = r;
    return *(int *)((char *)r + 0xC) != 0;
}

extern char *D_00629DE8;
extern char D_006A4620[];
extern void InitKeyInput(void *a0, void *a1);
extern int GetOrientOfWallOfGObj(void *a0, void *a1);
void *subCommonIdle(char *a0) {
    char *p;
    if (a0 != D_00629DE4 && a0 != D_00629DE8 && *(int *)(a0 + 0xC) != 4) {
        InitKeyInput(D_006A4620, a0);
        return D_006A4620;
    }
    p = *(char **)(a0 + 0x164) + 0xD0;
    GetOrientOfWallOfGObj(p, a0);
    return p;
}

extern void GetRootMatrixByDObj(void *out, void *obj);
extern void CageFixDL(void *a0, void *a1, void *a2);
extern char D_006A4630[];

void *ContinueCorrectPosition(void *a0) {
    char *s0;
    int x = *(int *)((char *)a0 + 0xC);
    switch (x) {
    case 1:
    case 2:
    case 4:
        s0 = *(char **)((char *)a0 + 0x164) + 0xE0;
        GetRootMatrixByDObj(s0, a0);
        return s0;
    case 0x2B: {
        int local[4];
        CageFixDL(D_006A4630, local, a0);
        return D_006A4630;
    }
    default:
        GetRootMatrixByDObj(D_006A4630, a0);
        return D_006A4630;
    }
}


typedef struct { char _p670[0x670]; char *p670; } S164;
typedef struct { char _p164[0x164]; S164 *p164; } SObj;


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonTurn);
#undef TURN_OBJ


int actCommonBackhand(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    CBrain670 *q = p->p_670;
    long long v = q->f_BC;
    return (int)v & 1;
}

void actCommonSlowrun(int a0, int a1) {
    D_0028E680[a0].w[2] = a1;
}

extern void func_00240038(void *a0, float f);

void ACT_LAYOUT_GAMEOVER(void *a0) {
    int local[4];
    func_00240038(local, -1.0f);
    dispPlane(a0, local);
}

extern void func_00240038_p(void *a0, int a1, float f) __asm__("func_00240038");

void ACTAdjustPlane(int *self)
{
    int buf[4];
    func_00240038_p(buf, (int)((char *)self[0x164 / 4] + 0x4A0), -1.0f);
    dispPlane((void *)self, buf);
}

extern void ChangeMailInLadder(void *buf, void *obj);

void _ACTMotDirSmzDirect(void *a0) {
    int local[4];
    ChangeMailInLadder(local, a0);
    dispPlane(a0, local);
}

extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern void eBrainInit(int a0);
extern char D_00552B60[];
extern char D_00552B70[];

void WithMailFunc_Idling(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    if (*(int *)(s + 0x180) == 0) {
        func_001AAD00(D_00552B60, 0x593);
        func_00260380(D_00552B60, 0x593, D_00552B70);
    }
    eBrainInit(*(int *)(s + 0x180));
}


extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern void eBrainInit(int a0);
extern char D_00552B60[];
extern char D_00552B70[];

void WithMailFunc_BossDamaged(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    if (*(int *)(s + 0x180) == 0) {
        func_001AAD00(D_00552B60, 0x60D);
        func_00260380(D_00552B60, 0x60D, D_00552B70);
    }
    eBrainInit(*(int *)(s + 0x180));
}


void WithMailFunc_FallDead(volatile int a0) {
    int q = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
    void *p = *(void **)(*(char **)(a0 + 0x164) + 0x678);
    *(int *)((char *)p + 0x368) = q * 0x82 / 0x3C;
}


void actCommonRevive(volatile int a0) {
    ACTParaStatus_Clear(a0);
}

void actCommonReviveAir(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actCommonPlay(volatile int a0) {
    ACTParaStatus_Clear(a0);
}

void actCommonOne(volatile int a0) {
    int x = a0;
    int y = a0;
    *(int *)(*(int *)(*(int *)(x + 0x164) + 0x670) + 0x2A0) = -1;
    *(int *)(*(int *)(*(int *)(y + 0x164) + 0x670) + 0x2A4) = 0;
}

extern void actCommonRopeCliff(int a0, int a1);

void actCommonDelete(volatile int a0) {
    actCommonRopeCliff(a0, 0);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_00288FD0;  /* stride 0x14 */

typedef struct {
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_28;  /* 0x28 */
} S_0027E700;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
} S_0028E680;  /* stride 0x18 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0055D4B0;  /* stride 0x4 */

/* end struct shapes */



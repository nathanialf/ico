#include "common.h"

#include "ico/types.h"

typedef struct { int a, b, c; } Blob12;

typedef struct { int w[6]; } SlowrunRec;

extern void iosOmSendMail(void *a0, int a1, int a2);
extern void SetDirectRootPosition();

void ACTSetPositionWithFitting(void *a0, float *pos)
{
    SetDirectRootPosition(a0, pos);
}
extern void SetDirectRootPositionNoFitting__pn() __asm__("SetDirectRootPositionNoFitting");

void ACTSetPositionNoFitting(int a0, int a1, int a2, int a3)
{
    SetDirectRootPositionNoFitting__pn(a0, a1, a2, a3);
}
extern void SetDirectRootPositionWithNodePoint();

void ACTSetPositionNodeWithFitting(int a0, int a1, int a2, int a3)
{
    SetDirectRootPositionWithNodePoint(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", ChangeMailInLadder);
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTCorrectMsg);
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTGetOrientFromIntrK);
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTRunIntrCorrect);
void WithMailFunc_WayBeginPosError(void *a0) {
    ACTWay_SetBeginPositionIllegal(a0);
}
extern char *D_00639EA4;
extern char *D_00639EA8;
extern void ExecWeaponHitReaction(void *a0);

void WithMailFunc_AttackFail(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    char *p = *(char **)(s + 0x30);
    int v = p != 0 ? *(int *)p : *(int *)(s + 0x5E0);
    if (a0 == D_00639EA4) {
        char *t = *(char **)(s + 0x150);
        if (t != 0) {
            *(int *)(*(char **)(t + 0x15C) + 0x5F4) = v;
            ExecWeaponHitReaction(t);
        }
    }
}
extern int stage_no;
extern int D_0063B210;
extern void ReleaseWeaponWithFumbleSequential(void *a0);
extern void *isysGObjSearchFromObjKindID_begin(int a0);

void WithMailFunc_AttackRejectInQueen(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    void *w = *(void **)(s + 0x150);
    if (w != 0) {
        ReleaseWeaponWithFumbleSequential(w);
        *(int *)(s + 0x150) = 0;
    }
    if (stage_no == 0x55 || D_0063B210 != 0) {
        void *e = isysGObjSearchFromObjKindID_begin(0x36);
        if (e != 0) {
            iosOmSendMail(e, 0xD, (int)a0);
        }
    }
}
extern int GetChainDirCorrectVal(int chain, int *out);
extern void *memset(void *dst, int c, int n);
extern float _GetDirection(void *p);
extern int RoundDegGV(int deg);
extern int AlignDegGV(int deg);
extern void _ApplyRyGV(void *a0, float a1);
extern void *test_CURRENTORIENT(char *a0);

void GetCorrectOrientOfChain(void *buf, void *obj)
{
    float q[4];
    int deg;

    if (GetChainDirCorrectVal(*(int *)(*(char **)((char *)obj + 0x164) + 0x190), &deg) != 0) {
        memset(q, 0, 16);
        q[2] = 1.0f;
        _ApplyRyGV(q,
                   (float)RoundDegGV(deg + AlignDegGV(RoundDegGV(
                       (int)(_GetDirection(test_CURRENTORIENT((char *)obj)) / 3.1415927f * 180.0f) - deg)))
                       * 3.1415927f / 180.0f);
        ((float *)buf)[0] = q[0];
        ((float *)buf)[1] = q[1];
        ((float *)buf)[2] = q[2];
    } else {
        ((float *)buf)[0] = *(float *)((char *)test_CURRENTORIENT((char *)obj) + 0);
        ((float *)buf)[1] = *(float *)((char *)test_CURRENTORIENT((char *)obj) + 4);
        ((float *)buf)[2] = *(float *)((char *)test_CURRENTORIENT((char *)obj) + 8);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", CollisCheckInRope);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRope);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnR);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnL);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeClimbEnd1);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeCliff);
ASM_LIT4_SLOT(D_00638E40, 3.1415927f);
ASM_LIT4_SLOT(D_00638E44, 3.1415927f);
ASM_LIT4_SLOT(D_00638E48, 3.1415927f);
ASM_LIT4_SLOT(D_00638E4C, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", TestCageUpDown);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeSpecial);
ASM_LIT4_SLOT(D_00638E50, 0.7853982f);
ASM_LIT4_SLOT(D_00638E54, 3.1415927f);
extern void SetFloorLeverWithNodePoint(void *a0, void *a1, int a2);
extern void SetWallLeverWithNodePoint(void *a0, void *a1, int a2);

void lever_nego1(void *a0, void *a1) {
    int m = *(int *)((char *)a1 + 0xC);
    if (m < 0x16) {
        return;
    }
    if (m < 0x18) {
        goto lever;
    }
    if (m >= 0x1A) {
        return;
    }
    SetWallLeverWithNodePoint(a1, a0, 0x16);
    return;
lever:
    SetFloorLeverWithNodePoint(a1, a0, 0x16);
}
extern void SetDirectRootPositionNoFitting(void *a0, void *a1);
extern void *test_CURRENTROOT(void *a0);

void SetDirectRootPositionXZ(void *a0, void *a1) {
    void *ret = test_CURRENTROOT(a0);
    *(float *)((char *)a1 + 4) = *(float *)((char *)ret + 4);
    SetDirectRootPositionNoFitting(a0, a1);
}
extern int D_0028F4C0[];

typedef struct { char _0[0x394]; int f394; } LeverAnim;
extern char D_00552DF0[];
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void SetMotionDirection();
extern void _ACTWait(int a0);
extern void debug_StdPrintfDummy();
extern void GetFloorLeverGlobalHoldPoint(void *out, void *lev);
extern void GetWallLeverGlobalHoldPoint(void *out, void *lev);
extern void SetDirectRootPositionNoFittingWithNodePointXZ(void *a0, int node, void *pos, float t);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTMotDirToWall (lines 1307-1312) into actCommonLever, so it
   is `inline` in the dev's TU; while this tail still has asm members a deferred
   inline would land at the object end instead of at its ROM slot, so the public
   body below stays a plain definition and this caller uses the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline void actMotDirToWall(char *a0) {
    int local[4];
    sceVu0ScaleVector(local, *(char **)(a0 + 0x164) + 0x4B0, -1.0f);
    SetMotionDirection(a0, local);
}

static inline void correctLeverHoldPoint(void *a0, char *lev) {
    float w[4];
    if (*(int *)(lev + 0xC) >= 0x16) {
        if (*(int *)(lev + 0xC) < 0x18) {
            GetFloorLeverGlobalHoldPoint(w, lev);
        } else if (*(int *)(lev + 0xC) < 0x1A) {
            GetWallLeverGlobalHoldPoint(w, lev);
            debug_StdPrintfDummy(D_00552DF0, w[0], w[1], w[2]);
        }
    }
    SetDirectRootPositionNoFittingWithNodePointXZ(a0, 0x16, w, 0.2f);
}

void actCommonLever(volatile int a0)
{
    float p[4];
    char *s = *(char **)(a0 + 0x164);
    char *lev = *(char **)(s + 0x5FC);

    ((LeverAnim *)*(char **)(*(char **)(a0 + 0x164) + 0x688))->f394 =
        ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 5;
    p[0] = *(float *)(s + 0x5A0);
    p[1] = *(float *)(s + 0x5A4);
    p[2] = *(float *)(s + 0x5A8);
    p[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 0x2C, s + 0x5A0, 1.0f);
    actMotDirToWall((char *)a0);
    while (1) {
        if (lev != 0) {
            if (*(int *)(*(char **)(a0 + 0x15C) + 0x604) != 0) {
                correctLeverHoldPoint((void *)a0, lev);
            }
            if (*(int *)(*(char **)(a0 + 0x15C) + 0x600) != 0) {
                lever_nego1((void *)a0, lev);
            }
        }
        _ACTWait(1);
    }
}
extern void eBrainSendMes(void *a0);

void EBRAIN_SEND_MES(void *a0, int a1) {
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        eBrainSendMes(a0);
}
extern char D_0063A720[];
extern void debug_StdPrintfDummy();
extern void EnemyDeleteParticle(void *a0, void *a1, void *a2);

void DamageFunc(char *a0) {
    int s = *(int *)(a0 + 0x164);
    debug_StdPrintfDummy(D_0063A720);
    if (a0 != D_00639EA8) {
        *(float *)(s + 0x1E0) -= (float)*(int *)(*(char **)(a0 + 0x164) + 0x1D0);
    }
    if (*(int *)(a0 + 0xC) == 4) {
        char *b;
        EBRAIN_SEND_MES(a0, 5);
        b = *(char **)(*(char **)(a0 + 0x164) + 0x680);
        EnemyDeleteParticle(a0, b + 0xE0, b + 0xF0);
    }
}
extern void DamageFunc(char *a0);

void DownFunc(char *a0) {
    DamageFunc(a0);
    if (*(int *)(a0 + 0xC) == 1) {
        EBRAIN_SEND_MES(*(void **)(*(char **)(a0 + 0x164) + 0x1B0), 6);
    }
}
extern char D_00552E30[];
extern void actAfterDown(volatile int a0);
extern void brainAddLevelGirl(float f);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void SetMotionDirection();
extern void ACTSendMailCorrect(char *a0, int a1);

void actCommonDown(volatile int a0)
{
    float v[4];
    char *s = *(char **)(a0 + 0x164);
    int notDamage = *(int *)(s + 0xD8) != 0x37 && *(int *)(s + 0xD8) != 0x38;

    debug_StdPrintfDummy(D_00552E30);
    *(int *)(s + 0x18) = (int)actAfterDown;
    if (notDamage) {
        if ((char *)a0 == D_00639EA4) {
            brainAddLevelGirl(1000.0f);
        }
        if ((char *)a0 == D_00639EA8) {
            sceVu0ScaleVector(v, *(char **)(a0 + 0x164) + 0x1C0, -1.0f);
            SetMotionDirection(a0, v);
        } else {
            SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
        }
        DownFunc((char *)a0);
    }
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xCC) = 0x10;
    while (1) {
        if (*(int *)(a0 + 0xC) != 4) {
            *(char *)(*(char **)(a0 + 0x164) + 0x1DA) = 1;
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xCC) <= 0) {
            ACTSendMailCorrect((char *)a0, 0x124);
        }
        _ACTWait(1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDie);
ASM_LIT4_SLOT(D_00638E5C, 0.01f);
extern float _GetRandom(void);
extern void *memset(void *dst, int c, int n);
extern void RotQuaternionX(float *q, short a);
extern void RotQuaternionY(float *q, short a);
extern void RotQuaternionZ(float *q, short a);
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q,
                                          float x, float y, float z, float w);
extern void ACTGameCollisionOff(volatile int *self);
extern char D_00552D90[];
extern char D_00552E60[];
extern void debug_assert(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);

typedef struct {
    int rot[3];
    float f0C;
    float f10;
    float f14;
    int f18;
    int f1C;
    int f20;
} ClingRec;

extern ClingRec D_002BC4C0[];

typedef struct { char _0[0x21C]; int f21C; int f220; } ClingSub;

void actCommonCling(volatile int a0)
{
    int no;
    int mot;

    int Cling(int idx, int m)
    {
        float q[4];
        ClingRec *r;
        int i;
        int v;

        r = &D_002BC4C0[idx];
        memset(q, 0, 16);
        q[3] = 1.0f;
        if (!((unsigned int)idx < 15)) {
            debug_assert(D_00552D90, 0xAAD);
            __assert(D_00552D90, 0xAAD, D_00552E60);
        }
        for (i = 0; i < 3; i++) {
            v = (r->rot[i] << 15) / 180;
            if (v != 0) {
                switch (i) {
                case 0:
                    RotQuaternionX(q, v);
                    break;
                case 1:
                    RotQuaternionY(q, v);
                    break;
                case 2:
                    RotQuaternionZ(q, v);
                    break;
                }
            }
        }
        SetMotionNodeFixModeParameter((void *)a0, (void *)m, r->f18, r->f20, q,
                                      r->f0C, r->f10, r->f14, 1.0f);
        return r->f1C;
    }

    no = (int)(_GetRandom() * 10.0f) % 15;
    mot = ((ClingSub *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f21C;

    ((ClingSub *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f220 = mot;
    ACTGameCollisionOff(a0);
    Cling(no, mot);
    _ACTWait(0);
}

extern int SetMotionDirectionSmooze(int a0, float *dir, float s);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);

void actCommonSlip(volatile int a0)
{
    float dir[4];
    float v2[4];
    float v3[4];

    if (*(unsigned char *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x280) == 0) {
        dir[0] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270);
        dir[1] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x274);
        dir[2] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x278);
    } else {
        sceVu0ScaleVector(dir, (float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270), -1.0f);
    }
    v2[0] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270);
    v2[1] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x274);
    v2[2] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x278);
    sceVu0ScaleVector(v3, (float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270), 30.0f);
    v3[1] = -20.0f;
    while (1) {
        SetMotionDirectionSmooze(a0, dir, 3.0f);
        _ACTWait(1);
    }
}
extern void ACT_LAYOUT_GAMEOVER(void);
extern int enable_game_pause;
extern int D_0063AA08;
extern void SetBoyStonizedVisual(volatile int a0);
extern void GetGameOverEffectCenterPosition(float *out);
extern void _OrientXZGV(void *out, void *a, void *b);
extern void ACTSetPositionWithFitting(void *a0, float *pos);
extern void SetMotionDirection();

void actCommonStoneDead(volatile int a0)
{
    float center[4];
    float dir[4];
    char *s = *(char **)(a0 + 0x164);

    if (*(int *)(s + 0xD8) == 0x22) {
        SetBoyStonizedVisual(a0);
        GetGameOverEffectCenterPosition(center);
        _OrientXZGV(dir, center, test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, dir);
    } else {
        ACTSetPositionWithFitting((void *)a0, test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
        *(int *)(a0 + 0x50) = 0;
    }
    enable_game_pause = 0;
    D_0063AA08 = 1;
    _ACTWait(300);
    ACT_LAYOUT_GAMEOVER();
    _ACTWait(0);
}
extern void debug_Printf(int a, int b, unsigned int c, char *d, ...);
extern char D_00552EB8[];
extern char D_00552EC8[];
extern void _ACTParaStatus_Set(int a0, int a1);
extern void afterCommonStone(volatile int a0);
extern int D_0063B13C;

typedef struct { char _0[0x14]; int f14; char _18[0x34]; int f4C; } StoneSub;

void actCommonStone(volatile int a0)
{
    StoneSub *s = (StoneSub *)*(char **)(a0 + 0x164);

    s->f14 = (int)afterCommonStone;
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x2A0) = 0;
    while (1) {
        if (D_0063B13C & 1) {
            debug_Printf(10, 0xAA, 0xFFFFFFF, D_00552EB8,
                         *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xCC));
        }
        if (D_0063B13C & 1) {
            debug_Printf(10, 0xB4, 0xFFFFFFF, D_00552EC8,
                         *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x29C));
        }
        switch (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x29C)) {
        case 0:
        case 1:
            break;
        case 2:
            _ACTParaStatus_Set(a0, 0x26);
            break;
        default:
            _ACTParaStatus_Set(a0, 0x27);
            break;
        }
        if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xCC) < 0) {
            ACTSendMailCorrect((char *)a0, 0xC7);
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x29C) = 0;
        }
        if (s->f4C >= 0x3D &&
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x29C) >= 3) {
            ACT_LAYOUT_GAMEOVER();
            _ACTWait(0);
        }
        ACTSendMailCorrect((char *)a0, 0x70);
        _ACTWait(1);
    }
}
extern int D_0028F4C0[];
extern void ACTSendMailCorrect(char *a0, int a1);

typedef struct { char _0[0x250]; int f250, f254, f258, f25C; } SofaObj;
typedef struct { char _0[0x3A0]; int f3A0, f3A4; } SofaAnim;

void actCommonSofa(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    SetDirectRootPositionNoFitting((void *)a0, s + 0x5B0);
    ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f250 = 0;
    ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f258 = 0;
    ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f25C = 0;
    *(void **)(s + 0x160) = *(void **)(s + 0x61C);
    while (1) {
        ((SofaAnim *)*(int *)(*(int *)(a0 + 0x164) + 0x688))->f3A0 =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 3;
        ((SofaAnim *)*(int *)(*(int *)(a0 + 0x164) + 0x688))->f3A4 =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10;
        if (((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f250 >
            ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f254) {
            ACTSendMailCorrect((char *)a0, 0x73);
        }
        ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f250 += 1;
        _ACTWait(1);
    }
}
void BoxBarSoundOn(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    switch (*(int *)(s + 0x34)) {
    case 0x31:
        ExecBoxMoveStartReaction(*(int *)(s + 0x158), *(int *)(s + 0x38));
        break;
    case 0x33:
        ExecRotObjectMoveStartReaction(*(int *)(s + 0x5F8));
        break;
    }
}
void BoxBarSoundOff(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    switch (*(int *)(s + 0x34)) {
    case 0x31:
        ExecBoxMoveEndReaction(*(int *)(s + 0x158));
        break;
    case 0x33:
        ExecRotObjectMoveEndReaction(*(int *)(s + 0x5F8));
        break;
    }
}
void _boxbar_set_sound(int a0, int mode)
{
    switch (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310)) {
    case 0:
        if (mode == 1) {
            BoxBarSoundOn((char *)a0);
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310) = 1;
        }
        break;
    case 1:
        if (mode == 0 || mode == 2) {
            BoxBarSoundOff((char *)a0);
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310) = mode;
        } else {
            BoxBarSoundOn((char *)a0);
        }
        break;
    case 2:
        if (mode == 0) {
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310) = 0;
        }
        if (mode == 3) {
            BoxBarSoundOn((char *)a0);
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310) = 1;
        }
        break;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBox);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBar);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonJumpDircorrect);
ASM_LIT4_SLOT(D_00638E60, 0.3f);
ASM_LIT4_SLOT(D_00638E64, 0.3f);
void funcCommonFallDircorrect(char *a0) {
    SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x360);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", correctJumpOrientByChain);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonJump);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonFall);
ASM_LIT4_SLOT(D_00638E68, 0.1f);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern int MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(void *v);
extern void _UnitMatrix(int a0);
extern void gif_StartPacketPri(int pri);
extern void gif_EndPacket(void);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);
extern void prim_DispWireSphere(float a3, void *a0, int a1, int a2);
extern char D_0029CF30[];

typedef union { float f[4]; long long ll[2]; } FlyPt;

static void debugDispFlyLimit(float *pos, float y0, float y1)
{
    MatrixDrive_PushMatrix();
    {
    FlyPt a = { { pos[0], y0, pos[2], 1.0f } };
    FlyPt b = { { pos[0], y1, pos[2], 1.0f } };

    _UnitMatrix(MatrixDrive_GetMatrix());
    gif_StartPacketPri(11);
    DrawLineG(&b, D_0029CF30, &a, D_0029CF30, 0);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(&a);
    prim_DispWireSphere(10.0f, D_0029CF30, 4, 4);
    MatrixDrive_PopMatrix();
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(&b);
    prim_DispWireSphere(10.0f, D_0029CF30, 4, 4);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
    }
    MatrixDrive_PopMatrix();
}
extern int MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_TransMatrixV(void *a0);
extern void _UnitMatrix(int a0);
extern void gif_EndPacket(void);
extern void gif_StartPacketPri(int a0);
extern void prim_DispWireSphere(float a3, void *a0, int a1, int a2);

void debugDispSphere(void *a0, void *a1, float f) {
    MatrixDrive_PushMatrix();
    _UnitMatrix(MatrixDrive_GetMatrix());
    gif_StartPacketPri(0xB);
    MatrixDrive_TransMatrixV(a0);
    prim_DispWireSphere(f, a1, 4, 4);
    gif_EndPacket();
    MatrixDrive_PopMatrix();
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", getLandOffset);
INCLUDE_ASM("asm/nonmatchings/src/commonact", completeEmergency);
ASM_LIT4_SLOT(D_00638E6C, 7000.0f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", emergencyCheck);
ASM_LIT4_SLOT(D_00638E70, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", flyCoreLoop);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonFly);
ASM_LIT4_SLOT(D_00638E74, 0.005f);
ASM_LIT4_SLOT(D_00638E78, 10000.0f);
ASM_LIT4_SLOT(D_00638E7C, 0.005f);
ASM_LIT4_SLOT(D_00638E80, 90000.0f);
ASM_LIT4_SLOT(D_00638E84, 0.05f);
ASM_LIT4_SLOT(D_00638E88, 0.005f);
ASM_LIT4_SLOT(D_00638E8C, 360000.0f);
ASM_LIT4_SLOT(D_00638E90, 0.92f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLadder);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonEdgeHang);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonBeginReady);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonEndReady);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonEndExec);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonError);
INCLUDE_ASM("asm/nonmatchings/src/commonact", SetMotionDirectionSmooze);
ASM_LIT4_SLOT(D_00638E94, 3.1415927f);
ASM_LIT4_SLOT(D_00638E98, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTDebugPrint);
void ACTSendMailCorrect(char *a0, int a1) {
    char *s = *(char **)(a0 + 0x164);
    if ((a1 == 0xB5 || a1 == 0xBA) && *(int *)(a0 + 0xC) == 1) {
        long long f = *(long long *)(s + 0x488);
        if (((int)(f >> 5) & 1) && ((int)(*(long long *)(s + 0x498) >> 5) & 1)) {
            a1 = 0xB6;
        } else if ((int)(f >> 3) & 1) {
            a1 = ((int)(*(long long *)(s + 0x498) >> 3) & 1) ? 0xB7 : a1;
        }
    }
    iosOmSendMail(a0, a1, (int)a0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTCommonMailTest);
ASM_LIT4_SLOT(D_00638E9C, 0.1f);
ASM_LIT4_SLOT(D_00638EA0, 0.1f);
ASM_LIT4_SLOT(D_00638EA4, 0.1f);
ASM_LIT4_SLOT(D_00638EA8, 0.1f);
ASM_LIT4_SLOT(D_00638EAC, 0.1f);
ASM_LIT4_SLOT(D_00638EB0, 0.99f);
ASM_LIT4_SLOT(D_00638EB4, 0.1f);
ASM_LIT4_SLOT(D_00638EB8, 0.99f);
ASM_LIT4_SLOT(D_00638EBC, 0.1f);
ASM_LIT4_SLOT(D_00638EC0, 0.1f);
ASM_LIT4_SLOT(D_00638EC4, 0.99f);
ASM_LIT4_SLOT(D_00638EC8, 0.1f);
ASM_LIT4_SLOT(D_00638ECC, 0.99f);
extern void _ApplyRyGV(void *a0, float a1);
extern void *test_CURRENTORIENT(char *a0);

extern int _RotyGV(void *a0, void *a1);

int E3_LeverCheck(char *a0) {
    float buf[3];
    int v;
    buf[0] = *(float *)((char *)test_CURRENTORIENT(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x0);
    buf[1] = *(float *)((char *)test_CURRENTORIENT(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x4);
    buf[2] = *(float *)((char *)test_CURRENTORIENT(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x8);
    _ApplyRyGV(buf, -1.5707964f);
    return _RotyGV(test_CURRENTORIENT(a0), buf) < 0
               ? -_RotyGV(test_CURRENTORIENT(a0), buf) < 0x2D
               : _RotyGV(test_CURRENTORIENT(a0), buf) < 0x2D;
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBecarry);
INCLUDE_ASM("asm/nonmatchings/src/commonact", subCommonIdle);
INCLUDE_ASM("asm/nonmatchings/src/commonact", ContinueCorrectPosition);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTurn);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBackhand);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonSlowrun);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTruckLever);
ASM_LIT4_SLOT(D_00638ED4, 0.2f);
ASM_LIT4_SLOT(D_00638ED8, 0.2f);
ASM_LIT4_SLOT(D_00638EDC, 0.1f);
ASM_LIT4_SLOT(D_00638EE0, 0.2f);
extern int D_00639EB8;
void ACT_LAYOUT_GAMEOVER(void) {
    if (D_00639EB8 == 0) {
        D_00639EB8 = 1;
        lt_switch_layout(0x3E);
    }
}
extern void AdjustRootPositionToVerticalSidePlaneOfWall(int a0, int a1, float a2);

void ACTAdjustPlane(int a0, int a1) {
    AdjustRootPositionToVerticalSidePlaneOfWall(a0, a1, 30.0f);
}
extern int D_0028F4C0[];

void ACTAcceptMail(char *a0, int a1) {
    if (a1 == 0xB1) {
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3C4) =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTMotDirSmzDirect);
typedef struct { int w[5]; } IdleRangeRec;

extern IdleRangeRec D_002A7DC8[];
extern SlowrunRec D_002ADD60[];

static inline void SetIdleMotionRange(int k, int mot)
{
    int n1 = D_002A7DC8[k].w[1];
    int n2 = D_002A7DC8[k].w[2];
    int n3 = D_002A7DC8[k].w[3];
    int n4 = D_002A7DC8[k].w[4];
    int i;

    if (mot != 0x47B) {
        D_002ADD60[n1].w[2] = mot;
        D_002ADD60[n2].w[2] = mot;
        for (i = n3; i < n4; i++) {
            D_002ADD60[i].w[0] = mot;
        }
    }
}

void WithMailFunc_Idling(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    int k = *(int *)(s + 0x48);
    int mot = *(int *)(*(char **)(a0 + 0x15C) + 0x4A0);

    SetIdleMotionRange(k, mot);
}
void WithMailFunc_BossDamaged(char *a0) {
    char *m = *(char **)(*(char **)(a0 + 0x164) + 0x680);
    *(int *)(m + 0x20C) -= 1;
}
extern float FSqrt(float a0);
extern void sceVu0Normalize(void *a0, void *a1);

void WithMailFunc_FallDead(char *a0) {
    float v[4];
    char *s = *(char **)(a0 + 0x15C);
    v[0] = *(float *)(s + 0x1D0);
    v[1] = *(float *)(s + 0x1D4);
    v[2] = *(float *)(s + 0x1D8);
    sceVu0Normalize(v, v);
    if ((double)FSqrt(v[0] * v[0] + v[2] * v[2]) > 0.3) {
        v[1] = 0.0f;
        sceVu0Normalize(v, v);
        SetMotionDirection(a0, v);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRevive);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonReviveAir);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonPlay);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonOne);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDelete);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCatchFire);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCatchFireBomb);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonPutFire);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBoxReverbe);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonItem);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonClimb);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCliffdown);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLadderBellow);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLadderBellowHang);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonEdge);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDodge);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDodgeJump);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonGuard);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonFallDamage);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDamage);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonShoal);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonSwim);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLever2);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeTouchWall);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeSwing);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeTurn);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeDownEnd);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeJump);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeJumpBefore);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeTurnSpecial);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeClimbEnd2);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCornered);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLookaround);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTurnWarn);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTurnStrict);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonPPipe);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonHandrail);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonOneWall);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonNull);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonBoxPush);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonBoxPull);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonBarPush);
void motCommonBarPull(volatile int a0) {
    char *g = (char *)a0;
    *(unsigned int *)(*(char **)(g + 0x164) + 0x38) = 0xFFFFFFFFu;
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonLadderUp);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonLadderDown);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonSlip);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopejumpDircorrect);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonHangNone);
extern char D_00553188[];
extern void _ACTWait(int a0);
extern void debug_StdPrintfDummy();

void motCommonHangWall(volatile int a0) {
    debug_StdPrintfDummy(D_00553188);
    _ACTWait(0);
}
extern char D_005531A8[];

void motCommonHangCliff(volatile int a0) {
    debug_StdPrintfDummy(D_005531A8);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnSpecialR);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnSpecialL);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonTruckLeverLoop);
ASM_LIT4_SLOT(D_00638EE4, 0.1f);
ASM_LIT4_SLOT(D_00638EE8, 3.1415927f);
ASM_LIT4_SLOT(D_00638EEC, 0.1f);
ASM_LIT4_SLOT(D_00638EF0, 3.1415927f);
extern char D_0063A780[];
extern void SetSwitchState(int a0, int a1);

void motCommonTruckLeverPull(volatile int a0) {
    int sw = *(int *)(*(int *)(a0 + 0x164) + 0x5FC);
    _ACTWait(0x1E);
    SetSwitchState(sw, -1);
    debug_StdPrintfDummy(D_0063A780);
    _ACTWait(0);
}
extern char D_0063A788[];

void motCommonTruckLeverPush(volatile int a0) {
    int sw = *(int *)(*(int *)(a0 + 0x164) + 0x5FC);
    _ACTWait(0x1E);
    SetSwitchState(sw, 1);
    debug_StdPrintfDummy(D_0063A788);
    _ACTWait(0);
}
void funcCommonRopeBefore(char *a0, int a1, int a2) {
    *(int *)(*(char **)(a0 + 0x164) + 0x190) = a2;
}
extern char D_00552D78[];
extern void ReleaseChain(int a0, int a1);

void afterCommonRope(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    debug_StdPrintfDummy(D_00552D78);
    ReleaseChain(*(int *)(s + 0x190), a0);
    {
        int g = a0;
        *(int *)(s + 0x194) = *(int *)(s + 0x190);
        *(int *)(*(int *)(g + 0x15C) + 0x420) = 0;
    }
}
void extraCommonNull(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}
extern int D_0063A61C;
extern void iosOmSendMail(void *a0, int a1, int a2);

void extraCommonCall(volatile int a0) {
    if (D_00639EA8) {
        iosOmSendMail(D_00639EA8, 0x44, D_0063A61C);
    }
    for (;;) {
        _ACTWait(1);
    }
}
extern int girlcalled;

void funcCommonWayOn(void *a0) {
    if (a0 == D_00639EA8) {
        girlcalled = 1;
    }
}
void funcCommonSofaWakeup(char *a0) {
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x250) = 0;
}
int _ACTMotReqResult(char *a0, int a1) {
    char *s = *(char **)(a0 + 0x164);
    char *r = SetMotionRequest(a0, a1, s + 0x620);
    *(char **)(s + 0x130) = r;
    return *(int *)(r + 0xC) != 0;
}
extern char D_006C0BA0[];
extern void GetRootOrient(void *a0, void *a1);
extern void _GetMotionDirection(void *a0, void *a1);

void *test_CURRENTORIENT(char *a0) {
    if (a0 != D_00639EA4 && a0 != D_00639EA8 && *(int *)(a0 + 0xC) != 4) {
        GetRootOrient(D_006C0BA0, a0);
        return D_006C0BA0;
    }
    {
        char *p = *(char **)(a0 + 0x164) + 0xF0;
        _GetMotionDirection(p, a0);
        return p;
    }
}
extern float D_006C0BB0[];
extern float D_0063A790[];
extern int GetCageChainPoint(float *out, float *buf, void *a0);
extern void GetRootPosition(float *out, void *a0);

void *test_CURRENTROOT(void *a0)
{
    float buf[4];
    float *p;
    float v;

    switch (*(int *)((char *)a0 + 0xC)) {
    case 1:
    case 2:
    case 4:
        p = (float *)*(char **)((char *)a0 + 0x164);
        p = (float *)((char *)p + 0x100);
        GetRootPosition(p, a0);
        return p;
    case 0x2C:
        if (GetCageChainPoint(D_006C0BB0, buf, a0) == 0) {
            v = D_0063A790[0];
            D_006C0BB0[0] = v;
            D_006C0BB0[1] = v;
            D_006C0BB0[2] = v;
        }
        return D_006C0BB0;
    default:
        GetRootPosition(D_006C0BB0, a0);
        return D_006C0BB0;
    }
}
typedef union { unsigned long long ll; int i; } CorrFlag;

void StartCorrectPosition(char *a0, float *pos, float *dir, int mode, float t)
{
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x70) =
        ((float *)test_CURRENTROOT(a0))[0];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x74) =
        ((float *)test_CURRENTROOT(a0))[1];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x78) =
        ((float *)test_CURRENTROOT(a0))[2];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x80) =
        ((float *)test_CURRENTORIENT(a0))[0];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x84) =
        ((float *)test_CURRENTORIENT(a0))[1];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x88) =
        ((float *)test_CURRENTORIENT(a0))[2];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x90) = pos[0];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x94) = pos[1];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x98) = pos[2];
    if (dir != 0) {
        *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xA0) = dir[0];
        *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xA4) = dir[1];
        *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xA8) = dir[2];
    }
    *(int *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xB0) = (int)t;
    *(int *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xB4) = 0;
    ((CorrFlag *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xB8))->i = mode;
    ((CorrFlag *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xB8))->ll |= (1ULL << 32);
}
int IsCorrectPosition(char *a0) {
    unsigned long long v = *(unsigned int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xBC);
    return (int)v & 1;
}
extern SlowrunRec D_002ADD60[];

void ControlMotionOrient(int a0, int a1) {
    D_002ADD60[a0].w[2] = a1;
}
extern int IsThisBoxTruck(void *a0);

int FloorIsTruck(void *a0) {
    char *p = *(char **)(*(int *)((char *)a0 + 0x15C));
    if (p != 0) {
        if (*(int *)(p + 0xC) == 0x11) {
            if (IsThisBoxTruck(p) == 7) {
                return 1;
            }
        }
    }
    return 0;
}
extern void SetMotionDirection();
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);

void _ACTMotDir_V(void *a0, void *a1) {
    int local[4];
    sceVu0ScaleVector(local, a1, -1.0f);
    SetMotionDirection(a0, local);
}
void ACTMotDirToWall(char *a0) {
    int local[4];
    sceVu0ScaleVector(local, *(char **)(a0 + 0x164) + 0x4B0, -1.0f);
    SetMotionDirection(a0, local);
}
extern void GetCorrectOrientOfChain(void *buf, void *obj);

void SetCorrectOrientOfChain(void *a0) {
    int local[4];
    GetCorrectOrientOfChain(local, a0);
    SetMotionDirection(a0, local);
}
extern char D_00552D90[];
extern char D_00552DA0[];
extern void debug_assert(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
extern void UnLockChainGeo(int a0);

void actAfterForceRope(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    if (*(int *)(s + 0x190) == 0) {
        debug_assert(D_00552D90, 0x5FB);
        __assert(D_00552D90, 0x5FB, D_00552DA0);
    }
    UnLockChainGeo(*(int *)(s + 0x190));
}
void actAfterForceRopeSwing(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    if (*(int *)(s + 0x190) == 0) {
        debug_assert(D_00552D90, 0x675);
        __assert(D_00552D90, 0x675, D_00552DA0);
    }
    UnLockChainGeo(*(int *)(s + 0x190));
}
void actAfterRopeJump(volatile int a0) {
    char *g = (char *)a0;
    *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) |= (1ULL << 31);
}
extern char *D_00639EA4;

void afterCommonRopeCliff(char *a0) {
    char *volatile local = a0;
    char *g = *(char **)(D_00639EA4 + 0x15C);
    *(int *)(g + 0x420) = 0;
}
void afterCommonRopeTurnSpecial(volatile int a0) {
    char *g = (char *)a0;
    *(int *)(*(char **)(g + 0x15C) + 0x420) = 0;
}
void actAfterDown(volatile int a0) {
    *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x688) + 0x37C) =
        ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0x82 / 0x3C;
}
extern void ACTGameCollisionOn(volatile int *self);

void afterCommonCling(volatile unsigned int a0)
{
    ACTGameCollisionOn(a0);
}
void actAfterSlip(int x) {
    volatile int local = x;
}
void afterCommonRevive(volatile unsigned int a0)
{
    ACTGameCollisionOn(a0);
}
void afterCommonStone(volatile int a0) {
    int g1 = a0;
    int g2 = a0;
    *(int *)(*(int *)(*(int *)(g1 + 0x164) + 0x680) + 0x2A0) = -1;
    *(int *)(*(int *)(*(int *)(g2 + 0x164) + 0x680) + 0x2A4) = 0;
}
extern void _boxbar_set_sound(int a0, int a1);

void afterCommonBox(volatile int a0) {
    _boxbar_set_sound(a0, 0);
}
extern Blob12 InitialColInfo;

extern void debug_StdPrintfDummy();

void afterCommonBar(volatile int a0) {
    debug_StdPrintfDummy("reset\n");
    *(Blob12 *)(*(char **)(a0 + 0x15C) + 0x1C0) = InitialColInfo;
    _boxbar_set_sound(a0, 0);
}
void actAfterJump(volatile int a0) {
    char *g = (char *)a0;
    *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) |= (1ULL << 31);
}
void actAfterFall(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    unsigned long long st = *(unsigned long long *)(s + 0x20) & ~(1ULL << 42);
    unsigned long long fl = *(unsigned long long *)(s + 0x18) & ~(1ULL << 53);
    *(unsigned long long *)(s + 0x18) = fl;
    *(unsigned long long *)(s + 0x20) = st | (1ULL << 31);
}
extern void SetEnemyFootPrintSwitch(int a0, int a1);
typedef struct { char _0[0x20]; unsigned long long status; } FlySub;

static inline void ResetFlyLimit(int a0)
{
    *(int *)(*(int *)(a0 + 0x15C) + 0x654) = 0;
}

void actAfterFly(volatile int a0) {
    FlySub *s = (FlySub *)*(int *)(a0 + 0x164);
    s->status |= 0x200;
    SetEnemyFootPrintSwitch(a0, 1);
    ResetFlyLimit(a0);
}
extern void sceVu0CopyVector(void *a0, void *a1);
extern void ClipWallField(void *a0);
extern void ClipFloor(void *a0);

void ClipCollisionWithField(char *a0) {
    int tmp[4];
    sceVu0CopyVector(tmp, a0 + 0x10);
    ClipWallField(a0);
    sceVu0CopyVector(a0 + 0x10, a0 + 0x20);
    ClipFloor(a0);
    sceVu0CopyVector(a0 + 0x10, tmp);
}
void afterCommonOneWall(int x) {
    volatile int local = x;
}
int ACTCheckFlagAttack(char *a0) {
    return *(int *)(*(char **)(a0 + 0x164) + 0x34) == 0xF;
}
extern void SetKidnapInfo(int a0, int a1);
extern void gflagOff(int a0);
typedef struct { char _0[0x74]; int coll; } BecSub;

void afterCommonBecarry(volatile int a0) {
    SetKidnapInfo(-1, -1);
    ((BecSub *)*(int *)(a0 + 0x15C))->coll = 1;
    ACTGameCollisionOn(a0);
    gflagOff(0x189);
}
void afterCommonTruckLever(volatile int a0) {
    char *g = (char *)a0;
    SetSwitchState(*(int *)(*(char **)(g + 0x164) + 0x5FC), 0);
}

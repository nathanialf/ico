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
extern char *D_00639EA4;
extern char *D_00639EA8;
extern void *test_CURRENTROOT(void *a0);
extern float _DistxzSqGV(void *a, void *b);

int ChangeMailInLadder(char *a0, int a1)
{
    float p[4];
    float q[4];
    char *s = *(char **)(a0 + 0x164);
    int ret = a1;
    int flag = 0;
    float lim1;
    float lim2;

    if (D_00639EA4 != 0 && D_00639EA8 != 0) {
        if (a0 == D_00639EA4) {
            if (*(int *)(s + 0x34) == 0x26) {
                flag = (*(int *)(*(char **)(D_00639EA8 + 0x164) + 0x34) == 0x26);
            }
        }
        if (a0 == D_00639EA8) {
            if (*(int *)(s + 0x34) == 0x26) {
                flag = 1;
            }
        }
        if (flag != 0 &&
            _DistxzSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8)) < 3600.0f) {
            lim1 = a0 == D_00639EA4 ? 175.0f : 225.0f;
            lim2 = a0 == D_00639EA4 ? 175.0f : 210.0f;
            if (a0 == D_00639EA4) {
                p[0] = ((float *)test_CURRENTROOT(a0))[0];
                p[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
                p[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
                q[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
                q[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
                q[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
            } else {
                p[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
                p[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
                p[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
                q[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
                q[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
                q[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
            }
            switch (a1) {
            case 0x14A:
                if (q[1] < p[1] &&
                    (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < lim2) {
                    *(unsigned long long *)(s + 0x18) |= (1ULL << 36);
                    ret = 0x150;
                }
                break;
            case 0x14B:
                if (q[1] > p[1] &&
                    (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < lim1) {
                    *(unsigned long long *)(s + 0x18) |= (1ULL << 37);
                    ret = 0x150;
                }
                break;
            }
        }
    }
    return ret;
}
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
void funcCommonJumpDircorrect(char *a0)
{
    SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x350);
}
ASM_LIT4_SLOT(D_00638E60, 0.3f);
ASM_LIT4_SLOT(D_00638E64, 0.3f);
void funcCommonFallDircorrect(char *a0) {
    SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x360);
}
extern void GetRootPosition(float *out, void *a0);
extern float D_0063A748[];
extern void GetMatrixDirectionToZ(void *m, void *orient);
extern void *isysGObjSearchFromObjKindID_next(void *o);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void sceVu0ApplyMatrix(void *out, void *m, void *v);
extern float GetChainHangRange(void *o);
extern float GetChainLength(void *o);

void correctJumpOrientByChain(char *a0)
{
    float out[4];
    float mtx[16];
    float pos[4];
    float p[4];
    float q[4];
    float dir[4];
    char *o;
    float t;
    float best = D_0063A748[0];
    float ang = 0.0f;

    pos[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
    pos[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    pos[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
    GetMatrixDirectionToZ(mtx, test_CURRENTORIENT(a0));

    for (o = isysGObjSearchFromObjKindID_begin(0x15); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        if (*(int *)(o + 0x16C) == 0) {
            continue;
        }
        GetRootPosition(p, o);
        sceVu0SubVector(q, p, pos);
        q[3] = 0.0f;
        sceVu0ApplyMatrix(q, mtx, q);
        if (q[2] < 0.0f || 1000.0f < q[2]) {
            continue;
        }
        if (GetChainHangRange(o) < (q[0] < 0.0f ? -q[0] : q[0])) {
            continue;
        }
        if (pos[1] < p[1]) {
            continue;
        }
        if (p[1] + GetChainLength(o) + 200.0f < pos[1]) {
            continue;
        }
        ang = q[0]; best = q[2]; if (ang < 0.0f) ang = -ang;
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
    }
    if (best == D_0063A748[0]) {
        return;
    }
    _OrientXZGV(dir, out, test_CURRENTROOT((void *)a0));
    t = ang * 20.0f / 300.0f;
    if (t < 0.0f) {
        t = 0.0f;
    } else if (20.0f < t) {
        t = 20.0f;
    }
    SetMotionDirectionSmooze((int)a0, dir, t);
}
extern char D_0055FE58[];
extern void actAfterJump(volatile int a0);

typedef union { unsigned long long ll; void *p; } ActFlagJ;
typedef struct { char _0[0x18E]; unsigned short f18E; } MotRecJ;

void actCommonJump(volatile int a0)
{
    float dir[4];
    char *s = *(char **)(a0 + 0x164);
    int chk = 0;
    int hit = 0;
    int n;

    ((ActFlagJ *)(s + 0x18))->ll &= ~(1ULL << 55);
    ((ActFlagJ *)(s + 0x18))->p = (void *)actAfterJump;
    if (*(int *)(s + 0xD8) == 0x52) {
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3B4) =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10;
    }
    if (*(int *)(s + 0xD8) == 0x105) {
        ((ActFlagJ *)(s + 0x18))->ll |= (1ULL << 55);
        if ((char *)a0 == D_00639EA8 && D_00639EA4 != 0) {
            _OrientXZGV(dir, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT((void *)a0));
            SetMotionDirection(a0, dir);
        }
    }
    ((ActFlagJ *)(s + 0x18))->ll &= ~(1ULL << 56);
    if (*(int *)(s + 0xD8) == 0xC5) {
        SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x510);
        ((ActFlagJ *)(s + 0x18))->ll |= (1ULL << 56);
    }
    n = *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900);
    if (n < 4) {
        if (0 < n) {
            switch ((unsigned int)*(int *)(s + 0xD8)) {
            case 0xBF:
            case 0xC0:
                chk = 1;
                break;
            case 0xBD:
                if (0.1f < *(float *)(s + 0x34C)) {
                    chk = 1;
                }
                break;
            }
            if (chk != 0) {
                correctJumpOrientByChain((char *)a0);
            }
        }
    }
    while (1) {
        if (((MotRecJ *)(D_0055FE58 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194))->f18E & 1) {
            hit = 1;
        }
        if (hit != 0 &&
            *(int *)(D_0055FE58 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194 + 0x150) == 1) {
            *(float *)(*(char **)(a0 + 0x15C) + 0x130) =
                *(float *)(*(char **)(a0 + 0x15C) + 0x138) = 0.0f;
        }
        ACTSendMailCorrect((char *)a0, 0xBD);
        _ACTWait(1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonFall);
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
extern char D_005F5D50[];
extern int stage_no;
extern int CheckWallAttributeEdegWall(void *a0);
extern void GetSkeltonPosition(float *dst, char *obj, int node);
extern void ClipFloor(void *a0);
extern void *memset(void *dst, int c, int n);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void ACTAdjustPlane(int a0, int a1);

typedef struct { char _0[0x190]; unsigned int f190; } StageRecEH;

typedef struct {
    char _00[0x20];
    float _20, _24, _28;
    char _2c[0x44];
    float _70;
    char _74[0x0C];
    int _80;
    char _84[0x04];
    int _88;
    int _8c;
    char _90[0x04];
    int _94;
    int _98;
    char _9c[0x24];
} EdgeHangWork;

void actCommonEdgeHang(volatile int a0)
{
    EdgeHangWork work;
    float p1[4];
    float p2[4];

    ACTAdjustPlane(a0, *(int *)(*(int *)(a0 + 0x164) + 0x688) + 0x8B0);
    while (1) {
        if (CheckWallAttributeEdegWall((void *)a0) == 0) {
            ACTSendMailCorrect((char *)a0, 0xE2);
        }
        if (-*(float *)(*(char **)(a0 + 0x15C) + 0x5E8) > 250.0f) {
            ACTSendMailCorrect((char *)a0, 0x18);
        }
        if ((((StageRecEH *)(D_005F5D50 + stage_no * 0x194))->f190 >> 2) & 1) {
            memset(&work, 0, 0xC0);
            GetSkeltonPosition((float *)&work, (char *)a0, 0x2C);
            GetSkeltonPosition(p1, (char *)a0, 0x33);
            GetSkeltonPosition(p2, (char *)a0, 0x2F);
            sceVu0AddVector((char *)&work + 0x10, p1, p2);
            sceVu0ScaleVector((char *)&work + 0x10, (char *)&work + 0x10, 0.5f);
            ClipFloor(&work);
            if (work._94 != 0) {
                ACTSendMailCorrect((char *)a0, 0xE2);
            }
        }
        _ACTWait(1);
    }
}
extern char D_0063A760[];
extern char D_0063A768[];
extern char D_005531E0[];

void funcCommonBeginReady(char *a0, int a1, char *a2)
{
    *(int *)(*(char **)(a0 + 0x164) + 0xE0) |= 1;
    debug_StdPrintfDummy(D_005531E0,
                         a2 == D_00639EA4 ? D_0063A760 : D_0063A768,
                         a0 == D_00639EA4 ? D_0063A760 : D_0063A768);
}
extern char D_005531F8[];

void funcCommonEndReady(char *a0, int a1, char *a2)
{
    *(int *)(*(char **)(a0 + 0x164) + 0xE0) |= 2;
    debug_StdPrintfDummy(D_005531F8,
                         a2 == D_00639EA4 ? D_0063A760 : D_0063A768,
                         a0 == D_00639EA4 ? D_0063A760 : D_0063A768);
}
extern char D_00553210[];

void funcCommonEndExec(char *a0, int a1, char *a2)
{
    *(int *)(*(char **)(a0 + 0x164) + 0xE0) |= 8;
    debug_StdPrintfDummy(D_00553210,
                         a2 == D_00639EA4 ? D_0063A760 : D_0063A768,
                         a0 == D_00639EA4 ? D_0063A760 : D_0063A768);
}
extern char D_00553228[];

void funcCommonError(char *a0, int a1, char *a2)
{
    *(int *)(*(char **)(a0 + 0x164) + 0xE0) |= 0x10;
    debug_StdPrintfDummy(D_00553228,
                         a2 == D_00639EA4 ? D_0063A760 : D_0063A768,
                         a0 == D_00639EA4 ? D_0063A760 : D_0063A768);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", SetMotionDirectionSmooze);
ASM_LIT4_SLOT(D_00638E94, 3.1415927f);
ASM_LIT4_SLOT(D_00638E98, 3.1415927f);
extern char D_00553240[];
extern char D_00553250[];
extern char D_00553260[];
extern char D_00553270[];
extern char D_00553280[];
extern char D_00553290[];
extern char D_005532A0[];
extern char D_005532B8[];
extern char D_005532D0[];
extern char D_005532E0[];
extern char D_005577F4[];
extern char D_005D1278[];
extern char D_0055FE58[];
extern char D_0055FF18[];
extern void *D_00639EA0;
extern int fptodp(float v);

typedef struct { char _0[0xC2]; short fC2; } MotNameRecDP;
typedef struct { char _0[0x186]; short f186; } MotRecDP;

void _ACTDebugPrint(char *a0)
{
    char *sub;
    char *w;

    if (a0 == 0) {
        return;
    }
    sub = *(char **)(a0 + 0x164);
    if (sub == 0) {
        return;
    }
    w = *(char **)(a0 + 0x15C) + 0x470;
    if (w == 0) {
        return;
    }
    if (D_0063B13C & 1) {
    debug_Printf(30, 90, 0xFFFFFFF, D_00553240, D_005D1278 + *(int *)(w + 0xD0) * 32);
    if (D_0063B13C & 1) {
    debug_Printf(30, 100, 0xFFFFFFF, D_00553250,
                 D_0055FF18 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194);
    if (D_0063B13C & 1) {
    debug_Printf(30, 110, 0xFFFFFFF, D_00553260, D_005577F4 + *(int *)(sub + 0x34) * 0x50);
    if (D_0063B13C & 1) {
    debug_Printf(30, 120, 0xFFFFFFF, D_00553270,
                 fptodp(*(float *)(*(char **)(a0 + 0x15C) + 0x4AC)));
    if (D_0063B13C & 1) {
    debug_Printf(30, 130, 0xFFFFFFF, D_00553280,
                 a0 == D_00639EA8 && D_00639EA0 != 0
                     ? ((MotNameRecDP *)(D_0055FF18 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194))->fC2
                     : ((MotRecDP *)(D_0055FE58 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194))->f186);
    if (D_0063B13C & 1) {
    debug_Printf(30, 140, 0xFFFFFFF, D_00553290, (int)*(float *)(sub + 0x1E0));
    if (D_0063B13C & 1) {
    debug_Printf(30, 150, 0xFFFFFFF, D_005532A0,
                 (int)*(float *)(*(char **)(sub + 0x130) + 0x138),
                 (int)-*(float *)(*(char **)(sub + 0x130) + 0x130));
    if (D_0063B13C & 1) {
    debug_Printf(30, 160, 0xFFFFFFF, D_005532B8,
                 (int)*(float *)(*(char **)(sub + 0x130) + 0x114),
                 (int)*(float *)(*(char **)(sub + 0x130) + 0x110));
    if (D_0063B13C & 1) {
    debug_Printf(30, 170, 0xFFFFFFF, D_005532D0, *(int *)(*(char **)(a0 + 0x15C) + 0x5F4));
    if (D_0063B13C & 1) {
    debug_Printf(30, 180, 0xFFFFFFF, D_005532E0,
                 *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1EC));
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
}
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
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void SetDirectRootPositionNoFittingWithNodePointXZ(void *a0, int node, void *pos, float t);

void actCommonBackhand(volatile int a0)
{
    float v[4];
    float dir[4];
    float pos[4];
    int frame;

    _OrientXZGV(dir, test_CURRENTROOT((void *)a0), test_CURRENTROOT(D_00639EA8));
    SetMotionDirection(a0, dir);
    v[0] = ((float *)test_CURRENTORIENT(D_00639EA8))[0];
    v[1] = ((float *)test_CURRENTORIENT(D_00639EA8))[1];
    v[2] = ((float *)test_CURRENTORIENT(D_00639EA8))[2];
    while (1) {
        sceVu0ScaleVector(pos, v, 50.0f);
        sceVu0AddVector(pos, test_CURRENTROOT(D_00639EA8), pos);
        SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, pos, 0.2f);
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x4A0) == 0xBD) {
            _OrientXZGV(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT((void *)a0));
            SetMotionDirection(a0, dir);
        }
        /* ROM-proven vestigial: the shipped code still computes this frame
           budget and drops it -- only D_0028F4C0[1]'s load and gcc's
           divide-by-zero trap survive (SRCFILE line 6205), which is
           mechanically unreachable without the division. */
        frame = (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1];
        _ACTWait(1);
    }
}
extern int GetSkeltonFocusNode(void *a0, void *a1);
extern char D_0055FE58[];
extern void SetDirectRootPositionNoFittingWithNodePointXZ(void *a0, int node, void *pos, float t);

typedef union { int i; float f; } IntFloatSR;

typedef struct { char _0[0x182]; short f182; short f184; short f186; char _188[4]; unsigned int f18C; char _190[4]; } MotRecSR;


void actCommonSlowrun(volatile int a0)
{
    float p[2][4];

    while (1) {
        int i1;
        int i2;

        i1 = GetSkeltonFocusNode(D_00639EA8, (void *)0x16);
        i2 = GetSkeltonFocusNode(D_00639EA4, (void *)6);
        ((IntFloatSR *)p[0])[0].f = *(float *)((i1 << 6) + *(int *)(*(char **)(D_00639EA8 + 0x15C) + 0xC) + 0x30);
        ((IntFloatSR *)p[0])[1].f = *(float *)((i1 << 6) + *(int *)(*(char **)(D_00639EA8 + 0x15C) + 0xC) + 0x34);
        ((IntFloatSR *)p[0])[2].f = *(float *)((i1 << 6) + *(int *)(*(char **)(D_00639EA8 + 0x15C) + 0xC) + 0x38);
        ((IntFloatSR *)p[1])[0].f = *(float *)((i2 << 6) + *(int *)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + 0x30);
        ((IntFloatSR *)p[1])[1].f = *(float *)((i2 << 6) + *(int *)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + 0x34);
        ((IntFloatSR *)p[1])[2].f = *(float *)((i2 << 6) + *(int *)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + 0x38);
        if ((((MotRecSR *)(D_0055FE58 + *(int *)(*(char **)(D_00639EA8 + 0x15C) + 0x4A0) * 0x194))->f18C >> 29) & 1) {
            SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, p[0], 0.2f);
        } else {
            SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, p[0], 0.1f);
        }
        _ACTWait(1);
    }
}
extern void afterCommonTruckLever(volatile int a0);

typedef struct { char _0[0x14]; int f14; } TruckLeverWork;

void actCommonTruckLever(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);
    char *lev = *(char **)(s + 0x5FC);

    ((TruckLeverWork *)s)->f14 = (int)afterCommonTruckLever;
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
extern void *D_00639EA0;

int _ACTMotDirSmzDirect(char *a0, float *a1)
{
    char *s = *(char **)(a0 + 0x164);

    *(float *)(s + 0x120) = a1[0];
    *(float *)(s + 0x124) = a1[1];
    *(float *)(s + 0x128) = a1[2];
    return SetMotionDirectionSmooze(
        (int)a0, a1,
        (float)(a0 == D_00639EA8 && D_00639EA0 != 0
                    ? ((MotRecSR *)(D_0055FE58 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194))->f182
                    : ((MotRecSR *)(D_0055FE58 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194))->f186));
}
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
extern char D_00552EA0[];
extern void afterCommonRevive(volatile unsigned int a0);
extern void EnemySetfAppearAll(void *a0);
extern void ResetEnemyPositionInfo(void *a0);

typedef struct { char _0[0x14]; int f14; } ReviveSub;

void actCommonRevive(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    debug_StdPrintfDummy(D_00552EA0);
    ACTGameCollisionOff(a0);
    ((ReviveSub *)s)->f14 = (int)afterCommonRevive;
    SetDirectRootPositionNoFitting((void *)a0, s + 0x170);
    EnemySetfAppearAll((void *)a0);
    for (;;) {
        ResetEnemyPositionInfo((void *)a0);
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern void EnemySetfAppearAll(void *a0);

void actCommonReviveAir(volatile int a0)
{
    SetDirectRootPositionNoFitting((void *)a0, *(char **)(a0 + 0x164) + 0x170);
    EnemySetfAppearAll((void *)a0);
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xE2);
        _ACTWait(1);
    }
}
extern char D_00552E00[];

void actCommonPlay(volatile int a0)
{
    debug_StdPrintfDummy(D_00552E00);
    _ACTWait(0);
}
void actCommonOne(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    if (*(int *)(s + 0xD8) == 0x1A0) {
        if (*(int *)(s + 0x138) & 1) {
            *(short *)(s + 0x13A) = ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 5;
        }
    }
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
void actCommonDelete(volatile int a0)
{
    _ACTWait(0);
}
extern int GetMotionFrameFlag1(void *a0);
extern void LightTorchOnOfWeapon(void *a0);

void actCommonCatchFire(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);
    int lit = 0;

    SetMotionDirection(a0, s + 0x4D0);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOnOfWeapon(*(void **)(s + 0x150));
            lit = 1;
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern void LightTorchOn(void *a0);

void actCommonCatchFireBomb(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);
    int lit = 0;

    SetMotionDirection(a0, s + 0x4D0);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOn(*(void **)(s + 0x614));
            lit = 1;
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
void actCommonPutFire(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);
    int lit = 0;

    SetMotionDirection(a0, s + 0x4E0);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOn(*(void **)(s + 0x618));
            lit = 1;
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
void actCommonBoxReverbe(volatile int a0)
{
    _ACTWait(0x28);
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
void actCommonItem(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
void actCommonClimb(volatile int a0)
{
    ACTAdjustPlane(a0, *(int *)(*(int *)(a0 + 0x164) + 0x688) + 0x8B0);
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern char D_005530F0[];

void actCommonCliffdown(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    debug_StdPrintfDummy(D_005530F0);
    SetMotionDirection(a0, s + 0x4C0);
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern void GetSkeltonPosition(float *dst, char *obj, int node);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern int ACTCheckCollis_CI(int a0, int a1, int *a2, char *a3);
extern int CompareAttribute(unsigned int a, unsigned int b);

typedef struct { float x, y, z; } Vec3f;

void actCommonLadderBellow(volatile int a0)
{
    float hit[4];
    float p[4];
    float q[4];
    float dir[4];
    int attr[4];

    while (1) {
        GetSkeltonPosition(p, (char *)a0, 0x2C);
        sceVu0ScaleVector(dir, test_CURRENTORIENT((char *)a0), 50.0f);
        sceVu0AddVector(q, p, dir);
        if (ACTCheckCollis_CI((int)p, (int)q, attr, (char *)hit) != 0) {
            if (CompareAttribute(attr[0], 0x3000) != 0) {
                ACTSendMailCorrect((char *)a0, 0x91);
                *(Vec3f *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3D8) = *(Vec3f *)hit;
            }
            if (CompareAttribute(attr[0], 0x400) != 0) {
                ACTSendMailCorrect((char *)a0, 0x90);
                *(Vec3f *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3CC) = *(Vec3f *)hit;
            }
        }
        ACTSendMailCorrect((char *)a0, 0xE2);
        _ACTWait(1);
    }
}
extern int CheckWallAttribute(void *a0, int a1);

void actCommonLadderBellowHang(volatile int a0)
{
    for (;;) {
        if (!CheckWallAttribute((void *)a0, 0x3000) && !CheckWallAttribute((void *)a0, 0x400)) {
            ACTSendMailCorrect((char *)a0, 0xE2);
        }
        _ACTWait(1);
    }
}
void actCommonEdge(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0x150);
        if (-*(float *)(*(char **)(a0 + 0x15C) + 0x5E8) > 250.0f) {
            ACTSendMailCorrect((char *)a0, 0x18);
        }
        _ACTWait(1);
    }
}
extern char D_00553138[];
extern void ACTSearchEnemy(void *a0, int *out_id, float *out_vec);
extern void SetMotionDirectionWithLimit(void *a0, float *dir, float lo, float hi);

void actCommonDodge(volatile int a0)
{
    float dir[4];
    int id = 0;
    char *s = *(char **)(a0 + 0x164);

    debug_StdPrintfDummy(D_00553138);
    if (*(int *)(a0 + 0xC) == 1) {
        ACTSearchEnemy((void *)a0, &id, dir);
    } else {
        _OrientXZGV(s + 0x120, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, s + 0x120);
    }
    while (1) {
        if (id != 0) {
            SetMotionDirectionWithLimit((void *)a0, dir, 10.0f, 90.0f);
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern void ACTSearchEnemy(void *a0, int *out_id, float *out_vec);

void actCommonDodgeJump(volatile int a0)
{
    float buf[4];
    int id = 0;
    char *s = *(char **)(a0 + 0x164);

    if (*(int *)(a0 + 0xC) == 1) {
        ACTSearchEnemy((void *)a0, &id, buf);
    } else {
        _OrientXZGV(s + 0x120, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, s + 0x120);
    }
    for (;;) {
        _ACTWait(1);
    }
}
extern char D_00553150[];
extern void ACTGame_LwsEffect_Guard(void *a0);

void actCommonGuard(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    debug_StdPrintfDummy(D_00553150);
    SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
    if (*(int *)(a0 + 0xC) == 4) {
        EBRAIN_SEND_MES((void *)a0, 6);
        ACTGame_LwsEffect_Guard((void *)a0);
    }
    iosOmSendMail(D_00639EA4, 0x11C, a0);
    if (*(int *)(s + 0xD8) == 0x11A) {
        ACTSetPositionWithFitting((void *)a0, (float *)test_CURRENTROOT((void *)a0));
    }
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern void brainSetSpMode(void);

void actCommonFallDamage(volatile int a0)
{
    if ((char *)a0 == D_00639EA4) {
        brainAddLevelGirl(1000.0f);
    }
    for (;;) {
        if ((char *)a0 == D_00639EA4 && D_00639EA8 != 0) {
            brainSetSpMode();
            iosOmSendMail(D_00639EA8, 0x3D, a0);
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern char D_00552E18[];

void actCommonDamage(volatile int a0)
{
    debug_StdPrintfDummy(D_00552E18);
    SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
    DamageFunc((char *)a0);
    if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1E4) == 3) {
        _ACTWait(0x168);
    }
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern char D_00553110[];

void actCommonShoal(volatile int a0)
{
    debug_StdPrintfDummy(D_00553110);
    _ACTWait(0);
}
extern char D_00553120[];

void actCommonSwim(volatile int a0)
{
    debug_StdPrintfDummy(D_00553120);
    for (;;) {
        _ACTWait(1);
    }
}
void actCommonLever2(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);
    char *lev = *(char **)(s + 0x5FC);

    SetDirectRootPositionXZ((void *)a0, s + 0x5A0);
    actMotDirToWall((char *)a0);
    while (1) {
        if (lev != 0) {
            /* ROM-proven vestigial: an empty guard. SRCFILE line 2443 emits
               exactly this dead volatile re-read and nothing else; retail
               dropped the body (actCommonLever keeps correctLeverHoldPoint
               here). */
            if (*(int *)(*(char **)(a0 + 0x15C) + 0x604) != 0) {
            }
            if (*(int *)(*(char **)(a0 + 0x15C) + 0x600) != 0) {
                lever_nego1((void *)a0, lev);
            }
        }
        _ACTWait(1);
    }
}
void actCommonRopeTouchWall(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    while (1) {
        if (((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 2 < *(int *)(s + 0x4C)) {
            ACTSendMailCorrect((char *)a0, 0xAA);
        }
        _ACTWait(1);
    }
}
extern void actAfterForceRopeSwing(volatile int a0);
extern void LockChainGeo(int a0);
extern void UnLockChainGeo(int a0);
extern void ChainGeo(int a0);
extern void PlumbOrientUpdateChain(int a0, float *q);
extern int CollisCheckInRope(void *a0, int chain);

typedef struct { char _0[0x18]; int f18; } RopeSwingWork;

void actCommonRopeSwing(volatile int a0)
{
    float q[4];
    char *s = *(char **)(a0 + 0x164);

    LockChainGeo(*(int *)(s + 0x190));
    ((RopeSwingWork *)s)->f18 = (int)actAfterForceRopeSwing;
    GetCorrectOrientOfChain(q, (void *)a0);
    *(float *)(s + 0x1A0) = q[0];
    *(float *)(s + 0x1A4) = q[1];
    *(float *)(s + 0x1A8) = q[2];
    PlumbOrientUpdateChain(*(int *)(s + 0x190), q);
    _ACTWait(1);
    while (1) {
        switch (CollisCheckInRope((void *)a0, *(int *)(s + 0x190))) {
        case 1:
            ACTSendMailCorrect((char *)a0, 0xA8);
            break;
        case 2:
            ACTSendMailCorrect((char *)a0, 0xA7);
            break;
        }
        UnLockChainGeo(*(int *)(s + 0x190));
        ChainGeo(*(int *)(s + 0x190));
        LockChainGeo(*(int *)(s + 0x190));
        SetMotionDirection(a0, q);
        _ACTWait(1);
    }
}
void actCommonRopeTurn(volatile int a0)
{
    for (;;) {
        _ACTWait(1);
    }
}
extern char D_0055FE58[];

typedef struct {
    char _00[0x20];
    float _20, _24, _28;
    char _2c[0x44];
    float _70;
    char _74[0x0C];
    int _80;
    char _84[0x04];
    int _88;
    int _8c;
    char _90[0x04];
    int _94;
    int _98;
    char _9c[0x24];
} FloorWork;

extern void GetSkeltonPosition(float *dst, char *obj, int node);
extern void ClipFloor(void *a0);

static inline int isRopeDownEndOnFloor(char *self)
{
    FloorWork work;
    char *rec = D_0055FE58 + *(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194;

    if ((*(unsigned int *)(rec + 0x18C) >> 4) & 1) {
        GetSkeltonPosition((float *)&work, self, 0x2C);
        GetSkeltonPosition((float *)((char *)&work + 0x10), self, 0x33);
        *(float *)((char *)&work + 0x14) = *(float *)((char *)&work + 0x14) - 5.0f;
        ClipFloor(&work);
        if (work._94 != 0) {
            return 1;
        }
    }
    return 0;
}

void actCommonRopeDownEnd(volatile int a0)
{
    while (1) {
        if (isRopeDownEndOnFloor((char *)a0)) {
            ACTSendMailCorrect((char *)a0, 0xA9);
        }
        _ACTWait(1);
    }
}
extern void actAfterRopeJump(volatile int a0);

typedef struct { char _0[0x130]; int f130; int f134; int f138; } RopeJumpWork;

void actCommonRopeJump(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    *(int *)(s + 0x18) = (int)actAfterRopeJump;
    if (*(int *)(s + 0xD8) == 0xA7) {
        ((RopeJumpWork *)*(int *)(a0 + 0x15C))->f130 = 0;
        ((RopeJumpWork *)*(int *)(a0 + 0x15C))->f134 = 0;
        ((RopeJumpWork *)*(int *)(a0 + 0x15C))->f138 = 0;
    }
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xBD);
        _ACTWait(1);
    }
}
void actCommonRopeJumpBefore(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xBD);
        _ACTWait(1);
    }
}
extern void afterCommonRopeTurnSpecial(volatile int a0);
extern int GetCageChainPoint(float *out, float *buf, void *a0);
extern void _InterGV(void *dst, void *a, void *b, float ta, float tb);
extern void SetChainRootUpdateMode(void *a0, int mode, float *p);

typedef struct { char _0[0x18]; int f18; } RopeTurnSpWork;
typedef union { float f[4]; int i[4]; } Vec4u;

void actCommonRopeTurnSpecial(volatile int a0)
{
    Vec4u base;
    float p0[4];
    float p1[4];
    float out[4];

    ((RopeTurnSpWork *)*(char **)(a0 + 0x164))->f18 = (int)afterCommonRopeTurnSpecial;
    base.f[0] = *(float *)(*(int *)(a0 + 0x15C) + 0x410);
    base.f[1] = *(float *)(*(int *)(a0 + 0x15C) + 0x414);
    base.f[2] = *(float *)(*(int *)(a0 + 0x15C) + 0x418);
    while (1) {
        GetCageChainPoint(p0, p1, *(void **)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x400));
        _InterGV(out, p0, p1, base.f[1] - p0[1], p1[1] - base.f[1]);
        out[1] = base.f[1];
        SetChainRootUpdateMode((void *)a0, 3, out);
        _ACTWait(1);
    }
}
void actCommonRopeClimbEnd2(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern void _ACTCharStatus_Set(char *a0, int bit, float f, int val);

void actCommonCornered(volatile int a0)
{
    float v[4];

    sceVu0ScaleVector(v, test_CURRENTORIENT((char *)a0), -1.0f);
    SetMotionDirection(a0, v);
    for (;;) {
        _ACTCharStatus_Set((char *)a0, 3, -1.0f, 0);
        _ACTWait(1);
    }
}
void actCommonLookaround(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern void GetRootMotionOrient(float *out, volatile int a0);
extern int SetMotionRequest(void *a0, int id, void *work);

void actCommonTurnWarn(volatile int a0)
{
    float q[4];
    char *s = *(char **)(a0 + 0x164);
    int prev = *(int *)(s + 0x40);

    while (1) {
        int d;

        if (*(int *)(s + 0x40) != 0x10D) {
            prev = *(int *)(s + 0x40);
        } else {
            *(int *)(s + 0x130) = SetMotionRequest((void *)a0, prev, s + 0x620);
        }
        GetRootMotionOrient(q, a0);
        d = _RotyGV(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3F0, q);
        if ((d < 0 ? -d : d) < 0xF) {
            ACTSendMailCorrect((char *)a0, 0xF5);
        }
        _ACTWait(1);
    }
}
extern void GetRootMotionOrient(float *out, volatile int a0);

void actCommonTurnStrict(volatile int a0)
{
    float q[4];
    char *t = *(char **)(a0 + 0x164) + 0x5C0;

    for (;;) {
        int d;

        GetRootMotionOrient(q, a0);
        d = _RotyGV(t, q);
        if ((d < 0 ? -d : d) < 0xF) {
            ACTSendMailCorrect((char *)a0, 0xF4);
        }
        _ACTWait(1);
    }
}
void actCommonPPipe(volatile int a0)
{
    _ACTWait(0);
}
typedef struct { char _0[0x4C0]; float f4C0; float f4C4; float f4C8; } HandrailNode;

void actCommonHandrail(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    ((HandrailNode *)*(char **)(*(char **)(a0 + 0x164) + 0x688))->f4C0 = *(float *)(s + 0x4B0);
    ((HandrailNode *)*(char **)(*(char **)(a0 + 0x164) + 0x688))->f4C4 = *(float *)(s + 0x4B4);
    ((HandrailNode *)*(char **)(*(char **)(a0 + 0x164) + 0x688))->f4C8 = *(float *)(s + 0x4B8);
    for (;;) {
        _ACTWait(1);
    }
}
extern void afterCommonOneWall(int x);

void actCommonOneWall(volatile int a0)
{
    *(int *)(*(int *)(a0 + 0x164) + 0x14) = (int)afterCommonOneWall;
    _ACTWait(0);
}
extern char D_005531C8[];

void motCommonNull(volatile int a0)
{
    debug_StdPrintfDummy(D_005531C8);
    for (;;) {
        _ACTWait(1);
    }
}
extern int IsThisBoxTruck(void *a0);

void motCommonBoxPush(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    *(int *)(s + 0x38) = 1;
    while (1) {
        if (IsThisBoxTruck(*(void **)(s + 0x158)) == 0) {
            SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x530);
        } else {
            actMotDirToWall((char *)a0);
        }
        _ACTWait(1);
    }
}
void motCommonBoxPull(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    *(unsigned int *)(s + 0x38) = -1;
    while (1) {
        if (IsThisBoxTruck(*(void **)(s + 0x158)) == 0) {
            SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x530);
        } else {
            actMotDirToWall((char *)a0);
        }
        _ACTWait(1);
    }
}
void motCommonBarPush(volatile int a0)
{
    *(int *)(*(int *)(a0 + 0x164) + 0x38) = 1;
    _ACTWait(0);
}
void motCommonBarPull(volatile int a0) {
    char *g = (char *)a0;
    *(unsigned int *)(*(char **)(g + 0x164) + 0x38) = 0xFFFFFFFFu;
    _ACTWait(0);
}
typedef struct { char _0[0x38]; int f38; } LadderMotWork;

void motCommonLadderUp(volatile int a0)
{
    LadderMotWork *s = (LadderMotWork *)*(char **)(a0 + 0x164);

    while (1) {
        s->f38 = 1;
        switch (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x290)) {
        case 1:
            ACTSendMailCorrect((char *)a0, 0x89);
        case 2:
            ACTSendMailCorrect((char *)a0, 0x8A);
            break;
        }
        _ACTWait(1);
    }
}
typedef struct { char _0[0x38]; unsigned int f38; } LadderDownMotWork;

void motCommonLadderDown(volatile int a0)
{
    LadderDownMotWork *s = (LadderDownMotWork *)*(char **)(a0 + 0x164);

    while (1) {
        s->f38 = -1;
        switch (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x294)) {
        case 1:
            ACTSendMailCorrect((char *)a0, 0x89);
        case 2:
            ACTSendMailCorrect((char *)a0, 0x8A);
            break;
        }
        _ACTWait(1);
    }
}
void motCommonSlip(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);

    while (1) {
        long long f = *(long long *)(s + 0x480);

        if (!((((int)(f >> 16) & 1) && ((int)(*(long long *)(s + 0x490) >> 16) & 1)) ||
              (((int)(f >> 17) & 1) && ((int)(*(long long *)(s + 0x490) >> 17) & 1)))) {
            ACTSendMailCorrect((char *)a0, 0xC7);
        }
        _ACTWait(1);
    }
}
void motCommonRopejumpDircorrect(volatile int a0)
{
    float v[4];
    char *s = *(char **)(a0 + 0x164);

    v[0] = *(float *)(s + 0x1A0);
    v[1] = *(float *)(s + 0x1A4);
    v[2] = *(float *)(s + 0x1A8);
    if (*(int *)(s + 0xD8) == 0xBE) {
        sceVu0ScaleVector(v, v, -1.0f);
    }
    for (;;) {
        SetMotionDirection(a0, v);
        _ACTWait(1);
    }
}
extern char D_00553168[];

void motCommonHangNone(volatile int a0)
{
    debug_StdPrintfDummy(D_00553168);
    _ACTWait(0);
}
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
ASM_LIT4_SLOT(D_00638EE4, 0.1f);
ASM_LIT4_SLOT(D_00638EE8, 3.1415927f);
ASM_LIT4_SLOT(D_00638EEC, 0.1f);
ASM_LIT4_SLOT(D_00638EF0, 3.1415927f);
extern char D_0063A778[];
extern void SetSwitchState(int a0, int a1);

void motCommonTruckLeverLoop(volatile int a0)
{
    int sw = *(int *)(*(int *)(a0 + 0x164) + 0x5FC);

    _ACTWait(6);
    SetSwitchState(sw, 0);
    debug_StdPrintfDummy(D_0063A778);
    _ACTWait(0);
}
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

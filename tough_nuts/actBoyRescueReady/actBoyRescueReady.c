#include "common.h"

/* boyact 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; } BoyState;
#include "ico/types.h"

void findChainInJump(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", CorrectOrient_RopeCliff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", motBoyHand100);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", motBoyHand200);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", hand_heroin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", CheckCollisionAttr);

typedef struct { char pad[4]; float f4; } CCPResult;
extern float D_00628E24;

typedef struct {
    char _0[4];
    float f4;          /* 0x4 */
    float f8;          /* 0x8 */
    char _c;           /* 0xC */
    unsigned char fD;  /* 0xD */
    char _e;           /* 0xE */
    unsigned char fF;  /* 0xF */
    float f10;         /* 0x10 */
    char _14[12];      /* 0x14 */
    char f20[4];       /* 0x20 */
    float f24;         /* 0x24 */
    char _28[8];       /* 0x28 */
    char f30[16];      /* 0x30 */
} Geo;

extern void *subCommonIdle(void *a0);
extern void *isysGObjSearchFromObjLayoutID(int id);
extern CCPResult *ContinueCorrectPosition(void *a0);
extern void _OrientXZGV(void *a0, void *a1, void *a2);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void ActGame_GetOrientQ(void *a0, void *a1, int a2);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void func_00191DB8(void *a0, float a1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", UpdateGeo);


/* BoyBgaManager */
typedef struct {
    int field0;
    char _4[0x8];
    unsigned char fC;
    char _d;
    unsigned char fE;
    char _f[0x11];
    char f20[0x10];
    char f30[0x10];
} BgaEntry;

extern BgaEntry D_0027DF90[];
extern char D_005525C8[];
extern char D_0062C3F8[];
extern void func_001AAD00(char *file, int line);
extern void __assert(char *file, int line, char *msg, int v);
static void UpdateGeo();
extern float stage_SetParentOfGObj(int a0, void *a1, void *a2, float a3);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", BoyBgaManager);


extern unsigned char D_0062BFDE;
extern unsigned char D_0062BFDF;
extern unsigned char D_0062BFE0;
extern void *subCommonIdle(void *a0);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern CCPResult *ContinueCorrectPosition(void *a0);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void CylinderCollision(void *a0, void *a1);
extern int func_00178DB0(int a0);
extern void func_00178E08(int a0);
extern int staffRollScroll(void *a0, int a1, int a2, int *p, int *q, int *r);
extern void _ACTWait(int a0);
extern void func_001790A8(void *a0);
extern void BoySekikaTexScroll(void *a0, int a1);
extern void func_001790E8(void *a0);

void E3_StageStartBoy(void *a0) {
    float buf[4];
    int w10, w14, w18;

    if (D_0062BFDE) {
        sceVu0ScaleVector(buf, subCommonIdle(a0), 100.0f);
        sceVu0AddVector(buf, buf, ContinueCorrectPosition(a0));
        CylinderCollision(a0, buf);
    }
    if (func_00178DB0(0x15B)) {
        func_00178E08(0x15B);
        return;
    }
    if (staffRollScroll(a0, 0, 0, &w10, &w14, &w18)) {
        if (D_0062BFE0) {
            return;
        }
        if (D_0062BFDF) {
            return;
        }
        _ACTWait(3);
        staffRollScroll(a0, 0, 0, &w10, &w14, &w18);
        _ACTWait(w10);
        func_001790A8(a0);
        BoySekikaTexScroll(a0, 7);
        _ACTWait(w14);
        func_001790E8(a0);
        _ACTWait(w18);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", GetChainSlope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", subBoyControl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_0014E858);

extern long long D_006A45A0[];
extern void GetLowerPlaneCollision(char *p, float a, float b, float c, float d, float e, float f);
extern void func_00102828(int obj);

void InitSwapWeapon(void)
{
    char *base = (char *)D_006A45A0;
    int *obj_ptr = *(int **)(base + 0x20);
    char *sub;
    if (obj_ptr == 0) return;
    sub = ((GObj *)((char *)obj_ptr))->p_15C;
    GetLowerPlaneCollision(sub + 0xA0,
                  *(float *)(base + 0x30),
                  *(float *)(base + 0x34),
                  *(float *)(base + 0x38),
                  -*(float *)(base + 0x40),
                  -*(float *)(base + 0x44),
                  -*(float *)(base + 0x48));
    func_00102828(*(int *)(base + 0x20));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", PutWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", OtherStageGirlPinchCamera_After);


extern void *D_00629DE4;
extern void *D_00629DE8;
extern CCPResult *ContinueCorrectPosition(void *);
extern void sceVu0SubVector(void *, CCPResult *, CCPResult *);
extern float sceVu0InnerProduct(void *, void *);
extern float _DistxzGV(void *, CCPResult *);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150608);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", subBoyCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoySwim);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyWalk);

extern void BeforeFunc2(void *a0);
extern void _RotyGV(void *a0, void *a1);

void actBoyRun(void *a0) {
    char buf[0x10];
    BeforeFunc2(buf);
    _RotyGV(buf, a0);
}

extern void *D_00629DE4;

int actBoyAttack(void) {
    void *p = D_00629DE4;
    void *q;
    if (p == 0) goto ret0;
    q = *(void **)((char *)p + 0x164);
    return *(int *)((char *)q + 0x130);
ret0:
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyTakeWeaponReady);

void actBoyTakeWeapon(int *volatile a0) {
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7C0);
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", pullup_check_heroin_position);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", ditch_check_heroin_position);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyPullupReady);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyPullupGo);

extern float ClearHandCameraCorrect(CCPResult *, CCPResult *);
extern void *isysGObjSearchFromObjKindID_next(void *);

void actBoyBelift(void *a0, int *out_id, float *out_vec) {
    float buf[4];
    void *node;
    int best;
    float thresh = 300.0f;

    node = isysGObjSearchFromObjLayoutID((*(int *)((char *)a0 + 0xC) ^ 1) ? 1 : 4);
    *out_id = 0;
    best = 0x5A;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = ContinueCorrectPosition(a0);
                if (ClearHandCameraCorrect(r1, ContinueCorrectPosition(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = ContinueCorrectPosition(node);
                    sceVu0SubVector(buf, r4, ContinueCorrectPosition(a0));
                    sign = ((int (*)(void *, void *))_RotyGV)(buf, subCommonIdle(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))_RotyGV)(buf, subCommonIdle(a0));
                    } else {
                        dist = ((int (*)(void *, void *))_RotyGV)(buf, subCommonIdle(a0));
                    }
                    if (dist < best) {
                        best = dist;
                        out_vec[0] = buf[0];
                        out_vec[1] = buf[1];
                        out_vec[2] = buf[2];
                        *out_id = (int)node;
                    }
                }
            }
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
}


extern void ExecWeaponHitReaction(void *a0);
extern void memset(void *a0, int a1, int a2);
extern void gamesysObjInfoPosSetStage(int a0, int a1, int a2, void *a3);
extern int D_006A4608[];
extern float D_00628F1C;
extern void *D_00629C90;

void actBoyRescueReady(void) {
    float buf[4];
    int *s16;
    if (D_00629DE4 == 0) return;
    s16 = *(int **)((char *)D_00629DE4 + 0x164);
    if (*(int *)((char *)s16 + 0x130) != 0) {
        ExecWeaponHitReaction(*(void **)((char *)s16 + 0x130));
        memset(buf, 0, 0x10);
        buf[0] = D_00628F1C;
        CylinderCollision((void *)*(int *)((char *)s16 + 0x130), buf);
        gamesysObjInfoPosSetStage(*(int *)((char *)s16 + 0x130), 0, 0, D_00629C90);
        *(int *)(*(int *)((char *)s16 + 0x130) + 0x16C) = 0;
    }
    D_006A4608[0] = 0;
    *(int *)D_006A45A0 = 0;
    *(int *)((char *)s16 + 0x130) = 0;
}


int actBoyDitch3mReady(void) {
    BoyState *p = *(BoyState **)((char *)D_00629DE4 + 0x164);
    unsigned int v = p->f_30;
    if (v >= 0x5D) {
        return 1;
    }
    if (v < 0x5B) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", SetStatusBoy_OtherStageGirlPinch);

extern int D_0062A894;

int actBoyStart(int *a0) {
    int *o = (int *)a0[0x59];
    if (o[0xC] == 0x35) goto ret1;
    {
        int *p = (int *)o[0x19E];
        if (p[0xE0] == 0) goto ret0;
        if (D_0062A894 == 0) goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", CorrectStickInfo);

extern unsigned long long D_006A45A8[];

int IsGirlEscortedInNextStage(void) {
    return (unsigned char)(D_006A45A8[0] >> 35) & 1;
}

extern unsigned char D_0062BFDC;

int actBoyStand(void) {
    return D_0062BFDC;
}

extern void *D_00629DE8;
int actBoyHang(void) {
    if (D_00629DE4 != 0 && D_00629DE8 != 0) {
        BoyState *p5 = *(BoyState **)((char *)D_00629DE4 + 0x164);
        int v4 = p5->f_30;
        if (v4 == 0x2D) {
            BoyState *p2 = *(BoyState **)((char *)D_00629DE8 + 0x164);
            if (p2->f_30 == v4) {
                int *q = *(int **)((char *)p5 + 0x140);
                return q[2];
            }
        }
    }
    return -1;
}


extern long long D_006A45A0_ll[] __asm__("D_006A45A0");
void OnGirlEscortFlag(void) {
    D_006A45A0_ll[1] |= 0x800000000LL;
}

extern char D_005529E0[];
extern unsigned char D_006A45F0[];
extern int RequestStageChangeSimple(void *a0, int a1, int a2, int a3, float a4, float a5);
extern void ACTGame_StageChangeGObjDirect(void *a0, void *a1, void *a2, int a3);

int RequestStageChangeKidnapEnd(void *a0, int a1) {
    char buf[0x10];
    int rv = 0;
    if (D_00629DE4 != 0) {
        rv = RequestStageChangeSimple(a0, 0, 0, 0, 0.25f, 4.0f) & 0xFF;
        if (rv != 0) {
            D_006A45F0[0] = 1;
            *(int *)(D_006A45F0 + 4) = a1;
            *(long *)buf = *(long *)D_005529E0;
            *(long *)(buf + 8) = *(long *)(D_005529E0 + 8);
            ACTGame_StageChangeGObjDirect(D_00629DE4, a0, buf, 0);
        }
    }
    return rv;
}

extern unsigned char D_006A45F0[];

int GetEfStageCameraTargetID(void) {
    if (D_006A45F0[0] == 0) goto ret0;
    return *(int *)(D_006A45F0 + 4);
ret0:
    return 0;
}

extern int D_006A4600[];

int actBoyItem(void) {
    return D_006A45F0[0];
}

void *actBoyItemAfter(void) {
    return D_006A4600;
}

int actBoyCliffHesitate(void) {
    return 0x18;
}

typedef struct { int d[6]; } HB_S18;
typedef struct { int d[2]; } HB_S8;
extern void *D_00629DE4;
extern void *D_00629DE8;
extern long long D_006A45A0[];
extern int D_006A4600[];
extern int D_0027DF70[];
extern void SetStatusBoy_OtherStageGirlPinch(void);

void actBoyHangBefore(void) {
    char *boy = (char *)D_00629DE4;
    char *dst = (char *)D_006A4600;

    *(HB_S18 *)D_006A4600 = *(HB_S18 *)D_0027DF70;

    if (boy != 0) {
        char *p = *(char **)(boy + 0x164);
        char *a = *(char **)(p + 0x130);
        if (a != 0) {
            *(int *)(dst + 0x8) = *(int *)(a + 0x8);
        }
        a = *(char **)(p + 0x134);
        if (a != 0) {
            *(int *)(dst + 0xC) = *(int *)(a + 0x8);
        }
        if (*(int *)(p + 0x30) == 0x2D) {
            *(int *)(dst + 0x10) = *(int *)(*(char **)(p + 0x140) + 0x8);
        }
        if (D_00629DE8 != 0 &&
            *(int *)(*(char **)((char *)D_00629DE8 + 0x164) + 0x30) == 0x2D) {
            *(int *)(dst + 0x14) |= 1;
        }
        SetStatusBoy_OtherStageGirlPinch();
        {
            unsigned long long v = D_006A45A0[1];
            *(int *)(dst + 0x14) =
                (*(int *)(dst + 0x14) & 0xFFFEFFFF) |
                (((unsigned char)(v >> 0x22) & 1) << 0x10);
            *(char *)(dst + 0x15) = (unsigned char)(v >> 0x21) & 1;
        }
        *(HB_S8 *)dst = *(HB_S8 *)((char *)D_006A45A0 + 0x50);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyReadyMove);

/* ACTSearchGObj: iterate over layout objects, pick best hand-camera match */
extern float ClearHandCameraCorrect(CCPResult *, CCPResult *);
extern void *isysGObjSearchFromObjKindID_next(void *);

void ACTSearchGObj(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh) {
    float buf[4];
    void *node;
    int best;

    node = isysGObjSearchFromObjLayoutID(a1);
    *out_id = 0;
    best = a2;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = ContinueCorrectPosition(a0);
                if (ClearHandCameraCorrect(r1, ContinueCorrectPosition(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = ContinueCorrectPosition(node);
                    sceVu0SubVector(buf, r4, ContinueCorrectPosition(a0));
                    sign = ((int (*)(void *, void *))_RotyGV)(buf, subCommonIdle(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))_RotyGV)(buf, subCommonIdle(a0));
                    } else {
                        dist = ((int (*)(void *, void *))_RotyGV)(buf, subCommonIdle(a0));
                    }
                    if (dist < best) {
                        best = dist;
                        out_vec[0] = buf[0];
                        out_vec[1] = buf[1];
                        out_vec[2] = buf[2];
                        *out_id = (int)node;
                    }
                }
            }
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
}


extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);
extern void debug_StdPrintfDummy(void *msg);
typedef struct { int a, b, c; } S12;
extern S12 D_0027E9D0;
extern char D_0062C428[];

void actBoyRescueSrc(volatile int a0) {
    _ACTGame_SearchGObj((void *)a0, 0, 3, 0, 0, 0, 0);
    *(S12 *)((char *)GOBJ_SUB(a0) + 0x1B0) = D_0027E9D0;
    debug_StdPrintfDummy(D_0062C428);
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoySupportGBBegin);

void actBoySupportGBLoop(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void _ACTWait(int);

void actBoySupportGBEnd(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    buf[0];
    while (1) {
        _ACTWait(1);
    }
}

void func_001531E8(int *a0, int *a1) {
    int n;
    int i;
    if (a0 != 0) {
        ((int *)D_006A45A0)[0] = a0[2];
    } else {
        ((int *)D_006A45A0)[0] = 0;
    }
    i = 0;
    n = 1;
    if (a1 != i) {
        ((int *)D_006A45A0)[n] = a1[2];
    } else {
        ((int *)D_006A45A0)[n] = i;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoySupportBGBegin);

typedef struct { long long d[12]; } S60;
typedef struct { int d[6]; } S18;
extern S60 src60_a __asm__("D_0027DF10");
extern S60 dst60_a __asm__("D_006A45A0");
extern S18 src18_a __asm__("D_0027DF70");
extern S18 dst18_a __asm__("D_006A4600");

void actBoyDitch3mExec(void) {
    dst60_a = src60_a;
    dst18_a = src18_a;
}

extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);

void actBoyHangG3M(void *a0, void *a1) {
    GetCylinderCollisionWithExceptOwnCollision(a0, a1);
}

extern void SetRootMatrixWithTransOffset(void *a0);

void IsAbleBoyControl(void *a0) {
    SetRootMatrixWithTransOffset(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", ACTSearchEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", DeleteBoyWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", isLiftBoyEnable);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", BoyInfoUpdate_StageChange);

extern void ACTWay_SetBeginPositionIllegal(void *g);

void ACTChkAttackIgnore_BOY(void *g) {
    ACTWay_SetBeginPositionIllegal(g);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned long long f_8;  /* 0x08 */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
} S_006A45A0;

typedef struct {
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned char      f_14;  /* 0x14 */
    unsigned char      f_15;  /* 0x15 */
    unsigned short     f_16;  /* 0x16 */
} S_006A4600;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027E0F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552600;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005527D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552810;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A590;  /* stride 0x4 */

/* end struct shapes */

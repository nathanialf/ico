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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", UpdateGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", BoyBgaManager);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", E3_StageStartBoy);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150608);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", subBoyCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoySwim);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyWalk);

extern void BeforeFunc2(void *a0);
extern void HandCameraCorrect(void *a0, void *a1);

void actBoyRun(void *a0) {
    char buf[0x10];
    BeforeFunc2(buf);
    HandCameraCorrect(buf, a0);
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyBelift);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyRescueReady);

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

int GetBoyWeaponGObj(void) {
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
void actBoyBHang(void) {
    D_006A45A0_ll[1] |= 0x800000000LL;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyFall);

extern unsigned char D_006A45F0[];

int actBoyCall(void) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyHangBefore);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyReadyMove);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyBeslam);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyRescueSrc);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyDitch3mExec);

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

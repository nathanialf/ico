#include "common.h"

#include "ico/types.h"

typedef struct { int d[6]; } S18;
typedef struct { long long d[12]; } S60;

typedef struct { int d[2]; } HB_S8;
typedef struct {
    int f0; int f4;
    union { long long ll; int i[2]; } u8;
    char pad[0x50 - 0x10];
    char c50[8];
} RMDst;

typedef struct { char _0[0x30]; int f_30; } BoyState;

typedef struct { char pad[4]; float f4; } CCPResult;













extern void ACTWay_SetBeginPositionIllegal();
extern void SetRootMatrixWithTransOffset();
extern void GetCylinderCollisionWithExceptOwnCollision();
extern int D_006AAB40[];
extern unsigned char D_006AAB30[];
extern void WeaponCurPos(int *self, int *other, int a2);
extern long long D_006AAAE0[];
extern int *D_00631AE4;
extern void *D_00631AE8;
extern unsigned char D_00633CEC;
extern long long D_006AAAE8[];
extern void _ACTWait();
extern void funcCommonJumpDircorrect();
extern void HandCameraCorrect();
extern void BeforeFunc2();
void findChainInJump(void) {}

INCLUDE_ASM("asm/nonmatchings/src/boyact", CorrectOrient_RopeCliff);

INCLUDE_ASM("asm/nonmatchings/src/boyact", motBoyHand100);

INCLUDE_ASM("asm/nonmatchings/src/boyact", motBoyHand200);

INCLUDE_ASM("asm/nonmatchings/src/boyact", hand_heroin);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0014DF18);

INCLUDE_ASM("asm/nonmatchings/src/boyact", CheckCollisionAttr);

INCLUDE_ASM("asm/nonmatchings/src/boyact", UpdateGeo);

INCLUDE_ASM("asm/nonmatchings/src/boyact", BoyBgaManager);

INCLUDE_ASM("asm/nonmatchings/src/boyact", E3_StageStartBoy);

INCLUDE_ASM("asm/nonmatchings/src/boyact", GetChainSlope);

INCLUDE_ASM("asm/nonmatchings/src/boyact", subBoyControl);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001501A0);

extern void GetLowerPlaneCollision(char *p, float a, float b, float c, float d, float e, float f);
extern void func_00102858(int obj);

void InitSwapWeapon(void)
{
    char *base = (char *)D_006AAAE0;
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
    func_00102858(*(int *)(base + 0x20));
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00150348);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001504D8);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00150568);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001520E8);

INCLUDE_ASM("asm/nonmatchings/src/boyact", subBoyCollision);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoySwim);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00153318);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyWalk);

void actBoyRun(int a0)
{
    int buf[4];
    BeforeFunc2(buf);
    HandCameraCorrect(buf, a0);

}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001538F4);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001538F8);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyTakeWeaponReady);

void actBoyTakeWeapon(volatile unsigned int a0)
{
    volatile int local;
    int *v1 = *(int **)(a0 + 0x164);
    int a1 = v1[0x678 / 4];
    funcCommonJumpDircorrect(a0, a1 + 0x7E0);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", pullup_check_heroin_position);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00153FE8);

INCLUDE_ASM("asm/nonmatchings/src/boyact", ditch_check_heroin_position);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyPullupReady);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyPullupGo);

extern float ClearHandCameraCorrect(CCPResult *a, CCPResult *b);
extern CCPResult *ContinueCorrectPosition(void *a0);
extern void func_00243AE8(void *, CCPResult *, CCPResult *);
extern void *isysGObjSearchFromObjKindID_begin(void *);
extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *subCommonIdle(void *a0);

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
                    func_00243AE8(buf, r4, ContinueCorrectPosition(a0));
                    sign = ((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    } else {
                        dist = ((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
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
            node = isysGObjSearchFromObjKindID_begin(node);
        } while (node != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyRescueReady);

int actBoyDitch3mReady(void) {
    BoyState *p = *(BoyState **)((char *)D_00631AE4 + 0x164);
    unsigned int v = p->f_30;
    if (v >= 0x5D) {
        return 1;
    }
    if (v < 0x5B) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154444);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154448);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154520);

int GetBoyWeaponGObj(void) {
    return (int)((unsigned char)((unsigned long long)D_006AAAE8[0] >> 35)) & 1;
}

unsigned char actBoyStand(void) {
    return D_00633CEC;
}

int actBoyHang(void)
{
    int *a = (int *)D_00631AE4;
    int *b = (int *)D_00631AE8;
    int *pa, *pb, *r;
    int v;
    if (a == 0) goto err;
    if (b == 0) goto err;
    pa = (int *)a[0x164/4];
    v = pa[0x30/4];
    if (v != 0x2D) goto err;
    pb = (int *)b[0x164/4];
    if (pb[0x30/4] != v) goto err;
    r = (int *)pa[0x150/4];
    return r[2];
err:
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154644);

void func_00154648(void) {
    D_006AAAE0[1] |= 0x800000000LL;
}

void func_00154668(int *self)
{
    int new_var;
    int *d;
    int *p;
    d = (int *) D_00631AE4;
    if (0 == d) return;
    if (self == 0) return;
    new_var = 0x164;
    p = (int *) d[new_var / 4];
    WeaponCurPos(self, d, 0x16);
    new_var = self[0x8 / 4];
    p[0x140 / 4] = (int) self;
    *(int *)D_006AAAE0 = new_var;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001546BC);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001546C0);

int actBoyCall(void)
{
    if (D_006AAB30[0]) {
        return *(int *)(D_006AAB30 + 4);
    }
    return 0;
}

unsigned char actBoyItem(void) {
    return D_006AAB30[0];
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0015479C);

int *func_001547A0(void) {
    return D_006AAB40;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001547AC);

int func_001547B0(void) {
    return 24;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyHangBefore);

void actBoyReadyMove(void) {
    char *src = (char *)D_006AAB40;
    RMDst *dst = (RMDst *)D_006AAAE0;
    long long v;
    dst->u8.i[0] = *(int *)(src + 0x10);
    v = dst->u8.ll;
    v &= ~(1LL << 32); v |= (long long)(*(unsigned char *)(src + 0x14) & 1) << 32;
    v &= ~(1LL << 33); v |= (long long)(*(unsigned char *)(src + 0x15) & 1) << 33;
    v &= ~(1LL << 34); v |= (long long)(*(unsigned short *)(src + 0x16) & 1) << 34;
    dst->f4 = *(int *)(src + 0xC);
    dst->f0 = *(int *)(src + 0x8);
    dst->u8.ll = v;
    *(HB_S8 *)dst->c50 = *(HB_S8 *)(src + 0);
}

void actBoyBeslam(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh) {
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
                    func_00243AE8(buf, r4, ContinueCorrectPosition(a0));
                    sign = ((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    } else {
                        dist = ((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
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
            node = isysGObjSearchFromObjKindID_begin(node);
        } while (node != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyRescueSrc);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoySupportGBBegin);

void actBoySupportGBLoop(int x) {
    volatile int local = x;
}

void actBoySupportGBEnd(int a0)
{
    volatile int local = a0;
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154CE8);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoySupportBGBegin);

extern S18 dst18_a __asm__("D_006AAB40");
extern S60 dst60_a __asm__("D_006AAAE0");
extern S18 src18_a __asm__("D_00281BF0");
extern S60 src60_a __asm__("D_00281B90");

void actBoyDitch3mExec(void) {
    dst60_a = src60_a;
    dst18_a = src18_a;
}

void actBoyHangG3M(int a0, int a1, int a2, int a3)
{
    GetCylinderCollisionWithExceptOwnCollision(a0, a1, a2, a3);
}

void IsAbleBoyControl(int a0, int a1, int a2, int a3)
{
    SetRootMatrixWithTransOffset(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", ACTSearchEnemy);

INCLUDE_ASM("asm/nonmatchings/src/boyact", DeleteBoyWeapon);

INCLUDE_ASM("asm/nonmatchings/src/boyact", isLiftBoyEnable);

INCLUDE_ASM("asm/nonmatchings/src/boyact", BoyInfoUpdate_StageChange);

void ACTChkAttackIgnore_BOY(int a0, int a1, int a2, int a3)
{
    ACTWay_SetBeginPositionIllegal(a0, a1, a2, a3);
}


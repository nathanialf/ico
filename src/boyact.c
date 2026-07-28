#include "common.h"













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

INCLUDE_ASM("asm/nonmatchings/src/boyact", InitSwapWeapon);

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

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyBelift);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyRescueReady);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyDitch3mReady);

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

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyReadyMove);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyBeslam);

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

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyDitch3mExec);

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


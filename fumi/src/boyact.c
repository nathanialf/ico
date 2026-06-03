#include "common.h"

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", InitSwapWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", PutWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", OtherStageGirlPinchCamera_After);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150608);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", subBoyCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoySwim);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyWalk);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyRun);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyTakeWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", pullup_check_heroin_position);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", ditch_check_heroin_position);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyPullupReady);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyPullupGo);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyBelift);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyRescueReady);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyDitch3mReady);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", SetStatusBoy_OtherStageGirlPinch);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyStart);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", CorrectStickInfo);

extern unsigned long long D_006A45A8[];

int GetBoyWeaponGObj(void) {
    return (unsigned char)(D_006A45A8[0] >> 35) & 1;
}

extern unsigned char D_0062BFDC;

int actBoyStand(void) {
    return D_0062BFDC;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyHang);

extern unsigned char D_006A45A0[];

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

extern unsigned char D_006A45F0[];
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_001531E8);

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

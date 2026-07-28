#include "common.h"










extern void ACTParaStatus_Clear(volatile int *self);
extern void _ACTWait();
extern void lt_fade_status();
extern int D_00631AF4;
extern char D_00558CB8[];
extern char D_00558CA0[];
extern char D_00558C88[];
extern void debug_assertMessage();
extern char D_00632318[];
extern int *D_00631AE4;
extern char D_00632310[];
extern void dispPlane();
extern void BoxExtGeoRestore(int *self);
extern void func_001E9DF0();
extern int func_001919A0();
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTSetPositionWithFitting);

INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTSetPositionNodeWithFitting);

INCLUDE_ASM("asm/nonmatchings/src/commonact", ChangeMailInLadder);

INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTCorrectMsg);

INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTGetOrientFromIntrK);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001572F0);

INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTRunIntrCorrect);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00157BB0);

INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_WayBeginPosError);

INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_AttackFail);

void func_00157DA0(int *a0)
{
    if (a0 == 0) {
        return;
    }
    if (a0[3] != 4) {
        return;
    }
    return func_001919A0((int)a0);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_AttackRejectInQueen);

INCLUDE_ASM("asm/nonmatchings/src/commonact", GetCorrectOrientOfChain);

INCLUDE_ASM("asm/nonmatchings/src/commonact", CollisCheckInRope);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00158328);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRope);

INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnR);

INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnL);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001588F0);

void actCommonRopeClimbEnd1(int *self)
{
    int *p = (int *)self[0x59];
    int code = p[0xC];
    switch (code) {
    case 0x31:
        BoxExtGeoRestore(p[0x52]);
        break;
    case 0x33:
        func_001E9DF0(p[0x17A]);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeCliff);

INCLUDE_ASM("asm/nonmatchings/src/commonact", TestCageUpDown);

void actCommonRopeSpecial(int a0)
{
    dispPlane(a0, *(int *)(*(int *)(a0 + 0x164) + 0x678) + 0x360);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", lever_nego1);

INCLUDE_ASM("asm/nonmatchings/src/commonact", SetDirectRootPositionXZ);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00159AF0);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLever);

INCLUDE_ASM("asm/nonmatchings/src/commonact", EBRAIN_SEND_MES);

INCLUDE_ASM("asm/nonmatchings/src/commonact", DamageFunc);

INCLUDE_ASM("asm/nonmatchings/src/commonact", DownFunc);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDown);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDie);

void Cling(int *a0, int a1, int *a2)
{
    int *cur = D_00631AE4;
    int *p = (int *)a0[0x59];
    p[0x34] |= 2;
    debug_assertMessage(D_00558C88,
                  (a2 == cur) ? D_00632310 : D_00632318,
                  (a0 == cur) ? D_00632310 : D_00632318);
}

void actCommonCling(int *a0, int a1, int *a2)
{
    int *cur = D_00631AE4;
    int *p = (int *)a0[0x59];
    p[0x34] |= 8;
    debug_assertMessage(D_00558CA0,
                  (a2 == cur) ? D_00632310 : D_00632318,
                  (a0 == cur) ? D_00632310 : D_00632318);
}

void actCommonSlip(int *a0, int a1, int *a2)
{
    int *cur = D_00631AE4;
    int *p = (int *)a0[0x59];
    p[0x34] |= 0x10;
    debug_assertMessage(D_00558CB8,
                  (a2 == cur) ? D_00632310 : D_00632318,
                  (a0 == cur) ? D_00632310 : D_00632318);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonStoneDead);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonStone);

INCLUDE_ASM("asm/nonmatchings/src/commonact", BoxBarSoundOn);

INCLUDE_ASM("asm/nonmatchings/src/commonact", BoxBarSoundOff);

INCLUDE_ASM("asm/nonmatchings/src/commonact", _boxbar_set_sound);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBox);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015CD70);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBar);

void func_0015D328(void)
{
    if (D_00631AF4 == 0) {
        D_00631AF4 = 1;
        lt_fade_status(0x3A);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonJumpDircorrect);

INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonFallDircorrect);

INCLUDE_ASM("asm/nonmatchings/src/commonact", correctJumpOrientByChain);

void actCommonJump(int a0)
{
    *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670) + 0x204) -= 1;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015D488);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015D520);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015D620);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015D6D0);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015DF60);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015E448);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonFly);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLadder);

void actCommonDodge(volatile unsigned int a0)
{
    int *v1 = *(int **)((char *)a0 + 0x164);
    *(unsigned int *)((char *)v1 + 0x34) = 0xFFFFFFFFu;
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonEdgeHang);

INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonBeginReady);

INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonEndReady);

INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonEndExec);

INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonError);

INCLUDE_ASM("asm/nonmatchings/src/commonact", SetMotionDirectionSmooze);

void _ACTDebugPrint(char *self, int unused, int val) {
    *(int *)(*(char **)(self + 0x164) + 0x180) = val;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTSendMailCorrect);

INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTCommonMailTest);

void E3_LeverCheck(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    *(int *)(p + 0x250) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBecarry);

INCLUDE_ASM("asm/nonmatchings/src/commonact", subCommonIdle);

INCLUDE_ASM("asm/nonmatchings/src/commonact", ContinueCorrectPosition);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTurn);

int actCommonBackhand(int *a0)
{
    int *v0 = (int *)a0[0x164 / 4];
    int *v1 = (int *)v0[0x670 / 4];
    long x = *(unsigned int *)((char *)v1 + 0xBC);
    return ((int)x) & 1;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonSlowrun);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F248);

INCLUDE_ASM("asm/nonmatchings/src/commonact", ACT_LAYOUT_GAMEOVER);

INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTAdjustPlane);

INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTMotDirSmzDirect);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F358);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F3C0);

void func_0015F428(volatile unsigned int a0)
{
    volatile int local;
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x20);
    *p |= 0x40000;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F450);

void actCommonRevive(volatile unsigned int a0)
{
    volatile int local;
    ACTParaStatus_Clear(a0);
}

void actCommonReviveAir(int x) {
    volatile int local = x;
}

void actCommonPlay(volatile unsigned int a0)
{
    volatile int local;
    ACTParaStatus_Clear(a0);
}

void actCommonOne(volatile unsigned int self)
{
    volatile int local;
    unsigned int a, b;
    a = self;
    b = self;
    *(int *)(*(int *)((char *)*(int *)(a + 0x164) + 0x670) + 0x2A0) = -1;
    *(int *)(*(int *)((char *)*(int *)(b + 0x164) + 0x670) + 0x2A4) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDelete);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F578);

void func_0015F5D0(volatile unsigned int a0)
{
    volatile int local;
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x20);
    *p |= 0x40000;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F5F8);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F650);


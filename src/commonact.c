#include "common.h"

typedef struct { int w[6]; } SlowrunRec;










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

extern void *ContinueCorrectPosition(void *a0);
extern void CylinderCollision(void *a0, void *a1);

void WithMailFunc_WayBeginPosError(void *a0, void *a1) {
    void *ret = ContinueCorrectPosition(a0);
    *(float *)((char *)a1 + 4) = *(float *)((char *)ret + 4);
    CylinderCollision(a0, a1);
}

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

extern char *D_00631AE8;
extern char D_006322E8[];
extern void UpdatePointBlur(void *a0, void *a1, void *a2);
extern void func_00157DA0__p4(void *a0, int a1) __asm__("func_00157DA0");

void WithMailFunc_AttackRejectInQueen(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    int v;
    debug_assertMessage(D_006322E8);
    if (a0 != (void *)D_00631AE8) {
        char *q = *(char **)((char *)a0 + 0x164);
        *(float *)(p + 0x1D0) -= (float)*(int *)(q + 0x1C0);
    }
    v = *(int *)((char *)a0 + 0xC);
    if (v == 4) {
        char *s;
        func_00157DA0__p4(a0, 5);
        s = *(char **)(*(char **)((char *)a0 + 0x164) + 0x670);
        UpdatePointBlur(a0, s + 0xE0, s + 0xF0);
    }
}

extern void func_00157DA0__p4(void *a0, int a1) __asm__("func_00157DA0");

void GetCorrectOrientOfChain(void *a0)
{
    WithMailFunc_AttackRejectInQueen(a0);
    if (*(int *)((char *)a0 + 0xC) == 1) {
        void *p = *(void **)((char *)a0 + 0x164);
        func_00157DA0__p4(*(void **)((char *)p + 0x1A0), 6);
    }
}

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

extern void func_00104F20(void);
extern void func_00105268(void);
extern int func_00105278(void);
extern void func_001052A8(void *a0);
extern void func_0010F630(void);
extern void func_00118678(int a0);
extern void gif_SpriteOffset(int a0);
extern void reg_dispBoxLine(void *a0, int a1, int a2, float a3);

void actCommonLever(void *a0, void *a1, float f) {
    func_00104F20();
    func_00118678(func_00105278());
    gif_SpriteOffset(0xB);
    func_001052A8(a0);
    reg_dispBoxLine(a1, 4, 4, f);
    func_0010F630();
    func_00105268();
}

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

extern void setNodePursueParticleEffectWithUpperLimit(int a0, int a1, float a2);

void funcCommonJumpDircorrect(int a0, int a1) {
    setNodePursueParticleEffectWithUpperLimit(a0, a1, 30.0f);
}

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

extern char D_00558C18[];
extern void _ACTWait__p4(int a0) __asm__("_ACTWait");

void funcCommonBeginReady(volatile int a0) {
    debug_assertMessage(D_00558C18);
    _ACTWait__p4(0);
}

extern char D_00558C38[];

void funcCommonEndReady(volatile int a0) {
    debug_assertMessage(D_00558C38);
    _ACTWait__p4(0);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonEndExec);

extern int CanWallLeverPull(int a0, int a1);
extern char D_00632330[];

void funcCommonError(volatile int a0) {
    char *state = *(char **)(a0 + 0x164);
    int v = *(int *)(state + 0x5EC);
    _ACTWait(0x1E);
    CanWallLeverPull(v, -1);
    debug_assertMessage(D_00632330);
    _ACTWait(0);
}

extern char D_00632338[];

void SetMotionDirectionSmooze(volatile int a0) {
    char *state = *(char **)(a0 + 0x164);
    int v = *(int *)(state + 0x5EC);
    _ACTWait(0x1E);
    CanWallLeverPull(v, 1);
    debug_assertMessage(D_00632338);
    _ACTWait(0);
}

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

extern SlowrunRec D_00292540[];

void actCommonSlowrun(int a0, int a1) {
    D_00292540[a0].w[2] = a1;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F248);

extern void func_00243B18(void *a0, float f);

void ACT_LAYOUT_GAMEOVER(void *a0) {
    int local[4];
    func_00243B18(local, -1.0f);
    dispPlane(a0, local);
}

extern void func_00240038_p(void *a0, int a1, float f) __asm__("func_00243B18");

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

extern void actCommonRopeCliff(int a0, int a1);

void actCommonDelete(volatile int a0) {
    actCommonRopeCliff(a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F578);

void func_0015F5D0(volatile unsigned int a0)
{
    volatile int local;
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x20);
    *p |= 0x40000;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F5F8);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F650);


#include "common.h"

typedef struct { int _0, _4, _8, _C, _10; } ChainEntry;

typedef union { float f; int i; } FI;

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
extern char *D_00631AE4__p4 __asm__("D_00631AE4");
extern void weaponFumbleSE(void *);

void ACTSetPositionWithFitting(char *self) {
    char *s164 = *(char **)(self + 0x164);
    int *p2C = *(int **)(s164 + 0x2C);
    int a1;
    if (p2C != 0) {
        a1 = *p2C;
    } else {
        a1 = *(int *)(s164 + 0x5D0);
    }
    if (self == D_00631AE4__p4) {
        char *p130 = *(char **)(s164 + 0x140);
        if (p130 != 0) {
            char *p15C = *(char **)(p130 + 0x15C);
            *(int *)(p15C + 0x5F4) = a1;
            weaponFumbleSE(p130);
        }
    }
}

extern int D_00631990;
extern int D_00632D90;
extern void func_001F2500(int a0);
extern int iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern int isysGObjSearchFromObjLayoutID(int a0);

void ACTSetPositionNodeWithFitting(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    int v = *(int *)(p + 0x140);
    void *obj;
    if (v != 0) {
        func_001F2500(v);
        *(int *)(p + 0x140) = 0;
    }
    if (D_00631990 == 0x53 || D_00632D90 != 0) {
        obj = (void *)isysGObjSearchFromObjLayoutID(0x35);
        if (obj != 0) {
            iosOmBeforeFuncStandard(obj, 0xD, a0);
        }
    }
}

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

extern void ActPara_GetDefTbl(int a0, int a1);
extern void BoxBarSoundOn(void *a0, int a1);
extern char D_00558978[];
extern char D_00552C78[], D_00558988[];
extern int D_00632CBC;
extern void _ACTWait__p4(int a0) __asm__("_ACTWait");
extern void actCommonOne__p4(volatile int a0) __asm__("actCommonOne");
extern void func_0015D328(void);
extern void traceLine(int a0, int a1, int a2, void *a3, int a4);

void motCommonRopeTurnL(volatile int self) {
    char *s164 = *(char **)(self + 0x164);
    char *o0 = *(char **)(*(char **)(self + 0x164) + 0x670);
    *(int *)(s164 + 0x14) = (int)actCommonOne__p4;
    *(int *)(o0 + 0x2A0) = 0;
    for (;;) {
        if (D_00632CBC & 1) {
            traceLine(0xA, 0xAA, 0x0FFFFFFF, D_00558978,
                      *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0xCC));
            if (D_00632CBC & 1) {
                traceLine(0xA, 0xB4, 0x0FFFFFFF, D_00558988,
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
            BoxBarSoundOn((void *)self, 0xB7);
            *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C) = 0;
        }
        if (*(int *)(s164 + 0x48) >= 0x3D) {
            if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C) >= 3) {
                func_0015D328();
                _ACTWait__p4(0);
            }
        }
        BoxBarSoundOn((void *)self, 0x69);
        _ACTWait__p4(1);
    }
}

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

extern int iosOmBeforeFuncStandard(void *a0, int a1, void *a2);

void BoxBarSoundOn(void *a0, int a1) {
    char *p = *(char **)((char *)a0 + 0x164);
    if ((a1 == 0xA8 || a1 == 0xAD) && *(int *)((char *)a0 + 0xC) == 1) {
        unsigned long long f470 = *(unsigned long long *)(p + 0x470);
        if ((unsigned int)(f470 >> 61) & 1) {
            if ((unsigned int)(*(unsigned long long *)(p + 0x480) >> 61) & 1) {
                a1 = 0xA9;
                goto done;
            }
        }
        if ((unsigned int)(f470 >> 59) & 1) {
            if ((unsigned int)(*(unsigned long long *)(p + 0x480) >> 59) & 1)
                a1 = 0xAA;
        }
    }
done:
    iosOmBeforeFuncStandard(a0, a1, a0);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", BoxBarSoundOff);

extern float D_00630CB8;
extern int HandCameraCorrect(void *a0, void *a1);
extern void func_001945B8(void *a0, float a1);
extern void *subCommonIdle__p4(int a0) __asm__("subCommonIdle");

int _boxbar_set_sound(char *a0) {
    float buf[3];
    int v;
    buf[0] = *(float *)((char *)subCommonIdle__p4(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x0);
    buf[1] = *(float *)((char *)subCommonIdle__p4(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x4);
    buf[2] = *(float *)((char *)subCommonIdle__p4(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x8);
    func_001945B8(buf, D_00630CB8);
    return HandCameraCorrect(subCommonIdle__p4(a0), buf) < 0
               ? -HandCameraCorrect(subCommonIdle__p4(a0), buf) < 0x2D
               : HandCameraCorrect(subCommonIdle__p4(a0), buf) < 0x2D;
}

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

extern char D_0055DA10_a[] __asm__("D_00565060");
extern int actCommonStoneDead(void *a0, float *a1, float a2);

int funcCommonFallDircorrect(void *a0, float *pos) {
    char *s164 = *(char **)((char *)a0 + 0x164);
    char *rec = D_0055DA10_a;
    ((FI *)(s164 + 0x110))->f = pos[0];
    ((FI *)(s164 + 0x114))->f = pos[1];
    ((FI *)(s164 + 0x118))->f = pos[2];
    rec = rec - (-(*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) * 0x190));
    return actCommonStoneDead(a0, pos, (float)*(int *)(rec + 0x138));
}

extern ChainEntry D_0028CDD0[];
extern SlowrunRec D_00292540[];

void correctJumpOrientByChain(void *a0) {
    char *s164 = *(char **)((char *)a0 + 0x164);
    char *s15C = *(char **)((char *)a0 + 0x15C);
    int v = *(int *)(s15C + 0x4A0);
    int idx = *(int *)(s164 + 0x44);
    int e4 = D_0028CDD0[idx]._4;
    int e8 = D_0028CDD0[idx]._8;
    int eC = D_0028CDD0[idx]._C;
    int e10 = D_0028CDD0[idx]._10;
    int i;
    if (v != 0x43E) {
        D_00292540[e4].w[2] = v;
        D_00292540[e8].w[2] = v;
        i = eC;
        while (i < e10) {
            D_00292540[i].w[0] = v;
            i++;
        }
    }
}

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

extern char D_00558848[];
extern int isBottomOfChain(int a0, int a1);

void ACTSendMailCorrect(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    int self;
    debug_assertMessage(D_00558848);
    isBottomOfChain(*(int *)(s + 0x180), a0);
    self = a0;
    *(int *)(s + 0x184) = *(int *)(s + 0x180);
    *(int *)(*(int *)(self + 0x15C) + 0x420) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTCommonMailTest);

void E3_LeverCheck(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    *(int *)(p + 0x250) = 0;
}

extern void *ExecMotionOrient(void *a0, void *a1, void *a2);

int actCommonBecarry(void *a0, void *a1) {
    char *s = *(char **)((char *)a0 + 0x164);
    void *r = ExecMotionOrient(a0, a1, s + 0x610);
    *(void **)(s + 0x120) = r;
    return *(int *)((char *)r + 0xC) != 0;
}

extern char D_006AAB60[];
extern int GetOrientOfWallOfGObj(void *a0, void *a1);
extern void InitKeyInput(void *a0, void *a1);

void *subCommonIdle(char *a0) {
    char *p;
    if (a0 != D_00631AE4__p4 && a0 != D_00631AE8 && *(int *)(a0 + 0xC) != 4) {
        InitKeyInput(D_006AAB60, a0);
        return D_006AAB60;
    }
    p = *(char **)(a0 + 0x164) + 0xE0;
    GetOrientOfWallOfGObj(p, a0);
    return p;
}

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


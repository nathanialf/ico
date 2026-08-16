#include "common.h"

extern void ChangeFieldCollisionDebugMode(void *a0);
extern void ActOrientTest(void *a0, void *a1, int a2);
extern void dispPlane();
/* func_00243B18 with its 3-parameter signature.  ACT_LAYOUT_GAMEOVER below
 * calls the same routine with only two arguments and the ROM proves it (no
 * $5 setup at 0x15F2B0), so both prototypes were live in the original
 * sources that splat merged into src/commonact. */
extern void func_00243B18_3(void *dst, void *src, float s) __asm__("func_00243B18");

static __inline__ int func_0015C418_probe(char *buf, char *obj) {
    ActOrientTest(buf, obj, 0x2C);
    ActOrientTest(buf + 0x10, obj, 0x33);
    *(float *)(buf + 0x14) -= 5.0f;
    ChangeFieldCollisionDebugMode(buf);
    return *(int *)(buf + 0x94) != 0;
}

static __inline__ void func_0015C818_disp(int obj) {
    int buf[4];
    func_00243B18_3(buf, *(char **)(obj + 0x164) + 0x4A0, -1.0f);
    dispPlane((void *)obj, buf);
}

typedef struct { char _0[0xBC]; unsigned int f_BC; char _padc0[0x144]; int f_204; char _pad208[0x48]; int f_250; } CBrain670;
typedef struct { char _0[0x30]; int f_30; unsigned int f_34; char _pad38[0x638]; CBrain670 *p_670; char _pad674[4]; void *p_678; } CommonActState;

typedef struct { int _0, _4, _8, _C, _10; } ChainEntry;

typedef union { float f; int i; } FI;

typedef struct { int w[6]; } SlowrunRec;










extern void ACTParaStatus_Clear(volatile int *self);
extern void _ACTWait();
extern void lt_fade_status();
extern int D_00631AF4;
extern const char D_00558CB8[];
extern const char D_00558CA0[];
extern const char D_00558C88[];
extern void debug_assertMessage();
extern char D_00632318[];
extern int *D_00631AE4;
extern char D_00632310[];
extern void dispPlane();
extern void BoxExtGeoRestore(int *self);
extern void func_001E9DF0();
extern int func_001919A0();
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
    if (self == (char *)D_00631AE4) {
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
ASM_LIT4_SLOT(D_00630C28, 3.14159274f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTCorrectMsg);

/* commonact .rodata run 0x558848..0x558DC0 — byte-verified against baseelf;
 * defs interleave with INCLUDE_ASM stubs so .o section order == VMA order */
const char D_00558848[0x18] = "common rope after func\n";
const char D_00558860[0x10] = "src/commonact.c";
const char D_00558870[0x10] = "ROPE_GOBJ!=NULL";

INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTGetOrientFromIntrK);
ASM_LIT4_SLOT(D_00630C2C, 3.14159274f);

const unsigned int D_005588A0[0x4] = { 0x00000000, 0x00000000, 0xC1A00000, 0x3F800000 };
const unsigned int D_005588B0[0x4] = { 0x00000000, 0x00000000, 0x41A00000, 0x3F800000 };
const char D_005588C0[0x18] = "enter actCommonPlay\n";
const char D_005588D8[0x18] = "enter actCommonDamage\n";
const char D_005588F0[0x18] = "enter actCommonDown\n";

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00156BA0);
ASM_LIT4_SLOT(D_00630C30, 3.14159274f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00156CF0);
ASM_LIT4_SLOT(D_00630C34, 3.14159274f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00156E40);
ASM_LIT4_SLOT(D_00630C38, 3.14159274f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00157160);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001572F0);

INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTRunIntrCorrect);
ASM_LIT4_SLOT(D_00630C3C, 0.785398185f);
ASM_LIT4_SLOT(D_00630C40, 3.14159274f);

extern void IsWallLeverStatus(void *a0, void *a1, int a2);
extern void func_001C0AE8(void *a0, void *a1, int a2);

void func_00157BB0(void *a0, void *a1) {
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
    func_001C0AE8(a1, a0, 0x16);
    return;
lever:
    IsWallLeverStatus(a1, a0, 0x16);
}

extern void *ContinueCorrectPosition(void *a0);
extern void CylinderCollision(void *a0, void *a1);

void WithMailFunc_WayBeginPosError(void *a0, void *a1) {
    void *ret = ContinueCorrectPosition(a0);
    *(float *)((char *)a1 + 4) = *(float *)((char *)ret + 4);
    CylinderCollision(a0, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_AttackFail);
ASM_LIT4_SLOT(D_00630C44, 0.2f);

void func_00157DA0(a0)
int *a0;
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
extern void func_00157DA0();

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
        func_00157DA0(a0, 5);
        s = *(char **)(*(char **)((char *)a0 + 0x164) + 0x670);
        UpdatePointBlur(a0, s + 0xE0, s + 0xF0);
    }
}


void GetCorrectOrientOfChain(void *a0)
{
    WithMailFunc_AttackRejectInQueen(a0);
    if (*(int *)((char *)a0 + 0xC) == 1) {
        void *p = *(void **)((char *)a0 + 0x164);
        func_00157DA0(*(void **)((char *)p + 0x1A0), 6);
    }
}

extern void _ACTWait(int a0);
extern void BoxBarSoundOn(void *a0, int a1);
extern void func_00181F38(float a0);
extern void GetCorrectOrientOfChain(void *a0);
extern void isExistEnemyParticle(char *a0);
extern void func_00157BB0(void *a0, void *a1);
extern void ReviveEnemyParticle(void *a0, int a1);
extern void func_0015F450();

void CollisCheckInRope(volatile int a0) {
    int buf[4];
    char *s164 = *(char **)(a0 + 0x164);
    char *self;
    debug_assertMessage(D_005588F0);
    self = (char *)a0;
    *(int *)(s164 + 0x18) = (int)func_0015F450;
    if (self == (char *)D_00631AE4) {
        func_00181F38(1000.0f);
    }
    if ((char *)a0 == D_00631AE8) {
        func_00243B18_3(buf, *(char **)(a0 + 0x164) + 0x1B0, -1.0f);
        dispPlane((void *)a0, buf);
    } else {
        dispPlane((void *)a0, *(char **)(a0 + 0x164) + 0x1B0);
    }
    GetCorrectOrientOfChain((void *)a0);
    for (;;) {
        if (*(int *)(a0 + 0xC) != 4) {
            *(char *)(*(char **)(a0 + 0x164) + 0x1CA) = 1;
        }
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00157FA0);
ASM_LIT4_SLOT(D_00630C48, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00158328);

const char D_00558960[0x18] = "enter actCommonRevive\n";
const char D_00558978[0x10] = "count =(%d)\n";
const char D_00558988[0x10] = "level =(%d)\n";

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRope);

INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnR);

extern int D_006325B4;
extern int D_00633060;
extern void SetCageFixGeometry(void *a0);
extern void actBoyHangG3M(void *a0, void *a1);
extern void darkVolume(void *a0);
extern void func_0015D328(void);
extern void func_001947D0(void *a0, void *a1, void *a2);

void func_00158690(volatile int a0) {
    char buf10[0x10];
    char buf20[0x10];
    if (*(int *)(*(int *)(a0 + 0x164) + 0xC8) == 0x22) {
        SetCageFixGeometry((void *)a0);
        darkVolume(buf10);
        func_001947D0(buf20, buf10, ContinueCorrectPosition((void *)a0));
        dispPlane((void *)a0, buf20);
    } else {
        actBoyHangG3M((void *)a0, ContinueCorrectPosition((void *)a0));
        dispPlane((void *)a0, (char *)*(void **)(a0 + 0x164) + 0x1B0);
        *(int *)(a0 + 0x50) = 0;
    }
    D_00633060 = 0;
    D_006325B4 = 1;
    _ACTWait(0x12C);
    func_0015D328();
    _ACTWait(0);
}

extern void ActPara_GetDefTbl(int a0, int a1);
extern void BoxBarSoundOn(void *a0, int a1);
extern char D_00552C78[];
extern int D_00632CBC;
extern void actCommonOne();
extern void func_0015D328(void);
extern void traceLine(int a0, int a1, int a2, void *a3, int a4);

void motCommonRopeTurnL(volatile int self) {
    char *s164 = *(char **)(self + 0x164);
    char *o0 = *(char **)(*(char **)(self + 0x164) + 0x670);
    *(int *)(s164 + 0x14) = (int)actCommonOne;
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
                _ACTWait(0);
            }
        }
        BoxBarSoundOn((void *)self, 0x69);
        _ACTWait(1);
    }
}

extern void BoxGeoRestore(int a0, int a1);
extern void func_001E9DE8(int a0);

void func_001588F0(void *a0) {
    char *s164 = *(char **)((char *)a0 + 0x164);
    int m = *(int *)(s164 + 0x30);
    if (m == 0x31) goto h31;
    if (m == 0x33) goto h33;
    return;
h31:
    BoxGeoRestore(*(int *)(s164 + 0x148), *(int *)(s164 + 0x34));
    return;
h33:
    func_001E9DE8(*(int *)(s164 + 0x5E8));
}

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
ASM_LIT4_SLOT(D_00630C4C, 0.3f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00158F10);
ASM_LIT4_SLOT(D_00630C50, 0.3f);


void func_00159220(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    void *x = p->p_678;
    dispPlane(a0, (char *)x + 0x350);
}

void actCommonRopeSpecial(int a0)
{
    dispPlane(a0, *(int *)(*(int *)(a0 + 0x164) + 0x678) + 0x360);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", lever_nego1);

INCLUDE_ASM("asm/nonmatchings/src/commonact", SetDirectRootPositionXZ);
ASM_LIT4_SLOT(D_00630C54, 0.1f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001595D0);

const char D_005589A8[0x28] = "\033[36mEMERGENCY WITH DANGER LOOP\033[m\n";
/* zero table with one 50.0f at +0x70 */
const unsigned int D_005589D0[0x30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x42480000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const char D_00558A90[0x30] = "EMERGENCY COMPLETE CHECK : SPEEDSQ:%f LENSQ:%f\n";
const char D_00558AC0[0x18] = "EMERGENCY BY NOMOVE";
const char D_00558AD8[0x18] = "EMERGENCY BY TIMEOUT";
const char D_00558AF0[0x20] = "EMERGENCY BY DANGER LOOP";

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
ASM_LIT4_SLOT(D_00630C58, 10000.0f);
ASM_LIT4_SLOT(D_00630C5C, 0.005f);
ASM_LIT4_SLOT(D_00630C60, 90000.0f);
ASM_LIT4_SLOT(D_00630C64, 0.05f);
ASM_LIT4_SLOT(D_00630C68, 0.005f);
ASM_LIT4_SLOT(D_00630C6C, 360000.0f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", DownFunc);
ASM_LIT4_SLOT(D_00630C70, 10000.0f);

const char D_00558B80[0x20] = "enter actCommonCliffdown\n";
const char D_00558BA0[0x10] = "act main shoal\n";
const char D_00558BB0[0x18] = "enter actCommonSwim\n";
const char D_00558BC8[0x18] = "enter actCommonDodge\n";
const char D_00558BE0[0x18] = "enter actCommonGuard\n";
const char D_00558BF8[0x20] = "enter motCommonHang None\n";
const char D_00558C18[0x20] = "enter motCommonHang Wall\n";
const char D_00558C38[0x20] = "enter motCommonHang Cliff\n";
const char D_00558C58[0x18] = "enter motCommonNull\n";
const char D_00558C70[0x18] = "ready begin %s to %s\n";
const char D_00558C88[0x18] = "ready end %s to %s\n";
const char D_00558CA0[0x18] = "exec end %s to %s\n";
const char D_00558CB8[0x18] = "????error %s to %s\n";

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDown);
ASM_LIT4_SLOT(D_00630C74, 0.005f);
ASM_LIT4_SLOT(D_00630C78, 0.92f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015ADF0);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDie);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015B4B8);

extern char D_00632310[];
extern char D_00632318[];

void func_0015B620(int a0, int a1, int a2) {
    char *msg = D_00558C70;
    int *m = *(int **)((char *)a0 + 0x164);
    int g = (int)D_00631AE4;
    char *s1;
    char *s2;
    *(int *)((char *)m + 0xD0) |= 1;
    s1 = (a2 == g) ? D_00632310 : D_00632318;
    s2 = (a0 == g) ? D_00632310 : D_00632318;
    debug_assertMessage(msg, s1, s2);
}

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
ASM_LIT4_SLOT(D_00630C7C, 3.14159274f);
ASM_LIT4_SLOT(D_00630C80, 3.14159274f);

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
ASM_LIT4_SLOT(D_00630C84, 0.1f);
ASM_LIT4_SLOT(D_00630C88, 0.1f);
ASM_LIT4_SLOT(D_00630C8C, 0.1f);
ASM_LIT4_SLOT(D_00630C90, 0.1f);
ASM_LIT4_SLOT(D_00630C94, 0.1f);
ASM_LIT4_SLOT(D_00630C98, 0.99f);
ASM_LIT4_SLOT(D_00630C9C, 0.1f);
ASM_LIT4_SLOT(D_00630CA0, 0.99f);
ASM_LIT4_SLOT(D_00630CA4, 0.1f);
ASM_LIT4_SLOT(D_00630CA8, 0.1f);
ASM_LIT4_SLOT(D_00630CAC, 0.99f);
ASM_LIT4_SLOT(D_00630CB0, 0.1f);
ASM_LIT4_SLOT(D_00630CB4, 0.99f);

extern int HandCameraCorrect(void *a0, void *a1);
extern void func_001945B8(void *a0, float a1);
extern void *subCommonIdle(char *a0);

int _boxbar_set_sound(char *a0) {
    float buf[3];
    int v;
    buf[0] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x0);
    buf[1] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x4);
    buf[2] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x8);
    func_001945B8(buf, -1.5707964f);
    return HandCameraCorrect(subCommonIdle(a0), buf) < 0
               ? -HandCameraCorrect(subCommonIdle(a0), buf) < 0x2D
               : HandCameraCorrect(subCommonIdle(a0), buf) < 0x2D;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBox);
ASM_LIT4_SLOT(D_00630CBC, 4225.0f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015C7C8);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015CD70);

/* 8-byte double 0.3: a C def would land in .sdata under -G8 */
INCLUDE_RODATA("asm/nonmatchings/src/commonact", D_00558DB8);

INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBar);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015D0B0);
ASM_LIT4_SLOT(D_00630CC0, 0.2f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015D1F8);
ASM_LIT4_SLOT(D_00630CC4, 0.2f);
ASM_LIT4_SLOT(D_00630CC8, 0.1f);

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

/* the per-character status table: stride 0x190 */
typedef struct {
    char _p0[0x138];
    int f_138;
    char _p1[0x4C];
    int f_188;
    char _p2[4];
} ACTCharStat;
extern ACTCharStat D_00565060[];
extern int actCommonStoneDead(void *a0, float *a1, float a2);

int funcCommonFallDircorrect(void *a0, float *pos) {
    char *s164 = *(char **)((char *)a0 + 0x164);
    ((FI *)(s164 + 0x110))->f = pos[0];
    ((FI *)(s164 + 0x114))->f = pos[1];
    ((FI *)(s164 + 0x118))->f = pos[2];
    return actCommonStoneDead(a0, pos,
        (float)D_00565060[*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0)].f_138);
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

extern void ACTParaStatus_Exec(void *a0);
extern void ResetEnemyEye(void *a0);
extern void actCommonPlay();

void func_0015D520(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    debug_assertMessage(D_00558960);
    ACTParaStatus_Exec((void *)a0);
    {
        void *self = (void *)a0;
        *(int *)(s164 + 0x14) = (int)actCommonPlay;
        CylinderCollision(self, s164 + 0x160);
    }
    isExistEnemyParticle((char *)a0);
    for (;;) {
        ResetEnemyEye((void *)a0);
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern void isExistEnemyParticle(char *a0);

void func_0015D5A0(volatile int a0) {
    CylinderCollision((void *)a0, *(char **)(a0 + 0x164) + 0x160);
    isExistEnemyParticle((char *)a0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xD2);
        _ACTWait(1);
    }
}


void func_0015D5F0(volatile int a0) {
    debug_assertMessage(D_005588C0);
    _ACTWait(0);
}

extern int D_00274EC0[];

void func_0015D620(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    if (*(int *)(s164 + 0xC8) == 0x182 && (*(int *)(s164 + 0x128) & 1)) {
        *(short *)(s164 + 0x12A) =
            (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] * 5;
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

void func_0015D6B0(volatile int a0) {
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015D6D0);

extern int GetDifferenceFromWallUpperPlane(void *a0);
extern void initializeQueenzSword(int a0);

void func_0015D7E8(volatile int a0) {
    char *s0 = *(char **)(a0 + 0x164);
    int flag = 0;
    dispPlane((void *)a0, s0 + 0x4C0);
    for (;;) {
        if (GetDifferenceFromWallUpperPlane((void *)a0) && flag == 0) {
            initializeQueenzSword(*(int *)(s0 + 0x140));
            flag = 1;
        }
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern void func_001F1868(int a0);

void func_0015D860(volatile int a0) {
    char *s0 = *(char **)(a0 + 0x164);
    int flag = 0;
    dispPlane((void *)a0, s0 + 0x4C0);
    for (;;) {
        if (GetDifferenceFromWallUpperPlane((void *)a0) && flag == 0) {
            func_001F1868(*(int *)(s0 + 0x604));
            flag = 1;
        }
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

void func_0015D8D8(volatile int a0) {
    char *s0 = *(char **)(a0 + 0x164);
    int flag = 0;
    dispPlane((void *)a0, s0 + 0x4D0);
    for (;;) {
        if (GetDifferenceFromWallUpperPlane((void *)a0) && flag == 0) {
            func_001F1868(*(int *)(s0 + 0x608));
            flag = 1;
        }
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

void func_0015D950(volatile int a0) {
    _ACTWait(0x28);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

void func_0015D988(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    funcCommonJumpDircorrect(a0, (int)s->p_678 + 0x7E0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}


void func_0015D9D0(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    debug_assertMessage(D_00558B80);
    dispPlane((void *)a0, s + 0x4B0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

typedef struct { int a, b, c; } Vec12;
extern void func_00243AD0(void *a0, void *a1, void *a2);
extern int ACTGame_StageChangeGObjID(void *a0, void *a1, void *a2, void *a3);
extern int func_00168A80(int a0, int a1);

void func_0015DA20(volatile int a0) {
    int buf10[4];
    int buf20[4];
    int buf30[4];
    int buf40[4];
    int buf50[4];
    for (;;) {
        ActOrientTest(buf20, (void *)a0, 0x2C);
        func_00243B18_3(buf40, subCommonIdle(a0), 50.0f);
        func_00243AD0(buf30, buf20, buf40);
        if (ACTGame_StageChangeGObjID(buf20, buf30, buf50, buf10)) {
            if (func_00168A80(buf50[0], 0x3000)) {
                BoxBarSoundOn((void *)a0, 0x87);
                *(Vec12 *)(*(int *)(*(char **)(a0 + 0x164) + 0x678) + 0x3B4) =
                    *(Vec12 *)buf10;
            }
            if (func_00168A80(buf50[0], 0x400)) {
                BoxBarSoundOn((void *)a0, 0x86);
                *(Vec12 *)(*(int *)(*(char **)(a0 + 0x164) + 0x678) + 0x3A8) =
                    *(Vec12 *)buf10;
            }
        }
        BoxBarSoundOn((void *)a0, 0xD2);
        _ACTWait(1);
    }
}

extern int ForMotionViewer_GetCurrentMotion(void *a0, int a1);

void func_0015DB58(volatile int a0) {
    for (;;) {
        if (ForMotionViewer_GetCurrentMotion((void *)a0, 0x3000) == 0 &&
            ForMotionViewer_GetCurrentMotion((void *)a0, 0x400) == 0) {
            BoxBarSoundOn((void *)a0, 0xD2);
        }
        _ACTWait(1);
    }
}

void func_0015DBB0(volatile int a0) {
    for (;;) {
        float v;
        BoxBarSoundOn((void *)a0, 0x13A);
        v = *(float *)(*(char **)(a0 + 0x15C) + 0x5E8);
        if (250.0f < -v) {
            BoxBarSoundOn((void *)a0, 0x18);
        }
        _ACTWait(1);
    }
}

extern void GetOrientOfCliffOfGObj(void *a0, void *a1, float f0, float f1);
extern void actBoyBelift(void *a0, void *a1, void *a2);

void func_0015DC10(volatile int a0) {
    int local20 = 0;
    char buf[0x10];
    void *s17 = *(void **)(a0 + 0x164);
    debug_assertMessage(D_00558BC8);
    if (*(int *)(a0 + 0xC) == 1) {
        actBoyBelift((void *)a0, &local20, buf);
    } else {
        void *r1 = ContinueCorrectPosition((char *)D_00631AE4);
        void *r2v = ContinueCorrectPosition((void *)a0);
        func_001947D0((char *)s17 + 0x110, r1, r2v);
        dispPlane((void *)a0, (char *)s17 + 0x110);
    }
    for (;;) {
        if (local20 != 0) {
            GetOrientOfCliffOfGObj((void *)a0, buf, 10.0f, 90.0f);
        }
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

void func_0015DCE8(volatile int a0) {
    int local20 = 0;
    int local10[3];
    char *s1 = *(char **)(a0 + 0x164);
    if (*(int *)(a0 + 0xC) == 1) {
        actBoyBelift((void *)a0, &local20, local10);
    } else {
        void *r1, *r2;
        s1 += 0x110;
        r1 = ContinueCorrectPosition((char *)D_00631AE4);
        r2 = ContinueCorrectPosition((void *)a0);
        func_001947D0(s1, r1, r2);
        dispPlane((void *)a0, s1);
    }
    for (;;) {
        _ACTWait(1);
    }
}

extern void func_0014B5B8(void *a0);

void func_0015DD78(volatile int a0) {
    char *base = *(char **)(a0 + 0x164);
    debug_assertMessage(D_00558BE0);
    dispPlane((void *)a0, *(char **)(a0 + 0x164) + 0x1B0);
    if (*(int *)(a0 + 0xC) == 4) {
        func_00157DA0((void *)a0, 6);
        func_0014B5B8((void *)a0);
    }
    iosOmBeforeFuncStandard((char *)D_00631AE4, 0x10C, (void *)a0);
    if (*(int *)(base + 0xC8) == 0x10A) {
        actBoyHangG3M((void *)a0, ContinueCorrectPosition((void *)a0));
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern void brainInitGirlSet(void);
extern void func_00181F38(float a0);

void func_0015DE38(volatile int a0) {
    if ((char *)a0 == (char *)D_00631AE4) {
        func_00181F38(1000.0f);
    }
    for (;;) {
        if ((char *)a0 == (char *)D_00631AE4 && D_00631AE8 != 0) {
            brainInitGirlSet();
            iosOmBeforeFuncStandard(D_00631AE8, 0x3A, (void *)a0);
        }
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}


void func_0015DEB0(volatile int a0) {
    debug_assertMessage(D_005588D8);
    dispPlane((void *)a0, *(char **)(a0 + 0x164) + 0x1B0);
    WithMailFunc_AttackRejectInQueen((void *)a0);
    if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x1DC) == 3) {
        _ACTWait(0x168);
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}


void func_0015DF30(volatile int a0) {
    debug_assertMessage(D_00558BA0);
    _ACTWait(0);
}


void func_0015DF60(volatile int a0) {
    debug_assertMessage(D_00558BB0);
    for (;;) {
        _ACTWait(1);
    }
}

extern void _DoAwaitGirl(void);
extern void func_001BC0B8(void *a0, void *a1);
extern void func_001BC4B8(void *a0, void *a1);
extern void func_00102C10(void *a0, int a1, void *a2, float f);

static __inline__ void func_0015DF88_mark(void *self2, int s17, int m) {
    int buf[4];
    if (m >= 0x16) {
        if (m < 0x18) {
            func_001BC0B8(buf, (void *)s17);
        } else if (m < 0x1A) {
            func_001BC4B8(buf, (void *)s17);
        }
    }
    func_00102C10(self2, 0x16, buf, 0.2f);
}

void func_0015DF88(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    int self = a0;
    int s17 = *(int *)(s164 + 0x5EC);
    *(int *)(s164 + 0x14) = (int)_DoAwaitGirl;
    func_0015C818_disp(self);
    for (;;) {
        if (s17 != 0) {
            if (*(int *)(*(int *)(a0 + 0x15C) + 0x604) != 0) {
                int m = *(int *)(s17 + 0xC);
                void *self2 = (void *)a0;
                func_0015DF88_mark(self2, s17, m);
            }
            if (*(int *)(*(int *)(a0 + 0x15C) + 0x600) != 0) {
                func_00157BB0((void *)a0, (void *)s17);
            }
        }
        _ACTWait(1);
    }
}

extern void func_00157BB0(void *a0, void *a1);

void func_0015E080(volatile int a0) {
    char *base = *(char **)(a0 + 0x164);
    int s17val = *(int *)(base + 0x5EC);
    WithMailFunc_WayBeginPosError((void *)a0, base + 0x590);
    func_0015C818_disp(a0);
    for (;;) {
        if (s17val) {
            (void)a0;
            if (*(int *)(*(char **)(a0 + 0x15C) + 0x600)) {
                func_00157BB0((void *)a0, (void *)s17val);
            }
        }
        _ACTWait(1);
    }
}

extern int D_00274EC0[];

void func_0015E118(volatile int a0) {
    char *s1 = *(char **)(a0 + 0x164);
    for (;;) {
        if ((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] / 2 <
            *(int *)(s1 + 0x48)) {
            BoxBarSoundOn((void *)a0, 0x9E);
        }
        _ACTWait(1);
    }
}

extern void ChangeMailInLadder(void *buf, void *obj);
extern int _ACTCorrectMsg(void *a0, int a1);
extern void GetChainClimbCollision(int a0, float *a1);
extern void eBrainGetTarget(int a0);
extern void eBrainInit(int a0);
extern void func_0018ECC8(int a0);
extern void func_0015F3C0();

void func_0015E1B0(volatile int a0) {
    float buf[4];
    int *s164 = *(int **)(a0 + 0x164);
    float *bp;
    int hv;

    eBrainGetTarget(s164[0x180 / 4]);
    hv = (int)func_0015F3C0;
    bp = buf;
    s164[0x18 / 4] = hv;
    ChangeMailInLadder(bp, (void *)a0);
    *(float *)&s164[0x190 / 4] = buf[0];
    *(float *)&s164[0x194 / 4] = buf[1];
    *(float *)&s164[0x198 / 4] = buf[2];
    GetChainClimbCollision(s164[0x180 / 4], buf);
    _ACTWait(1);
    for (;;) {
        int m = _ACTCorrectMsg((void *)a0, s164[0x180 / 4]);
        switch (m) {
        case 1:
            BoxBarSoundOn((void *)a0, 0x9C);
            break;
        case 2:
            BoxBarSoundOn((void *)a0, 0x9B);
            break;
        }
        eBrainInit(s164[0x180 / 4]);
        func_0018ECC8(s164[0x180 / 4]);
        eBrainGetTarget(s164[0x180 / 4]);
        dispPlane((void *)a0, buf);
        _ACTWait(1);
    }
}

void func_0015E2A8(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}

extern void ActOrientTest(void *a0, void *a1, int a2);
extern void ChangeFieldCollisionDebugMode(void *a0);

void func_0015E2C8(volatile int a0) {
    char buf[0xC0];
    for (;;) {
        char *obj = (char *)a0;
        int hit;
        ACTCharStat *rec = &D_00565060[*(int *)(*(char **)(obj + 0x15C) + 0x4A0)];
        if (!(rec->f_188 & 1)) goto no;
        if (func_0015C418_probe(buf, obj)) { hit = 1; goto test; }
      no:  hit = 0;
      test:
        if (hit) BoxBarSoundOn((void *)a0, 0x9D);
        _ACTWait(1);
    }
}

extern void func_0015F428();

void func_0015E388(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    int b1, b2, b3;
    *(int *)(s164 + 0x18) = (int)func_0015F428;
    if (*(int *)(s164 + 0xC8) == 0x9B) {
        b1 = a0;
        b2 = a0;
        b3 = a0;
        *(int *)(*(int *)(b1 + 0x15C) + 0x130) = 0;
        *(int *)(*(int *)(b2 + 0x15C) + 0x134) = 0;
        *(int *)(*(int *)(b3 + 0x15C) + 0x138) = 0;
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB0);
        _ACTWait(1);
    }
}

void func_0015E3F8(volatile int a0) {
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB0);
        _ACTWait(1);
    }
}

void func_0015E428(volatile int a0) {
    _ACTWait(0);
}

void func_0015E448(volatile int a0) {
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern void func_0014B270(void *a0, int a1, int a2, float f);

void func_0015E478(volatile int a0) {
    int buf[4];
    func_00243B18_3(buf, subCommonIdle((char *)a0), -1.0f);
    dispPlane((void *)a0, buf);
    for (;;) {
        func_0014B270((void *)a0, 3, 0, -1.0f);
        _ACTWait(1);
    }
}

void func_0015E4E0(volatile int a0) {
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern void *ExecMotionOrient(void *a0, void *a1, void *a2);
extern void func_00104748(void *a0, void *a1);

void func_0015E510(volatile int a0) {
    int buf[4];
    char *base = *(char **)(a0 + 0x164);
    int prev = *(int *)(base + 0x3C);
    for (;;) {
        int cur = *(int *)(base + 0x3C);
        char *o;
        int r, ar;
        if (cur != 0xED) {
            prev = cur;
        } else {
            *(void **)(base + 0x120) =
                ExecMotionOrient((void *)a0, (void *)prev, base + 0x610);
        }
        func_00104748(buf, (void *)a0);
        o = *(char **)(a0 + 0x164);
        r = HandCameraCorrect(*(char **)(o + 0x678) + 0x3D0, buf);
        ar = (r < 0) ? -r : r;
        if (ar < 0xF) {
            BoxBarSoundOn((void *)a0, 0xE5);
        }
        _ACTWait(1);
    }
}

void func_0015E5C8(volatile int a0) {
    int buf[4];
    char *p = *(char **)(a0 + 0x164) + 0x5B0;
    for (;;) {
        int r, ar;
        func_00104748(buf, (void *)a0);
        r = HandCameraCorrect(p, buf);
        ar = (r < 0) ? -r : r;
        if (ar < 0xF) {
            BoxBarSoundOn((void *)a0, 0xE4);
        }
        _ACTWait(1);
    }
}

void func_0015E638(volatile int a0) {
    _ACTWait(0);
}

void actCommonFly(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}

extern void boss_effect_process(int a0);

void func_0015E678(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    *(int *)(s164 + 0x14) = (int)boss_effect_process;
    _ACTWait(0);
}


void actCommonLadder(volatile int a0) {
    debug_assertMessage(D_00558C58);
    for (;;) {
        _ACTWait(1);
    }
}

void func_0015E6D8(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 1;
    for (;;) {
        func_0015C818_disp(a0);
        _ACTWait(1);
    }
}

void func_0015E730(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 0xFFFFFFFF;
    for (;;) {
        func_0015C818_disp(a0);
        _ACTWait(1);
    }
}

void func_0015E790(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 1;
    _ACTWait(0);
}

void actCommonDodge(volatile unsigned int a0)
{
    int *v1 = *(int **)((char *)a0 + 0x164);
    *(unsigned int *)((char *)v1 + 0x34) = 0xFFFFFFFFu;
    _ACTWait(0);
}

extern void BoxBarSoundOn(void *a0, int a1);

void actCommonEdgeHang(volatile int a0) {
    char *s1 = *(char **)(a0 + 0x164);
    for (;;) {
        char *o = *(char **)(*(char **)(a0 + 0x164) + 0x670);
        *(int *)(s1 + 0x34) = 1;
        switch (*(int *)(o + 0x290)) {
        case 1:
            BoxBarSoundOn((void *)a0, 0x81);
        case 2:
            BoxBarSoundOn((void *)a0, 0x82);
            break;
        }
        _ACTWait(1);
    }
}

void func_0015E878(volatile int a0) {
    char *s1 = *(char **)(a0 + 0x164);
    for (;;) {
        char *o = *(char **)(*(char **)(a0 + 0x164) + 0x670);
        *(unsigned int *)(s1 + 0x34) = 0xFFFFFFFFu;
        switch (*(int *)(o + 0x294)) {
        case 1:
            BoxBarSoundOn((void *)a0, 0x81);
        case 2:
            BoxBarSoundOn((void *)a0, 0x82);
            break;
        }
        _ACTWait(1);
    }
}

void func_0015E908(volatile int a0) {
    char *s16 = *(char **)(a0 + 0x164);
    for (;;) {
        long long v = *(long long *)(s16 + 0x470);
        if (((int)(v >> 9) & 1) &&
            ((int)(*(long long *)(s16 + 0x480) >> 9) & 1))
            goto wait;
        if (((int)(v >> 10) & 1) &&
            ((int)(*(long long *)(s16 + 0x480) >> 10) & 1))
            goto wait;
        BoxBarSoundOn((void *)a0, 0xB7);
    wait:
        _ACTWait(1);
    }
}


void func_0015E9A0(volatile int a0) {
    float v[4];
    char *s = *(char **)(a0 + 0x164);
    v[0] = *(float *)(s + 0x190);
    v[1] = *(float *)(s + 0x194);
    v[2] = *(float *)(s + 0x198);
    if (*(int *)(s + 0xC8) == 0xB1) {
        func_00243B18_3(v, v, -1.0f);
    }
    for (;;) {
        dispPlane((void *)a0, v);
        _ACTWait(1);
    }
}


void func_0015EA20(volatile int a0) {
    debug_assertMessage(D_00558BF8);
    _ACTWait(0);
}


void funcCommonBeginReady(volatile int a0) {
    debug_assertMessage(D_00558C18);
    _ACTWait(0);
}


void funcCommonEndReady(volatile int a0) {
    debug_assertMessage(D_00558C38);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonEndExec);
ASM_LIT4_SLOT(D_00630CD0, 0.1f);
ASM_LIT4_SLOT(D_00630CD4, 3.14159274f);

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015EC08);
ASM_LIT4_SLOT(D_00630CD8, 0.1f);
ASM_LIT4_SLOT(D_00630CDC, 3.14159274f);

extern int CanWallLeverPull(int a0, int a1);
extern char D_00632328[];

void func_0015ED60(volatile int a0) {
    char *state = *(char **)(a0 + 0x164);
    int v = *(int *)(state + 0x5EC);
    _ACTWait(6);
    CanWallLeverPull(v, 0);
    debug_assertMessage(D_00632328);
    _ACTWait(0);
}

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

void _ACTCommonMailTest(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}

extern char *D_00631AE8;
extern void *D_006321DC;
extern int iosOmBeforeFuncStandard(void *a0, int a1, void *a2);

void func_0015EEF0(volatile int a0) {
    if (D_00631AE8 != 0) {
        iosOmBeforeFuncStandard((void *)D_00631AE8, 0x40, D_006321DC);
    }
    for (;;) {
        _ACTWait(1);
    }
}

extern int D_00632508;

void func_0015EF28(void *a0) {
    if (a0 == (void *)D_00631AE8) {
        D_00632508 = 1;
    }
}

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
    if (a0 != (char *)D_00631AE4 && a0 != D_00631AE8 && *(int *)(a0 + 0xC) != 4) {
        InitKeyInput(D_006AAB60, a0);
        return D_006AAB60;
    }
    p = *(char **)(a0 + 0x164) + 0xE0;
    GetOrientOfWallOfGObj(p, a0);
    return p;
}

extern void GetRootMatrixByDObj(void *out, void *obj);
extern int CageFixDL(void *a0, void *a1, void *a2);
extern char D_006AAB70[];
extern float D_00632340[];

void *ContinueCorrectPosition(void *a0) {
    char *s0;
    int x = *(int *)((char *)a0 + 0xC);
    switch (x) {
    case 1:
    case 2:
    case 4:
        s0 = *(char **)((char *)a0 + 0x164) + 0xF0;
        GetRootMatrixByDObj(s0, a0);
        return s0;
    case 0x2B: {
        int local[4];
        if (CageFixDL(D_006AAB70, local, a0) == 0) {
            float f = D_00632340[0];
            ((float *)D_006AAB70)[0] = f;
            ((float *)D_006AAB70)[1] = f;
            ((float *)D_006AAB70)[2] = f;
        }
        return D_006AAB70;
    }
    default:
        GetRootMatrixByDObj(D_006AAB70, a0);
        return D_006AAB70;
    }
}

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

extern int ExecBoxMoveEndReaction(void *a0);

int func_0015F248(void *a0) {
    char *p = *(char **)(*(int *)((char *)a0 + 0x15C));
    if (p != 0) {
        if (*(int *)(p + 0xC) == 0x11) {
            if (ExecBoxMoveEndReaction(p) == 7) {
                return 1;
            }
        }
    }
    return 0;
}

extern void func_00243B18(void *a0, float f);

void ACT_LAYOUT_GAMEOVER(void *a0) {
    int local[4];
    func_00243B18(local, -1.0f);
    dispPlane(a0, local);
}


void ACTAdjustPlane(int *self)
{
    int buf[4];
    func_00243B18_3(buf, (char *)self[0x164 / 4] + 0x4A0, -1.0f);
    dispPlane((void *)self, buf);
}

extern void ChangeMailInLadder(void *buf, void *obj);

void _ACTMotDirSmzDirect(void *a0) {
    int local[4];
    ChangeMailInLadder(local, a0);
    dispPlane(a0, local);
}

extern void func_001AD768(char *file, int line);
extern void func_00263FF0(char *file, int line, char *expr);

void func_0015F358(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    if (*(int *)(s164 + 0x180) == 0) {
        func_001AD768(D_00558860, 0x5AF);
        func_00263FF0(D_00558860, 0x5AF, D_00558870);
    }
    eBrainInit(*(int *)(s164 + 0x180));
}

void func_0015F3C0(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    if (*(int *)(s164 + 0x180) == 0) {
        func_001AD768(D_00558860, 0x629);
        func_00263FF0(D_00558860, 0x629, D_00558870);
    }
    eBrainInit(*(int *)(s164 + 0x180));
}

void func_0015F428(volatile unsigned int a0)
{
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x20);
    *p |= 0x40000;
}

void func_0015F450(volatile int a0) {
    *(int *)(*(int *)(*(char **)(a0 + 0x164) + 0x678) + 0x37C) =
        (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] * 0x82 / 0x3C;
}

void actCommonRevive(volatile unsigned int a0)
{
    ACTParaStatus_Clear(a0);
}

void actCommonReviveAir(int x) {
    volatile int local = x;
}

void actCommonPlay(volatile unsigned int a0)
{
    ACTParaStatus_Clear(a0);
}

void actCommonOne(volatile unsigned int self)
{
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

typedef struct { int a, b, c; } Blob12;
extern Blob12 D_00282660;

void func_0015F578(volatile int a0) {
    debug_assertMessage("reset\n");
    *(Blob12 *)(*(char **)(a0 + 0x15C) + 0x1C0) = D_00282660;
    actCommonRopeCliff(a0, 0);
}

void func_0015F5D0(volatile unsigned int a0)
{
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x20);
    *p |= 0x40000;
}

void func_0015F5F8(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    *(long long *)(s164 + 0x20) &= ~0x2000000LL;
    *(long long *)(s164 + 0x18) &= ~0x1000000000000LL;
    *(long long *)(s164 + 0x20) |= 0x40000;
}


void func_0015F650(volatile int a0) {
    long long *s164 = *(long long **)(a0 + 0x164);
    s164[4] |= 1;
    ReviveEnemyParticle((void *)a0, 1);
    *(int *)(*(int *)(a0 + 0x15C) + 0x654) = 0;
}


/* .data — carved VMA 0X282390..0X282400 (5 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_00282390[12] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000,
};
unsigned int D_002823C0[4] = {
    0x00000080, 0x000000C0, 0x000000FF, 0x00000080,
};
unsigned int D_002823D0[4] = {
    0x00000000, 0x000000FF, 0x00000080, 0x00000080,
};
unsigned int D_002823E0[4] = {
    0x00000000, 0x00000000, 0x00000080, 0x00000080,
};
unsigned int D_002823F0[4] = {
    0x00000000, 0x00000080, 0x000000FF, 0x00000080,
};

/* .sdata — carved VMA 0X6322F0..0X632310, bytes verified against baserom/baseelf.rom.
   D_006322F0 ("reset\n") is not here: it is the string literal in func_0015F578.
   gcc puts a <=8-byte string constant in .sdata (mips_select_section) but never
   gp-addresses it (ENCODE_SECTION_INFO only flags VAR_DECLs), which is what the
   ROM's lui/addiu %hi/%lo pair at 0x15F580 shows. */
unsigned int D_006322F8[2] = {
    0x20746573, 0x000A7025,
};
unsigned int D_00632300 = 0x7F7FFFFF;
unsigned int D_00632304 = 0x7F7FFFFF;
unsigned int D_00632308[2] = {
    0x312E3125, 0x00002066,
};

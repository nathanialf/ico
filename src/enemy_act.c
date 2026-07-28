#include "common.h"

extern char D_00558E10[], D_00558E20[];
extern void func_001AD768(void *a0, int a1);
extern void func_00263FF0(void *a0, int a1, void *a2);
static inline int subEnemyBrain_ToBoy_chk(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    if (*(int *)(*(char **)(p + 0x670) + 0x1FC) != 5) {
        return 0;
    }
    if (*(int *)(*(char **)(p + 0x678) + 0x420) == 0) {
        func_001AD768(D_00558E10, 0x2FA);
        func_00263FF0(D_00558E10, 0x2FA, D_00558E20);
    }
    return 1;
}

typedef union { long long d; int w[2]; } MustChaseFlag;





extern int D_00632390;
/* KEEP_DEF: D_00632398 must be declared as array (not scalar) so
 * ee-gcc's small-data gp_rel optimization stays off, matching original. */
extern char D_00632398[];
extern void func_001919A0();
extern void ACTParaStatus_Clear(volatile int *self);
extern int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6);
extern void func_0017B288(int bit_idx);
extern void *D_00631AE8;
extern char D_002A4C48[];
extern void CanWallLeverPull(char *self, int a1);
void boss_effect_process(int x) {
    volatile int local = x;
}

int _DoAwait(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x30) == 0xF;
}

void _DoAwaitGirl(volatile unsigned int a0)
{
    int *v1 = *(int **)((char *)a0 + 0x164);
    CanWallLeverPull(*(int *)((char *)v1 + 0x5EC), 0);
}

extern char D_00558E10[];
extern void func_001AD768(void *a0, int a1);
extern void func_00263FF0(void *a0, int a1, void *a2);

void _MustChase(int a0) {
    char *g = *(char **)(*(int *)(a0 + 0x164) + 0x670);
    switch (*(int *)(g + 0x1E4)) {
    case 0:
        ((MustChaseFlag *)(g + 0x208))->d &= ~1LL;
        ((MustChaseFlag *)(*(char **)(*(int *)(a0 + 0x164) + 0x670) + 0x208))->d &= ~2LL;
        break;
    case 1:
        ((MustChaseFlag *)(g + 0x208))->d &= ~1LL;
        ((MustChaseFlag *)(*(char **)(*(int *)(a0 + 0x164) + 0x670) + 0x208))->d |= 2LL;
        break;
    case 2:
        ((MustChaseFlag *)(g + 0x208))->d |= 1LL;
        ((MustChaseFlag *)(*(char **)(*(int *)(a0 + 0x164) + 0x670) + 0x208))->d &= ~2LL;
        break;
    case 3:
        ((MustChaseFlag *)(g + 0x208))->d |= 1LL;
        ((MustChaseFlag *)(*(char **)(*(int *)(a0 + 0x164) + 0x670) + 0x208))->d |= 2LL;
        break;
    default:
        func_001AD768(D_00558E10, 0x324);
        func_00263FF0(D_00558E10, 0x324, D_00632398);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyControl);

extern void subEnemyControl(int *self, int a1);

void subEnemyCollision(int *self, int a1)
{
    char *p;
    int i;
    p = (char *)((int *)self[0x59])[0x19C] + 0x360;
    i = 0;
    do {
        if (*(signed char *)(p + 0x1D) != 0) {
            if (*(int *)(p + 0x14) == a1) {
                return;
            }
        }
        i++;
        p += 0x20;
    } while (i < 5);
    subEnemyControl(self, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015F9F4);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015F9F8);

extern void ActPara_GetDefTbl(void *a0, int a1);
extern char D_00565060[];
extern int D_00631AE4;
extern int IsEnemyBrainToGenerator(void *a0, int a1, int a2);

void actEnemyRestart(void *a0) {
    int *p;
    char *e;
    if (D_00631AE4 != 0) {
        ActPara_GetDefTbl(a0, 0x1B);
        p = *(int **)((char *)a0 + 0x15C);
        e = D_00565060 + p[0x4A0 / 4] * 0x190;
        if ((*(unsigned int *)(e + 0x188) >> 1) & 1) {
            IsEnemyBrainToGenerator(a0, D_00631AE4, 5);
        }
    }
}

extern int D_00631AE8__p4 __asm__("D_00631AE8");

void PairSetGeometry(void *a0) {
    int *p;
    char *e;
    if (D_00631AE8__p4 != 0) {
        ActPara_GetDefTbl(a0, 0x1B);
        p = *(int **)((char *)a0 + 0x15C);
        e = D_00565060 + p[0x4A0 / 4] * 0x190;
        if ((*(unsigned int *)(e + 0x188) >> 1) & 1) {
            IsEnemyBrainToGenerator(a0, D_00631AE8__p4, 5);
        }
    }
}

extern int ContinueCorrectPosition(int a0);
extern float D_00630CE0;
extern int D_00631AE4;
extern float RotateAccordingToStick_PatternThree(float *a0, float *a1);

int actEnemyForceSwitchToCarry(int a0) {
    float v1[4];
    float v2[4];
    float angle;
    float diff;
    int rv;
    if (D_00631AE4 == 0) {
        goto zero;
    }
    v1[0] = ((float *)ContinueCorrectPosition(D_00631AE4))[0];
    v1[1] = ((float *)ContinueCorrectPosition(D_00631AE4))[1];
    v1[2] = ((float *)ContinueCorrectPosition(D_00631AE4))[2];
    v2[0] = ((float *)ContinueCorrectPosition(a0))[0];
    v2[1] = ((float *)ContinueCorrectPosition(a0))[1];
    v2[2] = ((float *)ContinueCorrectPosition(a0))[2];
    angle = RotateAccordingToStick_PatternThree(v1, v2);
    if (angle < D_00630CE0) {
        diff = v1[1] - v2[1];
        if (diff < 0.0f) {
            if (200.0f < -diff) {
                return 1;
            }
            return 0;
        }
        rv = 0;
        if (!(200.0f < diff)) {
            return rv;
        }
    }
    rv = 1;
    goto end;
zero:
    rv = 0;
end:
    return rv;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyKidnapEnd);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00160720);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyKidnapBegin);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", MoveChestForCatchBoy);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyBodylift);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001613B0);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyPickupBegin);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00161AC8);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", CheckEnemyBrainMode);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", BrainMode_Requset);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyBrainMain);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", enemy_dodge);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", Battle_isCurrentStatus);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", GetFlyPosition);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", NakaBoss);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00163890);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", ChangeBrain_ToAttack);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00163B40);

extern void BoxBarSoundOn(void *a0, int a1);
extern char D_00558E20[];
extern char D_00558FB0[];
extern int D_00632DA0;
extern int DispPointBlur(void *a0);
extern int funcEnemyCarryFail(int *a0);

int subEnemyBrain_ToBoy(void *a0) {
    int f18 = 0;
    int f20 = 0;
    int rv = 0;
    int catch;
    int r;
    int a1v;

    r = DispPointBlur(a0);
    switch (r) {
    case 1:
        f18 = 1;
        break;
    case 2:
        f18 = 1;
        f20 = 1;
        break;
    }

    if (a0 == 0 || *(int *)((char *)a0 + 0xC) != 4) {
        func_001AD768(D_00558E10, 0x7D2);
        func_00263FF0(D_00558E10, 0x7D2, D_00558FB0);
    }

    if (funcEnemyCarryFail((int *)a0) == 0) {
        goto done;
    }

    catch = subEnemyBrain_ToBoy_chk(a0);

    if (catch != 0) {
        if (f20 != 0) {
            goto setE;
        }
        if (D_00632DA0 == 0) {
            goto done;
        }
    setE:
        BoxBarSoundOn(a0, 0x1E);
        rv = 1;
        goto done;
    } else {
        if (f18 == 0) {
            goto done;
        }
        BoxBarSoundOn(a0, 0x1D);
        rv = 1;
    }
done:
    return rv;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", ChangeBrain_ToKidnap);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyBrain_ToGirl);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _ApproachTarget_Boss);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", flyMailCore);

extern char D_00558ED8[];
extern unsigned int _ACTWait(int a0);
extern extern void debug_assertMessage();

void _ApproachTarget_Way(volatile unsigned int a0)
{
    volatile int local;
    int *new_var;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    debug_assertMessage((char *)D_00558ED8);
    s0 = new_var;
    s0[0x30 / 4] = 0x1;
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164EF4);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164EF8);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F3C);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F40);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F84);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F88);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164FCC);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164FD0);

extern int D_00631AE4;
extern void BoxBarSoundOn(void *a0, int a1);
extern int iosOmBeforeFuncStandard4(void *a0, int a1, void *a2, int a3) __asm__("iosOmBeforeFuncStandard");

void funcEnemyAiGetGirl(volatile int a0) {
    int p = *(int *)(a0 + 0x164);
    int g = *(int *)(p + 0x670);
    iosOmBeforeFuncStandard4((void *)D_00631AE4, *(int *)(g + 0x1F8), (void *)a0, g);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern void iosOmBeforeFuncStandard3(void *a0, int a1, void *a2) __asm__("iosOmBeforeFuncStandard");

void func_00165060(volatile int a0) {
    iosOmBeforeFuncStandard3((void *)D_00631AE4, 0xD2, (void *)a0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern void actChangeActBrain(void *a0, void *a1, void *a2);
extern int actEnemy_isLargeEnemy();
extern int D_006321DC;
extern void CylinderCollision(int *self, char *spill);
extern void ResetEnemyEye(int *self);
extern void actEnemyRun(int *self);
extern void func_001AE420(int *self, int a1, int a2, int a3);
extern int D_00631990;
extern char D_00558FA0[];
extern void func_001919A0__p2(void *a0, int a1) __asm__("func_001919A0");

void func_001650A0(void *a0) {
    void *volatile self = a0;
    int *p = *(int **)((char *)self + 0x164);
    char spill[16];
    int *s;
    p[0x138 / 4] = 0;
    actChangeActBrain((void *)D_006321DC, (void *)actEnemy_isLargeEnemy, (void *)p);
    s = (int *)self;
    *(long long *)(spill + 0) = *(long long *)((char *)D_00558FA0 + 0);
    *(long long *)(spill + 8) = *(long long *)((char *)D_00558FA0 + 8);
    CylinderCollision(s, spill);
    ResetEnemyEye(s);
    actEnemyRun(s);
    func_001919A0__p2((void *)self, 0xA);
    p[0x430 / 4] = 0;
    p[0x434 / 4] = 7;
    func_001AE420((int *)self, 7, 0, D_00631990);
    _ACTWait(0);
}

void actEnemyStand(char *self) {
    char *sub = *(char **)(self + 0x164);
    *(long long *)(sub + 0x150) |= 0x100000000LL;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165174);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165178);

void actEnemyRun(int *a0)
{
    char *base = D_002A4C48 + a0[2] * 0x4C;
    *(int *)(base + 0x48) &= ~0x200000;
}

void actEnemyHang(volatile int self_arg)
{
    register int *D asm("$3") = (int *)D_00631AE8;
    int new_var2;
    int *sub = (int *) ((int *) self_arg)[0x59];
    int *new_var;
    sub[0x4E] = (int) D;
    new_var2 = 0x4E;
    new_var = &sub[new_var2];
    iosOmBeforeFuncStandard((int *)D_00631AE8, 0x30, self_arg);
    new_var2 = *new_var;
    ((int *) ((int *) sub[0x4E])[0x57])[0x1D] = 1;
    ACTParaStatus_Clear((int *) new_var2);
    func_0017B288(0x168);
    sub[0x4E] = 0;
    if (sub[0xC] == 5)
    {
        func_001919A0((int *) self_arg, 4);
    }
    asm __volatile__("" : : : "memory");
}

void actEnemyCarry(int *a0)
{
    char *base = D_002A4C48 + a0[2] * 0x4C;
    *(int *)(base + 0x48) |= 0x40000;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0016529C);

int func_001652A0(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x430) == 2;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001652B4);

int func_001652B8(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x430) == 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001652CC);

int func_001652D0(int *a0)
{
    int *p = (int *)(D_002A4C48 + a0[2] * 0x4C);
    return ((unsigned int)p[0x48 / 4] >> 18) & 1;
}

int funcEnemyCarryFail(int *a0)
{
    unsigned int *p = (unsigned int *)(D_002A4C48 + a0[2] * 0x4C);
    unsigned int field = p[0x48 / 4];
    unsigned int v0 = (field >> 18) & 1;
    if (v0 != 0) goto zero;
    v0 = (field >> 21) & 1;
    v0 = v0 ^ 1;
    if (v0 == 0) goto one;
zero:
    return 0;
one:
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165344);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165348);

int actEnemyFlagOnFree(int *self) {
    int *p = (int *)self[0x164/4];
    int *q = (int *)p[0x670/4];
    if (q[0x1E0/4] == 0 && p[0x30/4] == 0x10) {
        return q[0x218/4];
    }
    return 0;
}

int afterCommonCarry(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    return *(int *)(p + 0x1E0) == 1;
}

int actEnemyFlagOnDead(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    return *(int *)(p + 0x1E0) == 2;
}

int EnemyBrainStatus_Boy(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    return *(int *)(p + 0x1E0) == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165414);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165418);

int func_00165488(char *self)
{
    char *sub;
    char *sub2;
    if (D_00631AE8 != 0) {
        char *sub_d = *(char **)((char *)D_00631AE8 + 0x164);
        if (*(int *)(sub_d + 0x30) != 0x6B) return 0;
    }
    sub = *(char **)((char *)self + 0x164);
    sub2 = *(char **)(sub + 0x670);
    return *(int *)(sub2 + 0x1FC) == 3;
}

int actEnemyFlagCheckActive(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    return *(int *)(p + 0x1DC);
}

int ACTEnemyForceSwitchToCarry(void) {
    return 1;
}

int actEnemy_GetClingTarget(int *a0) {
    unsigned int *p;
    unsigned int field;
    unsigned int v0;
    if (*(int *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x670) + 0x1DC) == 0)
        return 0;
    p = (unsigned int *)((char *)D_002A4C48 + a0[2] * 0x4C);
    field = p[0x48 / 4];
    v0 = (field >> 18) & 1;
    if (v0 != 0) goto zero;
    v0 = (field >> 21) & 1;
    v0 = v0 ^ 1;
    if (v0 == 0) goto one;
zero:
    return 0;
one:
    return 1;
}

extern char D_00558E10[];
extern char D_00558FB0[];
extern void func_001AD768(void *a0, int a1);
extern void func_00263FF0(void *a0, int a1, void *a2);

int actEnemy_isNormalEnemy(void *a0) {
    if (a0 == 0 || *(int *)((char *)a0 + 0xC) != 4) {
        func_001AD768(D_00558E10, 0x7D2);
        func_00263FF0(D_00558E10, 0x7D2, D_00558FB0);
    }
    return funcEnemyCarryFail((int *)a0);
}

int actEnemy_isLargeEnemy(volatile int a0) {
    int *p = *(int **)(a0 + 0x164);
    p[0x33C / 4] = 0;
    p[0x110 / 4] = 0;
    p[0x114 / 4] = 0;
    p[0x118 / 4] = 0;
    for (;;) {
        if (*(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670) + 0x210) == D_00631AE4) {
            actEnemyRestart((void *)a0);
        }
        _ACTWait(1);
    }
}

extern float pac_DispQW(void);
extern int DispCollisionPC(void *a0, int a1, int a2, int a3, unsigned char a4, float a5);

void func_00165610(volatile unsigned int a0)
{
    int *p = *(int **)(a0 + 0x164);
    p[0x33C / 4] = 0;
    p[0x110 / 4] = 0;
    p[0x114 / 4] = 0;
    p[0x118 / 4] = 0;
    if (D_00631AE4 != 0) {
        DispCollisionPC((void *)a0, D_00631AE4, (int)((char *)p + 0x110), 0, 0,
                        (float)((int)(pac_DispQW() * 10.0f) % 200 + 300));
    }
    p[0x33C / 4] = 0;
    p[0x110 / 4] = 0;
    p[0x114 / 4] = 0;
    p[0x118 / 4] = 0;
    for (;;) {
        actEnemyRestart((void *)a0);
        _ACTWait(1);
    }
}

extern char D_00559030[];

void func_001656C8(volatile unsigned int a0)
{
    int *p = *(int **)(a0 + 0x164);
    int *q = *(int **)((char *)*(int **)(a0 + 0x164) + 0x678);
    char *g = *(char **)((char *)*(int **)(a0 + 0x164) + 0x670);
    int t = p[0x13C / 4];
    q[0x420 / 4] = t;
    if ((unsigned char)DispCollisionPC((void *)a0, t,
                                       (int)((char *)p + 0x110), 0,
                                       *(unsigned char *)(g + 0x21C), 50.0f) == 0) {
        debug_assertMessage(D_00559030);
        p[0x33C / 4] = 0;
        p[0x110 / 4] = 0;
        p[0x114 / 4] = 0;
        p[0x118 / 4] = 0;
        _ACTWait(0x1E);
        BoxBarSoundOn((void *)a0, 0xF0);
        _ACTWait(0);
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0x14A);
        _ACTWait(1);
    }
}

extern int D_00274EC0[];

void func_00165780(volatile unsigned int a0)
{
    int *p = *(int **)(a0 + 0x164);
    int i, cnt;
    for (i = 0; i < (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] / 2; i++) {
        p[0x33C / 4] = 0;
        p[0x110 / 4] = 0;
        p[0x114 / 4] = 0;
        p[0x118 / 4] = 0;
        BoxBarSoundOn((void *)a0, 0xD6);
        if (p[0x30 / 4] == 0x47) {
            break;
        }
        _ACTWait(1);
    }
    for (i = 0; i < (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] * 0xFA / 0x3C; i++) {
        actEnemyRestart((void *)a0);
        _ACTWait(1);
    }
    func_001919A0__p2((void *)a0, 1);
    _ACTWait(0);

}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemy_isSmallEnemy);

void func_00165B50(char *self, int a1, int *a2)
{
    *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x200) = a1;
    if (a2) {
        int v = *a2;
        *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x20C) = v;
    } else {
        int v = D_00632390;
        *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x20C) = v;
    }
}

extern int HandCameraCorrect(float *a0, float *a1);
extern void actCommonStoneDead(void *a0, float *a1, float a2);
extern void dispPlane(void *a0, float *a1);
extern void func_00104748(float *a0, void *a1);
extern void func_001947D0(float *a0, int a1, int a2);

int IsEnemyBrainToGenerator(void *a0, int a1, int a2) {
    float posA[4];
    float mtx[4];
    float posB[4];
    char *p;
    char *q;
    float *m;
    int r0;
    int r1;
    int flag;
    int mode;
    int angle;
    int absA;

    p = *(char **)((char *)a0 + 0x164);
    r0 = ContinueCorrectPosition(a1);
    r1 = ContinueCorrectPosition(a0);
    func_001947D0(posA, r0, r1);
    q = *(char **)((char *)a0 + 0x164);
    *(float *)(p + 0x110) = posA[0];
    *(float *)(p + 0x114) = posA[1];
    *(float *)(p + 0x118) = posA[2];
    flag = *(int *)(q + 0x30);
    mode = ((flag ^ 3) == 0) ? 0x5A : 0x69;
    posB[0] = *(float *)(q + 0x110);
    posB[1] = *(float *)(q + 0x114);
    posB[2] = *(float *)(q + 0x118);
    m = mtx;
    func_00104748(m, a0);
    m = posB;
    angle = HandCameraCorrect(mtx, m);
    absA = (angle >= 0) ? angle : -angle;
    if (mode < absA) {
        *(float *)(q + 0x5B0) = posB[0];
        *(float *)(q + 0x5B4) = posB[1];
        *(float *)(q + 0x5B8) = posB[2];
        if (angle > 0) {
            BoxBarSoundOn(a0, 0xD8);
        } else {
            BoxBarSoundOn(a0, 0xD7);
        }
    } else if (absA < 0xF) {
        BoxBarSoundOn(a0, 0xE1);
    }
    if (a2 == 0) {
        dispPlane(a0, posA);
    } else {
        actCommonStoneDead(a0, posA, (float)a2);
    }
}

extern int subEnemyBrain_ToBoy(void *a0);

int IsEnemyBrainToBoy(void *a0) {
    int x = *(int *)(*(char **)((char *)a0 + 0x164) + 0x10);
    if (x < 0xC) {
        return -1;
    }
    return subEnemyBrain_ToBoy(a0);
}

extern void *isysGObjSearchFromObjKindID_begin(void *a0);
extern void *isysGObjSearchFromObjLayoutID(int a0);

void GetEnemyTypeFromGObj(int a0) {
    void *o = isysGObjSearchFromObjLayoutID(4);
    if (o != 0) {
        do {
            if (*(int *)(*(int *)(*(int *)((char *)o + 0x164) + 0x670) + 0x1DC) == 3) {
                int i;
                for (i = 0; i < 5; i++) {
                    char *e = (char *)((i << 5) + *(int *)(*(int *)((char *)o + 0x164) + 0x670) + 0x360);
                    if (e[0x1D] != 0) {
                        if (*(int *)(e + 0x10) == a0) {
                            e[0x1C] = 0;
                            return;
                        }
                    }
                }
            }
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165DC0);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165E08);


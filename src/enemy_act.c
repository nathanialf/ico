#include "common.h"





extern int D_00632390;
/* KEEP_DEF: D_00632398 must be declared as array (not scalar) so
 * ee-gcc's small-data gp_rel optimization stays off, matching original. */;
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

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _MustChase);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyControl);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyCollision);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015F9F4);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015F9F8);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyRestart);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", PairSetGeometry);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyForceSwitchToCarry);

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

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyBrain_ToBoy);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", ChangeBrain_ToKidnap);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyBrain_ToGirl);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _ApproachTarget_Boss);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", flyMailCore);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _ApproachTarget_Way);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164EF4);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164EF8);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F3C);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F40);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F84);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F88);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164FCC);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164FD0);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", funcEnemyAiGetGirl);

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

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemy_GetClingTarget);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemy_isNormalEnemy);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemy_isLargeEnemy);

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

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", IsEnemyBrainToGenerator);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", IsEnemyBrainToBoy);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", GetEnemyTypeFromGObj);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165DC0);

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165E08);


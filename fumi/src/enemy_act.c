#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", setBattleStatus);

void boss_effect_start(volatile int a0) {
    long long *p = *(long long **)(a0 + 0x164);
    p[4] &= ~0x40000LL;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", boss_effect_check_parts);

void boss_effect_process(int a0) {
    int buf[4];
    buf[0] = a0;
}

int _DoAwait(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    return p[0xC] == 0xF;
}

extern int CanWallLeverPull(int a0, int a1);

int _DoAwaitGirl(volatile int a0) {
    int p = *(int *)(a0 + 0x164);
    return CanWallLeverPull(*(int *)(p + 0x5EC), 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", _MustChase);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyControl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyAttack);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyRestart);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", PairSetGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyForceSwitchToCarry);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyKidnapEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyKidnapBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", MoveChestForCatchBoy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyBodylift);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_0015F2A8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyPickupBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_0015F9C0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", CheckEnemyBrainMode);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", BrainMode_Requset);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyBrainMain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", enemy_dodge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", Battle_isCurrentStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", GetFlyPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", NakaBoss);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_001616E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", ChangeBrain_ToAttack);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyBrain_ToBoy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", ChangeBrain_ToKidnap);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyBrain_ToGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", _ApproachTarget_Boss);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", flyMailCore);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", _ApproachTarget_Way);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyStart);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyBrain_Irregular);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyBrain_Attack);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyBrain_Cling);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", funcEnemyAiGetGirl);

void actEnemyStand(void *a0) {
    long long *p = *(long long **)((char *)a0 + 0x164);
    *(long long *)((char *)p + 0x140) |= 0x100000000LL;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyWalk);

typedef struct { char _[0x48]; unsigned int f48; } NestEntry;
extern NestEntry D_002A0A90[];

void actEnemyRun(int *a0) {
    NestEntry *t = D_002A0A90;
    int idx = a0[2];
    t[idx].f48 &= 0xFFDFFFFF;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyHang);

void actEnemyCarry(int *a0) {
    NestEntry *t = D_002A0A90;
    int idx = a0[2];
    t[idx].f48 |= 0x40000;
}

int actEnemyBodyslam(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    return p[0x10C] == 2;
}

int actEnemyBodyslamFail(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    return p[0x10C] == 1;
}

int actEnemyNest(int *a0) {
    NestEntry *t = D_002A0A90;
    int idx = a0[2];
    return (t[idx].f48 >> 18) & 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", funcEnemyCarryFail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyHyde);

int actEnemyFlagOnFree(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    if (q[0x78] == 0 && p[0xC] == 0x10) {
        return q[0x86];
    }
    return 0;
}

int afterCommonCarry(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    return q[0x78] == 1;
}

int actEnemyFlagOnDead(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    return q[0x78] == 2;
}

int EnemyBrainStatus_Boy(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    return q[0x78] == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", EnemyBrainStatus_Girl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyFlagCheckDead);

int actEnemyFlagCheckActive(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    return q[0x77];
}

int ACTEnemyForceSwitchToCarry(void) {
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemy_GetClingTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemy_isNormalEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemy_isLargeEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemy_isSmallEnemy);

extern int D_0062A670;

void func_00163988(int *a0, int a1, int *a2) {
    *(int *)(*(int *)(a0[0x59] + 0x670) + 0x200) = a1;
    if (a2 == 0) goto elsebr;
    *(int *)(*(int *)(a0[0x59] + 0x670) + 0x20C) = a2[0];
    return;
elsebr:
    *(int *)(*(int *)(a0[0x59] + 0x670) + 0x20C) = D_0062A670;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", IsEnemyBrainToGenerator);

extern int subEnemyBrain_ToBoy(void *a0);

int IsEnemyBrainToBoy(void *a0) {
    int x = *(int *)(*(char **)((char *)a0 + 0x164) + 0x10);
    if (x < 0xC) {
        return -1;
    }
    return subEnemyBrain_ToBoy(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", GetEnemyTypeFromGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", GetEnemyType);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_58;  /* 0x58 */
    unsigned int       f_74;  /* 0x74 */
    unsigned int       f_90;  /* 0x90 */
    unsigned int       f_AC;  /* 0xAC */
    unsigned int       f_C8;  /* 0xC8 */
    unsigned int       f_170;  /* 0x170 */
} S_0027E770;  /* stride 0x1C */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553140;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005532F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553420;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553440;  /* stride 0x4 */

/* end struct shapes */

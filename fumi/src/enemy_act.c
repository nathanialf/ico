#include "common.h"

/* enemy_act 0x164 actor-state view (local) */
typedef struct { char _0[0x1DC]; int f_1DC, f_1E0; char _pad1e4[0x34]; int f_218; } EBrain670;
typedef struct { char _0[0x30]; int f_30; char _pad34[0x10C]; long long f_140; char _pad148[0x2E8]; int f_430; char _pad434[0x23C]; EBrain670 *p_670; } EnemyActState;

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
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    return p->f_30 == 0xF;
}

extern int CanWallLeverPull(int a0, int a1);

int _DoAwaitGirl(volatile int a0) {
    int p = *(int *)(a0 + 0x164);
    return CanWallLeverPull(*(int *)(p + 0x5EC), 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", _MustChase);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyControl);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyAttack);

extern int D_00629DE4;
extern void ActPara_GetDefTbl(void *a0, int a1);
extern int IsEnemyBrainToGenerator(void *a0, int a1, int a2);
extern char D_0055DA10[];

void actEnemyRestart(void *a0) {
    int *p;
    char *e;
    if (D_00629DE4 != 0) {
        ActPara_GetDefTbl(a0, 0x1B);
        p = *(int **)((char *)a0 + 0x15C);
        e = D_0055DA10 + p[0x490 / 4] * 0x190;
        if ((*(unsigned int *)(e + 0x188) >> 1) & 1) {
            IsEnemyBrainToGenerator(a0, D_00629DE4, 5);
        }
    }
}

extern int D_00629DE8;
extern void ActPara_GetDefTbl(void *a0, int a1);
extern int IsEnemyBrainToGenerator(void *a0, int a1, int a2);
extern char D_0055DA10[];

void PairSetGeometry(void *a0) {
    int *p;
    char *e;
    if (D_00629DE8 != 0) {
        ActPara_GetDefTbl(a0, 0x1B);
        p = *(int **)((char *)a0 + 0x15C);
        e = D_0055DA10 + p[0x490 / 4] * 0x190;
        if ((*(unsigned int *)(e + 0x188) >> 1) & 1) {
            IsEnemyBrainToGenerator(a0, D_00629DE8, 5);
        }
    }
}

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

extern void debug_assertMessage(char *p);
extern unsigned int _ACTWait(int a0);

extern char D_005531D8[];

void _ApproachTarget_Way(volatile unsigned int a0)
{
    volatile int local;
    int *new_var;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    debug_assertMessage((char *)D_005531D8);
    s0 = new_var;
    s0[0x30 / 4] = 0x1;
    _ACTWait(0);
}

extern void debug_assertMessage(char *p);
extern unsigned int _ACTWait(int a0);

extern char D_00553208[];

void actEnemyStart(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage((char *)D_00553208);
    s0[0x30 / 4] = 0x2;
    _ACTWait(0);
}

extern void debug_assertMessage(char *p);
extern unsigned int _ACTWait(int a0);

extern char D_00553238[];

void subEnemyBrain_Irregular(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage((char *)D_00553238);
    s0[0x30 / 4] = 0x3;
    _ACTWait(0);
}

extern char D_00553280[];

void subEnemyBrain_Attack(volatile unsigned int a0)
{
    int *new_var;
    volatile int local;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    debug_assertMessage((char *)D_00553280);
    s0 = new_var;
    s0[0x30 / 4] = 0x1C;
    _ACTWait(0);
}

extern void func_00260380(void *a0, int a1, void *a2);
extern char D_00553110[];
extern char D_0062C4F8[];
void subEnemyBrain_Cling(int a0) {
    volatile int local;
    local = a0;
    func_001AAD00(D_00553110, 0xACB);
    func_00260380(D_00553110, 0xACB, D_0062C4F8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", funcEnemyAiGetGirl);

void actEnemyStand(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    p->f_140 |= 0x100000000LL;
}

extern void CylinderCollision(int *self, char *spill);
extern void ResetEnemyEye(int *self);
extern void actEnemyRun(int *self);

extern char D_005532A0[];

void actEnemyWalk(int *self)
{
    char spill[16];
    *(long long *)(spill + 0) = *(long long *)((char *)D_005532A0 + 0);
    *(long long *)(spill + 8) = *(long long *)((char *)D_005532A0 + 8);
    CylinderCollision(self, spill);
    ResetEnemyEye(self);
    actEnemyRun(self);
}

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
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    return p->f_430 == 2;
}

int actEnemyBodyslamFail(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    return p->f_430 == 1;
}

int actEnemyNest(int *a0) {
    NestEntry *t = D_002A0A90;
    int idx = a0[2];
    return (t[idx].f48 >> 18) & 1;
}

int funcEnemyCarryFail(int *a0)
{
    unsigned int *p = (unsigned int *)((char *)D_002A0A90 + a0[2] * 0x4C);
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

extern int MoveChestForCatchBoy(void *a0);
extern void BoxBarSoundOn(void *a0, int a1);
int actEnemyHyde(void *a0) {
    int r = MoveChestForCatchBoy(a0);
    if (r != 0) {
        func_00163988((int *)a0, 0, 0);
    }
    BoxBarSoundOn(a0, 0xF1);
    return r;
}

int actEnemyFlagOnFree(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    if (q->f_1E0 == 0 && p->f_30 == 0x10) {
        return q->f_218;
    }
    return 0;
}

int afterCommonCarry(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    return q->f_1E0 == 1;
}

int actEnemyFlagOnDead(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    return q->f_1E0 == 2;
}

int EnemyBrainStatus_Boy(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    return q->f_1E0 == 0;
}

extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern char D_00553110[];
extern char D_00553120[];
int EnemyBrainStatus_Girl(void *a0, int *a1) {
    void *p = *(char **)((char *)a0 + 0x164);
    int v = *(int *)(*(char **)((char *)p + 0x670) + 0x1FC);
    int w;
    if (v != 5) return 0;
    w = *(int *)(*(char **)((char *)p + 0x678) + 0x400);
    *a1 = w;
    if (w == 0) {
        func_001AAD00(D_00553110, 0x2E8);
        func_00260380(D_00553110, 0x2E8, D_00553120);
    }
    return 1;
}

extern int D_00629DE8;

int actEnemyFlagCheckDead(char *self)
{
    char *sub;
    char *sub2;
    if (D_00629DE8 != 0) {
        char *sub_d = *(char **)((char *)D_00629DE8 + 0x164);
        if (*(int *)(sub_d + 0x30) != 0x6B) return 0;
    }
    sub = *(char **)((char *)self + 0x164);
    sub2 = *(char **)(sub + 0x670);
    return *(int *)(sub2 + 0x1FC) == 3;
}

int actEnemyFlagCheckActive(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    return q->f_1DC;
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
    p = (unsigned int *)((char *)D_002A0A90 + a0[2] * 0x4C);
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

extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern char D_005532B0[];
int actEnemy_isNormalEnemy(void *a0) {
    if (a0 == 0 || *(int *)((char *)a0 + 0xC) != 4) {
        func_001AAD00(D_00553110, 0x7C0);
        func_00260380(D_00553110, 0x7C0, D_005532B0);
    }
    return funcEnemyCarryFail((int *)a0);
}

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

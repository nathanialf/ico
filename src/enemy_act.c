#include "common.h"

#include "ico/types.h"

extern int D_0063A7E0;

/* INTERIM stand-in: the 2001 source declares _BrainMode_SetDirect `inline` -- the
   disc listing attributes the call sites below (subEnemyBrain_Shoulder, _Pickup,
   _Bodyslam, ...) to its body lines 3055-3060 -- but its out-of-line copy must
   keep its own ROM slot further down while the rest of this TU's tail is still
   asm, and gcc 2.9 emits `inline` bodies at the END of the object.  Delete this
   twin and mark the real definition `inline` once the tail is C and the TU can
   be laid out. */
extern char *D_00639EA8;
extern void iosOmSendMail(int a0, int a1, int a2);
extern void eBrainSendMes(int a0, int a1);

/* INTERIM stand-in: afterCommonCarry is `inline` in the 2001 source -- the disc
   listing attributes subEnemyBrain_Irregular's mail block to its body lines
   3578-3593 -- while its out-of-line copy keeps its own ROM slot below.  Same
   deal as _BrainMode_SetDirect_INTERIM. */
static inline void afterCommonCarry_INTERIM(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    int self = a0;
    *(int *)(sub + 0x148) = (int)D_00639EA8;
    iosOmSendMail((int)D_00639EA8, 0x30, self);
    *(int *)(sub + 0x148) = 0;
    if (*(int *)(sub + 0x34) == 5) {
        eBrainSendMes(a0, 4);
    }
}

static inline void _BrainMode_SetDirect_INTERIM(char *a0, int a1, int *a2) {
    *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x208) = a1;
    if (a2 != 0) {
        *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x214) = *a2;
    } else {
        *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x214) = D_0063A7E0;
    }
}

extern char D_00553370[];
extern char D_0063A7E8[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

/* The enemy work's status word at +0x210 is a 64-bit flag set with a byte
   view; the union is what makes a write to it alias the pointer chase that
   reaches it, which is why ROM re-walks self->sub->enemy for the second
   assignment of every arm below. */
typedef union {
    char c[8];
    long long ll;
} EnemyStatusFlags;

typedef struct {
    char pad000[0x1E0];
    float bodySize;
    int liftKind;
    char pad1E8[0x1EC - 0x1E8];
    int battleType;
    char pad1F0[0x210 - 0x1F0];
    EnemyStatusFlags flags;
} EnemyBattleWork;

typedef struct {
    char pad000[0x14];
    void *after;
    char pad018[0x120 - 0x18];
    float dir[4];
    char pad130[0x680 - 0x130];
    EnemyBattleWork *enemy;
} EnemyActSub;

typedef struct {
    char pad000[0x164];
    EnemyActSub *sub;
} EnemyBattleGObj;

void setBattleStatus(EnemyBattleGObj *self)
{
    switch (self->sub->enemy->battleType) {
    case 0:
        self->sub->enemy->flags.ll &= ~1LL;
        self->sub->enemy->flags.ll &= ~2LL;
        break;
    case 1:
        self->sub->enemy->flags.ll &= ~1LL;
        self->sub->enemy->flags.ll |= 2LL;
        break;
    case 2:
        self->sub->enemy->flags.ll |= 1LL;
        self->sub->enemy->flags.ll &= ~2LL;
        break;
    case 3:
        self->sub->enemy->flags.ll |= 1LL;
        self->sub->enemy->flags.ll |= 2LL;
        break;
    default:
        debug_assert(D_00553370, 0x36B);
        __assert(D_00553370, 0x36B, D_0063A7E8);
    }
}
extern void boss_effect_callback(int id);
extern void *memset(void *dst, int c, int n);
extern void sceVu0CopyVector(float *dst, float *src);
extern int GatherEffect_Set(int kind, char *a, float *b, char *c, float f, void *fn);
extern void ReviveEnemyParticle(char *self, int id);
extern int D_0028F4C0[];

/* static inline of the 2001 source, listing lines 973-977 -- inlined by both
   boss_effect_start and boss_effect_process (the rows attributed to 973 are
   each call's argument setup, which is why they differ between the two). */
static inline void bossEffectSetNodePos(char *self, float *dst, int idx)
{
    char *g = *(char **)(self + 0x15C);

    sceVu0CopyVector(dst, (float *)(*(char **)(g + 0xC) + idx * 0x40 + 0x30));
    dst[3] = 1.0f;
}

#define BOSS_START_WORK(self) (*(int *)(*(int *)((self) + 0x164) + 0x680))

void boss_effect_start(char *self, int id)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (*(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x37D) == 0) {
            float buf[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

            bossEffectSetNodePos(self, (float *)(i * 0x20 + BOSS_START_WORK(self) + 0x360), id);
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x370) =
                GatherEffect_Set(12, (char *)BOSS_START_WORK(self) + (i * 0x20 + 0x360), buf,
                                 (char *)BOSS_START_WORK(self) + (i * 0x20 + 0x360), 1.0f,
                                 (void *)boss_effect_callback);
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x374) = id;
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x378) =
                (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1];
            *(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x37C) = 1;
            *(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x37D) = 1;
            return;
        }
    }
    ReviveEnemyParticle(self, id);
}
extern void boss_effect_start(char *a0, int a1);

void boss_effect_check_parts(char *a0, int a1) {
    char *p = *(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x360;
    int i;
    for (i = 0; i < 5; i++, p += 0x20) {
        if (p[0x1D] != 0 && *(int *)(p + 0x14) == a1) {
            return;
        }
    }
    boss_effect_start(a0, a1);
}
extern int isExistEnemyParticle(char *self, int i);
extern void GatherEffect_SetGoal(int gobj, float *pos);

typedef struct {
    char pad00[0x14];
    int id;
    int timer;
    char busy;
    char alive;
    char pad1E[2];
} BossPart;

#define BOSS_EFFECT_WORK(self) ((char *)*(int *)(*(int *)((self) + 0x164) + 0x680))
#define BOSS_EFFECT_PARTS(self, i) ((BossPart *)((i) * 0x20 + BOSS_EFFECT_WORK(self) + 0x360))

void boss_effect_process(char *self)
{
    float tmp[4];
    int n;
    int i;

    n = *(int *)(*(char **)(self + 0x15C) + 0x88);
    for (i = 0; i < n; i++) {
        if (isExistEnemyParticle(self, i) == 0) {
            boss_effect_check_parts(self, i);
        }
    }
    for (i = 0; i < 5; i++) {
        if (BOSS_EFFECT_PARTS(self, i)->alive == 0) {
            continue;
        }
        if (BOSS_EFFECT_PARTS(self, i)->busy != 0) {
            bossEffectSetNodePos(self, tmp, BOSS_EFFECT_PARTS(self, i)->id);
            GatherEffect_SetGoal(*(int *)((char *)(i * 0x20 + BOSS_EFFECT_WORK(self)) + 0x370),
                                 tmp);
        }
        if (BOSS_EFFECT_PARTS(self, i)->timer == 0) {
            ReviveEnemyParticle(self, BOSS_EFFECT_PARTS(self, i)->id);
        }
        if (BOSS_EFFECT_PARTS(self, i)->busy == 0 && BOSS_EFFECT_PARTS(self, i)->timer < 0) {
            BOSS_EFFECT_PARTS(self, i)->alive = 0;
        }
        BOSS_EFFECT_PARTS(self, i)->timer -= 1;
    }
}
extern void *D_00639EA4;

typedef struct {
    char pad00[0x100];
    int f100;
    char pad104[0x18C - 0x104];
    unsigned int flags18C;
    char pad190[4];
} EnemyParaRow;

extern EnemyParaRow D_0055FE58[];
extern void _ACTParaStatus_Set(char *self, int bit);
extern void EnemyUtil_TurnToBoy(char *self, int tgt, int a2);

void _DoAwait(char *self)
{
    EnemyParaRow *row;
    if (D_00639EA4 != 0) {
        _ACTParaStatus_Set(self, 0x1C);
        row = &D_0055FE58[*(int *)(*(char **)(self + 0x15C) + 0x4A0)];
        if ((row->flags18C >> 3) & 1) {
            EnemyUtil_TurnToBoy(self, (int)D_00639EA4, 5);
        }
    }
}
extern char *D_00639EA8;

void _DoAwaitGirl(char *self)
{
    EnemyParaRow *row;
    if (D_00639EA8 != 0) {
        _ACTParaStatus_Set(self, 0x1C);
        row = &D_0055FE58[*(int *)(*(char **)(self + 0x15C) + 0x4A0)];
        if ((row->flags18C >> 3) & 1) {
            EnemyUtil_TurnToBoy(self, (int)D_00639EA8, 5);
        }
    }
}
extern void *D_00639EA4;
extern float _DistxzSqGV(float *a0, float *a1);
extern void *test_CURRENTROOT(int a0);

int _MustChase(int a0) {
    float v1[4];
    float v2[4];
    float angle;
    float diff;
    int rv;
    if (D_00639EA4 == 0) {
        goto zero;
    }
    v1[0] = ((float *)test_CURRENTROOT((int)D_00639EA4))[0];
    v1[1] = ((float *)test_CURRENTROOT((int)D_00639EA4))[1];
    v1[2] = ((float *)test_CURRENTROOT((int)D_00639EA4))[2];
    v2[0] = ((float *)test_CURRENTROOT(a0))[0];
    v2[1] = ((float *)test_CURRENTROOT(a0))[1];
    v2[2] = ((float *)test_CURRENTROOT(a0))[2];
    angle = _DistxzSqGV(v1, v2);
    if (angle < 90000.0f) {
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
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyControl);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyCollision);
extern void _OrientXZGV(float *dst, float *a, float *b);
extern void SetMotionDirection(void *self, float *dir);
extern void ACTSendMailCorrect(void *a0, int a1);
extern void _ACTWait(int a0);
extern void ACTSearchEnemy(void *self, int *target, float *buf);
extern int GetMotionFrameFlag2(void *self);
extern void SetMotionDirectionWithLimit(void *self, float *buf, float a, float b);
extern void EnemyAttackCenter(void *self);

/* The actor sub-state's requested motion direction, a 3-float vector at
   +0x120 (the same slot _ApproachTarget and the brain zero-fills below).
   Spelling the three stores as struct members rather than `*(float *)`
   casts is what lets the volatile `a0` home reload hoist above the first
   of them, as ROM has it (gcc 2.9 alias.c fixed_scalar_and_varying_struct_p:
   a COMPONENT_REF store is in-struct/varying, a cast store is not). */
typedef struct {
    char pad000[0x120];
    float dir[3];
} ActSubDir;

void actEnemyAttack(volatile int a0)
{
    char *sub = *(char **)(a0 + 0x164);
    int hit = 0;
    float buf[4];
    float v[4];

    _ACTWait(2);
    ACTSearchEnemy((void *)a0, (int *)(sub + 0x188), buf);
    _OrientXZGV(v, (float *)test_CURRENTROOT((int)D_00639EA4),
                (float *)test_CURRENTROOT(a0));
    ((ActSubDir *)sub)->dir[0] = v[0];
    ((ActSubDir *)sub)->dir[1] = v[1];
    ((ActSubDir *)sub)->dir[2] = v[2];
    SetMotionDirection((void *)a0, v);
    while (1) {
        if (GetMotionFrameFlag2((void *)a0) != 0 && *(int *)(sub + 0x188) != 0) {
            SetMotionDirectionWithLimit((void *)a0, buf, 10.0f, 90.0f);
        }
        if (*(int *)(sub + 0x2E4) & 0x80) {
            hit = 1;
        }
        if (hit != 0) {
            ACTSendMailCorrect((void *)a0, 0xCD);
        }
        ACTSendMailCorrect((void *)a0, 0xC7);
        EnemyAttackCenter((void *)a0);
        _ACTWait(1);
    }
}
extern void SetDirectRootPositionNoFitting(int *self, char *spill);
extern int gamesysObjInfoPosSetStage(int w, int a1, int a2, int stage);
extern int stage_no;
extern void RandomizeEnemy(char *self);
extern int GetEnemyBattleType(char *self);
extern float GetEnemyDefLife(char *self);
extern float _ACTGame_GetParamF(int idx);
extern void InitMotionGeoInfo(char *p, float x, float y, float z, float a, float b,
                              float c);
extern void ResetEnemyPositionInfo(int *self);
extern void SetEnemyDissolve(char *self, float t);
extern void _BrainMode_SetDirect(char *a0, int a1, int *a2);
extern int D_0063AA00;
extern char D_002A8570[];

/* The disc listing attributes rows 2138-2143 -- which lie ABOVE this function's
   own def line 2151 -- to bodies inside both actEnemyRestart and actEnemyStart,
   so the 2001 source has a `static inline` here.  `max` really is a local (line
   2138 is its `li $a1,43`): with the literal 43 written into the compare, fold
   rewrites `idx <= 43` into `idx < 44` and gcc emits `slti`+`movn`, where ROM
   has `slt`+`movz` off a register-held 43.  Name derived: a fully-inlined
   static has no MAIN.MAP symbol. */
static inline float getEnemyRestartLife(char *self)
{
    int max = 43;
    int idx = D_0063AA00 + 38;

    idx = (idx < 38) ? 38 : ((idx <= max) ? idx : max);
    return GetEnemyDefLife(self) * _ACTGame_GetParamF(idx);
}

void actEnemyRestart(char *self, float *pos, float *dir, int kind, int mot)
{
    float v[4];
    char *sub;
    int mail;
    int idx;
    float life;

    sub = *(char **)(self + 0x164);
    mail = 50;
    v[0] = pos[0];
    v[2] = pos[2];
    v[1] = pos[1] - 100.0f;
    SetDirectRootPositionNoFitting((int *)self, (char *)v);
    gamesysObjInfoPosSetStage((int)self, *(int *)(sub + 0x444), 0, stage_no);
    switch (kind) {
    case 0:
        pos[1] = pos[1] +
                 *(float *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0x1E0) *
                     100.0f;
        break;
    case 1:
        mail = 51;
        break;
    case 2:
        mail = 52;
        break;
    }
    if (((int)(*(long long *)(sub + 0x20) >> 29)) & 1) {
        *(long long *)(sub + 0x20) = *(long long *)(sub + 0x20) & ~0x20000000;
    } else {
        RandomizeEnemy(self);
    }
    idx = 0;
    switch (GetEnemyBattleType(self)) {
    case 0:
        break;
    case 1:
        idx = 1;
        break;
    case 2:
        idx = 2;
        break;
    case 3:
        idx = 3;
        break;
    default:
        debug_assert(D_00553370, 2161);
        __assert(D_00553370, 2161, D_0063A7E8);
    }
    *(int *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0x1EC) = idx;
    setBattleStatus((EnemyBattleGObj *)self);
    life = getEnemyRestartLife(self);
    *(float *)(sub + 0x1E4) = life;
    *(float *)(sub + 0x1E0) = life;
    *(int *)(sub + 0x350) = 0;
    if (mot != 0) {
        *(int *)(sub + 0x54) = mot;
    } else {
        *(int *)(sub + 0x54) = 0;
    }
    *(int *)(sub + 0xD4) = (int)D_002A8570;
    ACTSendMailCorrect(self, mail);
    InitMotionGeoInfo(*(char **)(self + 0x15C) + 0xA0, pos[0], pos[1], pos[2], 0.0f,
                      0.0f, 0.0f);
    ResetEnemyPositionInfo((int *)self);
    SetEnemyDissolve(self, 0.0f);
    *(float *)(sub + 0x170) = pos[0];
    *(float *)(sub + 0x174) = pos[1];
    *(float *)(sub + 0x178) = pos[2];
    SetMotionDirection(self, dir);
    eBrainSendMes((int)self, 4);
    _BrainMode_SetDirect(self, 0, 0);
}
ASM_LIT4_SLOT(D_00638EF8, 0.001f);
ASM_LIT4_SLOT(D_00638EFC, 0.1f);
ASM_LIT4_SLOT(D_00638F00, 0.99f);
ASM_LIT4_SLOT(D_00638F04, 0.1f);
ASM_LIT4_SLOT(D_00638F08, 0.99f);
ASM_LIT4_SLOT(D_00638F0C, 0.1f);
ASM_LIT4_SLOT(D_00638F10, 0.99f);
ASM_LIT4_SLOT(D_00638F14, 0.1f);
ASM_LIT4_SLOT(D_00638F18, 0.1f);
ASM_LIT4_SLOT(D_00638F1C, 0.1f);
extern int ACTReserveTarget(void *owner, void *self, int pri);
extern void sceVu0ScaleVector(float *dst, float *src, float k);
extern void sceVu0AddVector(float *dst, float *a, float *b);
extern void SetDirectRootPositionNoFitting(int *self, char *spill);
extern void RotQuaternionY(float *q, int deg);
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q,
                                          float e, float f, float g, float h);
extern int D_0063B248;

/* PairSetGeometry is a NESTED function in the 2001 source: ROM passes it a
   static chain in $2 (STATIC_CHAIN_REGNUM) which it spills to 0($sp), and the
   listing names it PairSetGeometry.229, emitting its body ahead of its parent
   exactly as gcc 2.9 does for a nested definition. */
int actEnemyForceSwitchToCarry(void *a0)
{
    void PairSetGeometry(void *me, void *pair, float dist)
    {
        float p0[4];
        float p1[4];
        float dir[4];
        float ofs[4];

        p0[0] = ((float *)test_CURRENTROOT((int)me))[0];
        p0[1] = ((float *)test_CURRENTROOT((int)me))[1];
        p0[2] = ((float *)test_CURRENTROOT((int)me))[2];
        p1[0] = ((float *)test_CURRENTROOT((int)pair))[0];
        p1[1] = ((float *)test_CURRENTROOT((int)pair))[1];
        p1[2] = ((float *)test_CURRENTROOT((int)pair))[2];
        _OrientXZGV(dir, p1, p0);
        sceVu0ScaleVector(ofs, dir, dist);
        sceVu0AddVector(p1, p0, ofs);
        SetDirectRootPositionNoFitting((int *)pair, (char *)p1);
        *(float *)(*(char **)((char *)me + 0x164) + 0x120) = dir[0];
        *(float *)(*(char **)((char *)me + 0x164) + 0x124) = dir[1];
        *(float *)(*(char **)((char *)me + 0x164) + 0x128) = dir[2];
        sceVu0ScaleVector((float *)(*(char **)((char *)pair + 0x164) + 0x120), dir, -1.0f);
        SetMotionDirection(me, (float *)(*(char **)((char *)me + 0x164) + 0x120));
        SetMotionDirection(pair, (float *)(*(char **)((char *)pair + 0x164) + 0x120));
    }
    float q[4];
    char *sub = *(char **)((char *)a0 + 0x164);

    if (D_00639EA8 == 0) {
        return 0;
    }
    if (ACTReserveTarget(D_00639EA8, a0, 0xFF) == 0) {
        return 0;
    }
    if (*(int *)(*(char **)(D_00639EA8 + 0x164) + 0x34) == 0x6F) {
        return 0;
    }
    PairSetGeometry(a0, D_00639EA8, 50.0f);
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, -0x8000);
    SetMotionNodeFixModeParameter(D_00639EA8, a0, 2,
                                  *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x1F4),
                                  q, 18.0f, 0.0f, 0.0f, 1.0f);
    *(int *)(sub + 0x148) = (int)D_00639EA8;
    *(int *)(*(char **)(D_00639EA8 + 0x164) + 0x144) = (int)a0;
    eBrainSendMes((int)a0, 9);
    eBrainSendMes((int)a0, 7);
    if ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2 < *(int *)(sub + 0x10) && D_0063B248 != 0) {
        *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x4D0) = 1;
        if (D_00639EA4 != 0) {
            *(float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x4E0) =
                ((float *)test_CURRENTROOT((int)D_00639EA4))[0];
            *(float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x4E4) =
                ((float *)test_CURRENTROOT((int)D_00639EA4))[1];
            *(float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x4E8) =
                ((float *)test_CURRENTROOT((int)D_00639EA4))[2];
        } else {
            *(float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x4E0) =
                ((float *)test_CURRENTROOT((int)a0))[0];
            *(float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x4E4) =
                ((float *)test_CURRENTROOT((int)a0))[1];
            *(float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x4E8) =
                ((float *)test_CURRENTROOT((int)a0))[2];
        }
    }
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyKidnapEnd);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyKidnapBegin);
ASM_LIT4_SLOT(D_00638F20, 10000.0f);
ASM_LIT4_SLOT(D_00638F24, 0.0001f);
ASM_LIT4_SLOT(D_00638F28, 0.01f);
ASM_LIT4_SLOT(D_00638F2C, 0.1f);
extern void *D_00639EA4;
extern void *test_CURRENTORIENT(int a0);
extern void GetRootProjectionPosOfGObj(float *dst, char *gobj);
extern void GetSkeltonPosition(float *dst, char *gobj, int idx);
extern void _OrientXZGV(float *dst, float *a, float *b);
extern int _RotyGV(float *a0, void *a1);
extern void _ApplyRyGV(float *v, float ang);
extern void sceVu0ScaleVector(float *dst, float *src, float s);
extern void sceVu0AddVector(float *dst, float *a, float *b);
extern void debug_NMarker(float *pos, int r, int g, int b, float size);

void MoveChestForCatchBoy(char *self)
{
    float p0[4];
    float p1[4];
    float sk[4];
    float ori[4];
    float d[4];
    float sc[4];
    float t;
    float b;
    float a;
    int ang;
    int far;
    int ang2;

    *(int *)(*(int *)(self + 0x15C) + 0x550) = 1;
    *(int *)(*(int *)(self + 0x15C) + 0x380) = 2;
    GetRootProjectionPosOfGObj(p0, self);
    GetRootProjectionPosOfGObj(p1, (char *)D_00639EA4);
    GetSkeltonPosition(sk, self, 1);
    t = (p0[1] - p1[1]) / 600.0f;
    t = (t < 0.0f) ? 0.0f : ((1.0f < t) ? 1.0f : t);
    a = t * 1000.0f + -200.0f;
    b = t * -400.0f;
    ori[0] = ((float *)test_CURRENTORIENT((int)self))[0];
    ori[1] = ((float *)test_CURRENTORIENT((int)self))[1];
    ori[2] = ((float *)test_CURRENTORIENT((int)self))[2];
    _OrientXZGV(d, p1, p0);
    ang = _RotyGV(ori, (void *)d);
    if (-45 <= ang) {
        if (45 < ang) {
            ang2 = 45;
        } else {
            ang2 = ang;
        }
    } else {
        ang2 = -45;
    }
    _ApplyRyGV(ori, (float)ang2 * 3.1415927f / 180.0f);
    sceVu0ScaleVector(sc, ori, a);
    sc[1] = b;
    sceVu0AddVector((float *)(*(char **)(self + 0x15C) + 0x390), p0, sc);
    debug_NMarker((float *)(*(char **)(self + 0x15C) + 0x390), 255, 0, 0, 200.0f);
}

extern void GetMatrixDirectionToZ(float *dst, void *ori);
extern void sceVu0ApplyMatrix(float *dst, float *m, float *v);
extern void sceVu0SubVector(float *dst, float *a, float *b);
extern float _DistSqGV(float *a, float *b);
extern int GetMotionFrameFlag1(void *self);
extern int GetMotionFrameFlag2(void *self);
extern void _ACTMotDirSmzDirect(void *self, float *dir);
extern void afterEnemyBodylift(volatile int a0);
extern float D_0029D100[];

/* listing rows 2655-2657: a `static inline` outside this function's span. */
static inline void enemyBodyliftClearBoy(char *self)
{
    *(int *)(*(int *)(self + 0x15C) + 0x550) = 0;
    *(int *)(*(int *)(self + 0x15C) + 0x380) = 0;
}

void actEnemyBodylift(volatile int a0)
{
    float dir[4];
    float pos[4];
    float bpos[4];
    float mtx[16];
    float lv[4];
    EnemyActSub *sub;
    int hit;

    sub = ((EnemyBattleGObj *)a0)->sub;
    hit = 0;
    ((EnemyBattleGObj *)a0)->sub->enemy->flags.ll &= ~4LL;
    _OrientXZGV(dir, D_0029D100, (float *)test_CURRENTROOT((int)a0));
    sub->after = (void *)afterEnemyBodylift;
    if (((EnemyBattleGObj *)a0)->sub->enemy->liftKind != 3) {
        _OrientXZGV(sub->dir, (float *)test_CURRENTROOT((int)D_00639EA4),
                    (float *)test_CURRENTROOT((int)a0));
        SetMotionDirection((void *)a0, sub->dir);
    }
    for (;;) {
        ((EnemyBattleGObj *)a0)->sub->enemy->flags.ll &= ~4LL;
        if (((EnemyBattleGObj *)a0)->sub->enemy->liftKind == 3) {
            if (*(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 94) {
                enemyBodyliftClearBoy((char *)a0);
            } else {
                MoveChestForCatchBoy((char *)a0);
            }
        }
        GetSkeltonPosition(pos, (char *)a0, 22);
        bpos[0] = ((float *)test_CURRENTROOT((int)D_00639EA4))[0];
        bpos[1] = ((float *)test_CURRENTROOT((int)D_00639EA4))[1];
        bpos[2] = ((float *)test_CURRENTROOT((int)D_00639EA4))[2];
        if (((EnemyBattleGObj *)a0)->sub->enemy->liftKind == 3) {
            sceVu0SubVector(lv, (float *)test_CURRENTROOT((int)D_00639EA4), pos);
            GetMatrixDirectionToZ(mtx, test_CURRENTORIENT((int)a0));
            lv[3] = 0.0f;
            sceVu0ApplyMatrix(lv, mtx, lv);
            if (((lv[0] < 0.0f) ? -lv[0] : lv[0]) < 100.0f &&
                ((lv[1] < 0.0f) ? -lv[1] : lv[1]) < 100.0f && -300.0f < lv[2] &&
                lv[2] < 200.0f) {
                hit = 1;
            }
        } else {
            if (_DistSqGV(pos, bpos) <
                *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1E0) * 45.0f *
                    (*(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1E0) *
                     45.0f)) {
                hit = 1;
            }
        }
        /* Listing row 167d4c is a volatile read of the actor-entry home whose
           value nothing consumes, attributed to source line 2785 -- and lines
           2786..2807 emit no instructions at all, so 2785 is the surviving
           access of a statement whose remaining 22 lines were compiled out.
           A volatile access cannot be manufactured by scheduling, so the read
           has to be written. */
        (void)a0;
        if (GetMotionFrameFlag1((void *)a0) != 0 && hit != 0) {
            iosOmSendMail((int)D_00639EA4, 0x170, a0);
        }
        if (GetMotionFrameFlag2((void *)a0) != 0) {
            _OrientXZGV(bpos, (float *)test_CURRENTROOT((int)D_00639EA4),
                        (float *)test_CURRENTROOT((int)a0));
            _ACTMotDirSmzDirect((void *)a0, bpos);
        }
        if (*(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 94 &&
            *(int *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x680) +
                     0x22C) == (int)a0) {
            if (((EnemyBattleGObj *)a0)->sub->enemy->liftKind == 3) {
                if (0 < *(int *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x164) +
                                            0x680) +
                                 0xCC)) {
                    ACTSendMailCorrect((void *)a0, 0x176);
                } else {
                    ACTSendMailCorrect((void *)a0, 0x177);
                }
            } else {
                ACTSendMailCorrect((void *)a0, 0x174);
            }
        } else {
            ACTSendMailCorrect((void *)a0, 0xC7);
        }
        _ACTWait(1);
    }
}
extern void *test_CURRENTROOT(int a0);
extern void *test_CURRENTORIENT(int a0);
extern void _OrientXZGV(float *dst, float *a, float *b);
extern void SetMotionDirection(void *self, float *dir);
extern int _RotyGV(float *a0, void *a1);
extern int _ACTGame_SearchGObj(int self, char *tgt, float range, float height, int angle, float *out);
extern void ACTGame_InsertCamera_GirlIsPinch(void);
extern int actEnemyForceSwitchToCarry(void *a0);
extern void ACTSendMailCorrect(void *a0, int a1);
extern void _ACTWait(int a0);

/* Static inline of the 2001 source (listing lines 2889-2892 sit inside
   actEnemyPickupBegin's ROM range but above its own body lines).  ROM's frame
   is 0x80 with the 16-byte slot at sp+0x10 never referenced and buf at sp+0x20,
   so a second 16-byte vector was declared here ahead of buf and left unused. */
static inline int enemyPickupCheckGirl(int self)
{
    float pos[4];
    float buf[4];
    int ang;
    int mode;

    if (_ACTGame_SearchGObj(self, D_00639EA8, 170.0f, 100.0f, 45, buf) != 0) {
        ang = _RotyGV(buf, test_CURRENTORIENT((int)D_00639EA8));
        ang = (ang < 0) ? -ang : ang;
        mode = 2;
        if (ang <= 89) {
            mode = 1;
        }
    } else {
        mode = 0;
    }
    return mode;
}

void actEnemyPickupBegin(volatile int a0)
{
    float *dir = (float *)(*(char **)(a0 + 0x164) + 0x120);
    float *girl = (float *)test_CURRENTROOT((int)D_00639EA8);
    float *me = (float *)test_CURRENTROOT(a0);
    int mode;

    _OrientXZGV(dir, girl, me);
    SetMotionDirection((void *)a0, dir);
    while (1) {
        mode = enemyPickupCheckGirl(a0);
        if (mode < 3 && mode != 0) {
            if (actEnemyForceSwitchToCarry((void *)a0) != 0) {
                ACTGame_InsertCamera_GirlIsPinch();
                while (1) {
                    ACTSendMailCorrect((void *)a0, 0x16D);
                    _ACTWait(1);
                }
            }
        }
        ACTSendMailCorrect((void *)a0, 0x16E);
        _ACTWait(1);
    }
}
extern char D_002C2DC8[];

/* INTERIM stand-in: actEnemyFlagCheckActive is `inline` in the 2001 source (the
   disc listing attributes this call site's words to its body lines 2077-2096,
   and isEnemyHyde's line 2047 inside it), but its out-of-line copy must keep its
   own ROM slot above while the rest of this TU's tail is asm.  Drop it and mark
   the real definition `inline` once the tail is C. */
static inline int actEnemyFlagCheckActive_INTERIM(int *a0)
{
    unsigned int *p = (unsigned int *)(D_002C2DC8 + a0[2] * 0x4C);
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

extern void *eBrainGetTarget(char *self);

/* static inline of the 2001 source, listing lines 1148-1164 */
static inline int getEnemyBrainMes(char *self, int *data)
{
    char *t = (char *)eBrainGetTarget(self);

    if (t == 0) {
        *data = 0;
        return 0;
    }
    *data = *(int *)(t + 4);
    return *(unsigned short *)t;
}

void CheckEnemyBrainMode(char *self, int *outMode, int *outData)
{
    char *sub = *(char **)(self + 0x164);
    int mode;

    *outData = 0;
    if (*(int *)(sub + 0x148) != 0 &&
        D_0055FE58[*(int *)(*(char **)(self + 0x15C) + 0x4A0)].f100 == 0) {
        *outMode = -1;
        return;
    }
    if (((*(unsigned long long *)(sub + 0x18) >> 49) & 1) == 0) {
        *outMode = -1;
        return;
    }
    if (actEnemyFlagCheckActive_INTERIM((int *)self) == 0) {
        *outMode = -1;
        return;
    }
    switch (*(unsigned int *)(sub + 0x34)) {
    case 7:
    case 19:
    case 20:
    case 21:
    case 22:
    case 114:
    case 115:
        *outMode = -1;
        return;
    case 103:
        if (D_00639EA8 == 0) {
            *outMode = -1;
            return;
        }
        if (*(int *)(*(char **)(D_00639EA8 + 0x164) + 0x34) != 0x6F) {
            *outMode = -1;
            return;
        }
        if (*(int *)(*(char **)(D_00639EA8 + 0x164) + 0x144) != (int)self) {
            *outMode = -1;
            return;
        }
        break;
    }
    if (((*(unsigned long long *)(sub + 0x20) >> 34) & 1) == 0) {
        goto no_bit;
    }
    *(unsigned long long *)(sub + 0x20) &= ~(1ULL << 34);
    mode = -2;
    goto store;
no_bit:
    mode = getEnemyBrainMes(self, outData);
store:
    *outMode = mode;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", BrainMode_Requset);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyBrainMain);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyBrain_ToGenerator);

extern float _DistGV(void *a, void *b);
extern void GetRootPosition(float *dst, char *gobj);
extern float GetEnemyDefDodgeRange(char *self);
extern int IsBoyStatus_NotDanger(void);
extern int D_0063B240;
extern void sceVu0SubVector(float *dst, float *a, float *b);
extern void sceVu0Normalize(float *dst, float *src);
extern float _GetRandom(void);
extern int EnemyUtil_isOtherStatus(char *self, int mode);

/* static inline of the 2001 source, listing lines 1985-1997.  `sub` is computed
   INSIDE the helper (row 1986): in enemy_dodge the caller already holds it so
   cse deletes the load, which is why that call site shows only rows 1989-1997,
   while subEnemyBrain_Attack's two expansions carry 1985 and 1986 as real
   instructions. */
static inline void enemyDodgeSendMail(char *self)
{
    char *sub = *(char **)(self + 0x164);

    if (EnemyUtil_isOtherStatus(self, 0) != 0) {
        return;
    }
    if (((int)(_GetRandom() * 10.0f)) & 1) {
        ACTSendMailCorrect(self, 0xCF);
    }
    ACTSendMailCorrect(self, 0xCD);
    *(long long *)(sub + 0x20) |= 0x400;
}

void enemy_dodge(char *self)
{
    float a[4];
    float b[4];
    float c[4];
    char *boy = (char *)D_00639EA4;
    char *sub;
    float d;
    int ang;

    if (boy == 0) {
        return;
    }
    d = _DistGV(test_CURRENTROOT((int)boy), test_CURRENTROOT((int)self));
    if (d < GetEnemyDefDodgeRange(self)) {
        GetRootPosition(a, self);
        GetRootPosition(b, boy);
        sceVu0SubVector(c, b, a);
        sceVu0Normalize(c, c);
        ang = _RotyGV(c, test_CURRENTORIENT((int)boy));
        ang = (ang < 0) ? -ang : ang;
        if (ang < 114) {
            return;
        }
        ang = _RotyGV(c, test_CURRENTORIENT((int)self));
        ang = (ang < 0) ? -ang : ang;
        if ((float)ang < 45.0f) {
            if (IsBoyStatus_NotDanger() != 0) {
                return;
            }
            sub = *(char **)(self + 0x164);
            if ((((int)(*(long long *)(*(char **)(sub + 0x680) + 0x210) >> 1)) & 1) == 0) {
                if (d < 200.0f) {
                    enemyDodgeSendMail(self);
                }
            } else if (D_0063B240 == 0) {
                ACTSendMailCorrect(self, 0x113);
            }
        }
    }
}
extern float GetEnemyDefDodgeRange(char *self);
extern float _DistSqGV(float *a, float *b);
extern int IsBoyStatus_NotDanger(void);
extern int D_0063B240;

void enemy_dodge_to_boy(char *self)
{
    float boy[4];
    float me[4];
    float v[4];
    int ang;

    if (D_00639EA4 == 0) {
        return;
    }
    if (((int)(*(long long *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0x210) >> 1)) & 1) {
        boy[0] = ((float *)test_CURRENTROOT((int)D_00639EA4))[0];
        boy[1] = ((float *)test_CURRENTROOT((int)D_00639EA4))[1];
        boy[2] = ((float *)test_CURRENTROOT((int)D_00639EA4))[2];
        me[0] = ((float *)test_CURRENTROOT((int)self))[0];
        me[1] = ((float *)test_CURRENTROOT((int)self))[1];
        me[2] = ((float *)test_CURRENTROOT((int)self))[2];
        if (_DistSqGV(boy, me) <
            GetEnemyDefDodgeRange(self) * GetEnemyDefDodgeRange(self)) {
            _OrientXZGV(v, boy, me);
            ang = _RotyGV(v, test_CURRENTORIENT((int)D_00639EA4));
            ang = (ang < 0) ? -ang : ang;
            if (ang < 114) {
                return;
            }
            ang = _RotyGV(v, test_CURRENTORIENT((int)self));
            ang = (ang < 0) ? -ang : ang;
            if ((float)ang < 45.0f) {
                if (IsBoyStatus_NotDanger() != 0) {
                    return;
                }
                if (D_0063B240 != 0) {
                    return;
                }
                ACTSendMailCorrect(self, 0x113);
            }
        }
    }
}
extern float _DistxzGV(float *a, void *b);
extern int _AbsRotyGV(float *a, float *b);

/* listing rows 3858-3870: a `static inline` outside this function's span,
   expanded twice here (each expansion gets its OWN .lit4 0.7f and its own
   `1.2` .rodata double -- the pool duplication in ROM is what proves it is an
   inline function and not a shared helper). */
static inline float battleRangeScale(char *self, float v)
{
    char *work = *(char **)(*(char **)(self + 0x164) + 0x680);

    switch (*(int *)(work + 0x1E8)) {
    case 0:
    case 1:
        v = *(float *)(work + 0x1E0) * v;
        if (((int)(*(long long *)(work + 0x210) >> 1)) & 1) {
            v = v * 1.2;
        }
        break;
    case 2:
        v = *(float *)(work + 0x1E0) * 0.7f * v;
        break;
    }
    return v;
}

int Battle_isCurrentStatus(char *self, char *tgt, float *pos)
{
    float ori[4];
    float dir[4];
    int ret;
    float xz;
    float dy;
    float range;
    float vflag;
    float a;
    float b;
    int ang;
    int far;

    ret = 0;
    xz = _DistxzGV(pos, test_CURRENTROOT((int)tgt));
    dy = ((pos[1] - ((float *)test_CURRENTROOT((int)tgt))[1]) < 0.0f)
             ? -(pos[1] - ((float *)test_CURRENTROOT((int)tgt))[1])
             : (pos[1] - ((float *)test_CURRENTROOT((int)tgt))[1]);
    vflag = 0.0f;
    range = GetEnemyDefDodgeRange(self);
    if (200.0f < xz || battleRangeScale(self, 200.0f) < dy) {
        vflag = 1.0f;
    }
    if (xz < range && dy < battleRangeScale(self, 150.0f)) {
        vflag = -1.0f;
    }
    ori[0] = ((float *)test_CURRENTORIENT((int)tgt))[0];
    ori[1] = ((float *)test_CURRENTORIENT((int)tgt))[1];
    ori[2] = ((float *)test_CURRENTORIENT((int)tgt))[2];
    _OrientXZGV(dir, (float *)test_CURRENTROOT((int)self),
                (float *)test_CURRENTROOT((int)tgt));
    ang = _AbsRotyGV(ori, dir);
    a = (ang < 75) ? 1.0f : 0.0f;
    far = (101 <= ang);
    b = (a != 0.0f && *(int *)(*(char **)(tgt + 0x164) + 0x34) == 15) ? 1.0f : 0.0f;
    if (vflag < 0.0f) {
        ret = 1;
    }
    if (0.0f < vflag) {
        ret = 2;
    }
    if (b != 0.0f) {
        ret = 3;
    }
    if (vflag <= 0.0f) {
        ret = far ? 4 : ret;
    }
    return ret;
}
extern float _DistSqGV(float *a, float *b);
extern float _GetRandom(void);
extern float D_0063A7F4[];
extern float D_0029D130[4][4];
extern float D_0029D170[4][4];
extern float D_0029D1B0[];

int GetFlyPosition(float *out, float *me, float *tgt)
{
    int ret;

    ret = 0;
    if (tgt[1] < -500.0f && 1000.0f < ((tgt[2] < 0.0f) ? -tgt[2] : tgt[2]) &&
        -500.0f < me[1]) {
        out[0] = D_0029D1B0[0];
        out[1] = D_0029D1B0[1];
        out[2] = D_0029D1B0[2];
        return 2;
    }
    if (tgt[1] < -500.0f && 1000.0f < ((tgt[2] < 0.0f) ? -tgt[2] : tgt[2]) &&
        _DistSqGV(me, tgt) < 160000.0f) {
        out[0] = D_0029D1B0[0];
        out[1] = D_0029D1B0[1];
        out[2] = D_0029D1B0[2];
        return 2;
    }
    if (-150.0f < me[1]) {
        float best = D_0063A7F4[0];
        int besti = -1;
        int i;

        for (i = 0; i < 4; i++) {
            float d = _DistSqGV(me, D_0029D130[i]);

            if (d < best) {
                best = d;
                besti = i;
            }
        }
        if (besti != -1) {
            float *p = D_0029D170[besti];

            ret = 1;
            out[0] = p[0];
            out[1] = p[1];
            out[2] = p[2];
        }
    } else {
        float best = 0.0f;
        int besti = -1;
        int i;

        for (i = 0; i < 4; i++) {
            float d = _DistSqGV(tgt, D_0029D130[i]);

            if (best < d) {
                best = d;
                besti = i;
            }
        }
        if (besti != -1) {
            ret = 1;
            if (((int)(_GetRandom() * 10.0f)) & 1) {
                out[0] = D_0029D1B0[0];
                out[1] = D_0029D1B0[1];
                out[2] = D_0029D1B0[2];
            } else {
                /* The table base is its OWN statement: ROM computes
                   `addiu $v1,$s5,%lo(D_0029D130)` BEFORE `sll $v0,$s4,4`, which
                   only happens when the address is op0 of the PLUS.  Written as
                   one expression, `fold` sinks the (constant) address to op1 in
                   every spelling measured -- `D_0029D130[besti]`,
                   `(float *)D_0029D130 + besti*4`, `D_0029D130[0] + besti*4`,
                   `&D_0029D130[besti][0]`, `&D_0029D130[0][besti*4]`,
                   `besti*4 + D_0029D130[0]`, a struct-typed row, and `p = base;
                   p += besti*4;` -- so `sll` is emitted first, both arms' copy
                   blocks end up in the same registers and jump2 cross-jumps
                   them into one (6 insns short). */
                float *tbl = D_0029D130[0];
                float *p = tbl + besti * 4;

                out[0] = p[0];
                out[1] = p[1];
                out[2] = p[2];
            }
        }
    }
    return ret;
}
extern int _AbsRotyGV(float *a, float *b);
extern int stage_no;
extern void debug_StdPrintfDummy(char *fmt);

void NakaBoss(char *self, int flag)
{
    float bpos[4];
    float mpos[4];
    float ori[4];
    float dir[4];
    char *boy = D_00639EA4;
    int inc = 0;
    int half = (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 4;
    float dist;
    char *sub;

    if (stage_no != 86 && stage_no != 3 && stage_no != 46) {
        if (flag != 0) {
            enemy_dodge_to_boy(self);
        }
        return;
    }
    {
        if (boy == 0) {
            return;
        }
        dist = _DistGV(test_CURRENTROOT((int)boy), test_CURRENTROOT((int)self));
        if (GetFlyPosition((float *)(*(char **)(*(char **)(self + 0x164) + 0x688) +
                                     0x8A0),
                           test_CURRENTROOT((int)self),
                           test_CURRENTROOT((int)boy)) == 2) {
            ACTSendMailCorrect(self, 0x1D);
        }
        if (dist < 360.0) {
            GetRootPosition(bpos, boy);
            GetRootPosition(mpos, self);
            _OrientXZGV(dir, mpos, bpos);
            ori[0] = ((float *)test_CURRENTORIENT((int)boy))[0];
            ori[1] = ((float *)test_CURRENTORIENT((int)boy))[1];
            ori[2] = ((float *)test_CURRENTORIENT((int)boy))[2];
            if (_AbsRotyGV(ori, dir) < 60) {
                if (dist < 270.0) {
                    if (GetFlyPosition((float *)(*(char **)(*(char **)(self + 0x164) +
                                                            0x688) +
                                                 0x8A0),
                                       mpos, bpos) == 0) {
                        debug_StdPrintfDummy("not found");
                    }
                    inc = 1;
                    if (half <
                        *(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x398)) {
                        ACTSendMailCorrect(self, 0x1D);
                    } else if (dist < 120.0) {
                        ACTSendMailCorrect(self, 0x113);
                    }
                } else {
                    ACTSendMailCorrect(self, 0x113);
                }
            } else if (dist < 200.0f) {
                ACTSendMailCorrect(self, 0x113);
            }
        }
        sub = *(char **)(self + 0x164);
        if (inc != 0) {
            *(int *)(*(char **)(sub + 0x688) + 0x398) =
                *(int *)(*(char **)(sub + 0x688) + 0x398) + 1;
        } else {
            *(int *)(*(char **)(sub + 0x688) + 0x398) = 0;
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", ChangeBrain_ToAttack);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyBrain_ToBoy);
ASM_LIT4_SLOT(D_00638F40, 22500.0f);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", ChangeBrain_ToKidnap);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", subEnemyBrain_ToGirl);
extern void GetRootMotionOrient(float *out, char *self);
extern void SetMotionDirectionSmooze(void *self, float *dir, float t);
/* static inline of the 2001 source: the disc listing attributes rows
   1643-1660 -- which lie outside every function's own line span -- to the
   bodies of EnemyUtil_TurnToBoy, _ApproachTarget_Boss and subEnemyCollision
   alike, so this is a helper defined above them and inlined at each call.
   Name is descriptive, not recovered. */
static inline unsigned char enemyCheckTurnAngle(char *self)
{
    float mot[4];
    float cur[4];
    char *s = *(char **)(self + 0x164);
    int limit = (*(int *)(s + 0x34) == 3) ? 0x5A : 0x69;
    int ang;
    int aang;

    cur[0] = *(float *)(s + 0x120);
    cur[1] = *(float *)(s + 0x124);
    cur[2] = *(float *)(s + 0x128);
    GetRootMotionOrient(mot, self);
    ang = _RotyGV(mot, cur);
    aang = ang < 0 ? -ang : ang;
    if (limit < aang) {
        *(float *)(s + 0x5C0) = cur[0];
        *(float *)(s + 0x5C4) = cur[1];
        *(float *)(s + 0x5C8) = cur[2];
        if (ang > 0) {
            ACTSendMailCorrect(self, 0xE8);
        } else {
            ACTSendMailCorrect(self, 0xE7);
        }
        return 1;
    } else if (aang < 0xF) {
        ACTSendMailCorrect(self, 0xF1);
    }
    return 0;
}

int _ApproachTarget_Boss(char *self, void *tgt, void *pos, void *fn, float range,
                         unsigned char flag)
{
    float p0[4];
    float p1[4];
    char *sub = *(char **)(self + 0x164);

    for (;;) {
        GetRootProjectionPosOfGObj(p0, (char *)tgt);
        GetRootProjectionPosOfGObj(p1, self);
        if (fn != 0) {
            ((void (*)(char *, void *, float))fn)(
                self, tgt,
                _DistGV(test_CURRENTROOT((int)self), test_CURRENTROOT((int)tgt)));
        }
        *(float *)(sub + 0x34C) = 1.0f;
        _OrientXZGV((float *)pos, p0, p1);
        if (_DistxzSqGV(p0, p1) < 160000.0f && -50.0f < -(p0[1] - p1[1]) &&
            p1[1] - p0[1] < 500.0f && enemyCheckTurnAngle(self) == 0 &&
            *(int *)(sub + 0x34) != 10) {
            return 1;
        }
        _ACTWait(1);
    }
}
extern char D_00553380[];
extern char D_00553510[];
extern int D_0063B220;
extern int CanThisEnemyFly(void *self);
extern int actEnemyFlagCheckActive(int *a0);

/* INTERIM stand-ins: isEnemyActive (listing lines 2087-2088) and
   IsEnemyBrainToGenerator (831-834) are `inline` in the 2001 source; their
   out-of-line copies keep their own ROM slots further down while this TU's tail
   is asm.  See the note on _BrainMode_SetDirect_INTERIM. */
static inline int isEnemyActive_INTERIM(int *self)
{
    if (self == 0 || *(int *)((char *)self + 0xC) != 4) {
        debug_assert(D_00553370, 0x827);
        __assert(D_00553370, 0x827, D_00553510);
    }
    return actEnemyFlagCheckActive(self);
}

static inline int IsEnemyBrainToGenerator_INTERIM(char *a0)
{
    char *b = *(char **)(a0 + 0x164);

    if (*(int *)(*(char **)(b + 0x680) + 0x204) != 5) {
        return 0;
    }
    if (*(int *)(*(char **)(b + 0x688) + 0x460) == 0) {
        debug_assert(D_00553370, 0x341);
        __assert(D_00553370, 0x341, D_00553380);
    }
    return 1;
}

int flyMailCore(void *self)
{
    int flyLow = 0;
    int flyHigh = 0;
    int ret = 0;

    switch (CanThisEnemyFly(self)) {
    case 1:
        flyLow = 1;
        break;
    case 2:
        flyLow = 1;
        flyHigh = 1;
        break;
    }
    if (isEnemyActive_INTERIM((int *)self) == 0) {
        goto end;
    }
    if (IsEnemyBrainToGenerator_INTERIM((char *)self)) {
        if (flyHigh == 0 && D_0063B220 == 0) {
            goto end;
        }
        ACTSendMailCorrect(self, 0x1E);
        ret = 1;
    } else {
        if (flyLow == 0) {
            goto end;
        }
        ACTSendMailCorrect(self, 0x1D);
        ret = 1;
    }
end:
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _ApproachTarget_Way);
ASM_LIT4_SLOT(D_00638F48, 1440000.0f);
ASM_LIT4_SLOT(D_00638F4C, 40000.0f);
ASM_LIT4_SLOT(D_00638F50, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyStart);
ASM_LIT4_SLOT(D_00638F54, 369.0f);
ASM_LIT4_SLOT(D_00638F58, 0.05f);
void subEnemyBrain_Attack(volatile int a0)
{
    int i;

    for (i = 0; i < (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 6; i++) {
        enemyDodgeSendMail((char *)a0);
        _DoAwait((char *)a0);
        if (_MustChase(a0) != 0) {
            break;
        }
        _ACTWait(1);
    }
    for (i = 0; i < (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 100 / 60; i++) {
        if (i < (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 50 / 60) {
            enemyDodgeSendMail((char *)a0);
        }
        _DoAwait((char *)a0);
        if ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 80 / 60 < i) {
            if (_MustChase(a0) != 0) {
                break;
            }
        }
        _ACTWait(1);
    }
    _BrainMode_SetDirect_INTERIM((char *)a0, 0, 0);
    _ACTWait(0);
}
extern float _DistSqGV(float *a, float *b);

void subEnemyBrain_Cling(volatile int a0)
{
    char *sub = *(char **)(a0 + 0x164);
    int tgt = *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x218);
    float v[4];

    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x21C) = tgt;
    _OrientXZGV(v, (float *)test_CURRENTROOT(tgt), (float *)test_CURRENTROOT(a0));
    ((ActSubDir *)sub)->dir[0] = v[0];
    ((ActSubDir *)sub)->dir[1] = v[1];
    ((ActSubDir *)sub)->dir[2] = v[2];
    SetMotionDirection((void *)a0, v);
    ACTSendMailCorrect((void *)a0, 0xC2);
    _ACTWait(1);
    _ACTWait(1);
    while (1) {
        if (*(int *)(sub + 0x34) == 4 || *(int *)(sub + 0x34) == 0x10) {
            if (_DistSqGV((float *)test_CURRENTROOT(tgt),
                          (float *)test_CURRENTROOT(a0)) < 3600.0f) {
                ACTSendMailCorrect((void *)a0, 0xD0);
            }
        } else {
            _ACTWait(0x1E);
            _BrainMode_SetDirect_INTERIM((char *)a0, 0, 0);
        }
        _ACTWait(1);
    }
}
void funcEnemyAiGetGirl(int a0) {
    char *sub = *(char **)(a0 + 0x164);
    if (*(int *)(sub + 0x350) == 0) {
        *(int *)(sub + 0x350) = 1;
    }
}
extern char D_00553438[];
extern void debug_StdPrintfDummy(char *fmt);
extern void _ACTWait(int a0);

void actEnemyStand(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    debug_StdPrintfDummy(D_00553438);
    *(int *)(sub + 0x34) = 1;
    _ACTWait(0);
}
extern char D_00553468[];
extern void debug_StdPrintfDummy(char *fmt);
extern void _ACTWait(int a0);

void actEnemyWalk(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    debug_StdPrintfDummy(D_00553468);
    *(int *)(sub + 0x34) = 2;
    _ACTWait(0);
}
extern char D_00553498[];
extern void debug_StdPrintfDummy(char *fmt);
extern void _ACTWait(int a0);

void actEnemyRun(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    debug_StdPrintfDummy(D_00553498);
    *(int *)(sub + 0x34) = 3;
    _ACTWait(0);
}
extern char D_005534E0[];
extern void debug_StdPrintfDummy(char *fmt);
extern void _ACTWait(int a0);

void actEnemyHang(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    debug_StdPrintfDummy(D_005534E0);
    *(int *)(sub + 0x34) = 0x1C;
    _ACTWait(0);
}
extern char D_00553370[];
extern char D_0063A7E8[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

void actEnemyCarry(volatile int a0) {
    debug_assert(D_00553370, 0xB75);
    __assert(D_00553370, 0xB75, D_0063A7E8);
}
extern void iosOmSendMail(int a0, int a1, int a2);
extern void ACTSendMailCorrect(void *a0, int a1);
extern void _ACTWait(int a0);

void actEnemyBodyslam(volatile int a0)
{
    iosOmSendMail((int)D_00639EA4,
                  *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x200),
                  a0);
    while (1) {
        ACTSendMailCorrect((void *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern void iosOmSendMail(int a0, int a1, int a2);
extern void ACTSendMailCorrect(void *a0, int a1);
extern void _ACTWait(int a0);

void actEnemyBodyslamFail(volatile int a0)
{
    iosOmSendMail((int)D_00639EA4, 0xE2, a0);
    while (1) {
        ACTSendMailCorrect((void *)a0, 0xC7);
        _ACTWait(1);
    }
}
extern char *D_0063A61C;
extern int stage_no;
extern void RestoreReviveCount(int self);
extern void actChangeActBrain(char *a0, void *fn, char *a2);
extern void subEnemyBrain_Idle(volatile int a0);
extern int gamesysObjInfoPosSetStage(int w, int a1, int a2, int stage);
extern char D_00553500[];
extern void SetDirectRootPositionNoFitting(int *self, char *spill);
extern void ResetEnemyPositionInfo(int *self);
extern void actEnemyFlagOnFree(int *self);
extern void eBrainSendMes(int a0, int a1);

void actEnemyNest(volatile int a0)
{
    char *sub = *(char **)(a0 + 0x164);
    int *self;
    int stg;
    int x2;
    char spill[16];

    int x = a0;
    *(int *)(sub + 0x148) = 0;
    RestoreReviveCount(x);
    actChangeActBrain(D_0063A61C, (void *)subEnemyBrain_Idle, sub);
    self = (int *)a0;
    *(long long *)(spill + 0) = *(long long *)((char *)D_00553500 + 0);
    *(long long *)(spill + 8) = *(long long *)((char *)D_00553500 + 8);
    SetDirectRootPositionNoFitting(self, spill);
    ResetEnemyPositionInfo(self);
    actEnemyFlagOnFree(self);
    eBrainSendMes(a0, 0xA);
    stg = stage_no;
    *(int *)(sub + 0x440) = 0;
    x2 = a0;
    *(int *)(sub + 0x444) = 7;
    gamesysObjInfoPosSetStage(x2, 7, 0, stg);
    _ACTWait(0);
}
void funcEnemyCarryFail(char *a0) {
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x20) |= (1ULL << 34);
}
extern char D_00553500[];
extern void ResetEnemyPositionInfo(int *self);
extern void SetDirectRootPositionNoFitting(int *self, char *spill);
extern void actEnemyFlagOnFree(int *self);

void actEnemyHyde(int *self)
{
    char spill[16];
    *(long long *)(spill + 0) = *(long long *)((char *)D_00553500 + 0);
    *(long long *)(spill + 8) = *(long long *)((char *)D_00553500 + 8);
    SetDirectRootPositionNoFitting(self, spill);
    ResetEnemyPositionInfo(self);
    actEnemyFlagOnFree(self);
}
extern char D_002C2DC8[];

void actEnemyFlagOnFree(int *a0)
{
    char *base = D_002C2DC8 + a0[2] * 0x4C;
    *(int *)(base + 0x48) &= ~0x200000;
}
extern char *D_00639EA8;
extern void iosOmSendMail(int a0, int a1, int a2);
extern void eBrainSendMes(int a0, int a1);

void afterCommonCarry(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    int girl = (int)D_00639EA8;
    int self = a0;
    *(int *)(sub + 0x148) = girl;
    iosOmSendMail(girl, 0x30, self);
    *(int *)(sub + 0x148) = 0;
    if (*(int *)(sub + 0x34) == 5) {
        eBrainSendMes(a0, 4);
    }
}
void actEnemyFlagOnDead(int *a0)
{
    char *base = D_002C2DC8 + a0[2] * 0x4C;
    *(int *)(base + 0x48) |= 0x40000;
}
int EnemyBrainStatus_Boy(char *a0) {
    return *(int *)(*(char **)(a0 + 0x164) + 0x440) == 2;
}
int EnemyBrainStatus_Girl(char *a0) {
    return *(int *)(*(char **)(a0 + 0x164) + 0x440) == 1;
}
int actEnemyFlagCheckDead(int *a0)
{
    int *p = (int *)(D_002C2DC8 + a0[2] * 0x4C);
    return ((unsigned int)p[0x48 / 4] >> 18) & 1;
}
int actEnemyFlagCheckActive(int *a0)
{
    unsigned int *p = (unsigned int *)(D_002C2DC8 + a0[2] * 0x4C);
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
extern int actEnemyForceSwitchToCarry(void *a0);
extern void _BrainMode_SetDirect(char *a0, int a1, int *a2);
extern void ACTSendMailCorrect(void *a0, int a1);
int ACTEnemyForceSwitchToCarry(char *a0) {
    int r = actEnemyForceSwitchToCarry(a0);
    if (r != 0) {
        _BrainMode_SetDirect(a0, 0, 0);
    }
    ACTSendMailCorrect(a0, 0x104);
    return r;
}
int actEnemy_GetClingTarget(char *a0) {
    char *b = *(char **)(a0 + 0x164);
    char *e = *(char **)(b + 0x680);
    if (*(int *)(e + 0x1E8) == 0 && *(int *)(b + 0x34) == 0x10) {
        return *(int *)(e + 0x220);
    }
    return 0;
}
int actEnemy_isNormalEnemy(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1E8) == 1;
}
int actEnemy_isLargeEnemy(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1E8) == 2;
}
int actEnemy_isSmallEnemy(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1E8) == 0;
}
extern char D_00553370[];
extern char D_00553380[];
int IsEnemyBrainToGenerator(char *a0, int *out) {
    char *b = *(char **)(a0 + 0x164);
    if (*(int *)(*(char **)(b + 0x680) + 0x204) != 5) return 0;
    *out = *(int *)(*(char **)(b + 0x688) + 0x460);
    if (*out == 0) {
        debug_assert(D_00553370, 0x341);
        __assert(D_00553370, 0x341, D_00553380);
    }
    return 1;
}
extern char *D_00639EA8;
int IsEnemyBrainToBoy(char *self) {
    char *sub;
    char *sub2;
    if (D_00639EA8 != 0) {
        char *sub_d = *(char **)(D_00639EA8 + 0x164);
        if (*(int *)(sub_d + 0x34) != 0x6F) return 0;
    }
    sub = *(char **)(self + 0x164);
    sub2 = *(char **)(sub + 0x680);
    return *(int *)(sub2 + 0x204) == 3;
}
int GetEnemyTypeFromGObj(char *a0) {
    return ((EnemyBattleGObj *)a0)->sub->enemy->liftKind;
}
int GetEnemyType(void) {
    return 1;
}

int isEnemyKidnapEnable(int *self)
{
    if (*(int *)(*(int *)(*(int *)((char *)self + 0x164) + 0x680) + 0x1E4) == 0) {
        return 0;
    }
    return actEnemyFlagCheckActive_INTERIM(self);
}
extern char D_00553510[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern int actEnemyFlagCheckActive(int *a0);

int isEnemyActive(int *self)
{
    if (self == 0 || *(int *)((char *)self + 0xC) != 4) {
        debug_assert(D_00553370, 0x827);
        __assert(D_00553370, 0x827, D_00553510);
    }
    return actEnemyFlagCheckActive(self);
}
int GetMotherGeneratorLabelAskEnemy(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x464);
}
int GetMotherGeneratorGObjAskEnemy(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x468);
}
extern void _ACTWait(int a0);

void subEnemyBrain_Idle(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    *(int *)(sub + 0x34C) = 0;
    *(int *)(sub + 0x120) = 0;
    *(int *)(sub + 0x124) = 0;
    *(int *)(sub + 0x128) = 0;
    while (1) {
        if (*(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x218) == (int)D_00639EA4) {
            _DoAwait((char *)a0);
        }
        _ACTWait(1);
    }
}
extern float _GetRandom(void);
extern int _ApproachTarget(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);

void subEnemyBrain_Await(volatile int a0)
{
    char *sub = *(char **)(a0 + 0x164);
    *(int *)(sub + 0x34C) = 0;
    *(int *)(sub + 0x120) = 0;
    *(int *)(sub + 0x124) = 0;
    *(int *)(sub + 0x128) = 0;
    if (D_00639EA4 != 0) {
        _ApproachTarget((char *)a0, D_00639EA4, sub + 0x120, 0,
                        (float)((int)(_GetRandom() * 10.0f) % 200 + 300), 0);
    }
    *(int *)(sub + 0x34C) = 0;
    *(int *)(sub + 0x120) = 0;
    *(int *)(sub + 0x124) = 0;
    *(int *)(sub + 0x128) = 0;
    while (1) {
        _DoAwait((char *)a0);
        _ACTWait(1);
    }
}
extern int D_0028F4C0[];

void subEnemyBrain_FindGirl(volatile int a0)
{
    char *sub = *(char **)(a0 + 0x164);
    int i;

    for (i = 0; i < (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2; i++) {
        *(int *)(sub + 0x34C) = 0;
        *(int *)(sub + 0x120) = 0;
        *(int *)(sub + 0x124) = 0;
        *(int *)(sub + 0x128) = 0;
        ACTSendMailCorrect((void *)a0, 0xE6);
        if (*(int *)(sub + 0x34) == 0x47) {
            break;
        }
        _ACTWait(1);
    }
    for (i = 0; i < (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 250 / 60; i++) {
        _DoAwait((char *)a0);
        _ACTWait(1);
    }
    eBrainSendMes(a0, 1);
    _ACTWait(0);
}
extern float _DistGV(void *a, void *b);

void subEnemyBrain_BodyGuard(volatile int a0)
{
    char *sub = *(char **)(a0 + 0x164);
    int tgt = *(int *)(sub + 0x14C);
    float *pos = (float *)(sub + 0x120);

    while (1) {
        if (_DistGV(test_CURRENTROOT(a0), test_CURRENTROOT(tgt)) < 200.0f) {
            _ACTWait(1);
        } else {
            if ((unsigned char)_ApproachTarget((char *)a0, (void *)tgt, pos, 0, 100.0f, 0) == 0) {
                *(int *)(sub + 0x34C) = 0;
                *(int *)(sub + 0x120) = 0;
                *(int *)(sub + 0x124) = 0;
                *(int *)(sub + 0x128) = 0;
                _ACTWait(0x1E);
            }
            *(int *)(sub + 0x34C) = 0;
            *(int *)(sub + 0x120) = 0;
            *(int *)(sub + 0x124) = 0;
            *(int *)(sub + 0x128) = 0;
            _ACTWait(0x3C);
        }
    }
}

extern void _OrientXZGV(float *out, float *a, float *b);
extern void SetMotionDirection(void *self, float *dir);

void subEnemyBrain_Shoulder(volatile int a0)
{
    float *dir = (float *)(*(char **)(a0 + 0x164) + 0x120);
    float *girl = (float *)test_CURRENTROOT((int)D_00639EA8);
    float *me = (float *)test_CURRENTROOT(a0);
    _OrientXZGV(dir, girl, me);
    SetMotionDirection((void *)a0, dir);
    ACTSendMailCorrect((void *)a0, 0x162);
    while (1) {
        _ACTWait(0x78);
        _BrainMode_SetDirect_INTERIM((char *)a0, 0, 0);
    }
}
extern void ACTSendMailCorrect(void *a0, int a1);
extern void _ACTWait(int a0);
void subEnemyBrain_Pickup(volatile int a0) {
    ACTSendMailCorrect((void *)a0, 0x16C);
    while (1) {
        _ACTWait(0x78);
        _BrainMode_SetDirect_INTERIM((char *)a0, 0, 0);
    }
}
extern void ACTSendMailCorrect(void *a0, int a1);
extern void _ACTWait(int a0);
void subEnemyBrain_Bodyslam(volatile int a0) {
    if (*(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x1E4) == 3) {
        ACTSendMailCorrect((void *)a0, 0x175);
    } else {
        ACTSendMailCorrect((void *)a0, 0x173);
    }
    while (1) {
        _ACTWait(0x78);
        _BrainMode_SetDirect_INTERIM((char *)a0, 0, 0);
    }
}
/* Static inline helper of the 2001 source at enemy_act.c:816-826 (it has no
   symbol of its own and no census row; the disc listing shows its lines inlined
   here and in subEnemyCollision).  Name is descriptive, not recovered. */
static inline unsigned char isEnemyCarriedByGirl(int self)
{
    char *gsub;
    if (*(int *)(*(char **)(self + 0x164) + 0x148) == 0 || D_00639EA8 == 0) {
        return 0;
    }
    gsub = *(char **)(D_00639EA8 + 0x164);
    if (gsub == 0 || *(int *)(gsub + 0x34) != 0x6F) {
        return 0;
    }
    if (*(int *)(gsub + 0x144) == self) {
        return 1;
    }
    return 0;
}

typedef struct {
    char pad00[0x20];
    long long flags;
} EnemyBrainWork;

void subEnemyBrain_Irregular(volatile int a0)
{
    EnemyBrainWork *sub = *(EnemyBrainWork **)(a0 + 0x164);

    sub->flags &= ~(1LL << 34);
    eBrainSendMes(a0, 4);
    if (isEnemyCarriedByGirl(a0)) {
        afterCommonCarry_INTERIM(a0);
    }
    while (1) {
        _ACTWait(0x1E);
        _BrainMode_SetDirect_INTERIM((char *)a0, 0, 0);
    }
}
extern int D_0063A7E0;

void _BrainMode_SetDirect(char *a0, int a1, int *a2) {
    *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x208) = a1;
    if (a2 != 0) {
        *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x214) = *a2;
    } else {
        *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x214) = D_0063A7E0;
    }
}
extern void GetRootMotionOrient(float *out, char *self);
extern void SetMotionDirectionSmooze(void *self, float *dir, float t);

void EnemyUtil_TurnToBoy(char *self, int tgt, int smooze)
{
    float dir[4];
    char *sub = *(char **)(self + 0x164);

    _OrientXZGV(dir, (float *)test_CURRENTROOT(tgt), (float *)test_CURRENTROOT((int)self));
    *(float *)(sub + 0x120) = dir[0];
    *(float *)(sub + 0x124) = dir[1];
    *(float *)(sub + 0x128) = dir[2];
    enemyCheckTurnAngle(self);
    if (smooze == 0) {
        SetMotionDirection(self, dir);
    } else {
        SetMotionDirectionSmooze(self, dir, (float)smooze);
    }
}
extern int flyMailCore(void *a0);

int FlyMail(void *a0) {
    int x = *(int *)(*(char **)((char *)a0 + 0x164) + 0x10);
    if (x < 0xC) {
        return -1;
    }
    return flyMailCore(a0);
}
extern char *isysGObjSearchFromObjKindID_begin(int kind);
extern char *isysGObjSearchFromObjKindID_next(char *g);

void boss_effect_callback(int id)
{
    char *g;
    int i;
    char *p;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (*(int *)(*(int *)(*(char **)(g + 0x164) + 0x680) + 0x1E4) == 3) {
            for (i = 0; i < 5; i++) {
                p = (char *)(i * 0x20 + *(int *)(*(char **)(g + 0x164) + 0x680) + 0x360);
                if (p[0x1D] != 0 && *(int *)(p + 0x10) == id) {
                    p[0x1C] = 0;
                    return;
                }
            }
        }
    }
}
extern char D_00553450[];
extern void debug_StdPrintfDummy(char *fmt);
extern char *SetMotionRequest(int self, int mot, char *work);
extern void _ACTWait(int a0);

void motEnemyStand(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    debug_StdPrintfDummy(D_00553450);
    *(char **)(sub + 0x130) = SetMotionRequest(a0, 1, sub + 0x620);
    while (1) {
        _ACTWait(1);
    }
}
extern char D_00553480[];
extern void debug_StdPrintfDummy(char *fmt);
extern char *SetMotionRequest(int self, int mot, char *work);
extern void _ACTWait(int a0);

void motEnemyWalk(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    char *mot;
    debug_StdPrintfDummy(D_00553480);
    mot = SetMotionRequest(a0, 8, sub + 0x620);
    *(char **)(sub + 0x130) = mot;
    *(int *)(mot + 0x114) = 0;
    _ACTWait(0);
}
extern char D_005534B0[];
extern void debug_StdPrintfDummy(char *fmt);
extern char *SetMotionRequest(int self, int mot, char *work);
extern void _ACTWait(int a0);

void motEnemyRun(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    char *mot;
    debug_StdPrintfDummy(D_005534B0);
    mot = SetMotionRequest(a0, 0xD, sub + 0x620);
    *(char **)(sub + 0x130) = mot;
    *(int *)(mot + 0x114) = 0;
    _ACTWait(0);
}
extern char D_005534C8[];
extern void debug_StdPrintfDummy(char *fmt);
extern void _ACTWait(int a0);

void actEnemyJump(volatile int a0) {
    char *sub = *(char **)(a0 + 0x164);
    debug_StdPrintfDummy(D_005534C8);
    *(int *)(sub + 0x34) = 4;
    _ACTWait(0);
}
extern char *isysGObjSearchFromObjKindID_begin(int kind);
extern char *isysGObjSearchFromObjKindID_next(char *g);

int EnemyUtil_isOtherStatus(char *self, int mode)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (g != self) {
            char *sub = *(char **)(g + 0x164);
            if (*(int *)(sub + 0x34) == 0xF) {
                return (int)g;
            }
            if ((int)(*(long long *)(sub + 0x20) >> 10) & 1) {
                return (int)g;
            }
        }
    }
    return 0;
}
int isEnemyHyde(int *a0)
{
    int *p = (int *)(D_002C2DC8 + a0[2] * 0x4C);
    return (((unsigned int)p[0x48 / 4] >> 21) & 1) ^ 1;
}
extern int _ApproachTarget_Way(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
extern int _ApproachTarget_Boss(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);

int _ApproachTarget(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag) {
    if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0x1E4) != 3) {
        return _ApproachTarget_Way(self, tgt, pos, fn, range, flag);
    } else {
        return _ApproachTarget_Boss(self, tgt, pos, fn, range, flag);
    }
}
void afterEnemyBodylift(volatile int a0) {
    int x = a0;
    *(int *)(*(int *)(x + 0x15C) + 0x550) = 0;
    *(int *)(*(int *)(x + 0x15C) + 0x380) = 0;
}

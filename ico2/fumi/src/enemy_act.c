#include "enemy_act.h"
#include "debug.h"
#include "gamesys.h"
#include "gobj.h"
#include "obj_manager.h"
#include "gobj_process.h"
#include "act-game.h"
#include "act.h"
#include "boyact.h"
#include "gather_effect.h"
#include "camera-editor.h"
#include "ebrain.h"
#include "generator.h"
#include "enemy.h"
#include "geometryManager.h"
#include "motionOrientManager.h"
#include "quaternion.h"
#include <string.h>
#include "commonact.h"
#include "gflag.h"
#include "StageManager.h"
#include "backStage.h"
#include "matrixDrive.h"
#include "StageAnimation.h"
#include "darkVolume.h"
#include "sugiCommon.h"
#include <libvu0.h>
#include "act-way.h"
#include "isys.h"
#include "Matrix.h"
#include "GifPacket.h"
#include "debug_exception.h"
#include "enemy-control.h"
#include "Primitive.h"
#include "multiBgaManager.h"
#include "gv.h"
#include "main.h"
#include <assert.h>
#include "motionManager2.h"
#include "attackhit.h"
#include "pad.h"
#include "flyManager.h"
#include "include_asm.h"

int entesty;

/* The brain-mode table, one 28-byte record per mode: its name, its priority
   against the running mode, the brain function and four parameters
   (subEnemyBrainMain and BrainMode_Requset read them). */
typedef struct { /* field names derived */
    char *name;
    int pri;
    void (*brain)(GObj *);
    int aim;       /* 0x0C, copied to the actor's brainAim: 1 the girl, 2 the boy */
    int word10;    /* 0x10, read by nothing in the retail build */
    int stoppable; /* 0x14, nonzero: mail 0x20 stops the brain until mail 0x1F */
    int infoPos;   /* 0x18, copied to the actor's infoPos */
} EnemyBrainMode;  /* derived name */

void subEnemyBrain_ToBoy(GObj *volatile self);
void subEnemyBrain_ToGirl(GObj *volatile self);
void subEnemyBrain_ToGenerator(GObj *self);
void subEnemyBrain_Cling(GObj *volatile self);
void subEnemyBrain_Attack(GObj *volatile self);

EnemyBrainMode brainModeTable[] = {
    {"START", 0, subEnemyBrain_Idle, 0, 0, 1, 0},
    {"IDLE", 1, subEnemyBrain_Idle, 0, 0, 1, 0},
    {"AWAIT", 2, subEnemyBrain_Await, 2, 2, 1, 1},
    {"TO_BOY", 2, subEnemyBrain_ToBoy, 2, 2, 1, 1},
    {"TO_GIRL", 2, subEnemyBrain_ToGirl, 1, 3, 1, 2},
    {"TO_GENE", 2, subEnemyBrain_ToGenerator, 0, 1, 1, 4},
    {"FIND_GIRL", 2, subEnemyBrain_FindGirl, 0, 0, 1, 0},
    {"BODYGUARD", 2, subEnemyBrain_BodyGuard, 0, 4, 1, 5},
    {"CLING", 3, subEnemyBrain_Cling, 0, 0, 1, 0},
    {"ATTACK", 3, subEnemyBrain_Attack, 0, 0, 1, 0},
    {"SHOULDER", 3, subEnemyBrain_Shoulder, 0, 3, 1, 2},
    {"PICKUP", 3, subEnemyBrain_Pickup, 0, 1, 1, 4},
    {"BODYSLAM", 3, subEnemyBrain_Bodyslam, 0, 0, 1, 0},
    {"IRREGULAR", 4, subEnemyBrain_Irregular, 0, 0, 1, 0},
}; /* derived name */

/* The default target, read when a mode is set with no target:
   _BrainMode_SetDirect's else arm and the two nested brain-change children
   start from it. */
static const BrainModeTarget brainTargetNone = {0}; /* derived name */

#define BOSS_START_WORK(self) ((int)GOBJ_ACT(self)->enemy) /* derived name */

typedef struct { /* field names derived */
    char pad00[20];
    int id;
    int timer;
    char busy;
    char alive;
    char pad1E[2];
} BossPart; /* derived name */

#define BOSS_EFFECT_WORK(self) ((char *)GOBJ_ACT(self)->enemy) /* derived name */
#define BOSS_EFFECT_PARTS(self, i)                                                                 \
    ((BossPart *)((i) * 0x20 + BOSS_EFFECT_WORK(self) + 0x360)) /* derived name */

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* this TU's uses of _GetMotionDirection do not fit the prototype in
   motionManager2.h */

/* The DEBUG build holds the enemy's stick poll while the debug flag word's
   hold bit is set, a frame at a time, the way boyact.c's subBoyControl repeats
   its stick loop with _ACTWait; retail builds it as 0. */
#ifdef DEBUG
#define ENEMY_DEBUG_HOLD (debug_font_flag & 0x200) /* derived name */
#else
#define ENEMY_DEBUG_HOLD 0 /* derived name */
#endif

/* enemy.c's; no header declares it */
extern float GetEnemyDefParaIndex(void *self);

/* The point the lifting enemy turns to: three vectors (the first two equal),
   of which only the first is addressed. */
static sceVu0FVECTOR bodyliftTarget[3] = {
    {-311.0f, -89.0f, -147.0f, 0.0f},
    {-311.0f, -89.0f, -147.0f, 0.0f},
    {-770.0f, -1445.0f, -749.0f, 0.0f},
}; /* derived name */

/* FLT_MAX word in .sdata, declared as an incomplete array */
extern void SetEnemyStonizedVisual(void *self);
extern void BossEnemyFunc(void *self);

/* the TU's flag-test shape, a 64-bit shift-and-mask of a 32-bit word, as a
   function-like macro */
#define EA_CHKBIT(f, n) (((int)((long long)(f) >> (n))) & 1) /* derived name */

/* GetFlyPosition's points: the four the enemy measures against, the four it
   flies to (paired by index, 200 below), and the one it escapes to. */
static sceVu0FVECTOR flyCheckPos[4] = {
    {760.0f, -71.0f, 766.0f, 1.0f},
    {708.0f, -71.0f, -806.0f, 1.0f},
    {-1394.0f, -71.0f, -858.0f, 1.0f},
    {-1383.0f, -71.0f, 645.0f, 1.0f},
}; /* derived name */

static sceVu0FVECTOR flyDestPos[4] = {
    {842.0f, -271.0f, 1278.0f, 1.0f},
    {734.0f, -271.0f, -1273.0f, 1.0f},
    {-1394.0f, -271.0f, -1291.0f, 1.0f},
    {-1383.0f, -271.0f, 1291.0f, 1.0f},
}; /* derived name */

static sceVu0FVECTOR flyEscapePos = {1712.0f, -690.0f, 0.0f, 1.0f}; /* derived name */

/* The brain-mode target the ChangeBrain_ToAttack and ChangeBrain_ToKidnap
   children fill in from the default and hand to _BrainMode_SetDirect: one
   record shared by the nested functions of two parents, so file scope (the
   TU's whole .sbss). */
static BrainModeTarget brainTarget; /* derived name */

/* One start record per motion phase; the four of them are the actor's whole
   start parameter block. */
typedef struct { /* field names derived */
    int sizeClass;
    int paraStatus;
    int clingNode;
    int attackChance;
    int attackChance2;
    float maxLife;
    float bodyslamMail;
    unsigned int noGuard; /* the status word's bit 51, which turns away the guard mail */
} EnemyStartRec;          /* derived name */

/* The gobj's sub-object slot at +0x15C, an int handle the engine also reads
   as the sub record's address (see GOBJ_SUB in typedef.h), as a union of the
   two views. */
typedef union { /* field names derived */
    int handle;
    char *p;
} EnemySubSlot; /* derived name */

/* The actor's character kind at act+0x48, the index act.c's after_func_exec
   and BeforeFunc read into the status table's six-entry rows; actInitialize
   sets it to -1, actGirlStart to 1 and actEnemyStart to 2. */
typedef enum { ACT_KIND_NONE = -1, ACT_KIND_GIRL = 1, ACT_KIND_ENEMY = 2 } ActKind;

#define ENEMY_START_WORK(self) ((int)GOBJ_ACT(self)->enemy) /* derived name */

INCLUDE_ASM(setBattleStatus);

/* a static inline, inlined by both boss_effect_start and
   boss_effect_process */
static inline void bossEffectSetNodePos(GObj *self, float *dst, int idx) /* derived name */
{
    Sub15C *g = GOBJ_SUB(self);

    sceVu0CopyVector(dst, (float *)((char *)g->nodeMtx + idx * 0x40 + 0x30));
    dst[3] = 1.0f;
}

INCLUDE_ASM(boss_effect_start);

INCLUDE_ASM(boss_effect_check_parts);

INCLUDE_ASM(boss_effect_process);

INCLUDE_ASM(_DoAwait);

INCLUDE_ASM(_DoAwaitGirl);

static int _MustChase(GObj *self)
{
    float v1[4];
    float v2[4];
    float angle;
    float diff;
    int rv;
    if ((void *)boyGObj == 0) {
        goto zero;
    }
    v1[0] = test_CURRENTROOT(((void *)boyGObj))[0];
    v1[1] = test_CURRENTROOT(((void *)boyGObj))[1];
    v1[2] = test_CURRENTROOT(((void *)boyGObj))[2];
    v2[0] = test_CURRENTROOT(self)[0];
    v2[1] = test_CURRENTROOT(self)[1];
    v2[2] = test_CURRENTROOT(self)[2];
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

/* A static inline between setBattleStatus and boss_effect_callback, expanded
   only in subEnemyControl. */
static inline void enemyPollHitNodes(GObj *self) /* derived name */
{
    int n = GOBJ_SUB(self)->skelNodeNum;
    int i;

    for (i = 0; i < n; i++) {
        GetEnemyHitNodeFlag(self);
    }
}

INCLUDE_ASM(subEnemyControl);

/* A static inline, a helper defined above EnemyUtil_TurnToBoy,
   _ApproachTarget_Boss and subEnemyCollision and inlined at each call. */
static inline unsigned char enemyCheckTurnAngle(GObj *self) /* derived name */
{
    float mot[4];
    float cur[4];
    Act *s = GOBJ_ACT(self);
    int limit = (s->actMode == 3) ? 0x5A : 0x69;
    int ang;
    int aang;

    cur[0] = s->dir[0];
    cur[1] = s->dir[1];
    cur[2] = s->dir[2];
    GetRootMotionOrient(mot, self);
    ang = _RotyGV(mot, cur);
    aang = ang < 0 ? -ang : ang;
    if (limit < aang) {
        s->env.turnDir.f[0] = cur[0];
        s->env.turnDir.f[1] = cur[1];
        s->env.turnDir.f[2] = cur[2];
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

/* a static inline helper, inlined here and in subEnemyBrain_Irregular */
static inline unsigned char isEnemyCarriedByGirl(GObj *self) /* derived name */
{
    Act *gsub;
    if (GOBJ_ACT(self)->carried == 0 || (char *)girlGObj == 0) {
        return 0;
    }
    gsub = GOBJ_ACT(girlGObj);
    if ((char *)gsub == 0 || gsub->actMode != 0x6F) {
        return 0;
    }
    if (gsub->carrier == self) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM(subEnemyCollision);

INCLUDE_ASM_LIT(motEnemyStand);

INCLUDE_ASM_LIT(motEnemyWalk);

INCLUDE_ASM_LIT(motEnemyRun);

INCLUDE_ASM_LIT(actEnemyJump);

INCLUDE_ASM(actEnemyAttack);

INCLUDE_ASM_LIT(actEnemyHyde);

INCLUDE_ASM_LIT(isEnemyActive);

/* A static inline shared by actEnemyRestart and actEnemyStart.  `max` is a
   local holding 43. */
static inline float getEnemyRestartLife(GObj *self) /* derived name */
{
    int max = 43;
    int idx = gFlagGameClear + 38;

    idx = (idx < 38) ? 38 : ((idx <= max) ? idx : max);
    return GetEnemyDefLife(self) * _ACTGame_GetParamF(idx);
}

INCLUDE_ASM(actEnemyRestart);

/* PairSetGeometry is a GNU nested function, reading its parent's frame
   through the static chain. */
INCLUDE_ASM(PairSetGeometry_150);

INCLUDE_ASM(actEnemyForceSwitchToCarry);

static int kidnapEndCount = 0; /* derived name: cleared as actEnemyKidnapEnd starts its wait */

INCLUDE_ASM(actEnemyKidnapEnd);

/* A static inline inside actEnemyKidnapBegin, the same construction as
   enemyPickupCheckGirl above.  pos, declared ahead of buf, is read only by
   the DEBUG build's report of the girl's position. */
static inline int enemyKidnapCheckGirl(GObj *self) /* derived name */
{
    float pos[4];
    float buf[4];
    int ang;
    int mode;

    if (_ACTGame_SearchGObj(self, girlGObj, 60.0f, 100.0f, 45, buf) != 0) {
        ang = _RotyGV(buf, test_CURRENTORIENT((girlGObj)));
        ang = (ang < 0) ? -ang : ang;
        mode = 2;
        if (ang <= 89) {
            mode = 1;
        }
    } else {
        mode = 0;
    }
#ifdef DEBUG
    GetRootProjectionPosOfGObj(pos, (char *)((char *)girlGObj));
    scePrintf("kidnap check %d girl %f %f %f\n", mode, pos[0], pos[1], pos[2]);
#endif
    return mode;
}

INCLUDE_ASM(actEnemyKidnapBegin);

INCLUDE_ASM(MoveChestForCatchBoy);

/* a `static inline` defined outside this function */
static inline void enemyBodyliftClearBoy(char *self) /* derived name */
{
    GOBJ_SUB(self)->ctrl.catchBoy = 0;
    GOBJ_SUB(self)->root.lookMode = 0;
}

INCLUDE_ASM(actEnemyBodylift);

/* A static inline inside actEnemyPickupBegin.  A second 16-byte vector is
   declared ahead of buf; its reader is the DEBUG build's report of the girl's
   position, as in enemyKidnapCheckGirl. */
static inline int enemyPickupCheckGirl(GObj *self) /* derived name */
{
    float pos[4];
    float buf[4];
    int ang;
    int mode;

    if (_ACTGame_SearchGObj(self, girlGObj, 170.0f, 100.0f, 45, buf) != 0) {
        ang = _RotyGV(buf, test_CURRENTORIENT((girlGObj)));
        ang = (ang < 0) ? -ang : ang;
        mode = 2;
        if (ang <= 89) {
            mode = 1;
        }
    } else {
        mode = 0;
    }
#ifdef DEBUG
    GetRootProjectionPosOfGObj(pos, (char *)((char *)girlGObj));
    scePrintf("pickup check %d girl %f %f %f\n", mode, pos[0], pos[1], pos[2]);
#endif
    return mode;
}

INCLUDE_ASM(actEnemyPickupBegin);

/* a static inline */
static inline int getEnemyBrainMes(char *self, int *data) /* derived name */
{
    EBSlot *t = eBrainGetTarget(self);

    if (t == 0) {
        *data = 0;
        return 0;
    }
    *data = (int)t->target;
    return t->status;
}

INCLUDE_ASM(CheckEnemyBrainMode);

inline void _BrainMode_SetDirect(GObj *self, int mode, BrainModeTarget *tgt);

/* A static inline between _BrainMode_SetDirect and subEnemyBrainMain. */
static inline void _BrainMode_Set(GObj *self, int mode, int *tgt) /* derived name */
{
    if (brainModeTable[mode].pri < brainModeTable[GOBJ_ACT(self)->enemy->reqMode].pri) {
        return;
    }
    _BrainMode_SetDirect(self, mode, tgt);
}

INCLUDE_ASM(BrainMode_Requset_217);

INCLUDE_ASM(subEnemyBrainMain);

/* A static inline.  `sub` is computed inside the helper; in enemy_dodge the
   caller already holds it. */
static inline void enemyDodgeSendMail(GObj *self) /* derived name */
{
    Act *sub = GOBJ_ACT(self);

    if (EnemyUtil_isOtherStatus(self, 0) != 0) {
        return;
    }
    if (((int)(_GetRandom() * 10.0f)) & 1) {
        ACTSendMailCorrect(self, 0xCF);
    }
    ACTSendMailCorrect(self, 0xCD);
    *(long long *)((char *)sub + 0x20) |= 0x400;
}

INCLUDE_ASM(enemy_dodge);

static void enemy_dodge_to_boy(GObj *self);

/* a `static inline` defined outside this function, expanded twice here */
static inline float battleRangeScale(GObj *self, float v) /* derived name */
{
    EnemyBattleWork *work = GOBJ_ACT(self)->enemy;

    switch (work->sizeClass) {
    case 0:
    case 1:
        v = work->bodySize * v;
        if (((int)(*(long long *)((char *)work + 0x210) >> 1)) & 1) {
            v = v * 1.2;
        }
        break;
    case 2:
        v = work->bodySize * 0.7f * v;
        break;
    }
    return v;
}

INCLUDE_ASM(Battle_isCurrentStatus);

static int GetFlyPosition(float *out, float *me, float *tgt)
{
    int ret;

    ret = 0;
    if (tgt[1] < -500.0f && 1000.0f < ((tgt[2] < 0.0f) ? -tgt[2] : tgt[2]) && -500.0f < me[1]) {
        out[0] = flyEscapePos[0];
        out[1] = flyEscapePos[1];
        out[2] = flyEscapePos[2];
        return 2;
    }
    if (tgt[1] < -500.0f && 1000.0f < ((tgt[2] < 0.0f) ? -tgt[2] : tgt[2]) &&
        _DistSqGV(me, tgt) < 160000.0f) {
        out[0] = flyEscapePos[0];
        out[1] = flyEscapePos[1];
        out[2] = flyEscapePos[2];
        return 2;
    }
    if (-150.0f < me[1]) {
        float best = 3.40282347e+38f /* FLT_MAX */;
        int besti = -1;
        int i;

        for (i = 0; i < 4; i++) {
            float d = _DistSqGV(me, flyCheckPos[i]);

            if (d < best) {
                best = d;
                besti = i;
            }
        }
        if (besti != -1) {
            float *p = flyDestPos[besti];

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
            float d = _DistSqGV(tgt, flyCheckPos[i]);

            if (best < d) {
                best = d;
                besti = i;
            }
        }
        if (besti != -1) {
            ret = 1;
            if (((int)(_GetRandom() * 10.0f)) & 1) {
                out[0] = flyEscapePos[0];
                out[1] = flyEscapePos[1];
                out[2] = flyEscapePos[2];
            } else {
                /* the table base is its own statement */
                float *tbl = flyCheckPos[0];
                float *p = tbl + besti * 4;

                out[0] = p[0];
                out[1] = p[1];
                out[2] = p[2];
            }
        }
    }
    return ret;
}

/* An _ApproachTarget callback: _ApproachTarget_Way calls its `fn` through
   (void (*)(char *, void *, float)).  `dist` is unused here. */
INCLUDE_ASM(NakaBoss);

/* a file-scope helper expanded once inside subEnemyBrain_ToBoy */
static inline int isNearestEnemyToBoy(GObj *self, GObj *boy, float *pos) /* derived name */
{
    GObj *found = 0;
    float best = 3.40282347e+38f /* FLT_MAX */;
    GObj *g;
    float d;

    pos[0] = test_CURRENTROOT(boy)[0];
    pos[1] = test_CURRENTROOT(boy)[1];
    pos[2] = test_CURRENTROOT(boy)[2];
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        d = _DistSqGV(pos, test_CURRENTROOT(g));
        if (d < best) {
            best = d;
            found = g;
        }
    }
    return self == found;
}

INCLUDE_ASM(ChangeBrain_ToAttack_269);

INCLUDE_ASM(subEnemyBrain_ToBoy);

INCLUDE_ASM(ChangeBrain_ToKidnap_279);

INCLUDE_ASM(subEnemyBrain_ToGirl);

INCLUDE_ASM(_ApproachTarget_Boss);

static int flyMailCore(void *self);

INCLUDE_ASM(flyMailCore);

inline int FlyMail(void *self);

/* a static inline, expanded twice inside _ApproachTarget_Way */
static inline unsigned char waitEnemyFly(GObj *self) /* derived name */
{
    Act *sub = GOBJ_ACT(self);

    while (sub->actMode != 6) {
        if (FlyMail(self) == 0) {
            return 0;
        }
        _ACTWait(1);
    }
    return 1;
}

/* a static inline */
static inline int flyLimitMail(GObj *self, float *rp) /* derived name */
{
    Act *sub = GOBJ_ACT(self);

    if (sub->frame < 0xC) {
        return 0;
    }
    GetRootPosition(rp, self);
    if (GetFlyLimitClearance(rp) == 0) {
        return 0;
    }
    flyMailCore(self);
    return 1;
}

INCLUDE_ASM(col_301);

INCLUDE_ASM(_ApproachTarget_Way);

/* the bit-51 store to the actor word is a union access, the four 0.05f
 * stores go through a union view of the gobj+0x15C slot, and each life pair
 * is one chained assignment */
INCLUDE_ASM(actEnemyStart);

INCLUDE_ASM(subEnemyBrain_Irregular);

INCLUDE_ASM(subEnemyBrain_Attack);

INCLUDE_ASM(subEnemyBrain_Cling);

INCLUDE_ASM(funcEnemyAiGetGirl);

INCLUDE_ASM(actEnemyWalk);

INCLUDE_ASM(actEnemyRun);

INCLUDE_ASM(actEnemyHang);

INCLUDE_ASM(actEnemyStand);

INCLUDE_ASM(actEnemyCarry);

INCLUDE_ASM(actEnemyBodyslam);

INCLUDE_ASM(actEnemyBodyslamFail);

INCLUDE_ASM(actEnemyNest);

INCLUDE_ASM(funcEnemyCarryFail);

INCLUDE_ASM(actEnemyHyde);

INCLUDE_ASM(actEnemyFlagOnFree);

INCLUDE_ASM(afterCommonCarry);

INCLUDE_ASM(actEnemyFlagOnDead);

INCLUDE_ASM(EnemyBrainStatus_Boy);

INCLUDE_ASM(EnemyBrainStatus_Girl);

INCLUDE_ASM(actEnemyFlagCheckDead);

INCLUDE_ASM(actEnemyFlagCheckActive);

INCLUDE_ASM(ACTEnemyForceSwitchToCarry);

INCLUDE_ASM(actEnemy_GetClingTarget);

INCLUDE_ASM(actEnemy_isNormalEnemy);

INCLUDE_ASM(actEnemy_isLargeEnemy);

INCLUDE_ASM(actEnemy_isSmallEnemy);

INCLUDE_ASM(IsEnemyBrainToGenerator);

INCLUDE_ASM(IsEnemyBrainToBoy);

INCLUDE_ASM(GetEnemyTypeFromGObj);

INCLUDE_ASM(GetEnemyType);

INCLUDE_ASM(isEnemyKidnapEnable);

INCLUDE_ASM(isEnemyActive);

INCLUDE_ASM(subEnemyBrain_Idle);

INCLUDE_ASM(subEnemyBrain_Await);

INCLUDE_ASM(subEnemyBrain_ToGenerator);

INCLUDE_ASM(subEnemyBrain_FindGirl);

INCLUDE_ASM(subEnemyBrain_BodyGuard);

INCLUDE_ASM(subEnemyBrain_Shoulder);

INCLUDE_ASM(subEnemyBrain_Pickup);

INCLUDE_ASM(subEnemyBrain_Bodyslam);

INCLUDE_ASM(_BrainMode_SetDirect);

INCLUDE_ASM(EnemyUtil_TurnToBoy);

INCLUDE_ASM(FlyMail);

INCLUDE_ASM(boss_effect_callback);

INCLUDE_ASM(motEnemyStand);

INCLUDE_ASM(motEnemyWalk);

INCLUDE_ASM(motEnemyRun);

INCLUDE_ASM(actEnemyJump);

INCLUDE_ASM(EnemyUtil_isOtherStatus);

INCLUDE_ASM(isEnemyHyde);

INCLUDE_ASM(_ApproachTarget);

INCLUDE_ASM(afterEnemyBodylift);

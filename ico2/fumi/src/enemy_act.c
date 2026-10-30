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
#include "layout_texture.h"

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
    ((BossPart *)((i) * 0x20 + BOSS_EFFECT_WORK(self) + 0x3C0)) /* derived name */

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

/* The point the lifting enemy turns to: three vectors (the first two equal),
   of which only the first is addressed. */
static sceVu0FVECTOR bodyliftTarget[3] = {
    {-311.0f, -89.0f, -147.0f, 0.0f},
    {-311.0f, -89.0f, -147.0f, 0.0f},
    {-770.0f, -1445.0f, -749.0f, 0.0f},
}; /* derived name */

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

inline int IsEnemyBrainToGenerator(GObj *self, GObj **out)
{
    Act *b = GOBJ_ACT(self);
    if (b->enemy->mode != 5)
        return 0;
    *out = ((ActWork *)b->work)->genTarget;
    if (*out == 0) {
        debug_assert("src/enemy_act.c", 600);
        __assert("src/enemy_act.c", 600, "*generator_gop!=NULL");
    }
    return 1;
}

inline int IsEnemyBrainToBoy(GObj *self)
{
    Act *sub;
    EnemyBattleWork *sub2;
    if ((char *)girlGObj != 0) {
        Act *sub_d = GOBJ_ACT(girlGObj);
        if (sub_d->actMode != 106)
            return 0;
    }
    sub = GOBJ_ACT(self);
    sub2 = sub->enemy;
    return sub2->mode == 3;
}

static void setBattleStatus(GObj *self)
{
    switch (GOBJ_ACT(self)->enemy->battleType) {
    case 0:
        GOBJ_ACT(self)->enemy->flags.ll &= ~1LL;
        GOBJ_ACT(self)->enemy->flags.ll &= ~2LL;
        break;
    case 1:
        GOBJ_ACT(self)->enemy->flags.ll &= ~1LL;
        GOBJ_ACT(self)->enemy->flags.ll |= 2LL;
        break;
    case 2:
        GOBJ_ACT(self)->enemy->flags.ll |= 1LL;
        GOBJ_ACT(self)->enemy->flags.ll &= ~2LL;
        break;
    case 3:
        GOBJ_ACT(self)->enemy->flags.ll |= 1LL;
        GOBJ_ACT(self)->enemy->flags.ll |= 2LL;
        break;
    default:
        debug_assert("src/enemy_act.c", 642);
        __assert("src/enemy_act.c", 642, "0");
    }
}

/* a static inline, inlined by both boss_effect_start and
   boss_effect_process */
static inline void bossEffectSetNodePos(GObj *self, float *dst, int idx) /* derived name */
{
    Sub15C *g = GOBJ_SUB(self);

    sceVu0CopyVector(dst, (float *)((char *)g->nodeMtx + idx * 0x40 + 0x30));
    dst[3] = 1.0f;
}

inline void boss_effect_callback(int id)
{
    GObj *g;
    int i;
    char *p;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (GOBJ_ACT(g)->enemy->liftKind == 3) {
            for (i = 0; i < 5; i++) {
                p = (char *)(i * 0x20 + (int)GOBJ_ACT(g)->enemy + 0x3C0);
                if (p[0x1D] != 0 && *(int *)(p + 0x10) == id) {
                    p[0x1C] = 0;
                    return;
                }
            }
        }
    }
}

static void boss_effect_start(GObj *self, int id)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (*(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x3DD) == 0) {
            float buf[4] = {0.0f, 0.0f, 0.0f, 1.0f};

            bossEffectSetNodePos(self, (float *)(i * 0x20 + BOSS_START_WORK(self) + 0x3C0), id);
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x3D0) =
                GatherEffect_Set(12, (char *)BOSS_START_WORK(self) + (i * 0x20 + 0x3C0), buf,
                                 (char *)BOSS_START_WORK(self) + (i * 0x20 + 0x3C0), 1.0f,
                                 (void *)boss_effect_callback);
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x3D4) = id;
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x3D8) =
                (60 - systemStatus[0] * 10) / systemStatus[1];
            *(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x3DC) = 1;
            *(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x3DD) = 1;
            return;
        }
    }
    ReviveEnemyParticle(self, id);
}

static void boss_effect_check_parts(GObj *self, int id)
{
    char *p = (char *)GOBJ_ACT(self)->enemy + 0x3C0;
    int i;
    for (i = 0; i < 5; i++, p += 0x20) {
        if (p[0x1D] != 0 && *(int *)(p + 0x14) == id) {
            return;
        }
    }
    boss_effect_start(self, id);
}

static void boss_effect_process(GObj *self)
{
    float tmp[4];
    int n;
    int i;

    n = GOBJ_SUB(self)->skelNodeNum;
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
            GatherEffect_SetGoal(*(int *)((char *)(i * 0x20 + BOSS_EFFECT_WORK(self)) + 0x3D0),
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

static void _DoAwait(GObj *self)
{
    MotionDef *row;
    if (boyGObj != 0) {
        _ACTParaStatus_Set(self, 27);
        row = &motionKind[GOBJ_SUB(self)->ctrl.motion];
        if ((row->flags.word >> 6) & 1) {
            EnemyUtil_TurnToBoy(self, boyGObj, 5);
        }
    }
}

static void _DoAwaitGirl(GObj *self)
{
    MotionDef *row;
    if ((char *)girlGObj != 0) {
        _ACTParaStatus_Set(self, 27);
        row = &motionKind[GOBJ_SUB(self)->ctrl.motion];
        if ((row->flags.word >> 6) & 1) {
            EnemyUtil_TurnToBoy(self, girlGObj, 5);
        }
    }
}

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

/* a static inline */
static inline int getEnemyBrainMes(char *self, int *data) /* derived name */
{
    EBSlot *t = eBrainGetTarget((GObj *)self);

    if (t == 0) {
        *data = 0;
        return 0;
    }
    *data = (int)t->target;
    return t->status;
}

void subEnemyControl(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    float pos[4];
    float dir[4];
    int runCnt = 0;
    int walkCnt = 0;
    int stopCnt = 0;

    iosPadConnect(&sub->pad, 0, 1, &sub->padConf);
    while (1) {
        enemyPollHitNodes(self);
        /* the stick poll loop, subBoyControl's shape, repeating only under the
           DEBUG hold (retail breaks after one pass) */
        for (;;) {
            if (((int)(sub->flags18.ll >> 42)) & 1) {
                if (self == CurrentTargetGObj) {
                    iosPadConnect(&sub->pad, 0, 0, &sub->padConf);
                    iosPadRead(&sub->pad);
                    iosPadGetStick(&sub->pad, &sub->stick, 0, 2, 2, 0);
                    _GetMotionDirection(dir, self);
                    sub->stick.angle = CorrectStickInfo(dir, &sub->stick);
                    if (0.001f < sub->stick.mag) {
                        ConvertStickToAbsCoord(pos, &sub->stick);
                        sub->dir[0] = pos[0];
                        sub->dir[1] = pos[1];
                        sub->dir[2] = pos[2];
                    }
                } else if (self == CurrentTargetGObjSub) {
                    iosPadConnect(&sub->pad, 0, 1, &sub->padConf);
                } else {
                    iosPadConnect(&sub->pad, 0, 1, &sub->padConf);
                }
            }
            if (!ENEMY_DEBUG_HOLD) {
                break;
            }
            _ACTWait(1);
        }
        /* the whole counter update */
        stopCnt++;
        if (0.1f < sub->stick.mag) {
            stopCnt = 0;
        }
        if (0.1f < sub->stick.mag && (sub->stick.mag < 0.99f || (sub->pad.now & 0x20))) {
            walkCnt++;
        } else {
            walkCnt = 0;
        }
        /* moving and not walking, with the walking predicate repeated whole
           inside the negation, as commonact.c's _ACTCommonMailTest writes
           it */
        if (0.1f < sub->stick.mag &&
            !(0.1f < sub->stick.mag && (sub->stick.mag < 0.99f || (sub->pad.now & 0x20)))) {
            runCnt++;
        } else {
            runCnt = 0;
        }
        pos[0] = sub->dir[0];
        pos[1] = sub->dir[1];
        pos[2] = sub->dir[2];
        _ACTCommonMailTest(self, stopCnt, walkCnt, runCnt);
        switch (sub->actMode) {
        case 1:
            ACTSendMailCorrect((void *)self, 177);
            break;
        case 2:
            if (0.1f < sub->stick.mag && (sub->stick.mag < 0.99f || (sub->pad.now & 0x20)) &&
                !(walkCnt < 4)) {
                if (CheckFloorAttribute(self, 0x200)) {
                    ACTSendMailCorrect((void *)self, 164);
                } else {
                    ACTSendMailCorrect((void *)self, 163);
                }
            }
            break;
        case 3:
            ACTSendMailCorrect((void *)self, 168);
            break;
        /* a fifth case label, its value unknown: every index from 4 to 37 of
           the jump table goes to the break */
        case 4:
            break;
        case 38:
            if (100 < sub->stick.y - 128) {
                ACTSendMailCorrect((void *)self, 296);
            } else if (sub->stick.y - 128 < -100) {
                ACTSendMailCorrect((void *)self, 295);
            } else {
                ACTSendMailCorrect((void *)self, 301);
            }
            break;
        }
        _ACTWait(1);
    }
}

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
            ACTSendMailCorrect(self, 208);
        } else {
            ACTSendMailCorrect(self, 207);
        }
        return 1;
    } else if (aang < 0xF) {
        ACTSendMailCorrect(self, 217);
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
    if ((char *)gsub == 0 || gsub->actMode != 106) {
        return 0;
    }
    if (gsub->carrier == self) {
        return 1;
    }
    return 0;
}

void subEnemyCollision(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while ((int)sub->motReq == 0) {
        _ACTWait(1);
    }
    while (1) {
        float *dir = sub->dir;
        if (actEnemyFlagCheckActive(self) != 0) {
            *(long long *)((char *)sub + 0x18) = (long long)sub->flags18.ll | (1LL << 32);
        } else {
            *(long long *)((char *)sub + 0x18) = (long long)sub->flags18.ll & ~(1LL << 32);
        }
        if (GOBJ_ACT(self)->enemy->paraStatus != 0) {
            _ACTParaStatus_Set(self, GOBJ_ACT(self)->enemy->paraStatus);
        }
        if (GOBJ_ACT(self)->enemy->liftKind == 3) {
            GOBJ_ACT(self)->enemy->slowTimer -= 1;
            if (0 < GOBJ_ACT(self)->enemy->slowTimer) {
                float rate = (60 - GOBJ_ACT(self)->enemy->slowTimer) / 60.0f;
                float speed = (rate < 0.1f) ? 0.1f : ((1.0f < rate) ? 1.0f : rate);
                ACTGame_SetMotionPlaySpeedRatio_Reserve(self, speed, 8);
            }
        }
        ACTGame_CommonLoop((void *)self);
        CommonAttackCenter(self);
        if (GOBJ_ACT(self)->enemy->liftKind == 3) {
            boss_effect_process(self);
        }
        if (sub->actMode == 5 && 300.0f < GOBJ_SUB(self)->ctrl.groundHeight) {
            FlyMail((void *)self);
        }
        if (sub->stick.mag != 0.0f) {
            enemyCheckTurnAngle(self);
        }
        if (0.1f < sub->stick.mag && sub->actMode != 110) {
            SetMotionDirectionSmooze(self, dir,
                                     (float)motionKind[GOBJ_SUB(self)->ctrl.motion].dirFrames);
        }
        if (actEnemyFlagCheckDead(self) == 0) {
            ACTGame_SaveActorInformation(self);
        }
        if (sub->actMode != 107) {
            /* the actor-entry parameter, reloaded for the DEBUG build's state
               report */
            GObj *obj = self;
#ifdef DEBUG
            scePrintf("enemy %08x state %x\n", obj, sub->actMode);
#endif
        }
        if (sub->actMode != 22) {
            if (0x16 < (unsigned int)sub->actMode) {
                if (sub->actMode == 28) {
                    if (0.1f < sub->stick.mag &&
                        (sub->stick.angle < -134 || 134 < sub->stick.angle)) {
                        ACTSendMailCorrect((void *)self, 202);
                    } else if (0.1f < sub->stick.mag &&
                               (-45 <= sub->stick.angle && sub->stick.angle <= 45)) {
                        if ((pad[0].now & 4) == 0) {
                            ACTSendMailCorrect((void *)self, 177);
                        }
                    }
                    ACTSendMailCorrect((void *)self, 301);
                }
            }
        }
        DispMultiBgaManagerWithKind(398, GOBJ_WORK(self)->bga, 1);
        ACTParaStatus_Exec((void *)self);
        if (isEnemyActive(self) == 0 && isEnemyCarriedByGirl(self)) {
            afterCommonCarry(self);
        }
        _ACTWait(1);
    }
}

inline void actEnemyStand(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    debug_StdPrintfDummy("enter actEnemyStand\n");
    sub->actMode = 1;
    _ACTWait(0);
}

inline void motEnemyStand(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    debug_StdPrintfDummy("enter motEnemyStand\n");
    sub->motReq = SetMotionRequest(self, 1, sub->env.motOriReq);
    while (1) {
        _ACTWait(1);
    }
}

inline void actEnemyWalk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    debug_StdPrintfDummy("enter actEnemyWalk\n");
    sub->actMode = 2;
    _ACTWait(0);
}

inline void motEnemyWalk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    char *mot;
    debug_StdPrintfDummy("enter motEnemyWalk\n");
    mot = SetMotionRequest(self, 7, sub->env.motOriReq);
    sub->motReq = mot;
    *(int *)(mot + 0x114) = 0;
    _ACTWait(0);
}

inline void actEnemyRun(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    debug_StdPrintfDummy("enter actEnemyRun\n");
    sub->actMode = 3;
    _ACTWait(0);
}

inline void motEnemyRun(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    char *mot;
    debug_StdPrintfDummy("enter motEnemyRun\n");
    mot = SetMotionRequest(self, 12, sub->env.motOriReq);
    sub->motReq = mot;
    *(int *)(mot + 0x114) = 0;
    _ACTWait(0);
}

inline void actEnemyJump(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    debug_StdPrintfDummy("enter actEnemyJump\n");
    sub->actMode = 4;
    _ACTWait(0);
}

void actEnemyAttack(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int hit = 0;
    float buf[4];
    float v[4];

    _ACTWait(2);
    ACTSearchEnemy((void *)self, &sub->attackTurn, buf);
    _OrientXZGV(v, test_CURRENTROOT(((void *)boyGObj)), test_CURRENTROOT(self));
    sub->dir[0] = v[0];
    sub->dir[1] = v[1];
    sub->dir[2] = v[2];
    SetMotionDirection((void *)self, v);
    while (1) {
        if (GetMotionFrameFlag2((void *)self) != 0 && sub->attackTurn != 0) {
            SetMotionDirectionWithLimit((void *)self, buf, 10.0f, 90.0f);
        }
        if (sub->pad.trg & 0x80) {
            hit = 1;
        }
        if (hit != 0) {
            ACTSendMailCorrect((void *)self, 183);
        }
        ACTSendMailCorrect((void *)self, 177);
        EnemyAttackCenter(self);
        _ACTWait(1);
    }
}

/* A static inline.  `sub` is computed inside the helper; in enemy_dodge the
   caller already holds it. */
static inline void enemyDodgeSendMail(GObj *self) /* derived name */
{
    Act *sub = GOBJ_ACT(self);

    if (EnemyUtil_isOtherStatus(self, 0) != 0) {
        return;
    }
    if (((int)(_GetRandom() * 10.0f)) & 1) {
        ACTSendMailCorrect(self, 185);
    }
    ACTSendMailCorrect(self, 183);
    sub->flags18.ll |= 1LL << 62;
}

inline void actEnemyHang(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    debug_StdPrintfDummy("enter actEnemyHang\n");
    sub->actMode = 0x1C;
    _ACTWait(0);
}

inline void funcEnemyAiGetGirl(GObj *self)
{
    Act *sub = GOBJ_ACT(self);
    if (sub->wayMode == 0) {
        sub->wayMode = 1;
    }
}

inline void actEnemyHyde(GObj *self)
{
    sceVu0FVECTOR hide = {0.0f, 0.0f, -1000000.0f};
    SetDirectRootPosition(self, hide);
    ResetEnemyPositionInfo(self);
    actEnemyFlagOnFree(self);
}

inline int isEnemyHyde(GObj *self)
{
    GenGeo *g = &objLayout[self->labelId];
    return ((g->flags >> 21) & 1) ^ 1;
}

inline void actEnemyFlagOnFree(GObj *self)
{
    GenGeo *g = &objLayout[self->labelId];
    g->flags &= ~0x200000;
}

inline void actEnemyFlagOnDead(GObj *self)
{
    GenGeo *g = &objLayout[self->labelId];
    g->flags |= 0x40000;
}

inline int actEnemyFlagCheckDead(GObj *self)
{
    GenGeo *g = &objLayout[self->labelId];
    return (g->flags >> 18) & 1;
}

inline int isEnemyActive(GObj *self)
{
    if (self == 0 || self->kind != 4) {
        debug_assert("src/enemy_act.c", 1835);
        __assert("src/enemy_act.c", 1835, "ASSERTMSG__GOP_IS_NOT_ENEMY(gop)");
    }
    return actEnemyFlagCheckActive(self);
}

inline int actEnemyFlagCheckActive(GObj *self)
{
    GenGeo *g = &objLayout[self->labelId];
    unsigned int field = g->flags;
    unsigned int v0 = (field >> 18) & 1;
    if (v0 != 0)
        goto zero;
    v0 = (field >> 21) & 1;
    v0 = v0 ^ 1;
    if (v0 == 0)
        goto one;
zero:
    return 0;
one:
    return 1;
}

inline int actEnemy_isSmallEnemy(GObj *self)
{
    return GOBJ_ACT(self)->enemy->sizeClass == 0;
}

inline int actEnemy_isLargeEnemy(GObj *self)
{
    return GOBJ_ACT(self)->enemy->sizeClass == 2;
}

inline int actEnemy_isNormalEnemy(GObj *self)
{
    return GOBJ_ACT(self)->enemy->sizeClass == 1;
}

inline GObj *actEnemy_GetClingTarget(GObj *self)
{
    Act *b = GOBJ_ACT(self);
    EnemyBattleWork *e = b->enemy;
    if (e->sizeClass == 0 && b->actMode == 16) {
        return (GObj *)e->clingTarget;
    }
    return 0;
}

void actEnemyRestart(GObj *self, float *pos, float *dir, int kind, GObj *mother)
{
    Act *sub;
    int mail;
    int idx;
    float life;

    sub = GOBJ_ACT(self);
    mail = 48;
    switch (kind) {
    case 0:
        pos[1] = pos[1] + GOBJ_ACT(self)->enemy->bodySize * 100.0f;
        break;
    case 1:
        mail = 49;
        break;
    case 2:
        mail = 50;
        break;
    }
    RandomizeEnemy(self);
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
        debug_assert("src/enemy_act.c", 1899);
        __assert("src/enemy_act.c", 1899, "0");
    }
    GOBJ_ACT(self)->enemy->battleType = idx;
    setBattleStatus(self);
    life = GetEnemyDefLife(self);
    sub->maxLife = life;
    sub->life = life;
    sub->wayMode = 0;
    if (mother != 0) {
        sub->mother = mother;
    } else {
        sub->mother = 0;
    }
    sub->mail = (ActMail *)&actIntrList[70];
    ACTSendMailCorrect(self, mail);
    InitMotionGeoInfo(&GOBJ_SUB(self)->root, pos[0], pos[1], pos[2], 0.0f, 0.0f, 0.0f);
    ResetEnemyPositionInfo(self);
    sub->restartPosX = pos[0];
    sub->restartPosY = pos[1];
    sub->restartPosZ = pos[2];
    SetMotionDirection(self, dir);
    eBrainSendMes(self, 4);
}

/* PairSetGeometry is a GNU nested function, reading its parent's frame
   through the static chain. */
static int actEnemyForceSwitchToCarry(void *self)
{
    void PairSetGeometry(void *me, void *pair, float dist)
    {
        float p0[4];
        float p1[4];
        float dir[4];
        float ofs[4];

        p0[0] = test_CURRENTROOT(me)[0];
        p0[1] = test_CURRENTROOT(me)[1];
        p0[2] = test_CURRENTROOT(me)[2];
        p1[0] = test_CURRENTROOT(pair)[0];
        p1[1] = test_CURRENTROOT(pair)[1];
        p1[2] = test_CURRENTROOT(pair)[2];
        _OrientXZGV(dir, p1, p0);
        sceVu0ScaleVector(ofs, dir, dist);
        sceVu0AddVector(p1, p0, ofs);
        SetDirectRootPosition(pair, p1);
        GOBJ_ACT(me)->dir[0] = dir[0];
        GOBJ_ACT(me)->dir[1] = dir[1];
        GOBJ_ACT(me)->dir[2] = dir[2];
        sceVu0ScaleVector((float *)((char *)GOBJ_ACT(pair) + 0x100), dir, -1.0f);
        SetMotionDirection(me, (float *)((char *)GOBJ_ACT(me) + 0x100));
        SetMotionDirection(pair, (float *)((char *)GOBJ_ACT(pair) + 0x100));
    }
    float q[4];
    Act *sub = GOBJ_ACT(self);

    if ((char *)girlGObj == 0) {
        return 0;
    }
    if (ACTReserveTarget(girlGObj, self, 231) == 0) {
        return 0;
    }
    if (GOBJ_ACT(girlGObj)->actMode == 106) {
        return 0;
    }
    PairSetGeometry(self, (char *)girlGObj, 50.0f);
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, -0x8000);
    SetMotionNodeFixModeParameter(girlGObj, self, 2, GOBJ_ACT(self)->enemy->clingNode, q, 18.0f,
                                  0.0f, 0.0f, 1.0f);
    sub->carried = girlGObj;
    GOBJ_ACT(girlGObj)->carrier = self;
    ACTGameCollisionOff((void *)girlGObj);
    eBrainSendMes(self, 9);
    eBrainSendMes(self, 7);
    return 1;
}

inline int ACTEnemyForceSwitchToCarry(GObj *self)
{
    int r = actEnemyForceSwitchToCarry(self);
    if (r != 0) {
        _BrainMode_SetDirect(self, 0, 0);
    }
    ACTSendMailCorrect(self, 235);
    return r;
}

inline void actEnemyNest(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int stg;
    GObj *x2;

    sub->carried = 0;
    actChangeActBrain(isysCurrentGObj, (void *)subEnemyBrain_Idle, &sub->brainProc);
    actEnemyHyde(self);
    eBrainSendMes(self, 10);
    stg = stage_no;
    *(int *)((char *)sub + 0x430) = 0;
    x2 = self;
    sub->infoPos = 7;
    gamesysObjInfoPosSetStage(x2, 7, 0, stg);
    _ACTWait(0);
}

void actEnemyKidnapEnd(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    float mypos[4];
    float gpos[4];

    union { /* field names derived */
        float f[4];
        int i[4];
    } q;

    int revived = 0;
    GObj *target = 0;
    GObj *g;
    float best;
    float d;

    if (gflagChk(342) == 0) {
        ACTGame_InsertCamera_GirlIsPinch();
    }
    g = isysGObjSearchFromObjKindID_begin(33);
    best = 10000.0f;
    mypos[0] = test_CURRENTROOT((void *)self)[0];
    mypos[1] = test_CURRENTROOT((void *)self)[1];
    mypos[2] = test_CURRENTROOT((void *)self)[2];
    while (g != 0) {
        GetRootPosition(gpos, g);
        d = _DistGV(mypos, gpos);
        if (d < best) {
            best = d;
            target = g;
        }
        g = isysGObjSearchFromObjKindID_next(g);
    }
    if (target != 0) {
        memset(&q, 0, 0x10);
        q.f[3] = 1.0f;
        EntryMultiBgaManager(GOBJ_WORK(self)->bga, 0, -1, test_CURRENTROOT(target), q.f);
    }
    gflagOn(342);
    while (1) {
        if (((int)((long long)sub->flags20.ll >> 5)) & 1) {
            ACTGame_SetMotionPlaySpeedRatio_Reserve(self, 0.0001f, 9);
        }
        if (gflagChk(341) != 0) {
            stgmgrNextStagePreLoadForceStageSet(gFlagSaveStage);
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 3 < sub->modeFrame) {
                backStageTsuresariReturn();
                _ACTWait(0);
            }
        }
        if (5 <= sub->modeFrame) {
            if (GOBJ_ACT(girlGObj)->actMode != 106 || GOBJ_ACT(girlGObj)->carrier != self) {
                if (revived == 0) {
                    revived = 1;
                    RestoreReviveCount(self);
                }
                sub->infoPos = 0;
                gamesysObjInfoPosSetStage(self, 0, 0, stage_no);
            }
        }
        if (GOBJ_SUB(self)->ctrl.motion == 938) {
            /* the girl's record and her action are read before the tests,
               with the carried action's id in a local (as the USA build) */
            Act *gsub = GOBJ_ACT(girlGObj);
            int act = gsub->actMode;
            int carriedAct = 106;

            if (50.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if ((((int)((long long)sub->flags20.ll >> 5)) & 1) == 0) {
                    if (act == carriedAct && gsub->carrier == self) {
                        if (target != 0) {
                            /* q, the identity quaternion above, is
                               reused as stage_SetParentOfGObj's parent
                               record (the target object, then 0); the
                               flag and the record's first word are stored
                               through volatile views, the object only
                               after the flag */
                            *(volatile int *)&gameover_flag = 1;
                            *(volatile int *)&q.i[0] = (int)target;
                            q.i[1] = 0;
                            stage_SetParentOfGObj(394, &q);
                            stage_SetAnimation(394, 1, 0);
                            while (stage_CheckAnimationFinish(394) == 0) {
                                _ACTWait(1);
                            }
                            _ACTWait(1);
                        }
                        lt_switch_layout(58);
                    } else {
                        ACTSendMailCorrect(self, 310);
                    }
                }
            }
        }
        _ACTWait(1);
    }
}

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

void actEnemyKidnapBegin(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    float *dir = sub->dir;
    int mail = 312;
    int mode;

    while (1) {
        if (GOBJ_SUB(self)->ctrl.motion == 931) {
            _OrientXZGV(dir, test_CURRENTROOT((girlGObj)), test_CURRENTROOT(self));
            if (0.1f < sub->stick.mag && sub->actMode != 110) {
                SetMotionDirectionSmooze((void *)self, dir,
                                         (float)motionKind[GOBJ_SUB(self)->ctrl.motion].dirFrames);
            }
            mode = enemyKidnapCheckGirl(self);
            switch (mode) {
            case 1:
                mail = 313;
                /* fallthrough */
            case 2:
                if (actEnemyForceSwitchToCarry((void *)self) != 0) {
                    if (mode == 1) {
                        sceVu0ScaleVector(GOBJ_ACT(girlGObj)->dir, GOBJ_ACT(girlGObj)->dir, -1.0f);
                        SetMotionDirection((void *)((char *)girlGObj), GOBJ_ACT(girlGObj)->dir);
                    }
                    ACTGame_InsertCamera_GirlIsPinch();
                    while (1) {
                        ACTSendMailCorrect((void *)self, mail);
                        _ACTWait(1);
                    }
                }
                break;
            }
            ACTSendMailCorrect((void *)self, 314);
        }
        _ACTWait(1);
    }
}

/* a `static inline` defined outside this function */
static inline void enemyBodyliftClearBoy(char *self) /* derived name */
{
    GOBJ_SUB(self)->ctrl.catchBoy = 0;
    GOBJ_SUB(self)->root.lookMode = 0;
}

static void MoveChestForCatchBoy(GObj *self)
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
    int ang2;

    GOBJ_SUB(self)->ctrl.catchBoy = 1;
    GOBJ_SUB(self)->root.lookMode = 2;
    GetRootProjectionPosOfGObj(p0, self);
    GetRootProjectionPosOfGObj(p1, ((void *)boyGObj));
    GetSkeltonPosition(sk, self, 1);
    t = (p0[1] - p1[1]) / 600.0f;
    t = (t < 0.0f) ? 0.0f : ((1.0f < t) ? 1.0f : t);
    a = t * 1000.0f + -200.0f;
    b = t * -400.0f;
    ori[0] = test_CURRENTORIENT(self)[0];
    ori[1] = test_CURRENTORIENT(self)[1];
    ori[2] = test_CURRENTORIENT(self)[2];
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
    sceVu0AddVector(GOBJ_SUB(self)->root.lookPos, p0, sc);
    debug_NMarker(GOBJ_SUB(self)->root.lookPos, 255, 0, 0, 200.0f);
}

inline void afterEnemyBodylift(GObj *volatile self)
{
    enemyBodyliftClearBoy((char *)self);
}

void actEnemyBodylift(GObj *volatile self)
{
    float dir[4];
    float pos[4];
    float bpos[4];
    float mtx[16];
    float lv[4];
    Act *sub;
    int hit;

    sub = GOBJ_ACT(self);
    hit = 0;
    GOBJ_ACT(self)->enemy->flags.ll &= ~4LL;
    _OrientXZGV(dir, bodyliftTarget[0], test_CURRENTROOT(self));
    sub->after = (void *)afterEnemyBodylift;
    if (GOBJ_ACT(self)->enemy->liftKind != 3) {
        _OrientXZGV(sub->dir, test_CURRENTROOT(((void *)boyGObj)), test_CURRENTROOT(self));
        SetMotionDirection((void *)self, sub->dir);
    }
    for (;;) {
        GOBJ_ACT(self)->enemy->flags.ll &= ~4LL;
        if (GOBJ_ACT(self)->enemy->liftKind == 3) {
            if (GOBJ_ACT(boyGObj)->actMode == 90) {
                enemyBodyliftClearBoy((char *)self);
            } else {
                MoveChestForCatchBoy(self);
            }
        }
        GetSkeltonPosition(pos, self, 22);
        bpos[0] = test_CURRENTROOT(((void *)boyGObj))[0];
        bpos[1] = test_CURRENTROOT(((void *)boyGObj))[1];
        bpos[2] = test_CURRENTROOT(((void *)boyGObj))[2];
        if (GOBJ_ACT(self)->enemy->liftKind == 3) {
            sceVu0SubVector(lv, test_CURRENTROOT(((void *)boyGObj)), pos);
            GetMatrixDirectionToZ(mtx, test_CURRENTORIENT(self));
            lv[3] = 0.0f;
            sceVu0ApplyMatrix(lv, mtx, lv);
            if (((lv[0] < 0.0f) ? -lv[0] : lv[0]) < 100.0f &&
                ((lv[1] < 0.0f) ? -lv[1] : lv[1]) < 100.0f && -300.0f < lv[2] && lv[2] < 200.0f) {
                hit = 1;
            }
        } else {
            if (_DistSqGV(pos, bpos) < GOBJ_ACT(self)->enemy->bodySize * 45.0f *
                                           (GOBJ_ACT(self)->enemy->bodySize * 45.0f)) {
                hit = 1;
            }
        }
        if (GOBJ_SUB(self)->ctrl.motion == 972) {
            if (GOBJ_ACT(boyGObj)->actMode == 90 &&
                GOBJ_ACT(boyGObj)->enemy->liftedObj == (int)self &&
                GOBJ_ACT(self)->enemy->liftKind == 3 &&
                !(0 < GOBJ_ACT(boyGObj)->enemy->liftLevel)) {
                if (GetMotionFrameFlag1((void *)self) != 0) {
                    ACTSendMailCorrect((void *)self, 328);
                    iosOmSendMail(((void *)boyGObj), 202, self);
                }
                if (GetMotionFrameFlag2((void *)self) != 0) {
                    ACTSendMailCorrect((void *)self, 329);
                    iosOmSendMail(((void *)boyGObj), 202, self);
                }
            }
        } else {
            if (GetMotionFrameFlag1((void *)self) != 0 && hit != 0) {
                iosOmSendMail(((void *)boyGObj), 320, self);
            }
            if (GetMotionFrameFlag2((void *)self) != 0) {
                _OrientXZGV(bpos, test_CURRENTROOT(((void *)boyGObj)), test_CURRENTROOT(self));
                _ACTMotDirSmzDirect((void *)self, bpos);
            }
        }
        if (GOBJ_ACT(boyGObj)->actMode == 90 && GOBJ_ACT(boyGObj)->enemy->liftedObj == (int)self) {
            if (GOBJ_ACT(self)->enemy->liftKind == 3) {
                if (GOBJ_SUB(self)->ctrl.motion == 972) {
                    _ACTMotDirSmzDirect((void *)self, dir);
                    if (_AbsRotyGV(test_CURRENTORIENT(self), dir) < 5) {
                        GOBJ_ACT(self)->enemy->flags.ll |= 4LL;
                    }
                    if ((((int)(GOBJ_ACT(self)->enemy->flags.ll >> 2)) & 1) == 0) {
                        ACTGame_SetMotionPlaySpeedRatio_Reserve(self, 0.1f, 8);
                    }
                }
                if (0 < GOBJ_ACT(boyGObj)->enemy->liftLevel) {
                    ACTSendMailCorrect((void *)self, 326);
                } else {
                    ACTSendMailCorrect((void *)self, 327);
                }
            } else {
                ACTSendMailCorrect((void *)self, 324);
            }
        } else {
            ACTSendMailCorrect((void *)self, 177);
        }
        _ACTWait(1);
    }
}

inline void actEnemyBodyslamFail(GObj *volatile self)
{
    iosOmSendMail(((void *)boyGObj), 202, self);
    while (1) {
        ACTSendMailCorrect((void *)self, 177);
        _ACTWait(1);
    }
}

inline void actEnemyBodyslam(GObj *volatile self)
{
    iosOmSendMail(((void *)boyGObj), GOBJ_ACT(self)->enemy->bodyslamMail, self);
    while (1) {
        ACTSendMailCorrect((void *)self, 177);
        _ACTWait(1);
    }
}

void actEnemyPickupBegin(GObj *volatile self)
{
    inline int pickupCheckGirl(void) /* derived name */
    {
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
        {
            float pos[4];

            GetRootProjectionPosOfGObj(pos, (char *)((char *)girlGObj));
            scePrintf("pickup check %d girl %f %f %f\n", mode, pos[0], pos[1], pos[2]);
        }
#endif
        return mode;
    }
    float *dir = GOBJ_ACT(self)->dir;
    float *girl = test_CURRENTROOT((girlGObj));
    float *me = test_CURRENTROOT(self);
    int mode;

    _OrientXZGV(dir, girl, me);
    SetMotionDirection((void *)self, dir);
    while (1) {
        mode = pickupCheckGirl();
        if (mode < 3 && mode != 0) {
            if (actEnemyForceSwitchToCarry((void *)self) != 0) {
                ACTGame_InsertCamera_GirlIsPinch();
                while (1) {
                    ACTSendMailCorrect((void *)self, 317);
                    _ACTWait(1);
                }
            }
        }
        ACTSendMailCorrect((void *)self, 318);
        _ACTWait(1);
    }
}

inline void actEnemyCarry(GObj *volatile self)
{
    debug_assert("src/enemy_act.c", 2542);
    __assert("src/enemy_act.c", 2542, "0");
}

inline int EnemyBrainStatus_Boy(GObj *self)
{
    return GOBJ_ACT(self)->brainAim == 2;
}

inline int EnemyBrainStatus_Girl(GObj *self)
{
    return GOBJ_ACT(self)->brainAim == 1;
}

static void CheckEnemyBrainMode(char *self, int *outMode, int *outData)
{
    char *sub = *(char **)(self + 0x164);
    int mode;

    *outData = 0;
    if (*(int *)(sub + 0x128) != 0 && motionKind[GOBJ_SUB(self)->ctrl.motion].word0FC == 0) {
        *outMode = -1;
        return;
    }
    if (((*(unsigned long long *)(sub + 0x18) >> 43) & 1) == 0) {
        *outMode = -1;
        return;
    }
    if (actEnemyFlagCheckActive((GObj *)self) == 0) {
        *outMode = -1;
        return;
    }
    switch (*(unsigned int *)(sub + 0x30)) {
    case 19:
    case 20:
    case 21:
    case 22:
    case 109:
    case 110:
        *outMode = -1;
        return;
    }
    if (((*(long long *)(sub + 0x140) >> 32) & 1) == 0) {
        goto no_bit;
    }
    *(long long *)(sub + 0x140) &= ~(1LL << 32);
    mode = -2;
    goto store;
no_bit:
    mode = getEnemyBrainMes(self, outData);
store:
    *outMode = mode;
}

inline void _BrainMode_SetDirect(GObj *self, int mode, BrainModeTarget *tgt)
{
    GOBJ_ACT(self)->enemy->reqMode = mode;
    if (tgt != 0) {
        GOBJ_ACT(self)->enemy->flags.w.reqTarget = *tgt;
    } else {
        GOBJ_ACT(self)->enemy->flags.w.reqTarget = brainTargetNone;
    }
}

/* A static inline between _BrainMode_SetDirect and subEnemyBrainMain. */
static inline void _BrainMode_Set(GObj *self, int mode, BrainModeTarget *tgt) /* derived name */
{
    if (brainModeTable[mode].pri < brainModeTable[GOBJ_ACT(self)->enemy->reqMode].pri) {
        return;
    }
    _BrainMode_SetDirect(self, mode, tgt);
}

void subEnemyBrainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int mode;
    int data;

    /* BrainMode_Requset is a GNU nested function: it reads self out of
       subEnemyBrainMain's frame through the static chain. */
    void BrainMode_Requset(int req, int arg)
    {
        switch (req) {
        case 0:
            _BrainMode_Set(self, 1, 0);
            break;
        case -2:
            _BrainMode_Set(self, 1, 0);
            break;
        case 1:
            _BrainMode_Set(self, 3, 0);
            break;
        case 2:
            _BrainMode_Set(self, 4, 0);
            break;
        case 3:
            _BrainMode_Set(self, 6, 0);
            break;
        case -3:
        case -1:
        case 7:
            _BrainMode_Set(self, 13, 0);
            break;
        case 5:
            _BrainMode_Set(self, 7, (BrainModeTarget *)&arg);
            break;
        case 4:
        case 6:
            _BrainMode_Set(self, 5, (BrainModeTarget *)&arg);
            break;
        case 8:
            _BrainMode_SetDirect(self, 2, (BrainModeTarget *)&arg);
            break;
        default:
            debug_StdPrintfDummy("undefined mode [%d]\n", req);
            debug_assert("src/enemy_act.c", 2703);
            __assert("src/enemy_act.c", 2703, "0");
            break;
        }
    }

    GOBJ_ACT(self)->enemy->reqMode = GOBJ_ACT(self)->enemy->mode = 0;
    GOBJ_ACT(self)->enemy->waitCount = 2;
    _ACTWait(1);
    _ACTWait(1);
    _ACTWait(1);
    switch (sub->brainStatus) {
    case 4:
        if ((char *)girlGObj != 0) {
            eBrainSendMes(self, 9);
            eBrainSendMes(self, 7);
            sub->motReq = SetMotionRequest(self, 219, sub->env.motOriReq);
            actEnemyForceSwitchToCarry((void *)self);
            if (gflagChk(342) != 0) {
                sub->motReq = SetMotionRequest(self, 220, sub->env.motOriReq);
            }
        }
        break;
    case 1:
        if ((char *)girlGObj != 0 &&
            ACTCheckViewCl((void *)self, (char *)girlGObj, test_CURRENTROOT((girlGObj)), 360,
                           3.40282347e+38f /* FLT_MAX */) != 0) {
            eBrainSendMes(self, 2);
        } else {
            eBrainSendMes(self, 1);
        }
        break;
    case 2:
        if ((char *)girlGObj != 0) {
            eBrainSendMes(self, 2);
        }
        break;
    case 5:
        eBrainSendMes(self, 3);
        break;
    }
    while (1) {
        CheckEnemyBrainMode((char *)self, &mode, &data);
        BrainMode_Requset(mode, data);
        if (GOBJ_ACT(self)->enemy->reqMode != GOBJ_ACT(self)->enemy->mode ||
            (((int)(sub->flags18.ll >> 61)) & 1) != 0) {
            sub->flags18.ll &= ~(1LL << 61);
            GOBJ_ACT(self)->enemy->mode = GOBJ_ACT(self)->enemy->reqMode;
            GOBJ_ACT(self)->enemy->target = (int)GOBJ_ACT(self)->enemy->flags.w.reqTarget.gobj;
            sub->brainTarget = (GObj *)GOBJ_ACT(self)->enemy->target;
            sub->brainAim = brainModeTable[GOBJ_ACT(self)->enemy->mode].aim;
            sub->infoPos = brainModeTable[GOBJ_ACT(self)->enemy->mode].infoPos;
            if (sub->infoPos == 4) {
                gamesysObjInfoPosSetStage(self, 4, 0, stage_no);
            }
            actChangeActBrain(isysCurrentGObj,
                              (void *)brainModeTable[GOBJ_ACT(self)->enemy->mode].brain,
                              &sub->brainProc);
        }
        if (sub->carried != 0) {
            _ACTCharStatus_Set((void *)self, 12, -1.0f, 0);
        }
        if (GOBJ_ACT(self)->enemy->waitCount != 0) {
            GOBJ_ACT(self)->enemy->waitCount -= 1;
        }
        if (brainModeTable[GOBJ_ACT(self)->enemy->mode].stoppable != 0 &&
            (((int)(sub->flags18.ll >> 58)) & 1)) {
            char *g = *(char **)(char *)sub;

            isysGObjProcPause(g);
            *(long long *)((char *)sub + 0x20) |= 32LL;
            sub->stick.mag = 0;
            *(int *)((char *)sub + 0x100) = 0;
            *(int *)((char *)sub + 0x104) = 0;
            *(int *)((char *)sub + 0x108) = 0;
            sub->stick.y = 127;
            sub->stick.x = 127;
            while (1) {
                if (((int)(sub->flags18.ll >> 57)) & 1) {
                    isysGObjProcActive(g);
                    *(long long *)((char *)sub + 0x20) &= ~32LL;
                    break;
                }
                _ACTWait(1);
            }
        }
        _ACTWait(1);
    }
}

inline void afterCommonCarry(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    iosOmSendMail(sub->carried, 46, self);
    GOBJ_SUB(sub->carried)->disp = 1;
    ACTGameCollisionOn((void *)sub->carried);
    gflagOff(342);
    sub->carried = 0;
    if (sub->actMode == 5) {
        eBrainSendMes(self, 4);
    }
}

inline void funcEnemyCarryFail(GObj *self)
{
    GOBJ_ACT(self)->flags150.ll |= (1ULL << 32);
}

inline void subEnemyBrain_Idle(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    sub->stick.mag = 0;
    *(int *)((char *)sub + 0x100) = 0;
    *(int *)((char *)sub + 0x104) = 0;
    *(int *)((char *)sub + 0x108) = 0;
    while (1) {
        if (GOBJ_ACT(self)->enemy->target == (int)((void *)boyGObj)) {
            _DoAwait(self);
        }
        _ACTWait(1);
    }
}

inline void subEnemyBrain_Await(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    sub->stick.mag = 0;
    *(int *)((char *)sub + 0x100) = 0;
    *(int *)((char *)sub + 0x104) = 0;
    *(int *)((char *)sub + 0x108) = 0;
    if ((void *)boyGObj != 0) {
        _ApproachTarget(self, (void *)boyGObj, (char *)sub + 0x100, 0,
                        (float)((int)(_GetRandom() * 10.0f) % 200 + 300), 0);
    }
    sub->stick.mag = 0;
    *(int *)((char *)sub + 0x100) = 0;
    *(int *)((char *)sub + 0x104) = 0;
    *(int *)((char *)sub + 0x108) = 0;
    while (1) {
        _DoAwait(self);
        _ACTWait(1);
    }
}

inline void subEnemyBrain_FindGirl(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int i;

    for (i = 0; i < (60 - systemStatus[0] * 10) / systemStatus[1] / 2; i++) {
        *(int *)((char *)sub + 0x33C) = 0;
        *(int *)((char *)sub + 0x100) = 0;
        *(int *)((char *)sub + 0x104) = 0;
        *(int *)((char *)sub + 0x108) = 0;
        ACTSendMailCorrect((void *)self, 206);
        if (sub->actMode == 70) {
            break;
        }
        _ACTWait(1);
    }
    for (i = 0; i < (60 - systemStatus[0] * 10) / systemStatus[1] * 250 / 60; i++) {
        _DoAwait(self);
        _ACTWait(1);
    }
    eBrainSendMes(self, 1);
    _ACTWait(0);
}

/* The boy is down or in one of the actMode 20..22 states: no dodge then.  A
   static inline of this file (expanded in enemy_dodge and subEnemyBrain_ToBoy). */
static inline unsigned char IsBoyStatus_NotDanger(void)
{
    unsigned int st = (unsigned int)GOBJ_ACT(boyGObj)->actMode;
    if (st < 23) {
        if (st >= 20) {
            return 1;
        }
    }
    if (GOBJ_WORK(boyGObj)->downTimer > 0) {
        return 1;
    }
    return 0;
}

static void enemy_dodge(GObj *self)
{
    float a[4];
    float b[4];
    float c[4];
    GObj *boy = boyGObj;
    Act *sub;
    int ang;

    if (boy == 0) {
        return;
    }
    if (_DistGV(test_CURRENTROOT(boy), test_CURRENTROOT(self)) < 200.0f) {
        GetRootPosition(a, self);
        GetRootPosition(b, boy);
        sceVu0SubVector(c, b, a);
        sceVu0Normalize(c, c);
        ang = _RotyGV(c, test_CURRENTORIENT(boy));
        ang = (ang < 0) ? -ang : ang;
        if (ang < 114) {
            return;
        }
        ang = _RotyGV(c, test_CURRENTORIENT(self));
        ang = (ang < 0) ? -ang : ang;
        if ((float)ang < 45.0f) {
            if (IsBoyStatus_NotDanger() != 0) {
                return;
            }
            sub = GOBJ_ACT(self);
            if (sub->enemy->sizeClass != 0 &&
                (((int)(*(long long *)((char *)sub->enemy + 0x208) >> 1)) & 1) == 0) {
                enemyDodgeSendMail(self);
            } else {
                ACTSendMailCorrect(self, 249);
            }
        }
    }
}

inline void subEnemyBrain_ToGenerator(GObj *self)
{
    /* The actor handle is kept in a `volatile` local: this brain thread is
       resumed by the actor scheduler at every _ACTWait, so the frame slot,
       not a register, is the live copy of the handle. */
    GObj *volatile gobj = self;
    Act *sub = GOBJ_ACT(gobj);
    GObj *target = sub->brainTarget;

    GOBJ_WORK(gobj)->genTarget = target;
    if ((unsigned char)_ApproachTarget(gobj, target, (char *)sub + 0x100, 0, 50.0f,
                                       *(unsigned char *)((char *)GOBJ_ACT(gobj)->enemy + 0x21C)) ==
        0) {
        debug_StdPrintfDummy("to generator way error!");
        sub->stick.mag = 0;
        *(int *)((char *)sub + 0x100) = 0;
        *(int *)((char *)sub + 0x104) = 0;
        *(int *)((char *)sub + 0x108) = 0;
        _ACTWait(30);
        ACTSendMailCorrect((void *)gobj, 232);
        _ACTWait(0);
    }
    while (1) {
        ACTSendMailCorrect((void *)gobj, 315);
        _ACTWait(1);
    }
}

/* a `static inline` defined outside its callers, expanded four times in
   Battle_isCurrentStatus and once in subEnemyBrain_ToBoy; grow is a float
   flag (1.0f or 0.0f, like vflag below): 0.0f leaves out the 1.2 */
static inline float battleRangeScale(GObj *self, float v, float grow) /* derived name */
{
    EnemyBattleWork *work = GOBJ_ACT(self)->enemy;

    switch (work->sizeClass) {
    case 0:
    case 1:
        v = work->bodySize * v;
        if ((((int)(*(long long *)((char *)work + 0x208) >> 1)) & 1) && grow != 0.0f) {
            v = v * 1.2;
        }
        break;
    case 2:
        v = work->bodySize * 0.7f * v;
        break;
    }
    return v;
}

static int Battle_isCurrentStatus(GObj *self, GObj *tgt, float *pos)
{
    float ori[4];
    float dir[4];
    int ret;
    float xz;
    float dy;
    float vflag;
    float a;
    float b;
    int ang;
    int far;

    ret = 0;
    xz = _DistxzGV(pos, test_CURRENTROOT(tgt));
    dy = ((pos[1] - test_CURRENTROOT(tgt)[1]) < 0.0f) ? -(pos[1] - test_CURRENTROOT(tgt)[1])
                                                      : (pos[1] - test_CURRENTROOT(tgt)[1]);
    vflag = 0.0f;
    if (battleRangeScale(self, 270.0f, 1.0f) < xz || battleRangeScale(self, 200.0f, 1.0f) < dy) {
        vflag = 1.0f;
    }
    if (xz < battleRangeScale(self, 120.0f, 0.0f) && dy < battleRangeScale(self, 100.0f, 1.0f)) {
        vflag = -1.0f;
    }
    ori[0] = test_CURRENTORIENT(tgt)[0];
    ori[1] = test_CURRENTORIENT(tgt)[1];
    ori[2] = test_CURRENTORIENT(tgt)[2];
    _OrientXZGV(dir, test_CURRENTROOT(self), test_CURRENTROOT(tgt));
    ang = _AbsRotyGV(ori, dir);
    a = (ang < 75) ? 1.0f : 0.0f;
    far = (101 <= ang);
    b = (a != 0.0f && GOBJ_ACT(tgt)->actMode == 15) ? 1.0f : 0.0f;
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

inline void EnemyUtil_TurnToBoy(GObj *self, GObj *tgt, int smooze)
{
    float dir[4];
    Act *sub = GOBJ_ACT(self);

    _OrientXZGV(dir, test_CURRENTROOT(tgt), test_CURRENTROOT(self));
    sub->dir[0] = dir[0];
    sub->dir[1] = dir[1];
    sub->dir[2] = dir[2];
    enemyCheckTurnAngle(self);
    if (smooze == 0) {
        SetMotionDirection(self, dir);
    } else {
        SetMotionDirectionSmooze(self, dir, (float)smooze);
    }
}

inline int EnemyUtil_isOtherStatus(GObj *self, int mode)
{
    GObj *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (g != self) {
            Act *sub = GOBJ_ACT(g);
            if (sub->actMode == 15) {
                return (int)g;
            }
            if (((int)(sub->flags18.ll >> 62)) & 1) {
                return (int)g;
            }
        }
    }
    return 0;
}

void subEnemyBrain_ToBoy(GObj *volatile self)
{
    float v[4];
    float w[4];
    Act *sub = GOBJ_ACT(self);
    GObj *boy = boyGObj;
    int cnt = 0;
    int i, j;
    int mode;
    int r;
    unsigned char ret;
    int dbg = 0; /* local debug switch, see case 1 of the status switch */

    void ChangeBrain_ToAttack(void)
    {
        if (isLiftBoyEnable() != 0) {
            if (GOBJ_ACT(self)->enemy->sizeClass == 2) {
                BrainModeTarget *tgt = &brainTarget;

                /* the default target, then the boy; the same shape sits in
                   the other four arms (here and in ChangeBrain_ToKidnap) */
                brainTarget = brainTargetNone;
                brainTarget.gobj = boyGObj;
                if ((int)(random_unit() * 10.0f) % 100 < GOBJ_ACT(self)->enemy->attackChance2) {
                    _BrainMode_SetDirect(self, 12, tgt);
                } else {
                    _BrainMode_SetDirect(self, 9, tgt);
                }
            } else {
                /* the default target first, see the kind == 2 arm above */
                brainTarget = brainTargetNone;
                brainTarget.gobj = boyGObj;
                _BrainMode_SetDirect(self, 9, &brainTarget);
            }
        }
    }

    while (1) {
        mode = 0;
        r = (int)(random_unit() * 10.0f) % 100;
        debug_StdPrintfDummy("**toboy function start :: count=[%d]\n", cnt++);
        ret = _ApproachTarget(self, boy, (char *)sub + 0x100, 0,
                              battleRangeScale(self, 220.0f, 1.0f), 0);
        v[0] = test_CURRENTROOT((void *)self)[0];
        v[1] = test_CURRENTROOT((void *)self)[1];
        v[2] = test_CURRENTROOT((void *)self)[2];
        if (ret != 0) {
            debug_StdPrintfDummy("await start\n");
            for (i = 0; i < (60 - systemStatus[0] * 10) / systemStatus[1] * 75 / 60; i++) {
                mode = 0;
                switch (Battle_isCurrentStatus(self, boy, v)) {
                case 0:
                    break;
                case 1:
                    mode = 4;
                    /* a local debug switch, off: mark the position the status
                       test was given; the August TRFILE (4037-4041) and the
                       PAL listing (4282-4293) have code-less lines here */
                    if (dbg) {
                        debug_NMarker(v, 255, 0, 0, 100.0f);
                    }
                    if (r < GOBJ_ACT(self)->enemy->attackChance) {
                        mode = 3;
                    }
                    if (((int)(*(long long *)((char *)GOBJ_ACT(self)->enemy + 0x208) >> 1)) & 1) {
                        mode = 3;
                    }
                    break;
                case 2:
                    mode = 2;
                    break;
                case 3:
                    mode = 3;
                    if (GOBJ_ACT(self)->enemy->liftKind == 3) {
                        mode = 4;
                    }
                    debug_StdPrintfDummy("!!! wwarning !!!\n");
                    break;
                case 4:
                    mode = 5;
                    break;
                default:
                    debug_StdPrintfDummy("return value error :: [Battle_isCurrentStatus]\n");
                    break;
                }
                if (mode != 0) {
                    goto result;
                }
                sub->stick.mag = 0.0f;
                sub->dir[0] = 0.0f;
                sub->dir[1] = 0.0f;
                sub->dir[2] = 0.0f;
                _DoAwait(self);
                _ACTWait(1);
            }
            debug_StdPrintfDummy("await end\n");
            if ((((int)(*(long long *)((char *)GOBJ_ACT(self)->enemy + 0x208) >> 1)) & 1) == 0) {
                mode = 4;
            }
        } else {
            mode = 1;
        }
    result:
        debug_StdPrintfDummy("toboy ra is [%d]\n", mode);
        switch (mode - 1) {
        case 0:
            ACTSendMailCorrect(self, 232);
            break;
        case 1:
            break;
        case 2:
            if (IsBoyStatus_NotDanger() != 0) {
                if ((char *)girlGObj != 0) {
                    if (GOBJ_ACT(girlGObj)->actMode != 106) {
                        break;
                    }
                }
            }
            ACTSendMailCorrect(self, 249);
            break;
        case 3:
            if (isNearestEnemyToBoy(self, boyGObj, w) && EnemyUtil_isOtherStatus(self, 0) == 0) {
                ChangeBrain_ToAttack();
            }
            break;
        case 4:
            if (EnemyUtil_isOtherStatus(self, 0) == 0) {
                ChangeBrain_ToAttack();
            }
        }
        sub->stick.mag = 0.0f;
        sub->dir[0] = 0.0f;
        sub->dir[1] = 0.0f;
        sub->dir[2] = 0.0f;
        for (j = 0; j < 45; j++) {
            if (mode == 5) {
                if (EnemyUtil_isOtherStatus(self, 0) == 0) {
                    ChangeBrain_ToAttack();
                }
            }
            _DoAwait(self);
            _ACTWait(1);
        }
    }
}

inline void subEnemyBrain_BodyGuard(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    GObj *tgt = sub->brainTarget;
    float *pos = (float *)((char *)sub + 0x100);

    while (1) {
        if (_DistGV(test_CURRENTROOT(self), test_CURRENTROOT(tgt)) < 200.0f) {
            _ACTWait(1);
        } else {
            if ((unsigned char)_ApproachTarget(self, tgt, pos, 0, 100.0f, 0) == 0) {
                sub->stick.mag = 0;
                *(int *)((char *)sub + 0x100) = 0;
                *(int *)((char *)sub + 0x104) = 0;
                *(int *)((char *)sub + 0x108) = 0;
                _ACTWait(30);
            }
            sub->stick.mag = 0;
            *(int *)((char *)sub + 0x100) = 0;
            *(int *)((char *)sub + 0x104) = 0;
            *(int *)((char *)sub + 0x108) = 0;
            _ACTWait(60);
        }
    }
}

void subEnemyBrain_ToGirl(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    float p0[4];
    float p1[4];
    int i;
    int found;

    void ChangeBrain_ToKidnap(void)
    {
        switch (GOBJ_ACT(self)->enemy->sizeClass) {
        case 0:
            /* the default target first, see ChangeBrain_ToAttack */
            brainTarget = brainTargetNone;
            brainTarget.gobj = girlGObj;
            _BrainMode_SetDirect(self, 8, &brainTarget);
            break;
        case 2:
            brainTarget = brainTargetNone;
            brainTarget.gobj = girlGObj;
            _BrainMode_SetDirect(self, 11, &brainTarget);
            break;
        default:
            brainTarget = brainTargetNone;
            brainTarget.gobj = girlGObj;
            _BrainMode_SetDirect(self, 10, &brainTarget);
            break;
        }
    }

    GObj *girl = girlGObj;

    sub->stick.mag = 0.0f;
    sub->dir[0] = 0.0f;
    sub->dir[1] = 0.0f;
    sub->dir[2] = 0.0f;
    for (i = 0; i < (60 - systemStatus[0] * 10) / systemStatus[1]; i++) {
        _DoAwaitGirl(self);
        _ACTWait(1);
    }
    found = (unsigned char)_ApproachTarget(self, girl, (char *)sub + 0x100, (void *)enemy_dodge,
                                           130.0f, 0);
    GetRootProjectionPosOfGObj(p0, girl);
    GetRootProjectionPosOfGObj(p1, self);
    if (50.0f < (p0[1] - p1[1] < 0.0f ? -(p0[1] - p1[1]) : p0[1] - p1[1])) {
        found = 0;
    }
    if (found == 0) {
        sub->stick.mag = 0.0f;
        sub->dir[0] = 0.0f;
        sub->dir[1] = 0.0f;
        sub->dir[2] = 0.0f;
        _ACTWait(30);
        eBrainSendMes((void *)self, 5);
        ACTSendMailCorrect(self, 232);
        _ACTWait(0);
    }
    while (1) {
        debug_StdPrintfDummy("change to kidnap");
        ChangeBrain_ToKidnap();
        _ACTWait(1);
    }
}

static int _ApproachTarget_Boss(GObj *self, void *tgt, void *pos, void *fn, float range,
                                unsigned char flag)
{
    float p0[4];
    float p1[4];
    Act *sub = GOBJ_ACT(self);

    for (;;) {
        GetRootProjectionPosOfGObj(p0, tgt);
        GetRootProjectionPosOfGObj(p1, self);
        if (fn != 0) {
            ((void (*)(GObj *, void *, float))fn)(
                self, tgt, _DistGV(test_CURRENTROOT(self), test_CURRENTROOT(tgt)));
        }
        sub->stick.mag = 1.0f;
        _OrientXZGV((float *)pos, p0, p1);
        if (_DistxzSqGV(p0, p1) < 160000.0f && -50.0f < -(p0[1] - p1[1]) &&
            p1[1] - p0[1] < 500.0f && enemyCheckTurnAngle(self) == 0 && sub->actMode != 10) {
            return 1;
        }
        _ACTWait(1);
    }
}

/* the USA build's flyMailCore and FlyMail in one function: the frame test first */
void FlyMail(void *self)
{
    int flyLow = 0;
    int flyHigh = 0;
    GObj *gen;

    if (GOBJ_ACT(self)->frame < 12) {
        return;
    }
    switch (CanThisEnemyFly(self)) {
    case 1:
        flyLow = 1;
        break;
    case 2:
        flyLow = 1;
        flyHigh = 1;
        break;
    }
    if (isEnemyActive(self) == 0) {
        return;
    }
    if (IsEnemyBrainToGenerator(self, &gen)) {
        if (flyHigh == 0 && debug_enemy_fly_with_girl == 0) {
            return;
        }
        ACTSendMailCorrect(self, 30);
    } else {
        if (flyLow == 0) {
            return;
        }
        ACTSendMailCorrect(self, 29);
    }
}

static int _ApproachTarget_Way(GObj *self, void *tgt, void *pos, void *fn, float range,
                               unsigned char flag);

static int _ApproachTarget_Way(GObj *self, void *tgt, void *pos, void *fn, float range,
                               unsigned char flag)
{
    float p0[4];
    float p1[4];
    Act *sub = GOBJ_ACT(self);
    int i;

    GetRootProjectionPosOfGObj(p0, tgt);
    GetRootProjectionPosOfGObj(p1, self);
    for (i = 0; i < 20; i++) {
        if (IsSelectID_EnemyCtrl(*(int *)((char *)self + 8)) != 0) {
            break;
        }
        _ACTWait(1);
    }
    if (ACTWayMove_BeginDetail(self, p1, p0, tgt, 0) == 0) {
        FlyMail(self);
        return 0;
    }
    while (1) {
        GetRootProjectionPosOfGObj(p0, tgt);
        GetRootProjectionPosOfGObj(p1, self);
        if (!(_DistSqGV(p1, p0) < 1440000.0f) ||
            240.0f < ((p1[1] - p0[1] < 0.0f) ? -(p1[1] - p0[1]) : (p1[1] - p0[1]))) {
            FlyMail(self);
        }
        if (fn != 0) {
            ((void (*)(GObj *, void *, float))fn)(
                self, tgt, _DistGV(test_CURRENTROOT(self), test_CURRENTROOT(tgt)));
        }
        if (sub->actMode == 6) {
            _ACTWait(1);
            continue;
        }
        if (ACTWayMove_NextDetail(self, pos, p0) == 0) {
            return 0;
        }
        *(float *)((char *)pos + 0) = sub->wayNodeX;
        *(float *)((char *)pos + 4) = sub->wayNodeY;
        *(float *)((char *)pos + 8) = sub->wayNodeZ;
        if (((int)(((ActStatusWord *)((char *)sub + 0x3E0))->q >> 16)) & 1) {
            FlyMail(self);
        }
        if ((((int)(((ActStatusWord *)((char *)sub + 0x3E0))->q >> 16)) & 1) == 0 &&
            sub->wayGoalDist < range && sub->wayGoalHeight < 100.0f &&
            ((sub->wayGoalHeight < 0.0f) ? -sub->wayGoalHeight : sub->wayGoalHeight) < 200.0f) {
            return 1;
        }
        if (sub->wayGoalDist < 200.0f) {
            sub->stick.mag = 0.5f;
        } else if (ACTWay_IsMustWalkFromWay(self) != 0) {
            sub->stick.mag = 0.5f;
        } else {
            sub->stick.mag = 1.0f;
        }
        if (flag != 0) {
            SetMotionDirection(self, (float *)((char *)sub + 0x100));
            flag = 0;
        }
        _ACTWait(1);
    }
    /* disabled in retail: the motion-request timer and mail reports */
    if (0) {
        debug_StdPrintfDummy("_ACTMotReqTimer wait\n");
        debug_StdPrintfDummy("_ACTMotReqTimer error loop\n");
        debug_StdPrintfDummy("\tmail[%d] can not accept\n");
    }
}

inline int _ApproachTarget(GObj *self, void *tgt, void *pos, void *fn, float range,
                           unsigned char flag)
{
    if (GOBJ_ACT(self)->enemy->liftKind != 3) {
        return _ApproachTarget_Way(self, tgt, pos, fn, range, flag);
    } else {
        return _ApproachTarget_Boss(self, tgt, pos, fn, range, flag);
    }
}

inline int isEnemyKidnapEnable(GObj *self)
{
    if (GOBJ_ACT(self)->enemy->liftKind == 0) {
        return 0;
    }
    return actEnemyFlagCheckActive(self);
}

inline int GetEnemyType(float x, float y, float z)
{
    float size[5] = {0.6f, 1.1f, 2.2f, 9.9f, -1.0f};
    int i;

    for (i = 0; 0.0f < size[i]; i++) {
        if (x < size[i]) {
            return i;
        }
    }
    return 3;
}

inline int GetEnemyTypeFromGObj(GObj *obj)
{
    return GOBJ_ACT(obj)->enemy->liftKind;
}

void actEnemyStart(GObj *self)
{
    char *act;
    int alive;
    float life;

    debug_StdPrintfDummy("actEnemyStart:%p\n", self);
    act = (char *)actInitialize(self);
    actInitialize_ext_charcter(self);
    actInitialize_only_charcter((char *)self);
    actInitialize_geo(self);
    ACTGame_LwsEffectInit(self);
    ACTParaStatus_Init(self);
    _ACTCharStatus_Init((int **)self);
    GOBJ_WORK(self)->bga = InitMultiBgaManager(1);
    {
        EnemyStartRec p[4] = {
            {0, 30, 18, 90, 0, _ACTGame_GetParamF(15), 321.0f, 1},
            {1, 0, 18, 50, 0, _ACTGame_GetParamF(16), 321.0f, 0},
            {2, 29, 22, 25, 50, _ACTGame_GetParamF(17), 321.0f, 0},
            {2, 28, 22, 0, 100, 3.40282347e+38f /* FLT_MAX */, 322.0f, 1},
        };
        unsigned long long bit;
        float size = *(float *)((int)GOBJ_SUB(self)->nodes + 0x20);
        int kind = GetEnemyType(size, 0.0f, 0.0f); /* y and z are not read */

        GOBJ_ACT(self)->enemy->bodySize = size;
        GOBJ_ACT(self)->enemy->liftKind = kind;
        GOBJ_ACT(self)->enemy->sizeClass = p[kind].sizeClass;
        GOBJ_ACT(self)->enemy->paraStatus = p[kind].paraStatus;
        GOBJ_ACT(self)->enemy->clingNode = p[kind].clingNode;
        GOBJ_ACT(self)->enemy->attackChance = p[kind].attackChance;
        GOBJ_ACT(self)->enemy->attackChance2 = p[kind].attackChance2;
        *(float *)(act + 0x1D4) = p[kind].maxLife;
        GOBJ_ACT(self)->enemy->bodyslamMail = (int)p[kind].bodyslamMail;
        GOBJ_ACT(self)->enemy->bossLife = 3;
        bit = p[kind].noGuard;
        ((ActStatusWord *)(act + 0x18))->q =
            (((ActStatusWord *)(act + 0x18))->q & ~(1ULL << 45)) | ((bit & 1) << 45);
    }
    if (GOBJ_ACT(self)->enemy->liftKind == 3) {
        *(float *)(((EnemySubSlot *)((char *)self + 0x15C))->p + 0x44C) = 0.05f;
        *(float *)(((EnemySubSlot *)((char *)self + 0x15C))->p + 0x450) = 0.05f;
        *(float *)(((EnemySubSlot *)((char *)self + 0x15C))->p + 0x454) = 0.05f;
        *(float *)(((EnemySubSlot *)((char *)self + 0x15C))->p + 0x458) = 0.05f;
    }
    GOBJ_ACT(self)->enemy->battleType = debug_enemy_battle_type;
    setBattleStatus(self);
    alive = 0;
    if (actEnemyFlagCheckDead(self) != 0) {
        alive = 1;
    }
    if (alive != 0) {
        *(long long *)(act + 0x18) = *(long long *)(act + 0x18) & ~(1LL << 32);
    }
    _ACTWait(1);
    *(IntrMail **)(act + 0xB0) = &actIntrList[65];
    if (debug_brain_flag != 0) {
        actCreateSubThread((void *)subEnemyBrainMain, 20);
    }
    actCreateSubThread((void *)subEnemyControl, 21);
    actCreateSubThread((void *)subEnemyCollision, 21);
    actCreateSubThread((void *)subCommonIdle, 21);
    *(IntrMail **)(act + 0xB4) = &actIntrList[70];
    *(ActKind *)(act + 0x44) = ACT_KIND_ENEMY;
    life = GetEnemyDefLife(self);
    *(float *)(act + 0x1D0) = *(float *)(act + 0x1D4) = life;
    if (life < 10.0f) {
        *(float *)(act + 0x1D0) = *(float *)(act + 0x1D4) = 10.0f;
    }
    *(int *)(act + 0x340) = 0;
    ACTSendMailCorrect(self, 177);
    if (alive != 0) {
        actEnemyHyde(self);
    }
    _ACTWait(0);
}

void subEnemyBrain_Irregular(GObj *volatile self)
{
    GOBJ_ACT(self)->flags150.ll &= ~(1ULL << 32);
    eBrainSendMes(self, 4);
    if (isEnemyCarriedByGirl(self)) {
        afterCommonCarry(self);
    }
    while (1) {
        _ACTWait(30);
        _BrainMode_SetDirect(self, 0, 0);
    }
}

void subEnemyBrain_Attack(GObj *volatile self)
{
    int i;

    for (i = 0; i < (60 - systemStatus[0] * 10) / systemStatus[1] / 6; i++) {
        enemyDodgeSendMail(self);
        _DoAwait(self);
        if (_MustChase(self) != 0) {
            break;
        }
        _ACTWait(1);
    }
    for (i = 0; i < (60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60; i++) {
        _DoAwait(self);
        if ((60 - systemStatus[0] * 10) / systemStatus[1] * 80 / 60 < i) {
            if (_MustChase(self) != 0) {
                break;
            }
        }
        _ACTWait(1);
    }
    _BrainMode_SetDirect(self, 0, 0);
    _ACTWait(0);

    /* the bit-51 store to the actor word is a union access, the four 0.05f
 * stores go through a union view of the gobj+0x15C slot, and each life pair
 * is one chained assignment */
}

void subEnemyBrain_Cling(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int tgt = GOBJ_ACT(self)->enemy->target;
    float v[4];

    GOBJ_ACT(self)->enemy->clingReq = tgt;
    _OrientXZGV(v, test_CURRENTROOT((GObj *)tgt), test_CURRENTROOT(self));
    sub->dir[0] = v[0];
    sub->dir[1] = v[1];
    sub->dir[2] = v[2];
    SetMotionDirection((void *)self, v);
    ACTSendMailCorrect((void *)self, 175);
    _ACTWait(1);
    _ACTWait(1);
    while (1) {
        if (sub->actMode == 4 || sub->actMode == 16) {
            if (_DistSqGV(test_CURRENTROOT((GObj *)tgt), test_CURRENTROOT(self)) < 3600.0f) {
                ACTSendMailCorrect((void *)self, 186);
            }
        } else {
            _ACTWait(30);
            _BrainMode_SetDirect(self, 0, 0);
        }
        _ACTWait(1);
    }
}

inline void subEnemyBrain_Shoulder(GObj *volatile self)
{
    float *dir = (float *)((char *)GOBJ_ACT(self) + 0x100);
    float *girl = test_CURRENTROOT((girlGObj));
    float *me = test_CURRENTROOT(self);
    _OrientXZGV(dir, girl, me);
    SetMotionDirection((void *)self, dir);
    ACTSendMailCorrect((void *)self, 311);
    while (1) {
        _ACTWait(120);
        _BrainMode_SetDirect(self, 0, 0);
    }
}

inline void subEnemyBrain_Pickup(GObj *volatile self)
{
    ACTSendMailCorrect((void *)self, 316);
    while (1) {
        _ACTWait(120);
        _BrainMode_SetDirect(self, 0, 0);
    }
}

inline void subEnemyBrain_Bodyslam(GObj *volatile self)
{
    if (GOBJ_ACT(self)->enemy->liftKind == 3) {
        ACTSendMailCorrect((void *)self, 325);
    } else {
        ACTSendMailCorrect((void *)self, 323);
    }
    while (1) {
        _ACTWait(120);
        _BrainMode_SetDirect(self, 0, 0);
    }
}

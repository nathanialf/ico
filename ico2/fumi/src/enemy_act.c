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

int entesty;

/* The brain-mode table, one 28-byte record per mode: its name, its priority
   against the running mode, the brain function and four parameters
   (subEnemyBrainMain and BrainMode_Requset read them).  The names are this
   TU's own string literals ("START" .. "IRREGULAR"), still placeholders here
   because the .sdata run that holds nine of them is not carved yet. */
typedef struct {
    char *name;
    int pri;
    void (*brain)(int);
    int f0C;
    int f10;
    int f14;
    int f18;
} EnemyBrainMode;

void subEnemyBrain_Await(volatile int a0);
void subEnemyBrain_ToBoy(volatile int a0);
void subEnemyBrain_ToGirl(volatile int a0);
void subEnemyBrain_ToGenerator(int self);
void subEnemyBrain_FindGirl(volatile int a0);
void subEnemyBrain_BodyGuard(volatile int a0);
void subEnemyBrain_Cling(volatile int a0);
void subEnemyBrain_Attack(volatile int a0);
void subEnemyBrain_Shoulder(volatile int a0);
void subEnemyBrain_Pickup(volatile int a0);
void subEnemyBrain_Bodyslam(volatile int a0);
void subEnemyBrain_Irregular(volatile int a0);

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
};

/* The brain-mode default target, read when a mode is set with no target:
   _BrainMode_SetDirect's else arm and the two nested brain-change children
   read it.  A one-element const array: it is not folded to its value the way
   a const scalar is (decl_constant_value skips arrays), its reads are
   unchanging so cse carries them over the mode store, and the ROM's 8-byte
   slot after the table's names (4 bytes of pad) is gcc's alignment for a
   4-byte array. */
static const int brainTargetNone[1] = {0}; /* derived name */

/* kept local: agrees with mv_defs.h, which this TU does not include */
extern void __assert(const char *file, int line, const char *expr);

#define BOSS_START_WORK(self) ((int)GOBJ_ACT(self)->f_680)

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

typedef struct {
    char pad00[0x100];
    int f100;
    char pad104[0x182 - 0x104];
    short f182;
    char pad184[2];
    short f186;
    char pad188[0x18C - 0x188];
    unsigned int flags18C;
    char pad190[4];
} EnemyParaRow;

extern EnemyParaRow motionKind[];
/* kept local: this TU's uses of _GetMotionDirection do not fit the prototype in
   motionManager2.h */
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern void _GetMotionDirection(int a0, int a1);
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern int CheckFloorAttribute(char *self, int attr);
extern void _ACTCommonMailTest(int self, int a1, int a2, int a3);

/* The DEBUG build holds the enemy's stick poll while the debug flag word's
   hold bit is set, a frame at a time, the way boyact.c's subBoyControl repeats
   its stick loop with _ACTWait; retail builds it as 0. Name and bit ours. */
#ifdef DEBUG
#define ENEMY_DEBUG_HOLD (debug_font_flag & 0x200)
#else
#define ENEMY_DEBUG_HOLD 0
#endif

extern void ACTGame_CommonLoop(void *self);
/* kept local: enemy_act.c does not carry multiBgaManager.h, and this TU reads
   only the display list pointer it hands the manager. */
/* The pad record layout_texture.c reconstructs as LtPad; this TU reads only its
   button word at +0, and the incomplete array type is what keeps ROM's %hi/%lo
   pair where a small scalar would go gp-relative under -G 8. */
extern void ACTParaStatus_Exec(void *self);
extern float GetEnemyDefParaIndex(void *self);
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern void SetMotionDirection(void *a0, float *a1);
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern int GetMotionFrameFlag2(char *self);
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern void SetMotionDirectionWithLimit(void *self, float *dir, float lim0, float lim1);
/* kept local: void is void * here, void in attackhit.h */
extern void EnemyAttackCenter(void *self);
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern void InitMotionGeoInfo(char *self, float x, float y, float z, float rx, float ry, float rz);
extern char D_002A8570[];
/* kept local: motionManager2.h lists the parameters as (self, obj, x, y, z, mode, node, w, quat);
   the callers pass them in this order */
extern void SetMotionNodeFixModeParameter(char *self, char *obj, int mode, int node, void *quat,
                                          float x, float y, float z, float w);
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern void GetRootProjectionPosOfGObj(int a0, int a1);
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern int GetMotionFrameFlag1(char *self);

/* The point the lifting enemy turns to.  RECONSTRUCTION: the ROM holds three
   vectors here (0x30 bytes, the first two equal) and only the first is ever
   addressed, so the bytes cannot say whether the developer wrote one table or
   three objects; the 8 bytes of fill after brainModeTable prove the 16-byte
   alignment. */
static sceVu0FVECTOR bodyliftTarget[3] = {
    {-311.0f, -89.0f, -147.0f, 0.0f},
    {-311.0f, -89.0f, -147.0f, 0.0f},
    {-770.0f, -1445.0f, -749.0f, 0.0f},
};

extern char objLayout[];
extern char actModeTbl[];
/* FLT_MAX word in .sdata; the incomplete array type is what keeps the ROM's
   %hi/%lo pair instead of a gp-relative load. */
extern void SetEnemyStonizedVisual(void *self);
extern void BossEnemyFunc(void *self);

/* RECONSTRUCTION: the listing puts the whole row-3197 test on its own row with
   no helper rows, and the bytes (lwu, dsll32/dsra32, andi) are a 64-bit
   shift-and-mask of a 32-bit word, the TU's flag-test shape: a function-like
   macro.  The name is ours. */
#define EA_CHKBIT(f, n) (((int)((long long)(f) >> (n))) & 1)

/* GetFlyPosition's points: the four the enemy measures against, the four it
   flies to (paired by index, 200 below), and the one it escapes to. */
static sceVu0FVECTOR flyCheckPos[4] = {
    {760.0f, 0.0f, 766.0f, 1.0f},
    {708.0f, 0.0f, -806.0f, 1.0f},
    {-1394.0f, 0.0f, -858.0f, 1.0f},
    {-1383.0f, 0.0f, 645.0f, 1.0f},
};

static sceVu0FVECTOR flyDestPos[4] = {
    {842.0f, -200.0f, 1278.0f, 1.0f},
    {734.0f, -200.0f, -1273.0f, 1.0f},
    {-1394.0f, -200.0f, -1291.0f, 1.0f},
    {-1383.0f, -200.0f, 1291.0f, 1.0f},
};

static sceVu0FVECTOR flyEscapePos = {1712.0f, -600.0f, 0.0f, 1.0f};

/* The brain-mode target the ChangeBrain_ToAttack and ChangeBrain_ToKidnap
   children hand to _BrainMode_SetDirect: one word shared by the nested
   functions of two parents, so file scope (the TU's whole .sbss). */
static char *brainTarget;

/* "change to kidnap": the string follows subEnemyBrain_ToBoy's two jump tables
   in the ROM's .rodata (0x5536C8), so it stays in the blob while the TU's own
   .rodata run ends at the tables. */

/* kept local: enemy_act.c carries none of these owners' headers, and the ROM
   proves gif_StartPacketPri takes the packet priority its GifPacket.h
   prototype does not name. */
/* kept local: agrees with flyManager.h, which this TU does not include */
extern int GetFlyLimitClearance(void *pos);
/* kept local: agrees with motionManager2.h, which this TU does not include (SetMotionNodeFixModeParameter differs) */
extern int CheckFloorAttribute(char *self, int attr);
/* the three actor sub-threads this function starts; their bodies are below */
extern char D_002A84F8[];

/* One start record per motion phase; the four of them are the actor's whole
   start parameter block. */
typedef struct {
    int mode;
    int f04;
    int f08;
    int f0C;
    int f10;
    float f14;
    float f18;
    unsigned int f1C;
} EnemyStartRec;

/* The gobj's sub-object slot at +0x15C, an int handle the engine also reads
   as the sub record's address (see GOBJ_SUB in typedef.h). Reconstruction:
   ROM re-reads the slot before each of actEnemyStart's four float stores
   through it while the int chase through gobj+0x164 survives them, which
   is what a union view of the slot gives (alias set 0 on the slot, float
   on the stores); the union's name and members are ours. */
typedef union {
    int handle;
    char *p;
} EnemySubSlot;

/* The actor's character kind at act+0x48, the index act.c's after_func_exec
   and BeforeFunc read into the status table's six-entry rows; actInitialize
   sets it to -1, actGirlStart to 1 and actEnemyStart to 2. Reconstruction:
   an enumerated type, as the ROM proves here (only a store of a type other
   than int lets the gFlagGameClear load below issue ahead of it); the names are
   ours, the values the ROM's. */
typedef enum { ACT_KIND_NONE = -1, ACT_KIND_GIRL = 1, ACT_KIND_ENEMY = 2 } ActKind;

#define ENEMY_START_WORK(self) ((int)GOBJ_ACT(self)->f_680)

typedef struct {
    char pad00[0x20];
    long long flags;
} EnemyBrainWork;

inline int IsEnemyBrainToGenerator(char *a0, int *out)
{
    Act *b = GOBJ_ACT(a0);
    if (b->f_680->mode != 5)
        return 0;
    *out = (int)((ActWork *)b->f_688)->f_460;
    if (*out == 0) {
        debug_assert("src/enemy_act.c", 0x341);
        __assert("src/enemy_act.c", 0x341, "*generator_gop!=NULL");
    }
    return 1;
}

inline int IsEnemyBrainToBoy(char *self)
{
    Act *sub;
    EnemyBattleWork *sub2;
    if ((char *)girlGObj != 0) {
        Act *sub_d = GOBJ_ACT(girlGObj);
        if (sub_d->unk34 != 0x6F)
            return 0;
    }
    sub = GOBJ_ACT(self);
    sub2 = sub->f_680;
    return sub2->mode == 3;
}

void setBattleStatus(char *self)
{
    switch (GOBJ_ACT(self)->f_680->battleType) {
    case 0:
        GOBJ_ACT(self)->f_680->flags.ll &= ~1LL;
        GOBJ_ACT(self)->f_680->flags.ll &= ~2LL;
        break;
    case 1:
        GOBJ_ACT(self)->f_680->flags.ll &= ~1LL;
        GOBJ_ACT(self)->f_680->flags.ll |= 2LL;
        break;
    case 2:
        GOBJ_ACT(self)->f_680->flags.ll |= 1LL;
        GOBJ_ACT(self)->f_680->flags.ll &= ~2LL;
        break;
    case 3:
        GOBJ_ACT(self)->f_680->flags.ll |= 1LL;
        GOBJ_ACT(self)->f_680->flags.ll |= 2LL;
        break;
    default:
        debug_assert("src/enemy_act.c", 0x36B);
        __assert("src/enemy_act.c", 0x36B, "0");
    }
}

inline void boss_effect_callback(int id)
{
    char *g;
    int i;
    char *p;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (GOBJ_ACT(g)->f_680->liftKind == 3) {
            for (i = 0; i < 5; i++) {
                p = (char *)(i * 0x20 + (int)GOBJ_ACT(g)->f_680 + 0x360);
                if (p[0x1D] != 0 && *(int *)(p + 0x10) == id) {
                    p[0x1C] = 0;
                    return;
                }
            }
        }
    }
}

/* static inline of the 2001 source, listing lines 973-977 -- inlined by both
   boss_effect_start and boss_effect_process (the rows attributed to 973 are
   each call's argument setup, which is why they differ between the two). */
static inline void bossEffectSetNodePos(char *self, float *dst, int idx)
{
    Sub15C *g = GOBJ_SUB(self);

    sceVu0CopyVector(dst, (float *)((char *)g->f_C + idx * 0x40 + 0x30));
    dst[3] = 1.0f;
}

void boss_effect_start(char *self, int id)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (*(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x37D) == 0) {
            float buf[4] = {0.0f, 0.0f, 0.0f, 1.0f};

            bossEffectSetNodePos(self, (float *)(i * 0x20 + BOSS_START_WORK(self) + 0x360), id);
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x370) =
                GatherEffect_Set(12, (char *)BOSS_START_WORK(self) + (i * 0x20 + 0x360), buf,
                                 (char *)BOSS_START_WORK(self) + (i * 0x20 + 0x360), 1.0f,
                                 (void *)boss_effect_callback);
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x374) = id;
            *(int *)(i * 0x20 + BOSS_START_WORK(self) + 0x378) =
                (0x3C - systemStatus[0] * 10) / systemStatus[1];
            *(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x37C) = 1;
            *(char *)(i * 0x20 + BOSS_START_WORK(self) + 0x37D) = 1;
            return;
        }
    }
    ReviveEnemyParticle(self, id);
}

void boss_effect_check_parts(char *a0, int a1)
{
    char *p = (char *)GOBJ_ACT(a0)->f_680 + 0x360;
    int i;
    for (i = 0; i < 5; i++, p += 0x20) {
        if (p[0x1D] != 0 && *(int *)(p + 0x14) == a1) {
            return;
        }
    }
    boss_effect_start(a0, a1);
}

void boss_effect_process(char *self)
{
    float tmp[4];
    int n;
    int i;

    n = GOBJ_SUB(self)->f_88;
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

void _DoAwait(char *self)
{
    EnemyParaRow *row;
    if ((void *)boyGObj != 0) {
        _ACTParaStatus_Set(self, 0x1C);
        row = &motionKind[GOBJ_SUB(self)->f_4A0];
        if ((row->flags18C >> 3) & 1) {
            EnemyUtil_TurnToBoy(self, (int)((void *)boyGObj), 5);
        }
    }
}

void _DoAwaitGirl(char *self)
{
    EnemyParaRow *row;
    if ((char *)girlGObj != 0) {
        _ACTParaStatus_Set(self, 0x1C);
        row = &motionKind[GOBJ_SUB(self)->f_4A0];
        if ((row->flags18C >> 3) & 1) {
            EnemyUtil_TurnToBoy(self, (int)((char *)girlGObj), 5);
        }
    }
}

int _MustChase(int a0)
{
    float v1[4];
    float v2[4];
    float angle;
    float diff;
    int rv;
    if ((void *)boyGObj == 0) {
        goto zero;
    }
    v1[0] = test_CURRENTROOT((int)((void *)boyGObj))[0];
    v1[1] = test_CURRENTROOT((int)((void *)boyGObj))[1];
    v1[2] = test_CURRENTROOT((int)((void *)boyGObj))[2];
    v2[0] = test_CURRENTROOT(a0)[0];
    v2[1] = test_CURRENTROOT(a0)[1];
    v2[2] = test_CURRENTROOT(a0)[2];
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

/* Static inline of the 2001 source, listing rows 908-915: the rows sit between
   setBattleStatus and boss_effect_callback, the body has no ROM slot of its own
   and subEnemyControl is the only place it is expanded, so this name is ours. */
static inline void enemyPollHitNodes(int self)
{
    int n = GOBJ_SUB(self)->f_88;
    int i;

    for (i = 0; i < n; i++) {
        GetEnemyHitNodeFlag((char *)self);
    }
}

void subEnemyControl(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    float pos[4];
    float dir[4];
    int runCnt = 0;
    int walkCnt = 0;
    int stopCnt = 0;

    iosPadConnect((char *)sub + 0x2D8, 0, 1, (int)((char *)sub + 0x1E8));
    while (1) {
        enemyPollHitNodes(a0);
        /* The stick poll loop, subBoyControl's shape, repeating only under the
           DEBUG hold (retail breaks after one pass). What the bytes pin: a loop
           at the flag test (an 8-aligned loop label at the test's shift, and
           the ((char *)CurrentTargetGObjSub) arm moved by loop.c into the hole after the hit-node
           loop, which loop.c does only for an arm whose jump leaves a loop)
           whose exit is unconditional when jump.c first sees it (a condition
           cse folds later does not thread the arm's jump out, measured). What
           they cannot pin: the debug build's condition. */
        for (;;) {
            if (((int)(sub->flags18.ll >> 48)) & 1) {
                if (a0 == (int)((char *)CurrentTargetGObj)) {
                    iosPadConnect((char *)sub + 0x2D8, 0, 0, (int)((char *)sub + 0x1E8));
                    iosPadRead((char *)sub + 0x2D8);
                    iosPadGetStick((char *)sub + 0x2D8, (char *)sub + 0x338, 0, 2, 2, 0);
                    _GetMotionDirection(dir, a0);
                    sub->f_340 = CorrectStickInfo(dir, (char *)sub + 0x338);
                    if (0.001f < sub->f_34C) {
                        ConvertStickToAbsCoord(pos, (char *)sub + 0x338);
                        sub->dir[0] = pos[0];
                        sub->dir[1] = pos[1];
                        sub->dir[2] = pos[2];
                    }
                } else if (a0 == (int)((char *)CurrentTargetGObjSub)) {
                    iosPadConnect((char *)sub + 0x2D8, 0, 1, (int)((char *)sub + 0x1E8));
                } else {
                    iosPadConnect((char *)sub + 0x2D8, 0, 1, (int)((char *)sub + 0x1E8));
                }
            }
            if (!ENEMY_DEBUG_HOLD) {
                break;
            }
            _ACTWait(1);
        }
        /* The listing gives the whole counter update one row (1580); gcse
           moves this increment up to both exits of the hit-node test. */
        stopCnt++;
        if (0.1f < sub->f_34C) {
            stopCnt = 0;
        }
        if (0.1f < sub->f_34C && (sub->f_34C < 0.99f || (sub->f_2E0 & 0x20))) {
            walkCnt++;
        } else {
            walkCnt = 0;
        }
        /* moving and not walking, with the walking predicate repeated whole
           inside the negation, as commonact.c's _ACTCommonMailTest writes it;
           the repeated conjunct is the ROM's dead second branch. */
        if (0.1f < sub->f_34C &&
            !(0.1f < sub->f_34C && (sub->f_34C < 0.99f || (sub->f_2E0 & 0x20)))) {
            runCnt++;
        } else {
            runCnt = 0;
        }
        pos[0] = sub->dir[0];
        pos[1] = sub->dir[1];
        pos[2] = sub->dir[2];
        _ACTCommonMailTest(a0, stopCnt, walkCnt, runCnt);
        switch (sub->unk34) {
        case 1:
            ACTSendMailCorrect((void *)a0, 0xC7);
            break;
        case 2:
            if (0.1f < sub->f_34C && (sub->f_34C < 0.99f || (sub->f_2E0 & 0x20)) &&
                !(walkCnt < 4)) {
                if (CheckFloorAttribute((char *)a0, 0x200)) {
                    ACTSendMailCorrect((void *)a0, 0xB6);
                } else {
                    ACTSendMailCorrect((void *)a0, 0xB5);
                }
            }
            break;
        case 3:
            ACTSendMailCorrect((void *)a0, 0xBA);
            break;
        /* RECONSTRUCTION: the ROM dispatches this switch through a 38-entry
           table (jtbl_005533A0), and ee-gcc builds a table only from five or
           more case labels, so a fifth label stands here.  Its value is not
           recoverable: every index from 4 to 37 points at the break label and
           listing rows 1603-1617 emit no instruction. */
        case 4:
            break;
        case 38:
            if (100 < sub->f_33C - 128) {
                ACTSendMailCorrect((void *)a0, 0x14B);
            } else if (sub->f_33C - 128 < -100) {
                ACTSendMailCorrect((void *)a0, 0x14A);
            } else {
                ACTSendMailCorrect((void *)a0, 0x150);
            }
            break;
        }
        _ACTWait(1);
    }
}

/* static inline of the 2001 source: the disc listing attributes rows
   1642-1663 -- which lie outside every function's own line span -- to the
   bodies of EnemyUtil_TurnToBoy, _ApproachTarget_Boss and subEnemyCollision
   alike, so this is a helper defined above them and inlined at each call.
   Name is descriptive, not recovered. */
static inline unsigned char enemyCheckTurnAngle(char *self)
{
    float mot[4];
    float cur[4];
    Act *s = GOBJ_ACT(self);
    int limit = (s->unk34 == 3) ? 0x5A : 0x69;
    int ang;
    int aang;

    cur[0] = s->dir[0];
    cur[1] = s->dir[1];
    cur[2] = s->dir[2];
    GetRootMotionOrient(mot, self);
    ang = _RotyGV(mot, cur);
    aang = ang < 0 ? -ang : ang;
    if (limit < aang) {
        s->f_5C0 = cur[0];
        s->f_5C4 = cur[1];
        s->f_5C8 = cur[2];
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

/* Static inline helper of the 2001 source at enemy_act.c:816-826 (it has no
   symbol of its own and no census row; the disc listing shows its lines inlined
   here and in subEnemyBrain_Irregular).  Name is descriptive, not recovered. */
static inline unsigned char isEnemyCarriedByGirl(int self)
{
    Act *gsub;
    if (GOBJ_ACT(self)->f_148 == 0 || (char *)girlGObj == 0) {
        return 0;
    }
    gsub = GOBJ_ACT(girlGObj);
    if ((char *)gsub == 0 || gsub->unk34 != 0x6F) {
        return 0;
    }
    if (gsub->f_144 == self) {
        return 1;
    }
    return 0;
}

void subEnemyCollision(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int idx;

    while ((int)sub->f_130 == 0) {
        _ACTWait(1);
    }
    while (1) {
        float *dir = (float *)((char *)sub + 0x120);
        if (actEnemyFlagCheckActive((int *)a0) != 0) {
            *(long long *)((char *)sub + 0x18) = (long long)sub->flags18.ll | (1LL << 32);
        } else {
            *(long long *)((char *)sub + 0x18) = (long long)sub->flags18.ll & ~(1LL << 32);
        }
        if ((((int)((long long)sub->flags18.ll >> 32)) & 1) == 0 && sub->unk34 != 0x16) {
            *(long long *)((char *)sub + 0x18) = (long long)sub->flags18.ll & ~(1LL << 33);
        } else {
            *(long long *)((char *)sub + 0x18) = (long long)sub->flags18.ll | (1LL << 33);
        }
        if (GOBJ_ACT(a0)->f_680->f_1F0 != 0) {
            _ACTParaStatus_Set((char *)a0, GOBJ_ACT(a0)->f_680->f_1F0);
        }
        if (GOBJ_ACT(a0)->f_680->liftKind == 3) {
            GOBJ_ACT(a0)->f_680->slowTimer -= 1;
            if (0 < GOBJ_ACT(a0)->f_680->slowTimer) {
                float rate = (60 - GOBJ_ACT(a0)->f_680->slowTimer) / 60.0f;
                float speed = (rate < 0.1f) ? 0.1f : ((1.0f < rate) ? 1.0f : rate);
                ACTGame_SetMotionPlaySpeedRatio_Reserve((char *)a0, speed, 8);
            }
        }
        ACTGame_CommonLoop((void *)a0);
        CommonAttackCenter((char *)a0);
        if (GOBJ_ACT(a0)->f_680->liftKind == 3) {
            boss_effect_process((char *)a0);
        }
        if (sub->unk34 == 5 && 400.0f < GOBJ_SUB(a0)->f_560) {
            FlyMail((void *)a0);
        }
        if (sub->f_34C != 0.0f) {
            enemyCheckTurnAngle((char *)a0);
        }
        if ((stage_no == 19 || stage_no == 28) && sub->unk34 == 6) {
        } else if (0.1f < sub->f_34C && sub->unk34 != 0x73) {
            SetMotionDirectionSmooze((void *)a0, dir,
                                     (float)((a0 == (int)((char *)girlGObj) && girlControlMode != 0)
                                                 ? motionKind[GOBJ_SUB(a0)->f_4A0].f182
                                                 : motionKind[GOBJ_SUB(a0)->f_4A0].f186));
        }
        if (actEnemyFlagCheckDead((int *)a0) == 0) {
            ACTGame_SaveActorInformation((char *)a0);
        }
        if (sub->unk34 != 0x70) {
            /* The January listing's rows 1761-1770 emit no instruction at all;
               the only word left of this block is the volatile reload of the
               actor-entry parameter, whose reader is the DEBUG build's state
               report (report ours). */
            int self = a0;
#ifdef DEBUG
            scePrintf("enemy %08x state %x\n", self, sub->unk34);
#endif
        }
        if (sub->unk34 != 0x16) {
            if (0x16 < (unsigned int)sub->unk34) {
                if (sub->unk34 == 0x1C) {
                    if (0.1f < sub->f_34C && (sub->f_340 < -134 || 134 < sub->f_340)) {
                        ACTSendMailCorrect((void *)a0, 0xE2);
                    } else if (0.1f < sub->f_34C && (-45 <= sub->f_340 && sub->f_340 <= 45)) {
                        if ((pad[0].now & 4) == 0) {
                            ACTSendMailCorrect((void *)a0, 0xC7);
                        }
                    }
                    ACTSendMailCorrect((void *)a0, 0x150);
                }
            }
        }
        DispMultiBgaManagerWithKind(0x1FA, GOBJ_WORK(a0)->f_378, 1);
        idx = (int)GetEnemyDefParaIndex((void *)a0);
        if ((unsigned int)(idx - 1) < 4) {
            _ACTParaStatus_Set((char *)a0, idx + 0x1C);
        }
        ACTParaStatus_Exec((void *)a0);
        if (isEnemyActive((int *)a0) == 0 && isEnemyCarriedByGirl(a0)) {
            afterCommonCarry(a0);
        }
        _ACTWait(1);
    }
}

inline void actEnemyStand(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    debug_StdPrintfDummy("enter actEnemyStand\n");
    sub->unk34 = 1;
    _ACTWait(0);
}

inline void motEnemyStand(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    debug_StdPrintfDummy("enter motEnemyStand\n");
    *(char **)((char *)sub + 0x130) = SetMotionRequest(a0, 1, *(MotOriReq *)((char *)sub + 0x620));
    while (1) {
        _ACTWait(1);
    }
}

inline void actEnemyWalk(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    debug_StdPrintfDummy("enter actEnemyWalk\n");
    sub->unk34 = 2;
    _ACTWait(0);
}

inline void motEnemyWalk(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    char *mot;
    debug_StdPrintfDummy("enter motEnemyWalk\n");
    mot = SetMotionRequest(a0, 8, *(MotOriReq *)((char *)sub + 0x620));
    *(char **)((char *)sub + 0x130) = mot;
    *(int *)(mot + 0x114) = 0;
    _ACTWait(0);
}

inline void actEnemyRun(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    debug_StdPrintfDummy("enter actEnemyRun\n");
    sub->unk34 = 3;
    _ACTWait(0);
}

inline void motEnemyRun(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    char *mot;
    debug_StdPrintfDummy("enter motEnemyRun\n");
    mot = SetMotionRequest(a0, 0xD, *(MotOriReq *)((char *)sub + 0x620));
    *(char **)((char *)sub + 0x130) = mot;
    *(int *)(mot + 0x114) = 0;
    _ACTWait(0);
}

inline void actEnemyJump(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    debug_StdPrintfDummy("enter actEnemyJump\n");
    sub->unk34 = 4;
    _ACTWait(0);
}

void actEnemyAttack(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int hit = 0;
    float buf[4];
    float v[4];

    _ACTWait(2);
    ACTSearchEnemy((void *)a0, (int *)((char *)sub + 0x188), buf);
    _OrientXZGV(v, test_CURRENTROOT((int)((void *)boyGObj)), test_CURRENTROOT(a0));
    sub->dir[0] = v[0];
    sub->dir[1] = v[1];
    sub->dir[2] = v[2];
    SetMotionDirection((void *)a0, v);
    while (1) {
        if (GetMotionFrameFlag2((void *)a0) != 0 && sub->f_188 != 0) {
            SetMotionDirectionWithLimit((void *)a0, buf, 10.0f, 90.0f);
        }
        if (sub->unk2E4 & 0x80) {
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

inline void actEnemyHang(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    debug_StdPrintfDummy("enter actEnemyHang\n");
    sub->unk34 = 0x1C;
    _ACTWait(0);
}

inline void funcEnemyAiGetGirl(int a0)
{
    Act *sub = GOBJ_ACT(a0);
    if (sub->f_350 == 0) {
        sub->f_350 = 1;
    }
}

inline void actEnemyHyde(int *self)
{
    sceVu0FVECTOR hide = {0.0f, 0.0f, -1000000.0f};
    SetDirectRootPositionNoFitting(self, hide);
    ResetEnemyPositionInfo(self);
    actEnemyFlagOnFree(self);
}

inline int isEnemyHyde(int *a0)
{
    int *p = (int *)(objLayout + a0[2] * 0x4C);
    return (((unsigned int)p[0x48 / 4] >> 21) & 1) ^ 1;
}

inline void actEnemyFlagOnFree(int *a0)
{
    char *base = objLayout + a0[2] * 0x4C;
    *(int *)(base + 0x48) &= ~0x200000;
}

inline void actEnemyFlagOnDead(int *a0)
{
    char *base = objLayout + a0[2] * 0x4C;
    *(int *)(base + 0x48) |= 0x40000;
}

inline int actEnemyFlagCheckDead(int *a0)
{
    int *p = (int *)(objLayout + a0[2] * 0x4C);
    return ((unsigned int)p[0x48 / 4] >> 18) & 1;
}

inline int isEnemyActive(int *self)
{
    if (self == 0 || *(int *)((char *)self + 0xC) != 4) {
        debug_assert("src/enemy_act.c", 0x827);
        __assert("src/enemy_act.c", 0x827, "ASSERTMSG__GOP_IS_NOT_ENEMY(gop)");
    }
    return actEnemyFlagCheckActive(self);
}

inline int actEnemyFlagCheckActive(int *a0)
{
    unsigned int *p = (unsigned int *)(objLayout + a0[2] * 0x4C);
    unsigned int field = p[0x48 / 4];
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

inline int actEnemy_isSmallEnemy(char *a0)
{
    return GOBJ_ACT(a0)->f_680->f_1E8 == 0;
}

inline int actEnemy_isLargeEnemy(char *a0)
{
    return GOBJ_ACT(a0)->f_680->f_1E8 == 2;
}

inline int actEnemy_isNormalEnemy(char *a0)
{
    return GOBJ_ACT(a0)->f_680->f_1E8 == 1;
}

inline int actEnemy_GetClingTarget(char *a0)
{
    Act *b = GOBJ_ACT(a0);
    EnemyBattleWork *e = b->f_680;
    if (e->f_1E8 == 0 && b->unk34 == 0x10) {
        return e->f_220;
    }
    return 0;
}

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
    int idx = gFlagGameClear + 38;

    idx = (idx < 38) ? 38 : ((idx <= max) ? idx : max);
    return GetEnemyDefLife(self) * _ACTGame_GetParamF(idx);
}

void actEnemyRestart(char *self, float *pos, float *dir, int kind, int mot)
{
    float v[4];
    Act *sub;
    int mail;
    int idx;
    float life;

    sub = GOBJ_ACT(self);
    mail = 50;
    v[0] = pos[0];
    v[2] = pos[2];
    v[1] = pos[1] - 100.0f;
    SetDirectRootPositionNoFitting((int *)self, (char *)v);
    gamesysObjInfoPosSetStage((int *)self, sub->f_444, 0, stage_no);
    switch (kind) {
    case 0:
        pos[1] = pos[1] + GOBJ_ACT(self)->f_680->bodySize * 100.0f;
        break;
    case 1:
        mail = 51;
        break;
    case 2:
        mail = 52;
        break;
    }
    if (((int)((long long)sub->flags20.ll >> 29)) & 1) {
        *(long long *)((char *)sub + 0x20) = (long long)sub->flags20.ll & ~0x20000000;
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
        debug_assert("src/enemy_act.c", 2161);
        __assert("src/enemy_act.c", 2161, "0");
    }
    GOBJ_ACT(self)->f_680->battleType = idx;
    setBattleStatus(self);
    life = getEnemyRestartLife(self);
    sub->f_1E4 = life;
    sub->f_1E0 = life;
    sub->f_350 = 0;
    if (mot != 0) {
        sub->f_54 = mot;
    } else {
        sub->f_54 = 0;
    }
    *(int *)((char *)sub + 0xD4) = (int)D_002A8570;
    ACTSendMailCorrect(self, mail);
    InitMotionGeoInfo((char *)GOBJ_SUB(self) + 0xA0, pos[0], pos[1], pos[2], 0.0f, 0.0f, 0.0f);
    ResetEnemyPositionInfo((int *)self);
    SetEnemyDissolve(self, 0.0f);
    sub->f_170 = pos[0];
    sub->f_174 = pos[1];
    sub->f_178 = pos[2];
    SetMotionDirection(self, dir);
    eBrainSendMes((int)self, 4);
    _BrainMode_SetDirect(self, 0, 0);
}

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

        p0[0] = test_CURRENTROOT((int)me)[0];
        p0[1] = test_CURRENTROOT((int)me)[1];
        p0[2] = test_CURRENTROOT((int)me)[2];
        p1[0] = test_CURRENTROOT((int)pair)[0];
        p1[1] = test_CURRENTROOT((int)pair)[1];
        p1[2] = test_CURRENTROOT((int)pair)[2];
        _OrientXZGV(dir, p1, p0);
        sceVu0ScaleVector(ofs, dir, dist);
        sceVu0AddVector(p1, p0, ofs);
        SetDirectRootPositionNoFitting((int *)pair, (char *)p1);
        GOBJ_ACT(me)->dir[0] = dir[0];
        GOBJ_ACT(me)->dir[1] = dir[1];
        GOBJ_ACT(me)->dir[2] = dir[2];
        sceVu0ScaleVector((float *)((char *)GOBJ_ACT(pair) + 0x120), dir, -1.0f);
        SetMotionDirection(me, (float *)((char *)GOBJ_ACT(me) + 0x120));
        SetMotionDirection(pair, (float *)((char *)GOBJ_ACT(pair) + 0x120));
    }
    float q[4];
    Act *sub = GOBJ_ACT(a0);

    if ((char *)girlGObj == 0) {
        return 0;
    }
    if (ACTReserveTarget((char *)girlGObj, a0, 0xFF) == 0) {
        return 0;
    }
    if (GOBJ_ACT(girlGObj)->unk34 == 0x6F) {
        return 0;
    }
    PairSetGeometry(a0, (char *)girlGObj, 50.0f);
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, -0x8000);
    SetMotionNodeFixModeParameter((char *)girlGObj, a0, 2, GOBJ_ACT(a0)->f_680->f_1F4, q, 18.0f,
                                  0.0f, 0.0f, 1.0f);
    sub->f_148 = girlGObj;
    GOBJ_ACT(girlGObj)->f_144 = (int)a0;
    eBrainSendMes((int)a0, 9);
    eBrainSendMes((int)a0, 7);
    if ((0x3C - systemStatus[0] * 10) / systemStatus[1] * 2 < sub->f_10 &&
        debug_enemy_kidnap_timer != 0) {
        GOBJ_WORK(a0)->f_4D0 = 1;
        if ((void *)boyGObj != 0) {
            GOBJ_WORK(a0)->f_4E0 = test_CURRENTROOT((int)((void *)boyGObj))[0];
            GOBJ_WORK(a0)->f_4E4 = test_CURRENTROOT((int)((void *)boyGObj))[1];
            GOBJ_WORK(a0)->f_4E8 = test_CURRENTROOT((int)((void *)boyGObj))[2];
        } else {
            GOBJ_WORK(a0)->f_4E0 = test_CURRENTROOT((int)a0)[0];
            GOBJ_WORK(a0)->f_4E4 = test_CURRENTROOT((int)a0)[1];
            GOBJ_WORK(a0)->f_4E8 = test_CURRENTROOT((int)a0)[2];
        }
    }
    return 1;
}

inline int ACTEnemyForceSwitchToCarry(char *a0)
{
    int r = actEnemyForceSwitchToCarry(a0);
    if (r != 0) {
        _BrainMode_SetDirect(a0, 0, 0);
    }
    ACTSendMailCorrect(a0, 0x104);
    return r;
}

inline void actEnemyNest(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int stg;
    int x2;

    int x = a0;
    *(int *)((char *)sub + 0x148) = 0;
    RestoreReviveCount(x);
    actChangeActBrain(isysCurrentGObj, (void *)subEnemyBrain_Idle, (char *)sub);
    actEnemyHyde((int *)a0);
    eBrainSendMes(a0, 0xA);
    stg = stage_no;
    *(int *)((char *)sub + 0x440) = 0;
    x2 = a0;
    sub->f_444 = 7;
    gamesysObjInfoPosSetStage((int *)x2, 7, 0, stg);
    _ACTWait(0);
}

static int kidnapEndCount = 0; /* derived name: cleared as actEnemyKidnapEnd starts its wait */

void actEnemyKidnapEnd(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    float mypos[4];
    float gpos[4];

    union {
        float f[4];
        int i[4];
    } q;

    float pos[4];
    float tmp[4];
    int sent = 0;
    float *p;
    int cnt = 0;
    char *target = 0;
    char *g;
    float best;
    float d;
    float dist = 0.0f;
    float ratio;
    int n;
    int r;

    if (gflagChk(393) == 0) {
        ACTGame_InsertCamera_GirlIsPinch();
    }
    g = isysGObjSearchFromObjKindID_begin(33);
    best = 10000.0f;
    mypos[0] = test_CURRENTROOT((void *)a0)[0];
    mypos[1] = test_CURRENTROOT((void *)a0)[1];
    mypos[2] = test_CURRENTROOT((void *)a0)[2];
    while (g != 0) {
        GetRootPosition(gpos, g);
        d = _DistGV(mypos, gpos);
        if (d < best) {
            best = d;
            target = g;
        }
        g = isysGObjSearchFromObjKindID_next(g);
    }
    p = pos;
    if (target != 0) {
        memset(&q, 0, 0x10);
        q.f[3] = 1.0f;
        EntryMultiBgaManager(GOBJ_WORK(a0)->f_378, 0, -1, test_CURRENTROOT(target), q.f);
    }
    gflagOn(393);
    kidnapEndCount = 0;
    while (1) {
        if (((int)((long long)sub->flags20.ll >> 21)) & 1) {
            ACTGame_SetMotionPlaySpeedRatio_Reserve((char *)a0, 0.0001f, 9);
        }
        if (gflagChk(392) != 0) {
            stgmgrNextStagePreLoadForceStageSet(gFlagSaveStage);
            if ((0x3C - systemStatus[0] * 10) / systemStatus[1] * 3 < sub->f_4C) {
                backStageTsuresariReturn();
                _ACTWait(0);
            }
        }
        if (5 <= sub->f_4C) {
            if (GOBJ_ACT(girlGObj)->unk34 != 0x6F || GOBJ_ACT(girlGObj)->f_144 != a0) {
                sub->f_444 = 0;
                gamesysObjInfoPosSetStage((int *)a0, 0, 0, stage_no);
            }
        }
        if (GetEfStageCameraTargetID() != 0) {
            ACTGame_SetMotionPlaySpeedRatio_Reserve((char *)a0, 2.0f, 0);
            if ((0x3C - systemStatus[0] * 10) / systemStatus[1] * 5 < sub->f_4C) {
                goto gameover;
            }
        }
        if (GOBJ_SUB(a0)->f_4A0 == 952) {
            /* RECONSTRUCTION (listing row 2486): the girl's record and her
               action are read before the null test, and the ROM loads 0x6F
               into a register of its own in that same block and compares the
               register in the if (a literal is re-materialised in the
               compare's block, as at this function's four other 0x6F sites).
               The bytes pin a local holding the value, set with the record;
               not its name or its declaration layout. */
            Act *gsub = GOBJ_ACT(girlGObj);
            int act = gsub->unk34;
            int carriedAct = 0x6F;

            if ((char *)girlGObj == 0 || act != carriedAct || gsub->f_144 != a0) {
                ratio = dist / (float)((0x3C - systemStatus[0] * 10) / systemStatus[1]);
                SetEnemyDissolve((char *)a0,
                                 (ratio < 0.01) ? 0.01f : ((1.0f < ratio) ? 1.0f : ratio));
                dist = dist + 1.0f;
            }
            if (50.0f < GOBJ_SUB(a0)->f_4AC) {
                if ((((int)((long long)sub->flags20.ll >> 21)) & 1) == 0) {
                gameover:
                    if (GOBJ_ACT(girlGObj)->unk34 == 0x6F && GOBJ_ACT(girlGObj)->f_144 == a0) {
                        if (target != 0) {
                            q.i[0] = (int)target;
                            best = 0.0f;
                            q.i[1] = 0;
                            if ((void *)boyGObj != 0 && (char *)girlGObj != 0) {
                                GetRootPosition(pos, (void *)boyGObj);
                                GetRootPosition(tmp, (char *)girlGObj);
                                best = GetPointDistance(pos, tmp) + 1000.0f;
                                debug_StdPrintfDummy("radius: %f\n", best);
                            }
                            gameover_flag = 1;
                            if ((char *)girlGObj != 0) {
                                *(int *)((char *)girlGObj + 0x16C) = 0;
                            }
                            stage_SetParentOfGObj(502, &q);
                            n = (GetEfStageCameraTargetID() != 0) ? 120 : 300;
                            r = n * ((0x3C - systemStatus[0] * 10) / systemStatus[1]) / 60;
                            StartGameOverEffect((int)test_CURRENTROOT(target),
                                                (best < (float)(r * 50)) ? 50.0f : best / (float)r);
                            _ACTRun(r);
                        }
                        ACT_LAYOUT_GAMEOVER();
                        _ACTWait(0);
                    } else {
                        ACTSendMailCorrect((char *)a0, 353);
                    }
                }
            }
        }
        if ((void *)boyGObj != 0) {
            if (GOBJ_ACT(boyGObj)->unk34 == 0x6D) {
                _OrientXZGV(q.f, test_CURRENTROOT((void *)boyGObj), test_CURRENTROOT((void *)a0));
                sceVu0ScaleVector(q.f, q.f, -1.0f);
                SetMotionDirectionSmooze(a0, q.f, 3.0f);
                ACTSendMailCorrect((char *)a0, 0x167);
                ACTSendMailCorrect((char *)a0, 0x168);
                ACTSendMailCorrect((char *)a0, 0x169);
                ACTSendMailCorrect((char *)a0, 0x16A);
            }
        }
        if (target != 0) {
            pos[0] = test_CURRENTROOT(target)[0];
            pos[1] = test_CURRENTROOT(target)[1];
            pos[2] = test_CURRENTROOT(target)[2];
            pos[1] = test_CURRENTROOT((void *)a0)[1];
            _InterGV(tmp, p, test_CURRENTROOT((void *)a0), 5.0f, 1.0f);
            SetRootPosition((char *)a0, tmp);
        }
        ACTSendMailCorrect((char *)a0, 0x16B);
        if ((char *)girlGObj == 0 || GOBJ_ACT(girlGObj)->unk34 != 0x6F ||
            GOBJ_ACT(girlGObj)->f_144 != a0) {
            if ((0x3C - systemStatus[0] * 10) / systemStatus[1] / 6 < ++cnt && sent == 0) {
                eBrainSendMes(a0, 10);
                sent = 1;
            }
        }
        _ACTWait(1);
    }
}

/* Static inline of the 2001 source: the listing attributes rows 2609-2614 to a
   body inside actEnemyKidnapBegin's ROM range but above its own lines, the same
   construction as enemyPickupCheckGirl above.  Rows 2605-2608 emit nothing and
   ROM's frame is 0xB0 with a 16-byte slot at sp+0x10 that no retail code
   reads, so a second vector is declared ahead of buf (drop it and the frame is
   0xA0); its reader is the DEBUG build's report of the girl's position (report
   ours). */
static inline int enemyKidnapCheckGirl(int self)
{
    float pos[4];
    float buf[4];
    int ang;
    int mode;

    if (_ACTGame_SearchGObj(self, (char *)girlGObj, 60.0f, 100.0f, 45, buf) != 0) {
        ang = _RotyGV(buf, test_CURRENTORIENT((int)((char *)girlGObj)));
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

void actEnemyKidnapBegin(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    float *dir = (float *)((char *)sub + 0x120);
    int mail = 0x163;
    int mode;

    while (1) {
        if (GOBJ_SUB(a0)->f_4A0 == 0x3AA) {
            _OrientXZGV(dir, test_CURRENTROOT((int)((char *)girlGObj)), test_CURRENTROOT(a0));
            if (0.1f < sub->f_34C && sub->unk34 != 0x73) {
                SetMotionDirectionSmooze(
                    (void *)a0, dir,
                    (float)((a0 == (int)((char *)girlGObj) && girlControlMode != 0)
                                ? motionKind[GOBJ_SUB(a0)->f_4A0].f182
                                : motionKind[GOBJ_SUB(a0)->f_4A0].f186));
            }
            mode = enemyKidnapCheckGirl(a0);
            switch (mode) {
            case 1:
                mail = 0x164;
                /* fallthrough */
            case 2:
                if (actEnemyForceSwitchToCarry((void *)a0) != 0) {
                    if (mode == 1) {
                        sceVu0ScaleVector((float *)((char *)GOBJ_ACT(girlGObj) + 0x120),
                                          (float *)((char *)GOBJ_ACT(girlGObj) + 0x120), -1.0f);
                        SetMotionDirection((void *)((char *)girlGObj),
                                           (float *)((char *)GOBJ_ACT(girlGObj) + 0x120));
                    }
                    ACTGame_InsertCamera_GirlIsPinch();
                    while (1) {
                        ACTSendMailCorrect((void *)a0, mail);
                        _ACTWait(1);
                    }
                }
                break;
            }
            ACTSendMailCorrect((void *)a0, 0x165);
        }
        _ACTWait(1);
    }
}

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
    int ang2;

    GOBJ_SUB(self)->f_550 = 1;
    GOBJ_SUB(self)->f_380 = 2;
    GetRootProjectionPosOfGObj(p0, self);
    GetRootProjectionPosOfGObj(p1, (char *)((void *)boyGObj));
    GetSkeltonPosition(sk, self, 1);
    t = (p0[1] - p1[1]) / 600.0f;
    t = (t < 0.0f) ? 0.0f : ((1.0f < t) ? 1.0f : t);
    a = t * 1000.0f + -200.0f;
    b = t * -400.0f;
    ori[0] = test_CURRENTORIENT((int)self)[0];
    ori[1] = test_CURRENTORIENT((int)self)[1];
    ori[2] = test_CURRENTORIENT((int)self)[2];
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
    sceVu0AddVector((float *)((char *)GOBJ_SUB(self) + 0x390), p0, sc);
    debug_NMarker((float *)((char *)GOBJ_SUB(self) + 0x390), 255, 0, 0, 200.0f);
}

inline void afterEnemyBodylift(volatile int a0)
{
    int x = a0;
    GOBJ_SUB(x)->f_550 = 0;
    GOBJ_SUB(x)->f_380 = 0;
}

/* listing rows 2655-2657: a `static inline` outside this function's span. */
static inline void enemyBodyliftClearBoy(char *self)
{
    GOBJ_SUB(self)->f_550 = 0;
    GOBJ_SUB(self)->f_380 = 0;
}

void actEnemyBodylift(volatile int a0)
{
    float dir[4];
    float pos[4];
    float bpos[4];
    float mtx[16];
    float lv[4];
    Act *sub;
    int hit;

    sub = GOBJ_ACT(a0);
    hit = 0;
    GOBJ_ACT(a0)->f_680->flags.ll &= ~4LL;
    _OrientXZGV(dir, bodyliftTarget[0], test_CURRENTROOT((int)a0));
    sub->after = (void *)afterEnemyBodylift;
    if (GOBJ_ACT(a0)->f_680->liftKind != 3) {
        _OrientXZGV(sub->dir, test_CURRENTROOT((int)((void *)boyGObj)), test_CURRENTROOT((int)a0));
        SetMotionDirection((void *)a0, sub->dir);
    }
    for (;;) {
        GOBJ_ACT(a0)->f_680->flags.ll &= ~4LL;
        if (GOBJ_ACT(a0)->f_680->liftKind == 3) {
            if (GOBJ_ACT(boyGObj)->unk34 == 94) {
                enemyBodyliftClearBoy((char *)a0);
            } else {
                MoveChestForCatchBoy((char *)a0);
            }
        }
        GetSkeltonPosition(pos, (char *)a0, 22);
        bpos[0] = test_CURRENTROOT((int)((void *)boyGObj))[0];
        bpos[1] = test_CURRENTROOT((int)((void *)boyGObj))[1];
        bpos[2] = test_CURRENTROOT((int)((void *)boyGObj))[2];
        if (GOBJ_ACT(a0)->f_680->liftKind == 3) {
            sceVu0SubVector(lv, test_CURRENTROOT((int)((void *)boyGObj)), pos);
            GetMatrixDirectionToZ(mtx, test_CURRENTORIENT((int)a0));
            lv[3] = 0.0f;
            sceVu0ApplyMatrix(lv, mtx, lv);
            if (((lv[0] < 0.0f) ? -lv[0] : lv[0]) < 100.0f &&
                ((lv[1] < 0.0f) ? -lv[1] : lv[1]) < 100.0f && -300.0f < lv[2] && lv[2] < 200.0f) {
                hit = 1;
            }
        } else {
            if (_DistSqGV(pos, bpos) <
                GOBJ_ACT(a0)->f_680->bodySize * 45.0f * (GOBJ_ACT(a0)->f_680->bodySize * 45.0f)) {
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
            iosOmSendMail((int)((void *)boyGObj), 0x170, a0);
        }
        if (GetMotionFrameFlag2((void *)a0) != 0) {
            _OrientXZGV(bpos, test_CURRENTROOT((int)((void *)boyGObj)), test_CURRENTROOT((int)a0));
            _ACTMotDirSmzDirect((void *)a0, bpos);
        }
        if (GOBJ_ACT(boyGObj)->unk34 == 94 && GOBJ_ACT(boyGObj)->f_680->f_22C == (int)a0) {
            if (GOBJ_ACT(a0)->f_680->liftKind == 3) {
                if (0 < GOBJ_ACT(boyGObj)->f_680->f_CC) {
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

inline void actEnemyBodyslamFail(volatile int a0)
{
    iosOmSendMail((int)((void *)boyGObj), 0xE2, a0);
    while (1) {
        ACTSendMailCorrect((void *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actEnemyBodyslam(volatile int a0)
{
    iosOmSendMail((int)((void *)boyGObj), GOBJ_ACT(a0)->f_680->f_200, a0);
    while (1) {
        ACTSendMailCorrect((void *)a0, 0xC7);
        _ACTWait(1);
    }
}

/* Static inline of the 2001 source (listing lines 2889-2892 sit inside
   actEnemyPickupBegin's ROM range but above its own body lines).  ROM's frame
   is 0x80 with the 16-byte slot at sp+0x10 no retail code references and buf
   at sp+0x20, so a second 16-byte vector is declared here ahead of buf; its
   reader is the DEBUG build's report of the girl's position, as in
   enemyKidnapCheckGirl (report ours). */
static inline int enemyPickupCheckGirl(int self)
{
    float pos[4];
    float buf[4];
    int ang;
    int mode;

    if (_ACTGame_SearchGObj(self, (char *)girlGObj, 170.0f, 100.0f, 45, buf) != 0) {
        ang = _RotyGV(buf, test_CURRENTORIENT((int)((char *)girlGObj)));
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

void actEnemyPickupBegin(volatile int a0)
{
    float *dir = (float *)((char *)GOBJ_ACT(a0) + 0x120);
    float *girl = test_CURRENTROOT((int)((char *)girlGObj));
    float *me = test_CURRENTROOT(a0);
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

inline void actEnemyCarry(volatile int a0)
{
    debug_assert("src/enemy_act.c", 0xB75);
    __assert("src/enemy_act.c", 0xB75, "0");
}

inline int EnemyBrainStatus_Boy(char *a0)
{
    return GOBJ_ACT(a0)->f_440 == 2;
}

inline int EnemyBrainStatus_Girl(char *a0)
{
    return GOBJ_ACT(a0)->f_440 == 1;
}

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
    if (*(int *)(sub + 0x148) != 0 && motionKind[GOBJ_SUB(self)->f_4A0].f100 == 0) {
        *outMode = -1;
        return;
    }
    if (((*(unsigned long long *)(sub + 0x18) >> 49) & 1) == 0) {
        *outMode = -1;
        return;
    }
    if (actEnemyFlagCheckActive((int *)self) == 0) {
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
        if ((char *)girlGObj == 0) {
            *outMode = -1;
            return;
        }
        if (GOBJ_ACT(girlGObj)->unk34 != 0x6F) {
            *outMode = -1;
            return;
        }
        if (GOBJ_ACT(girlGObj)->f_144 != (int)self) {
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

inline void _BrainMode_SetDirect(char *a0, int a1, int *a2)
{
    GOBJ_ACT(a0)->f_680->reqMode = a1;
    if (a2 != 0) {
        *(int *)((char *)GOBJ_ACT(a0)->f_680 + 0x214) = *a2;
    } else {
        *(int *)((char *)GOBJ_ACT(a0)->f_680 + 0x214) = brainTargetNone[0];
    }
}

/* Static inline of the 2001 source: the listing puts its body at rows 3064-3065
   between _BrainMode_SetDirect (3056-3060) and subEnemyBrainMain (3074), and no
   ROM slot carries it, so it is inline-only. */
static inline void _BrainMode_Set(char *a0, int mode, int *tgt)
{
    if (brainModeTable[mode].pri < brainModeTable[GOBJ_ACT(a0)->f_680->reqMode].pri) {
        return;
    }
    _BrainMode_SetDirect(a0, mode, tgt);
}

void subEnemyBrainMain(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int mode;
    int data;
    int i;

    /* BrainMode_Requset is a nested function in the ROM: subEnemyBrainMain
       passes it a static chain in $2 (STATIC_CHAIN_REGNUM) which it spills to
       0(sp) and reads a0 out of the parent frame through.  The listing names it
       BrainMode_Requset.299 and puts its body at lines 3083-3104. */
    void BrainMode_Requset(int req, int arg)
    {
        switch (req) {
        case 0:
            _BrainMode_Set((char *)a0, 1, 0);
            break;
        case -2:
            _BrainMode_Set((char *)a0, 1, 0);
            break;
        case 1:
            _BrainMode_Set((char *)a0, 3, 0);
            break;
        case 2:
            _BrainMode_Set((char *)a0, 4, 0);
            break;
        case 3:
            _BrainMode_Set((char *)a0, 6, 0);
            break;
        case -3:
        case -1:
        case 7:
            _BrainMode_Set((char *)a0, 13, 0);
            break;
        case 5:
            _BrainMode_Set((char *)a0, 7, &arg);
            break;
        case 4:
        case 6:
            _BrainMode_Set((char *)a0, 5, &arg);
            break;
        case 8:
            _BrainMode_SetDirect((char *)a0, 2, &arg);
            break;
        default:
            debug_StdPrintfDummy("undefined mode [%d]\n", req);
            debug_assert("src/enemy_act.c", 3102);
            __assert("src/enemy_act.c", 3102, "0");
            break;
        }
    }

    GOBJ_ACT(a0)->f_680->reqMode = GOBJ_ACT(a0)->f_680->mode = 0;
    GOBJ_ACT(a0)->f_680->waitCount = 2;
    _ACTWait(1);
    _ACTWait(1);
    _ACTWait(1);
    switch (sub->f_448) {
    case 4:
        if ((char *)girlGObj != 0) {
            eBrainSendMes(a0, 9);
            i = 0;
            eBrainSendMes(a0, 7);
            actEnemyForceSwitchToCarry((void *)a0);
            for (; i < 5; i++) {
                if (sub->unk34 == 5) {
                    ACTReserveTarget((char *)girlGObj, (void *)a0, 0xFF);
                    *(char **)((char *)sub + 0x130) =
                        SetMotionRequest(a0, 0x109, *(MotOriReq *)((char *)sub + 0x620));
                } else {
                    *(char **)((char *)sub + 0x130) =
                        SetMotionRequest(a0, 0x107, *(MotOriReq *)((char *)sub + 0x620));
                }
                if (*(int *)((char *)sub->f_130 + 0xC) != 0) {
                    break;
                }
                _ACTWait(1);
            }
            if (gflagChk(0x189) != 0) {
                *(char **)((char *)sub + 0x130) =
                    SetMotionRequest(a0, 0x108, *(MotOriReq *)((char *)sub + 0x620));
            }
        }
        break;
    case 1:
        if ((char *)girlGObj != 0 &&
            ACTCheckViewCl((void *)a0, (char *)girlGObj, test_CURRENTROOT((int)((char *)girlGObj)),
                           0x168, 3.40282347e+38f /* FLT_MAX */) != 0) {
            eBrainSendMes(a0, 2);
        } else {
            eBrainSendMes(a0, 1);
        }
        break;
    case 2:
        if ((char *)girlGObj != 0) {
            eBrainSendMes(a0, 2);
        }
        break;
    case 5:
        eBrainSendMes(a0, 3);
        break;
    }
    while (1) {
        if ((char *)girlGObj != 0 && GOBJ_ACT(girlGObj)->unk34 == 0x6F &&
            GOBJ_ACT(girlGObj)->f_144 == (int)a0 && EA_CHKBIT(GOBJ_WORK(a0)->f_454, 0)) {
            ACTSendMailCorrect((void *)a0, 0x1E);
            ACTSendMailCorrect((void *)a0, 0x1D);
        }
        CheckEnemyBrainMode((char *)a0, &mode, &data);
        BrainMode_Requset(mode, data);
        if (GOBJ_ACT(a0)->f_680->reqMode != GOBJ_ACT(a0)->f_680->mode ||
            (((int)(sub->flags20.ll >> 9)) & 1) != 0) {
            sub->flags20.ll &= ~0x200LL;
            GOBJ_ACT(a0)->f_680->mode = GOBJ_ACT(a0)->f_680->reqMode;
            GOBJ_ACT(a0)->f_680->target = GOBJ_ACT(a0)->f_680->flags.w.reqTarget;
            sub->f_14C = (char *)GOBJ_ACT(a0)->f_680->target;
            sub->f_440 = brainModeTable[GOBJ_ACT(a0)->f_680->mode].f0C;
            sub->f_444 = brainModeTable[GOBJ_ACT(a0)->f_680->mode].f18;
            if (sub->f_444 == 4) {
                gamesysObjInfoPosSetStage((int *)a0, 4, 0, stage_no);
            }
            actChangeActBrain(isysCurrentGObj,
                              (void *)brainModeTable[GOBJ_ACT(a0)->f_680->mode].brain, (char *)sub);
        }
        if (sub->f_148 != 0) {
            _ACTCharStatus_Set((void *)a0, 0x10, -1.0f, 0);
        }
        if (GOBJ_ACT(a0)->f_680->waitCount != 0) {
            GOBJ_ACT(a0)->f_680->waitCount -= 1;
        }
        if ((((int)((long long)sub->flags20.ll >> 6)) & 1) != 0) {
            char *g = *(char **)(char *)sub;

            if (sub->unk34 != 0x67) {
                SetEnemyStonizedVisual((void *)a0);
            }
            *(long long *)((char *)sub + 0x20) |= 0x200000LL;
            sub->f_34C = 0;
            *(int *)((char *)sub + 0x120) = 0;
            *(int *)((char *)sub + 0x124) = 0;
            *(int *)((char *)sub + 0x128) = 0;
            sub->f_33C = 127;
            sub->f_338 = 127;
            isysGObjProcPause(g);
            while (1) {
                _ACTWait(1);
            }
        }
        if (brainModeTable[GOBJ_ACT(a0)->f_680->mode].f14 != 0 &&
            (((int)((long long)sub->flags20.ll >> 5)) & 1) != 0) {
            char *g = *(char **)(char *)sub;

            isysGObjProcPause(g);
            *(long long *)((char *)sub + 0x20) |= 0x200000LL;
            sub->f_34C = 0;
            *(int *)((char *)sub + 0x120) = 0;
            *(int *)((char *)sub + 0x124) = 0;
            *(int *)((char *)sub + 0x128) = 0;
            sub->f_33C = 127;
            sub->f_338 = 127;
            while (1) {
                if ((char *)girlGObj == 0 || GOBJ_ACT(girlGObj)->unk34 != 0x6F ||
                    GOBJ_ACT(girlGObj)->f_144 != (int)a0) {
                    if ((((StatusAttr *)(actModeTbl + GOBJ_ACT(a0)->unk34 * 0x50))->f_4C >> 5) &
                        1) {
                        ACTSendMailCorrect((void *)a0, 0x102);
                    }
                }
                if ((((int)((long long)sub->flags20.ll >> 4)) & 1) != 0) {
                    isysGObjProcActive(g);
                    *(long long *)((char *)sub + 0x20) &= ~0x200000LL;
                    break;
                }
                _ACTWait(1);
            }
        }
        BossEnemyFunc((void *)a0);
        _ACTWait(1);
    }
}

inline void afterCommonCarry(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int girl = (int)girlGObj;
    int self = a0;
    sub->f_148 = girl;
    iosOmSendMail(girl, 0x30, self);
    sub->f_148 = 0;
    if (sub->unk34 == 5) {
        eBrainSendMes(a0, 4);
    }
}

inline void funcEnemyCarryFail(char *a0)
{
    GOBJ_ACT(a0)->flags20.ll |= (1ULL << 34);
}

inline void subEnemyBrain_Idle(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    sub->f_34C = 0;
    *(int *)((char *)sub + 0x120) = 0;
    *(int *)((char *)sub + 0x124) = 0;
    *(int *)((char *)sub + 0x128) = 0;
    while (1) {
        if (GOBJ_ACT(a0)->f_680->target == (int)((void *)boyGObj)) {
            _DoAwait((char *)a0);
        }
        _ACTWait(1);
    }
}

inline void subEnemyBrain_Await(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    sub->f_34C = 0;
    *(int *)((char *)sub + 0x120) = 0;
    *(int *)((char *)sub + 0x124) = 0;
    *(int *)((char *)sub + 0x128) = 0;
    if ((void *)boyGObj != 0) {
        _ApproachTarget((char *)a0, (void *)boyGObj, (char *)sub + 0x120, 0,
                        (float)((int)(_GetRandom() * 10.0f) % 200 + 300), 0);
    }
    sub->f_34C = 0;
    *(int *)((char *)sub + 0x120) = 0;
    *(int *)((char *)sub + 0x124) = 0;
    *(int *)((char *)sub + 0x128) = 0;
    while (1) {
        _DoAwait((char *)a0);
        _ACTWait(1);
    }
}

inline void subEnemyBrain_FindGirl(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int i;

    for (i = 0; i < (0x3C - systemStatus[0] * 10) / systemStatus[1] / 2; i++) {
        *(int *)((char *)sub + 0x34C) = 0;
        *(int *)((char *)sub + 0x120) = 0;
        *(int *)((char *)sub + 0x124) = 0;
        *(int *)((char *)sub + 0x128) = 0;
        ACTSendMailCorrect((void *)a0, 0xE6);
        if (sub->unk34 == 0x47) {
            break;
        }
        _ACTWait(1);
    }
    for (i = 0; i < (0x3C - systemStatus[0] * 10) / systemStatus[1] * 250 / 60; i++) {
        _DoAwait((char *)a0);
        _ACTWait(1);
    }
    eBrainSendMes(a0, 1);
    _ACTWait(0);
}

void subEnemyBrain_ToGenerator(int self)
{
    /* The actor handle is kept in a `volatile` local: this brain thread is
       resumed by the actor scheduler at every _ACTWait, so the frame slot --
       not a register -- is the live copy of the handle. */
    volatile int a0 = self;
    Act *sub = GOBJ_ACT(a0);
    char *target = sub->f_14C;

    GOBJ_WORK(a0)->f_460 = target;
    SetKidnapInfo(-1, -1);
    if (GOBJ_WORK(a0)->f_4D0 != 0) {
        float best = 0.0f;
        char *g;

        for (g = isysGObjSearchFromObjKindID_begin(33); g != 0;
             g = isysGObjSearchFromObjKindID_next(g)) {
            if (IsOpenGenerator(g) != 0) {
                float d;

                d = _DistSqGV((float *)((char *)GOBJ_ACT(a0)->f_688 + 0x4E0),
                              test_CURRENTROOT((int)g));
                if (best < d) {
                    best = d;
                    GOBJ_WORK(a0)->f_460 = g;
                    sub->f_14C = g;
                    target = g;
                    SetKidnapInfo(*(int *)(a0 + 8), *(int *)(target + 8));
                }
            }
        }
    }
    if ((unsigned char)_ApproachTarget((char *)a0, target, (char *)sub + 0x120, 0, 50.0f,
                                       *(unsigned char *)((char *)GOBJ_ACT(a0)->f_680 + 0x224)) ==
        0) {
        debug_StdPrintfDummy("to generator way error!");
        sub->f_34C = 0;
        *(int *)((char *)sub + 0x120) = 0;
        *(int *)((char *)sub + 0x124) = 0;
        *(int *)((char *)sub + 0x128) = 0;
        _ACTWait(30);
        ACTSendMailCorrect((void *)a0, 0x100);
        _ACTWait(0);
    }
    while (1) {
        ACTSendMailCorrect((void *)a0, 0x166);
        _ACTWait(1);
    }
}

/* static inline of the 2001 source, listing lines 1985-1997.  `sub` is computed
   INSIDE the helper (row 1986): in enemy_dodge the caller already holds it so
   cse deletes the load, which is why that call site shows only rows 1989-1997,
   while subEnemyBrain_Attack's two expansions carry 1985 and 1986 as real
   instructions. */
static inline void enemyDodgeSendMail(char *self)
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

void enemy_dodge(char *self)
{
    float a[4];
    float b[4];
    float c[4];
    char *boy = (char *)boyGObj;
    Act *sub;
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
            sub = GOBJ_ACT(self);
            if ((((int)(*(long long *)((char *)sub->f_680 + 0x210) >> 1)) & 1) == 0) {
                if (d < 200.0f) {
                    enemyDodgeSendMail(self);
                }
            } else if (debug_ignore_dodge == 0) {
                ACTSendMailCorrect(self, 0x113);
            }
        }
    }
}

void enemy_dodge_to_boy(char *self)
{
    float boy[4];
    float me[4];
    float v[4];
    int ang;

    if ((void *)boyGObj == 0) {
        return;
    }
    if (((int)(*(long long *)((char *)GOBJ_ACT(self)->f_680 + 0x210) >> 1)) & 1) {
        boy[0] = test_CURRENTROOT((int)((void *)boyGObj))[0];
        boy[1] = test_CURRENTROOT((int)((void *)boyGObj))[1];
        boy[2] = test_CURRENTROOT((int)((void *)boyGObj))[2];
        me[0] = test_CURRENTROOT((int)self)[0];
        me[1] = test_CURRENTROOT((int)self)[1];
        me[2] = test_CURRENTROOT((int)self)[2];
        if (_DistSqGV(boy, me) < GetEnemyDefDodgeRange(self) * GetEnemyDefDodgeRange(self)) {
            _OrientXZGV(v, boy, me);
            ang = _RotyGV(v, test_CURRENTORIENT((int)((void *)boyGObj)));
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
                if (debug_ignore_dodge != 0) {
                    return;
                }
                ACTSendMailCorrect(self, 0x113);
            }
        }
    }
}

/* listing rows 3858-3870: a `static inline` outside this function's span,
   expanded twice here (each expansion gets its OWN .lit4 0.7f and its own
   `1.2` .rodata double -- the pool duplication in ROM is what proves it is an
   inline function and not a shared helper). */
static inline float battleRangeScale(char *self, float v)
{
    EnemyBattleWork *work = GOBJ_ACT(self)->f_680;

    switch (work->f_1E8) {
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
    dy = ((pos[1] - test_CURRENTROOT((int)tgt)[1]) < 0.0f)
             ? -(pos[1] - test_CURRENTROOT((int)tgt)[1])
             : (pos[1] - test_CURRENTROOT((int)tgt)[1]);
    vflag = 0.0f;
    range = GetEnemyDefDodgeRange(self);
    if (200.0f < xz || battleRangeScale(self, 200.0f) < dy) {
        vflag = 1.0f;
    }
    if (xz < range && dy < battleRangeScale(self, 150.0f)) {
        vflag = -1.0f;
    }
    ori[0] = test_CURRENTORIENT((int)tgt)[0];
    ori[1] = test_CURRENTORIENT((int)tgt)[1];
    ori[2] = test_CURRENTORIENT((int)tgt)[2];
    _OrientXZGV(dir, test_CURRENTROOT((int)self), test_CURRENTROOT((int)tgt));
    ang = _AbsRotyGV(ori, dir);
    a = (ang < 75) ? 1.0f : 0.0f;
    far = (101 <= ang);
    b = (a != 0.0f && GOBJ_ACT(tgt)->unk34 == 15) ? 1.0f : 0.0f;
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

inline void EnemyUtil_TurnToBoy(char *self, int tgt, int smooze)
{
    float dir[4];
    Act *sub = GOBJ_ACT(self);

    _OrientXZGV(dir, test_CURRENTROOT(tgt), test_CURRENTROOT((int)self));
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

inline int EnemyUtil_isOtherStatus(char *self, int mode)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (g != self) {
            Act *sub = GOBJ_ACT(g);
            if (sub->unk34 == 0xF) {
                return (int)g;
            }
            if ((int)((long long)sub->flags20.ll >> 10) & 1) {
                return (int)g;
            }
        }
    }
    return 0;
}

int GetFlyPosition(float *out, float *me, float *tgt)
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
                /* The table base is its OWN statement: ROM computes
                   `addiu $v1,$s5,%lo(flyCheckPos)` BEFORE `sll $v0,$s4,4`, which
                   only happens when the address is op0 of the PLUS.  Written as
                   one expression, `fold` sinks the (constant) address to op1 in
                   every spelling measured -- `flyCheckPos[besti]`,
                   `(float *)flyCheckPos + besti*4`, `flyCheckPos[0] + besti*4`,
                   `&flyCheckPos[besti][0]`, `&flyCheckPos[0][besti*4]`,
                   `besti*4 + flyCheckPos[0]`, a struct-typed row, and `p = base;
                   p += besti*4;` -- so `sll` is emitted first, both arms' copy
                   blocks end up in the same registers and jump2 cross-jumps
                   them into one (6 insns short). */
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

/* An _ApproachTarget callback: the ROM's two call sites (0x0016837C and
   0x0016876C) set $f12 as well as $a0/$a1, and _ApproachTarget_Way calls its
   `fn` through (void (*)(char *, void *, float)).  `dist` is unused here. */
void NakaBoss(char *self, void *tgt, float dist)
{
    float bpos[4];
    float mpos[4];
    float ori[4];
    float dir[4];
    char *boy = boyGObj;
    int inc = 0;
    int half = (0x3C - systemStatus[0] * 10) / systemStatus[1] / 4;
    float dist;
    Act *sub;

    if (stage_no != 86 && stage_no != 3 && stage_no != 46) {
        if (tgt != 0) {
            enemy_dodge_to_boy(self);
        }
        return;
    }
    {
        if (boy == 0) {
            return;
        }
        dist = _DistGV(test_CURRENTROOT((int)boy), test_CURRENTROOT((int)self));
        if (GetFlyPosition((float *)((char *)GOBJ_ACT(self)->f_688 + 0x8A0),
                           test_CURRENTROOT((int)self), test_CURRENTROOT((int)boy)) == 2) {
            ACTSendMailCorrect(self, 0x1D);
        }
        if (dist < 360.0) {
            GetRootPosition(bpos, boy);
            GetRootPosition(mpos, self);
            _OrientXZGV(dir, mpos, bpos);
            ori[0] = test_CURRENTORIENT((int)boy)[0];
            ori[1] = test_CURRENTORIENT((int)boy)[1];
            ori[2] = test_CURRENTORIENT((int)boy)[2];
            if (_AbsRotyGV(ori, dir) < 60) {
                if (dist < 270.0) {
                    if (GetFlyPosition((float *)((char *)GOBJ_ACT(self)->f_688 + 0x8A0), mpos,
                                       bpos) == 0) {
                        debug_StdPrintfDummy("not found");
                    }
                    inc = 1;
                    if (half < GOBJ_WORK(self)->f_398) {
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
        sub = GOBJ_ACT(self);
        if (inc != 0) {
            ((ActWork *)sub->f_688)->f_398 = ((ActWork *)sub->f_688)->f_398 + 1;
        } else {
            ((ActWork *)sub->f_688)->f_398 = 0;
        }
    }
}

/* Listing rows 3965-3981: a file-scope helper with no ROM slot of its own,
   expanded once inside subEnemyBrain_ToBoy.  The name is ours. */
static inline int isNearestEnemyToBoy(int self, char *boy, float *pos)
{
    char *found = 0;
    float best = 3.40282347e+38f /* FLT_MAX */;
    char *g;
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
    return (char *)self == found;
}

void subEnemyBrain_ToBoy(volatile int a0)
{
    float v[4];
    float w[4];
    Act *sub = GOBJ_ACT(a0);
    char *boy = boyGObj;
    int cnt = 0;
    int i, j;
    int mode;
    int r;
    unsigned char ret;

    void ChangeBrain_ToAttack(void)
    {
        if (isLiftBoyEnable() != 0) {
            if (GOBJ_ACT(a0)->f_680->f_1E8 == 2) {
                char **tgt = &brainTarget;

                /* RECONSTRUCTION (chain 3 passes 148 to 160): the bytes pin a
                   read of the default brainTargetNone[0] on this statement's line (the
                   listing's 4224: the load sits with the boy load and the slot
                   store, and is held in $s1 across _GetRandom for both
                   expansions' else arms) that is used when jump1 runs and
                   leaves no code of its own: this store to the slot, which the
                   next store overwrites and flow deletes.  What the bytes
                   cannot pin is the text of that read; the same shape sits in
                   the other four arms (here and in ChangeBrain_ToKidnap).  The
                   listing also puts the slot address (`la &brainTarget`) on
                   that one line in all five arms, i.e. one statement did the
                   three things; this text spreads them over three lines and
                   the words are the same. */
                brainTarget = (char *)brainTargetNone[0];
                brainTarget = boyGObj;
                if ((int)(random_unit() * 10.0f) % 100 < GOBJ_ACT(a0)->f_680->f_1FC) {
                    _BrainMode_SetDirect((char *)a0, 12, (int *)tgt);
                } else {
                    _BrainMode_SetDirect((char *)a0, 9, (int *)tgt);
                }
            } else {
                /* RECONSTRUCTION: the default read on the statement's line (the
                   listing's 4235), see the kind == 2 arm above. */
                brainTarget = (char *)brainTargetNone[0];
                brainTarget = boyGObj;
                _BrainMode_SetDirect((char *)a0, 9, (int *)&brainTarget);
            }
        }
    }

    while (1) {
        mode = 0;
        r = (int)(random_unit() * 10.0f) % 100;
        debug_StdPrintfDummy("**toboy function start :: count=[%d]\n", cnt++);
        ret = _ApproachTarget((char *)a0, boy, (char *)sub + 0x120, NakaBoss, 200.0f, 0);
        v[0] = test_CURRENTROOT((void *)a0)[0];
        v[1] = test_CURRENTROOT((void *)a0)[1];
        v[2] = test_CURRENTROOT((void *)a0)[2];
        if (ret != 0) {
            debug_StdPrintfDummy("await start\n");
            for (i = 0; i < (0x3C - systemStatus[0] * 10) / systemStatus[1] * 75 / 60; i++) {
                mode = 0;
                switch (Battle_isCurrentStatus((char *)a0, boy, v)) {
                case 0:
                    break;
                case 1:
                    mode = 4;
                    if (r < GOBJ_ACT(a0)->f_680->f_1F8) {
                        mode = 3;
                    }
                    if (((int)(*(long long *)((char *)GOBJ_ACT(a0)->f_680 + 0x210) >> 1)) & 1) {
                        mode = 3;
                    }
                    if (debug_ignore_dodge != 0) {
                        mode = 4;
                    }
                    if (mode != 3) {
                        if (!(_DistSqGV(test_CURRENTROOT((void *)a0),
                                        test_CURRENTROOT((void *)boyGObj)) < 22500.0f)) {
                            mode = 0;
                        }
                    }
                    break;
                case 2:
                    mode = 2;
                    break;
                case 3:
                    mode = 3;
                    if (GOBJ_ACT(a0)->f_680->liftKind == 3) {
                        mode = 4;
                    }
                    if (debug_ignore_dodge != 0) {
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
                sub->f_34C = 0.0f;
                sub->dir[0] = 0.0f;
                sub->dir[1] = 0.0f;
                sub->dir[2] = 0.0f;
                _DoAwait((char *)a0);
                NakaBoss((char *)a0, 0, 0.0f);
                _ACTWait(1);
            }
            debug_StdPrintfDummy("await end\n");
            if ((((int)(*(long long *)((char *)GOBJ_ACT(a0)->f_680 + 0x210) >> 1)) & 1) == 0) {
                mode = 4;
            }
        } else {
            mode = 1;
        }
    result:
        debug_StdPrintfDummy("toboy ra is [%d]\n", mode);
        if (stage_no == 86 || stage_no == 3 || stage_no == 46) {
            if (mode == 4 || mode == 5) {
                mode = 3;
            }
        }
        switch (mode - 1) {
        case 0:
            ACTSendMailCorrect((char *)a0, 0x100);
            break;
        case 1:
            break;
        case 2:
            if (IsBoyStatus_NotDanger() != 0) {
                if ((char *)girlGObj != 0) {
                    if (GOBJ_ACT(girlGObj)->unk34 != 0x6F) {
                        break;
                    }
                }
            }
            ACTSendMailCorrect((char *)a0, 0x113);
            break;
        case 3:
            if (isNearestEnemyToBoy(a0, (void *)boyGObj, w) &&
                EnemyUtil_isOtherStatus((char *)a0, 0) == 0) {
                ChangeBrain_ToAttack();
            }
            break;
        case 4:
            if (EnemyUtil_isOtherStatus((char *)a0, 0) == 0) {
                ChangeBrain_ToAttack();
            }
        }
        sub->f_34C = 0.0f;
        sub->dir[0] = 0.0f;
        sub->dir[1] = 0.0f;
        sub->dir[2] = 0.0f;
        for (j = 0; j < (0x3C - systemStatus[0] * 10) / systemStatus[1] * 90 / 60; j++) {
            if (mode == 5) {
                if (EnemyUtil_isOtherStatus((char *)a0, 0) == 0) {
                    ChangeBrain_ToAttack();
                }
            }
            _DoAwait((char *)a0);
            NakaBoss((char *)a0, 0, 0.0f);
            _ACTWait(1);
        }
    }
}

inline void subEnemyBrain_BodyGuard(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int tgt = (int)sub->f_14C;
    float *pos = (float *)((char *)sub + 0x120);

    while (1) {
        if (_DistGV(test_CURRENTROOT(a0), test_CURRENTROOT(tgt)) < 200.0f) {
            _ACTWait(1);
        } else {
            if ((unsigned char)_ApproachTarget((char *)a0, (void *)tgt, pos, 0, 100.0f, 0) == 0) {
                sub->f_34C = 0;
                *(int *)((char *)sub + 0x120) = 0;
                *(int *)((char *)sub + 0x124) = 0;
                *(int *)((char *)sub + 0x128) = 0;
                _ACTWait(30);
            }
            sub->f_34C = 0;
            *(int *)((char *)sub + 0x120) = 0;
            *(int *)((char *)sub + 0x124) = 0;
            *(int *)((char *)sub + 0x128) = 0;
            _ACTWait(60);
        }
    }
}

void subEnemyBrain_ToGirl(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    float p0[4];
    float p1[4];
    int i;
    int found;

    void ChangeBrain_ToKidnap(void)
    {
        switch (GOBJ_ACT(a0)->f_680->f_1E8) {
        case 0:
            /* RECONSTRUCTION: the default read on the statement's line (the
               listing's 4476, 4480 and 4484), see ChangeBrain_ToAttack. */
            brainTarget = (char *)brainTargetNone[0];
            brainTarget = girlGObj;
            _BrainMode_SetDirect((char *)a0, 8, (int *)&brainTarget);
            break;
        case 2:
            brainTarget = (char *)brainTargetNone[0];
            brainTarget = girlGObj;
            _BrainMode_SetDirect((char *)a0, 11, (int *)&brainTarget);
            break;
        default:
            brainTarget = (char *)brainTargetNone[0];
            brainTarget = girlGObj;
            _BrainMode_SetDirect((char *)a0, 10, (int *)&brainTarget);
            break;
        }
    }

    char *girl = girlGObj;

    sub->f_34C = 0.0f;
    sub->dir[0] = 0.0f;
    sub->dir[1] = 0.0f;
    sub->dir[2] = 0.0f;
    for (i = 0; i < (0x3C - systemStatus[0] * 10) / systemStatus[1]; i++) {
        _DoAwaitGirl((char *)a0);
        _ACTWait(1);
    }
    found = (unsigned char)_ApproachTarget((char *)a0, girl, (char *)sub + 0x120,
                                           (void *)enemy_dodge, 130.0f, 0);
    GetRootProjectionPosOfGObj(p0, girl);
    GetRootProjectionPosOfGObj(p1, (char *)a0);
    if (50.0f < (p0[1] - p1[1] < 0.0f ? -(p0[1] - p1[1]) : p0[1] - p1[1])) {
        found = 0;
    }
    if (found == 0) {
        sub->f_34C = 0.0f;
        sub->dir[0] = 0.0f;
        sub->dir[1] = 0.0f;
        sub->dir[2] = 0.0f;
        _ACTWait(30);
        eBrainSendMes((void *)a0, 5);
        ACTSendMailCorrect((char *)a0, 0x100);
        _ACTWait(0);
    }
    while (1) {
        debug_StdPrintfDummy("change to kidnap");
        ChangeBrain_ToKidnap();
        _ACTWait(1);
    }
}

int _ApproachTarget_Boss(char *self, void *tgt, void *pos, void *fn, float range,
                         unsigned char flag)
{
    float p0[4];
    float p1[4];
    Act *sub = GOBJ_ACT(self);

    for (;;) {
        GetRootProjectionPosOfGObj(p0, (char *)tgt);
        GetRootProjectionPosOfGObj(p1, self);
        if (fn != 0) {
            ((void (*)(char *, void *, float))fn)(
                self, tgt, _DistGV(test_CURRENTROOT((int)self), test_CURRENTROOT((int)tgt)));
        }
        sub->f_34C = 1.0f;
        _OrientXZGV((float *)pos, p0, p1);
        if (_DistxzSqGV(p0, p1) < 160000.0f && -50.0f < -(p0[1] - p1[1]) &&
            p1[1] - p0[1] < 500.0f && enemyCheckTurnAngle(self) == 0 && sub->unk34 != 10) {
            return 1;
        }
        _ACTWait(1);
    }
}

int flyMailCore(void *self)
{
    int flyLow = 0;
    int flyHigh = 0;
    int ret = 0;
    int gen;

    switch (CanThisEnemyFly(self)) {
    case 1:
        flyLow = 1;
        break;
    case 2:
        flyLow = 1;
        flyHigh = 1;
        break;
    }
    if (isEnemyActive((int *)self) == 0) {
        goto end;
    }
    if (IsEnemyBrainToGenerator((char *)self, &gen)) {
        if (flyHigh == 0 && debug_enemy_fly_with_girl == 0) {
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

inline int FlyMail(void *a0)
{
    int x = GOBJ_ACT(a0)->f_10;
    if (x < 0xC) {
        return -1;
    }
    return flyMailCore(a0);
}

/* static inline of the 2001 source, listing rows 4681-4689, which lie outside
   every function's own line span; the listing expands them twice inside
   _ApproachTarget_Way.  Name is descriptive, not recovered. */
static inline unsigned char waitEnemyFly(char *self)
{
    Act *sub = GOBJ_ACT(self);

    while (sub->unk34 != 6) {
        if (FlyMail(self) == 0) {
            return 0;
        }
        _ACTWait(1);
    }
    return 1;
}

/* static inline of the 2001 source, listing rows 4665-4672.  Name is
   descriptive, not recovered. */
static inline int flyLimitMail(char *self, float *rp)
{
    Act *sub = GOBJ_ACT(self);

    if (sub->f_10 < 0xC) {
        return 0;
    }
    GetRootPosition(rp, self);
    if (GetFlyLimitClearance(rp) == 0) {
        return 0;
    }
    flyMailCore(self);
    return 1;
}

int _ApproachTarget_Way(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag)
{
    float p0[4];
    float p1[4];
    float rp[4];
    Act *sub = GOBJ_ACT(self);
    int i;
    int ret;

    GetRootProjectionPosOfGObj(p0, (char *)tgt);
    GetRootProjectionPosOfGObj(p1, self);
    for (i = 0; i < (0x3C - systemStatus[0] * 10) / systemStatus[1] * 40 / 60; i++) {
        if (IsSelectID_EnemyCtrl(*(int *)(self + 8)) != 0) {
            break;
        }
        _ACTWait(1);
    }
    ret = ACTWayMove_BeginDetail(self, p1, p0, tgt, 0, 0);
    if (ret == 0) {
        ret = waitEnemyFly(self);
        if (ret == 0) {
            return 0;
        }
    }
    while (1) {
        GetRootProjectionPosOfGObj(p0, (char *)tgt);
        GetRootProjectionPosOfGObj(p1, self);
        if (!(_DistSqGV(p1, p0) < 1440000.0f) ||
            140.0f < ((p1[1] - p0[1] < 0.0f) ? -(p1[1] - p0[1]) : (p1[1] - p0[1]))) {
            flyLimitMail(self, rp);
        }
        if (fn != 0) {
            ((void (*)(char *, void *, float))fn)(
                self, tgt, _DistGV(test_CURRENTROOT((int)self), test_CURRENTROOT((int)tgt)));
        }
        if (sub->unk34 == 6) {
            _ACTWait(1);
            continue;
        }
        if (ACTWayMove_NextDetail(self, pos, p0, 0, 0) == 0) {
            if (waitEnemyFly(self) == 0) {
                return 0;
            }
        }
        *(float *)((char *)pos + 0) = sub->f_3E0;
        *(float *)((char *)pos + 4) = sub->f_3E4;
        *(float *)((char *)pos + 8) = sub->f_3E8;
        if (((int)(((ActStatusWord *)((char *)sub + 0x3F0))->q >> 17)) & 1) {
            if (debug_fly_limit_test != 0) {
                static int col[4] = {255, 100, 0, 128};

                MatrixDrive_PushMatrix();
                GetRootPosition(rp, self);
                _UnitMatrix(MatrixDrive_GetMatrix());
                MatrixDrive_TransMatrixV((char *)rp);
                gif_StartPacketPri(11);
                prim_DispWireSphere(100.0f, col, 4, 4);
                gif_EndPacket();
                MatrixDrive_PopMatrix();
            }
            FlyMail(self);
        }
        if (*(int *)(self + 8) == 0xEAD && (((int)(sub->flags20.ll >> 39)) & 1)) {
            FlyMail(self);
        }
        if (stage_no == 9 && CheckFloorAttribute(self, 0x100000) != 0 &&
            (tgt == (void *)boyGObj || tgt == (void *)((char *)girlGObj)) &&
            _DistxzSqGV(test_CURRENTROOT((int)self), test_CURRENTROOT((int)tgt)) < 40000.0f &&
            ((test_CURRENTROOT((int)self)[1] - test_CURRENTROOT((int)tgt)[1] < 0.0f)
                 ? -(test_CURRENTROOT((int)self)[1] - test_CURRENTROOT((int)tgt)[1])
                 : (test_CURRENTROOT((int)self)[1] - test_CURRENTROOT((int)tgt)[1])) < 150.0f) {
            return 1;
        }
        if (tgt == (void *)((char *)girlGObj) && _DistxzSqGV(p1, p0) < 10000.0f &&
            ((p1[1] - p0[1] < 0.0f) ? -(p1[1] - p0[1]) : (p1[1] - p0[1])) < 50.0f &&
            WayMove_CheckCollis(p1, p0, 0, 0) == 0) {
            return 1;
        }
        if ((((int)(((ActStatusWord *)((char *)sub + 0x3F0))->q >> 17)) & 1) == 0 &&
            sub->f_3F8 < range && sub->f_3FC < 100.0f &&
            ((sub->f_3FC < 0.0f) ? -sub->f_3FC : sub->f_3FC) < 200.0f) {
            return 1;
        }
        if (sub->f_3F8 < 200.0f) {
            sub->f_34C = 0.5f;
        } else if (ACTWay_IsMustWalkFromWay(self) != 0) {
            sub->f_34C = 0.5f;
        } else {
            sub->f_34C = 1.0f;
        }
        if (flag != 0) {
            SetMotionDirection(self, (float *)((char *)sub + 0x120));
            flag = 0;
        }
        _ACTWait(1);
    }
    /* Disabled in retail: the motion-request timer and mail reports.  What
       the bytes pin: their three texts in .rodata after subEnemyBrain_ToGirl's
       "change to kidnap" and before actEnemyStart's trace, with no
       instruction; the listing gives this function no row between the loop's
       last statement (4842) and its closing line (5060).  What they cannot:
       the statements around them, the condition and the mail number the
       third one printed. */
    if (0) {
        debug_StdPrintfDummy("_ACTMotReqTimer wait\n");
        debug_StdPrintfDummy("_ACTMotReqTimer error loop\n");
        debug_StdPrintfDummy("\tmail[%d] can not accept\n");
    }
}

inline int _ApproachTarget(char *self, void *tgt, void *pos, void *fn, float range,
                           unsigned char flag)
{
    if (GOBJ_ACT(self)->f_680->liftKind != 3) {
        return _ApproachTarget_Way(self, tgt, pos, fn, range, flag);
    } else {
        return _ApproachTarget_Boss(self, tgt, pos, fn, range, flag);
    }
}

inline int isEnemyKidnapEnable(int *self)
{
    if (GOBJ_ACT(self)->f_680->liftKind == 0) {
        return 0;
    }
    return actEnemyFlagCheckActive(self);
}

inline int GetEnemyType(float x, float y, float z)
{
    return 1;
}

inline int GetEnemyTypeFromGObj(char *a0)
{
    return GOBJ_ACT(a0)->f_680->liftKind;
}

inline int GetMotherGeneratorLabelAskEnemy(char *a0)
{
    return GOBJ_WORK(a0)->f_464;
}

inline int GetMotherGeneratorGObjAskEnemy(char *a0)
{
    return GOBJ_WORK(a0)->f_468;
}

/* Listing rows 5128-5301. What the bytes pin, each read off the scheduler's
 * dependences: the bit-51 store to the actor word is a union access (the
 * gobj+0x164 chase for the ==3 test waits for it); the four 0.05f stores are
 * float stores through a union view of the gobj+0x15C slot (the slot is
 * re-read before each, the int gobj+0x164 load before them survives and
 * gcse reuses it after the if); the character-kind store at act+0x48 is not
 * int-typed (the gFlagGameClear load issues ahead of it); each life pair is one
 * chained assignment (rows 5286 and 5288). What they cannot pin: the names of
 * the union and enum types and their other members. */
void actEnemyStart(char *self)
{
    char *act;
    int alive;
    float life;

    debug_StdPrintfDummy("actEnemyStart:%p\n", self);
    act = actInitialize(self);
    actInitialize_ext_charcter(self);
    actInitialize_only_charcter(self);
    actInitialize_geo(self);
    if (*(int *)(self + 8) == 3757) {
        *(long long *)(act + 0x20) = *(long long *)(act + 0x20) | 0x40000000;
    }
    ACTGame_LwsEffectInit(self);
    ACTParaStatus_Init(self);
    _ACTCharStatus_Init((int **)self);
    *(int *)(GOBJ_ACT(self)->f_688 + 0x378) = InitMultiBgaManager(1);
    {
        EnemyStartRec p[4] = {
            {0, 35, 18, 90, 0, _ACTGame_GetParamF(20), 369.0f, 1},
            {1, 0, 18, 50, 0, _ACTGame_GetParamF(21), 369.0f, 0},
            {2, 34, 22, 25, 50, _ACTGame_GetParamF(22), 369.0f, 0},
            {2, 33, 22, 0, 100, 3.40282347e+38f /* FLT_MAX */, 370.0f, 1},
        };
        unsigned long long bit;

        GOBJ_ACT(self)->f_680->bodySize = *(float *)((int)GOBJ_SUB(self)->p_870 + 0x20);
        GOBJ_ACT(self)->f_680->liftKind = 1;
        GOBJ_ACT(self)->f_680->f_1E8 = p[1].mode;
        GOBJ_ACT(self)->f_680->f_1F0 = p[1].f04;
        GOBJ_ACT(self)->f_680->f_1F4 = p[1].f08;
        GOBJ_ACT(self)->f_680->f_1F8 = p[1].f0C;
        GOBJ_ACT(self)->f_680->f_1FC = p[1].f10;
        *(float *)(act + 0x1E4) = p[1].f14;
        GOBJ_ACT(self)->f_680->f_200 = (int)p[1].f18;
        GOBJ_ACT(self)->f_680->f_20C = 3;
        bit = p[1].f1C;
        ((ActStatusWord *)(act + 0x18))->q =
            (((ActStatusWord *)(act + 0x18))->q & ~(1ULL << 51)) | ((bit & 1) << 51);
    }
    if (GOBJ_ACT(self)->f_680->liftKind == 3) {
        *(float *)(((EnemySubSlot *)(self + 0x15C))->p + 0x45C) = 0.05f;
        *(float *)(((EnemySubSlot *)(self + 0x15C))->p + 0x460) = 0.05f;
        *(float *)(((EnemySubSlot *)(self + 0x15C))->p + 0x464) = 0.05f;
        *(float *)(((EnemySubSlot *)(self + 0x15C))->p + 0x468) = 0.05f;
    }
    GOBJ_ACT(self)->f_680->battleType = debug_enemy_battle_type;
    setBattleStatus(self);
    alive = 0;
    if (actEnemyFlagCheckDead((int *)self) != 0) {
        alive = 1;
    }
    if (alive != 0) {
        *(long long *)(act + 0x18) = *(long long *)(act + 0x18) & ~(1LL << 32);
        *(long long *)(act + 0x18) = *(long long *)(act + 0x18) & ~(1LL << 33);
    }
    _ACTWait(1);
    GOBJ_WORK(self)->f_464 = GetMotherGenerator(*(int *)(self + 8));
    if (GOBJ_WORK(self)->f_464 != -1) {
        GOBJ_WORK(self)->f_468 = isysGObjSearchFromObjLayoutID(GOBJ_WORK(self)->f_464);
    }
    *(char **)(act + 0xD0) = D_002A84F8;
    if (debug_brain_flag != 0) {
        actCreateSubThread((void *)subEnemyBrainMain, (void *)20);
    }
    actCreateSubThread((void *)subEnemyControl, (void *)21);
    actCreateSubThread((void *)subEnemyCollision, (void *)21);
    actCreateSubThread((void *)subCommonIdle, (void *)21);
    *(char **)(act + 0xD4) = D_002A84F8 + 0x78;
    *(ActKind *)(act + 0x48) = ACT_KIND_ENEMY;
    life = getEnemyRestartLife(self);
    *(float *)(act + 0x1E0) = *(float *)(act + 0x1E4) = life;
    if (life < 10.0f) {
        *(float *)(act + 0x1E0) = *(float *)(act + 0x1E4) = 10.0f;
    }
    *(int *)(act + 0x350) = 0;
    ACTSendMailCorrect(self, 199);
    if (alive != 0) {
        actEnemyHyde((int *)self);
    }
    _ACTWait(0);
}

inline void subEnemyBrain_Irregular(volatile int a0)
{
    EnemyBrainWork *sub = *(EnemyBrainWork **)(a0 + 0x164);

    sub->flags &= ~(1LL << 34);
    eBrainSendMes(a0, 4);
    if (isEnemyCarriedByGirl(a0)) {
        afterCommonCarry(a0);
    }
    while (1) {
        _ACTWait(30);
        _BrainMode_SetDirect((char *)a0, 0, 0);
    }
}

void subEnemyBrain_Attack(volatile int a0)
{
    int i;

    for (i = 0; i < (0x3C - systemStatus[0] * 10) / systemStatus[1] / 6; i++) {
        enemyDodgeSendMail((char *)a0);
        _DoAwait((char *)a0);
        if (_MustChase(a0) != 0) {
            break;
        }
        _ACTWait(1);
    }
    for (i = 0; i < (0x3C - systemStatus[0] * 10) / systemStatus[1] * 100 / 60; i++) {
        if (i < (0x3C - systemStatus[0] * 10) / systemStatus[1] * 50 / 60) {
            enemyDodgeSendMail((char *)a0);
        }
        _DoAwait((char *)a0);
        if ((0x3C - systemStatus[0] * 10) / systemStatus[1] * 80 / 60 < i) {
            if (_MustChase(a0) != 0) {
                break;
            }
        }
        _ACTWait(1);
    }
    _BrainMode_SetDirect((char *)a0, 0, 0);
    _ACTWait(0);
}

void subEnemyBrain_Cling(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int tgt = GOBJ_ACT(a0)->f_680->target;
    float v[4];

    GOBJ_ACT(a0)->f_680->f_21C = tgt;
    _OrientXZGV(v, test_CURRENTROOT(tgt), test_CURRENTROOT(a0));
    sub->dir[0] = v[0];
    sub->dir[1] = v[1];
    sub->dir[2] = v[2];
    SetMotionDirection((void *)a0, v);
    ACTSendMailCorrect((void *)a0, 0xC2);
    _ACTWait(1);
    _ACTWait(1);
    while (1) {
        if (sub->unk34 == 4 || sub->unk34 == 0x10) {
            if (_DistSqGV(test_CURRENTROOT(tgt), test_CURRENTROOT(a0)) < 3600.0f) {
                ACTSendMailCorrect((void *)a0, 0xD0);
            }
        } else {
            _ACTWait(30);
            _BrainMode_SetDirect((char *)a0, 0, 0);
        }
        _ACTWait(1);
    }
}

inline void subEnemyBrain_Shoulder(volatile int a0)
{
    float *dir = (float *)((char *)GOBJ_ACT(a0) + 0x120);
    float *girl = test_CURRENTROOT((int)((char *)girlGObj));
    float *me = test_CURRENTROOT(a0);
    _OrientXZGV(dir, girl, me);
    SetMotionDirection((void *)a0, dir);
    ACTSendMailCorrect((void *)a0, 0x162);
    while (1) {
        _ACTWait(120);
        _BrainMode_SetDirect((char *)a0, 0, 0);
    }
}

inline void subEnemyBrain_Pickup(volatile int a0)
{
    ACTSendMailCorrect((void *)a0, 0x16C);
    while (1) {
        _ACTWait(120);
        _BrainMode_SetDirect((char *)a0, 0, 0);
    }
}

inline void subEnemyBrain_Bodyslam(volatile int a0)
{
    if (GOBJ_ACT(a0)->f_680->liftKind == 3) {
        ACTSendMailCorrect((void *)a0, 0x175);
    } else {
        ACTSendMailCorrect((void *)a0, 0x173);
    }
    while (1) {
        _ACTWait(120);
        _BrainMode_SetDirect((char *)a0, 0, 0);
    }
}

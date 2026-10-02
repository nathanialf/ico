/*
 * ico2/fumi/include/enemy_act.h
 *
 * The declarations of what enemy_act.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ENEMY_ACT_H
#define ENEMY_ACT_H

#include "typedef.h"
#include "chain.h"

/* The target a brain-mode request carries (_BrainMode_SetDirect). */
typedef struct { /* field names derived */
    GObj *gobj;
} BrainModeTarget; /* derived name */

/* A 64-bit flag word with a byte view (the enemy work's +0x210 status word and
   the sub record's +0x20 word).  A write through the byte view may alias the
   pointers that reach it, so each arm below re-reads self->sub->enemy for its
   second assignment.  The two-word view is the enemy work's: +0x210 is one
   64-bit word and +0x214, the requested brain target, a record inside it. */

typedef union { /* field names derived */
    char c[8];
    long long ll;

    struct {
        int bits;
        BrainModeTarget reqTarget;
    } w;
} EnemyStatusFlags; /* derived name */

/* The enemy work at sub+0x680: the running brain mode (+0x204) and the one
   _BrainMode_SetDirect requests (+0x208), the requested target inside the
   status word and the running target (+0x218), a countdown (+0x224). */
typedef struct EnemyBattleWork { /* field names derived */
    char pad0[84];
    unsigned int speedRatioPri; /* 0x54 */
    float speedRatio;           /* 0x58 */
    int paraTimer;              /* 0x5C */
    int paraRandom;             /* 0x60 */
    char pad64[12];
    float corrPosX; /* 0x70 */
    float corrPosY; /* 0x74 */
    float corrPosZ; /* 0x78 */
    char pad7C[4];
    float corrDirX; /* 0x80 */
    float corrDirY; /* 0x84 */
    float corrDirZ; /* 0x88 */
    char pad8C[4];
    float corrDstX; /* 0x90 */
    float corrDstY; /* 0x94 */
    float corrDstZ; /* 0x98 */
    char pad9C[4];
    float corrDstDirX; /* 0xA0 */
    float corrDstDirY; /* 0xA4 */
    float corrDstDirZ; /* 0xA8 */
    char padAC[4];
    int corrFrames; /* 0xB0 */
    int corrCount;  /* 0xB4 */
    char padB8[4];
    unsigned int corrFlags; /* 0xBC */
    int jumpOrient;         /* 0xC0 */
    char padC4[8];
    int liftLevel;    /* 0xCC */
    int floorAttrOff; /* 0xD0 */
    char padD4[12];
    float hitDir[4];      /* 0xE0, the direction of the last attack that hit (AttackGenerate) */
    short hitNodes[100];  /* 0xF0, the nodes that attack hit, -1 terminated (AttackCheckHit) */
    struct BgaDisp *lwsEffect; /* 0x1B8, the guard effect's multi-BGA slots */
    char pad1BC[4];
    float ropeCliffX; /* 0x1C0 */
    float ropeCliffY; /* 0x1C4 */
    float ropeCliffZ; /* 0x1C8 */
    char pad1CC[20];
    float bodySize;
    int liftKind;
    int sizeClass; /* 0x1E8 */
    int battleType;
    int paraStatus;    /* 0x1F0 */
    int clingNode;     /* 0x1F4 */
    int attackChance;  /* 0x1F8 */
    int attackChance2; /* 0x1FC */
    int bodyslamMail;  /* 0x200 */
    int mode;
    int reqMode;
    int bossLife; /* 0x20C */
    EnemyStatusFlags flags;
    int target;
    int clingReq;    /* 0x21C */
    int clingTarget; /* 0x220 */
    int waitCount;
    int slowTimer;
    int liftedObj;   /* 0x22C */
    float readyPosX; /* 0x230 */
    float readyPosY; /* 0x234 */
    float readyPosZ; /* 0x238 */
    char pad23C[4];
    float readyDirX; /* 0x240 */
    float readyDirY; /* 0x244 */
    float readyDirZ; /* 0x248 */
    char pad24C[4];
    int sofaWake;         /* 0x250 the frames on the sofa, cleared on waking */
    int sofaWakeTime;     /* 0x254 the frames after which the sofa sends mail 0x73 */
    int dirSmoothFrames;  /* 0x258 */
    int dirSmoothFrames2; /* 0x25C */
    int clingedFrames;    /* 0x260 */
    char pad264[12];
    float slipDirX; /* 0x270 */
    float slipDirY; /* 0x274 */
    float slipDirZ; /* 0x278 */
    char pad27C[20];
    int ladderUpStep;   /* 0x290 */
    int ladderDownStep; /* 0x294 */
    char pad298[4];
    int stoneLevel; /* 0x29C */
    int stonePair;  /* 0x2A0 */
    int word2A4;    /* 0x2A4 */
    int stoneHitNoWeapon; /* 0x2A8, queen-battle stone hits taken with no weapon */
    int stoneHitWeapon;   /* 0x2AC, the same hits taken with a weapon */
    int word2B0;    /* 0x2B0 */
    char pad2B4[44];
    struct GObj *rescueObj; /* 0x2E0 */
    char pad2E4[12];
    float rescueBoyPos[4];  /* 0x2F0, where the boy stands to pull the girl up, 60 short of her */
    float rescueGirlPos[4]; /* 0x300, the girl's position, 50 up: [1] is the height she is set to */
    int boxBarSound; /* 0x310 */
    char pad314[28];
    float climbOrient[4]; /* 0x330 the orient of the chain or wall climbed */
    float climbPos[4];    /* 0x340 the climb's position */
    ClimbCol climbCol;    /* 0x350 the wall the climb holds, as GetChainClimbCollision fills it */
    struct GObj *climbObj; /* 0x35C the chain or cage climbed */
} EnemyBattleWork;   /* derived name */

/* enemy_act.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void funcEnemyAiGetGirl(struct GObj *self);
void actEnemyStand(GObj *volatile self);
void actEnemyWalk(GObj *volatile self);
void actEnemyRun(GObj *volatile self);
void actEnemyHang(GObj *volatile self);
void actEnemyCarry(GObj *volatile self);
void actEnemyBodyslam(GObj *volatile self);
void actEnemyBodyslamFail(GObj *volatile self);
void actEnemyNest(GObj *volatile self);
void funcEnemyCarryFail(struct GObj *self);
void actEnemyHyde(GObj *self);
inline void actEnemyFlagOnFree(GObj *self);
inline void afterCommonCarry(GObj *volatile self);
void actEnemyFlagOnDead(GObj *self);
int EnemyBrainStatus_Boy(struct GObj *self);
int EnemyBrainStatus_Girl(struct GObj *self);
inline int actEnemyFlagCheckDead(GObj *self);
inline int actEnemyFlagCheckActive(GObj *self);
int ACTEnemyForceSwitchToCarry(GObj *self);
int actEnemy_GetClingTarget(struct GObj *self);
int actEnemy_isNormalEnemy(struct GObj *self);
int actEnemy_isLargeEnemy(struct GObj *self);
int actEnemy_isSmallEnemy(struct GObj *self);
int IsEnemyBrainToGenerator(GObj *self, GObj **out);
int IsEnemyBrainToBoy(struct GObj *self);
int GetEnemyTypeFromGObj(struct GObj *obj);
int GetEnemyType(float x, float y, float z);
int isEnemyKidnapEnable(GObj *self);
inline int isEnemyActive(GObj *self);
int GetMotherGeneratorLabelAskEnemy(struct GObj *enemy);
struct GObj *GetMotherGeneratorGObjAskEnemy(struct GObj *enemy);
inline void subEnemyBrain_Idle(GObj *volatile self);
void subEnemyBrain_Await(GObj *volatile self);
void subEnemyBrain_FindGirl(GObj *volatile self);
void subEnemyBrain_BodyGuard(GObj *volatile self);
void subEnemyBrain_Shoulder(GObj *volatile self);
void subEnemyBrain_Pickup(GObj *volatile self);
void subEnemyBrain_Bodyslam(GObj *volatile self);
void subEnemyBrain_Irregular(GObj *volatile self);
inline void _BrainMode_SetDirect(GObj *self, int mode, BrainModeTarget *tgt);
inline void EnemyUtil_TurnToBoy(GObj *self, GObj *tgt, int smooze);
inline int FlyMail(void *self);
void boss_effect_callback(int id);
void motEnemyStand(GObj *volatile self);
void motEnemyWalk(GObj *volatile self);
void motEnemyRun(GObj *volatile self);
void actEnemyJump(GObj *volatile self);
inline int EnemyUtil_isOtherStatus(GObj *self, int mode);
int isEnemyHyde(GObj *self);

inline int _ApproachTarget(GObj *self, void *tgt, void *pos, void *fn, float range,
                           unsigned char flag);

void afterEnemyBodylift(GObj *volatile self);

void actEnemyRestart(GObj *self, float *pos, float *dir, int kind, GObj *mother);
/* enemy_act.o's last .sdata global (act.c sets it) */
extern int entesty;
void subEnemyControl(GObj *volatile self);
void subEnemyCollision(GObj *volatile self);
void subEnemyBrainMain(GObj *volatile self);

#endif /* ENEMY_ACT_H */

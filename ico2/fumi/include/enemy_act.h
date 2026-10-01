/*
 * ico2/fumi/include/enemy_act.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what enemy_act.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ENEMY_ACT_H
#define ENEMY_ACT_H

#include "typedef.h"

/* A 64-bit flag word with a byte view (the enemy work's +0x210 status word and
   the sub record's +0x20 word); the union is what makes a write to it alias
   the pointer chase that reaches it, which is why ROM re-walks
   self->sub->enemy for the second assignment of every arm below.  The two-word
   view is the enemy work's: the ROM reads and writes +0x210 as one 64-bit word
   and +0x214, the requested brain target, as an int inside it.  The member
   names are ours. */
typedef union {
    char c[8];
    long long ll;

    struct {
        int bits;
        int reqTarget;
    } w;
} EnemyStatusFlags;

/* The enemy work at sub+0x680: the running brain mode (+0x204) and the one
   _BrainMode_SetDirect requests (+0x208), the requested target inside the
   status word and the running target (+0x218), a countdown (+0x224).  The
   field names are ours. */
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
    char padD4[228];
    int lwsEffect; /* 0x1B8 */
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
    int sofaWake;         /* 0x250 */
    int word254;          /* 0x254 */
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
    int count2A8;   /* 0x2A8 */
    int count2AC;   /* 0x2AC */
    int word2B0;    /* 0x2B0 */
    char pad2B4[44];
    char *rescueObj; /* 0x2E0 */
    char pad2E4[32];
    float rescueY; /* 0x304 */
    char pad308[8];
    int boxBarSound; /* 0x310 */
} EnemyBattleWork;

/* enemy_act.c defines these `inline`, so the compiler emits them after the
 * rest of the file in the order they are first declared: this list is the
 * ROM's order of the TU's closing run, from funcEnemyAiGetGirl to
 * afterEnemyBodylift. */
void funcEnemyAiGetGirl(struct GObj *a0);
void actEnemyStand(GObj *volatile a0);
void actEnemyWalk(GObj *volatile a0);
void actEnemyRun(GObj *volatile a0);
void actEnemyHang(GObj *volatile a0);
void actEnemyCarry(GObj *volatile a0);
void actEnemyBodyslam(GObj *volatile a0);
void actEnemyBodyslamFail(GObj *volatile a0);
void actEnemyNest(GObj *volatile a0);
void funcEnemyCarryFail(struct GObj *a0);
void actEnemyHyde(int *self);
inline void actEnemyFlagOnFree(int *a0);
inline void afterCommonCarry(GObj *volatile a0);
void actEnemyFlagOnDead(int *a0);
int EnemyBrainStatus_Boy(struct GObj *a0);
int EnemyBrainStatus_Girl(struct GObj *a0);
inline int actEnemyFlagCheckDead(int *a0);
inline int actEnemyFlagCheckActive(int *a0);
int ACTEnemyForceSwitchToCarry(GObj *a0);
int actEnemy_GetClingTarget(struct GObj *a0);
int actEnemy_isNormalEnemy(struct GObj *a0);
int actEnemy_isLargeEnemy(struct GObj *a0);
int actEnemy_isSmallEnemy(struct GObj *a0);
int IsEnemyBrainToGenerator(char *a0, int *out);
int IsEnemyBrainToBoy(struct GObj *self);
int GetEnemyTypeFromGObj(struct GObj *a0);
int GetEnemyType(float x, float y, float z);
int isEnemyKidnapEnable(int *self);
inline int isEnemyActive(int *self);
int GetMotherGeneratorLabelAskEnemy(struct GObj *a0);
int GetMotherGeneratorGObjAskEnemy(struct GObj *a0);
inline void subEnemyBrain_Idle(GObj *volatile a0);
void subEnemyBrain_Await(GObj *volatile a0);
void subEnemyBrain_FindGirl(GObj *volatile a0);
void subEnemyBrain_BodyGuard(GObj *volatile a0);
void subEnemyBrain_Shoulder(GObj *volatile a0);
void subEnemyBrain_Pickup(GObj *volatile a0);
void subEnemyBrain_Bodyslam(GObj *volatile a0);
void subEnemyBrain_Irregular(GObj *volatile a0);
inline void _BrainMode_SetDirect(char *a0, int a1, int *a2);
inline void EnemyUtil_TurnToBoy(GObj *self, GObj *tgt, int smooze);
inline int FlyMail(void *a0);
void boss_effect_callback(int id);
void motEnemyStand(GObj *volatile a0);
void motEnemyWalk(GObj *volatile a0);
void motEnemyRun(GObj *volatile a0);
void actEnemyJump(GObj *volatile a0);
inline int EnemyUtil_isOtherStatus(char *self, int mode);
int isEnemyHyde(int *a0);
inline int _ApproachTarget(GObj *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
void afterEnemyBodylift(GObj *volatile a0);

int _ApproachTarget_Boss(GObj *self, void *tgt, void *pos, void *fn, float range,
                         unsigned char flag);

int _ApproachTarget_Way(GObj *self, void *tgt, void *pos, void *fn, float range,
                        unsigned char flag);

int actEnemyForceSwitchToCarry(void *a0);
void actEnemyRestart(GObj *self, float *pos, float *dir, int kind, int mot);
void boss_effect_start(char *self, int id);
int flyMailCore(void *self);
/* MAIN.MAP global of enemy_act.o's .sdata, the run's last word (act.c sets it) */
extern int entesty;
void subEnemyControl(GObj *volatile a0);
void subEnemyCollision(GObj *volatile a0);
void subEnemyBrainMain(GObj *volatile a0);

#endif /* ENEMY_ACT_H */

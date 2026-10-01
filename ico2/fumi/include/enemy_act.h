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
typedef struct EnemyBattleWork {
    char _pad0[0x54];
    unsigned int f_54; /* 0x54 */
    float f_58;        /* 0x58 */
    int f_5C;          /* 0x5C */
    int f_60;          /* 0x60 */
    char _pad64[0xC];
    float f_70; /* 0x70 */
    float f_74; /* 0x74 */
    float f_78; /* 0x78 */
    char _pad7C[0x4];
    float f_80; /* 0x80 */
    float f_84; /* 0x84 */
    float f_88; /* 0x88 */
    char _pad8C[0x4];
    float f_90; /* 0x90 */
    float f_94; /* 0x94 */
    float f_98; /* 0x98 */
    char _pad9C[0x4];
    float f_A0; /* 0xA0 */
    float f_A4; /* 0xA4 */
    float f_A8; /* 0xA8 */
    char _padAC[0x4];
    int f_B0; /* 0xB0 */
    int f_B4; /* 0xB4 */
    char _padB8[0x4];
    unsigned int f_BC; /* 0xBC */
    int f_C0;          /* 0xC0 */
    char _padC4[0x8];
    int f_CC; /* 0xCC */
    int f_D0; /* 0xD0 */
    char _padD4[0xE4];
    int f_1B8; /* 0x1B8 */
    char _pad1BC[0x4];
    float f_1C0; /* 0x1C0 */
    float f_1C4; /* 0x1C4 */
    float f_1C8; /* 0x1C8 */
    char _pad1CC[0x14];
    float bodySize;
    int liftKind;
    int f_1E8; /* 0x1E8 */
    int battleType;
    int f_1F0; /* 0x1F0 */
    int f_1F4; /* 0x1F4 */
    int f_1F8; /* 0x1F8 */
    int f_1FC; /* 0x1FC */
    int f_200; /* 0x200 */
    int mode;
    int reqMode;
    int f_20C; /* 0x20C */
    EnemyStatusFlags flags;
    int target;
    int f_21C; /* 0x21C */
    int f_220; /* 0x220 */
    int waitCount;
    int slowTimer;
    int f_22C;   /* 0x22C */
    float f_230; /* 0x230 */
    float f_234; /* 0x234 */
    float f_238; /* 0x238 */
    char _pad23C[0x4];
    float f_240; /* 0x240 */
    float f_244; /* 0x244 */
    float f_248; /* 0x248 */
    char _pad24C[0x4];
    int f_250; /* 0x250 */
    int f_254; /* 0x254 */
    int f_258; /* 0x258 */
    int f_25C; /* 0x25C */
    int f_260; /* 0x260 */
    char _pad264[0xC];
    float f_270; /* 0x270 */
    float f_274; /* 0x274 */
    float f_278; /* 0x278 */
    char _pad27C[0x14];
    int f_290; /* 0x290 */
    int f_294; /* 0x294 */
    char _pad298[0x4];
    int f_29C; /* 0x29C */
    int f_2A0; /* 0x2A0 */
    int f_2A4; /* 0x2A4 */
    int f_2A8; /* 0x2A8 */
    int f_2AC; /* 0x2AC */
    int f_2B0; /* 0x2B0 */
    char _pad2B4[0x2C];
    char *f_2E0; /* 0x2E0 */
    char _pad2E4[0x20];
    float f_304; /* 0x304 */
    char _pad308[0x8];
    int f_310; /* 0x310 */
} EnemyBattleWork;

/* enemy_act.c defines these `inline`, so the compiler emits them after the
 * rest of the file in the order they are first declared: this list is the
 * ROM's order of the TU's closing run, from funcEnemyAiGetGirl to
 * afterEnemyBodylift. */
void funcEnemyAiGetGirl(int a0);
void actEnemyStand(volatile int a0);
void actEnemyWalk(volatile int a0);
void actEnemyRun(volatile int a0);
void actEnemyHang(volatile int a0);
void actEnemyCarry(volatile int a0);
void actEnemyBodyslam(volatile int a0);
void actEnemyBodyslamFail(volatile int a0);
void actEnemyNest(volatile int a0);
void funcEnemyCarryFail(char *a0);
void actEnemyHyde(int *self);
void actEnemyFlagOnFree(int *a0);
void afterCommonCarry(volatile int a0);
void actEnemyFlagOnDead(int *a0);
int EnemyBrainStatus_Boy(char *a0);
int EnemyBrainStatus_Girl(char *a0);
int actEnemyFlagCheckDead(int *a0);
int actEnemyFlagCheckActive(int *a0);
int ACTEnemyForceSwitchToCarry(char *a0);
int actEnemy_GetClingTarget(char *a0);
int actEnemy_isNormalEnemy(char *a0);
int actEnemy_isLargeEnemy(char *a0);
int actEnemy_isSmallEnemy(char *a0);
int IsEnemyBrainToGenerator(char *a0, int *out);
int IsEnemyBrainToBoy(char *self);
int GetEnemyTypeFromGObj(char *a0);
int GetEnemyType(float x, float y, float z);
int isEnemyKidnapEnable(int *self);
int isEnemyActive(int *self);
int GetMotherGeneratorLabelAskEnemy(char *a0);
int GetMotherGeneratorGObjAskEnemy(char *a0);
void subEnemyBrain_Idle(volatile int a0);
void subEnemyBrain_Await(volatile int a0);
void subEnemyBrain_FindGirl(volatile int a0);
void subEnemyBrain_BodyGuard(volatile int a0);
void subEnemyBrain_Shoulder(volatile int a0);
void subEnemyBrain_Pickup(volatile int a0);
void subEnemyBrain_Bodyslam(volatile int a0);
void subEnemyBrain_Irregular(volatile int a0);
void _BrainMode_SetDirect(char *a0, int a1, int *a2);
void EnemyUtil_TurnToBoy(char *self, int tgt, int smooze);
int FlyMail(void *a0);
void boss_effect_callback(int id);
void motEnemyStand(volatile int a0);
void motEnemyWalk(volatile int a0);
void motEnemyRun(volatile int a0);
void actEnemyJump(volatile int a0);
int EnemyUtil_isOtherStatus(char *self, int mode);
int isEnemyHyde(int *a0);
int _ApproachTarget(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
void afterEnemyBodylift(volatile int a0);

int _ApproachTarget_Boss(char *self, void *tgt, void *pos, void *fn, float range,
                         unsigned char flag);
int _ApproachTarget_Way(char *self, void *tgt, void *pos, void *fn, float range,
                        unsigned char flag);
int actEnemyForceSwitchToCarry(void *a0);
void actEnemyRestart(char *self, float *pos, float *dir, int kind, int mot);
void boss_effect_start(char *self, int id);
int flyMailCore(void *self);

/* MAIN.MAP global of enemy_act.o's .sdata, the run's last word (act.c sets it) */
extern int entesty;

void subEnemyControl(volatile int a0);
void subEnemyCollision(volatile int a0);
void subEnemyBrainMain(volatile int a0);

#endif /* ENEMY_ACT_H */

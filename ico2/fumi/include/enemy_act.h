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

int _ApproachTarget_Boss(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
int _ApproachTarget_Way(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
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

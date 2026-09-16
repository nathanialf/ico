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

int ACTEnemyForceSwitchToCarry(char *a0);
void EnemyUtil_TurnToBoy(char *self, int tgt, int smooze);
int EnemyUtil_isOtherStatus(char *self, int mode);
int GetEnemyTypeFromGObj(char *a0);
int GetMotherGeneratorGObjAskEnemy(char *a0);
int GetMotherGeneratorLabelAskEnemy(char *a0);
int IsEnemyBrainToBoy(char *self);
int IsEnemyBrainToGenerator(char *a0, int *out);
int _ApproachTarget(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
int _ApproachTarget_Boss(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
int _ApproachTarget_Way(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
void _BrainMode_SetDirect(char *a0, int a1, int *a2);
int actEnemyFlagCheckActive(int *a0);
int actEnemyFlagCheckDead(int *a0);
void actEnemyFlagOnFree(int *a0);
int actEnemyForceSwitchToCarry(void *a0);
void actEnemyRestart(char *self, float *pos, float *dir, int kind, int mot);
int actEnemy_GetClingTarget(char *a0);
int actEnemy_isLargeEnemy(char *a0);
void afterEnemyBodylift(volatile int a0);
void boss_effect_callback(int id);
void boss_effect_start(char *self, int id);
int flyMailCore(void *self);
int isEnemyActive(int *self);
int isEnemyHyde(int *a0);
int isEnemyKidnapEnable(int *self);
void subEnemyBrain_Idle(volatile int a0);

#endif /* ENEMY_ACT_H */

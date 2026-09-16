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

extern int ACTEnemyForceSwitchToCarry(char *a0);
extern void EnemyUtil_TurnToBoy(char *self, int tgt, int smooze);
extern int EnemyUtil_isOtherStatus(char *self, int mode);
extern int GetEnemyTypeFromGObj(char *a0);
extern int GetMotherGeneratorGObjAskEnemy(char *a0);
extern int GetMotherGeneratorLabelAskEnemy(char *a0);
extern int IsEnemyBrainToBoy(char *self);
extern int IsEnemyBrainToGenerator(char *a0, int *out);
extern int _ApproachTarget(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
extern int _ApproachTarget_Boss(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
extern int _ApproachTarget_Way(char *self, void *tgt, void *pos, void *fn, float range, unsigned char flag);
extern void _BrainMode_SetDirect(char *a0, int a1, int *a2);
extern int actEnemyFlagCheckActive(int *a0);
extern int actEnemyFlagCheckDead(int *a0);
extern void actEnemyFlagOnFree(int *a0);
extern int actEnemyForceSwitchToCarry(void *a0);
extern void actEnemyRestart(char *self, float *pos, float *dir, int kind, int mot);
extern int actEnemy_GetClingTarget(char *a0);
extern int actEnemy_isLargeEnemy(char *a0);
extern void afterEnemyBodylift(volatile int a0);
extern void boss_effect_callback(int id);
extern void boss_effect_start(char *self, int id);
extern int flyMailCore(void *self);
extern int isEnemyActive(int *self);
extern int isEnemyHyde(int *a0);
extern int isEnemyKidnapEnable(int *self);
extern void subEnemyBrain_Idle(volatile int a0);

#endif /* ENEMY_ACT_H */

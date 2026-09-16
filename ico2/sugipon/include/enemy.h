/*
 * ico2/sugipon/include/enemy.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what enemy.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ENEMY_H
#define ENEMY_H

extern int CanThisEnemyFly(char *a0);
extern void CheckEnemyHit(void *a0, void *a1, void *a2, void *a3);
extern void EnemyDeleteParticle(void *a0, void *a1, void *a2);
extern void EnemySetfAppearAll(char *self);
extern int GetEnemyBattleType(char *a0);
extern float GetEnemyDefDodgeRange(char *a0);
extern float GetEnemyDefLife(char *a0);
extern int RandomizeEnemy(char *self);
extern void ResetEnemyPositionInfo(char *self);
extern void ReviveEnemyParticle(char *a0, int a1);
extern void SetEnemyDissolve(char *self, float ratio);
extern void SetEnemyFootPrintSwitch(char *a0, int a1);
extern void dispEnemyObject(void *self);
extern int isExistEnemyParticle(char *a0, int a1);

#endif /* ENEMY_H */

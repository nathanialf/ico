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

int CanThisEnemyFly(char *a0);
void CheckEnemyHit(void *a0, void *a1, void *a2, void *a3);
void EnemyDeleteParticle(void *a0, void *a1, void *a2);
void EnemySetfAppearAll(char *self);
int GetEnemyBattleType(char *a0);
float GetEnemyDefDodgeRange(char *a0);
float GetEnemyDefLife(char *a0);
int RandomizeEnemy(char *self);
void ResetEnemyPositionInfo(char *self);
void ReviveEnemyParticle(char *a0, int a1);
void SetEnemyDissolve(char *self, float ratio);
void SetEnemyFootPrintSwitch(char *a0, int a1);
void dispEnemyObject(void *self);
int isExistEnemyParticle(char *a0, int a1);

#endif /* ENEMY_H */

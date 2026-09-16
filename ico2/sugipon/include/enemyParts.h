/*
 * ico2/sugipon/include/enemyParts.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what enemyParts.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ENEMYPARTS_H
#define ENEMYPARTS_H

int DispEnemyEye(char *a0);
int DispEnemyFootPrints(int *a0);
int EntryEnemyFootPrint(char *self, void *pos);
int ExecEnemyFootPrints(char *self);
char *InitEnemyEye(int num, int a1, int a2);
char *InitEnemyFootPrint(int num);
int ResetEnemyEye(char *self);
int UpdateEnemyEye(char *a0, int a1, float f);

#endif /* ENEMYPARTS_H */

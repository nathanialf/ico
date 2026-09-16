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

extern int DispEnemyEye(char *a0);
extern int DispEnemyFootPrints(int *a0);
extern int EntryEnemyFootPrint(char *self, void *pos);
extern int ExecEnemyFootPrints(char *self);
extern char *InitEnemyEye(int num, int a1, int a2);
extern char *InitEnemyFootPrint(int num);
extern int ResetEnemyEye(char *self);
extern int UpdateEnemyEye(char *a0, int a1, float f);

#endif /* ENEMYPARTS_H */

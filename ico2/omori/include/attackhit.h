/*
 * ico2/omori/include/attackhit.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what attackhit.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ATTACKHIT_H
#define ATTACKHIT_H

void EnemyAttackCenter(void);
int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, int kind);

#endif /* ATTACKHIT_H */

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

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order attackhit.c's inline tail has. */
void CommonAttackCenter(char *a0);
int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, int kind);
void AttackCenter_WithDir(char *gop, int group, float *pos, float *dir, float radius);

void EnemyAttackCenter(void);

#endif /* ATTACKHIT_H */

/*
 * ico2/omori/include/attackhit.h
 *
 * The declarations of what attackhit.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ATTACKHIT_H
#define ATTACKHIT_H

void CommonAttackCenter(char *a0);
int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, char *spare);
void AttackCenter_WithDir(char *gop, int group, float *pos, float *dir, float radius);

void EnemyAttackCenter(char *gobj);

#endif /* ATTACKHIT_H */

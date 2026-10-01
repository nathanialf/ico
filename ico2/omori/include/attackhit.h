/*
 * ico2/omori/include/attackhit.h
 *
 * The declarations of what attackhit.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ATTACKHIT_H
#define ATTACKHIT_H

void CommonAttackCenter(struct GObj *gobj);
int _AttackCenter(struct GObj *gop, int group, float *pos, float *ofs, float radius, struct GObj *spare);
void AttackCenter_WithDir(struct GObj *gop, int group, float *pos, float *dir, float radius);

void EnemyAttackCenter(struct GObj *gobj);

#endif /* ATTACKHIT_H */

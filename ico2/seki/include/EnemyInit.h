/*
 * ico2/seki/include/EnemyInit.h
 *
 * The declarations of what EnemyInit.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ENEMYINIT_H
#define ENEMYINIT_H

int enemy_GetPositionTable(int idx, int sub_idx);
void enemy_Initialize(void);

extern int EnemyKindNum;

struct EnemyModelSet;
extern struct EnemyModelSet enemy_enemymodel01_enemymodel04;
extern struct EnemyModelSet *enemymodel01[];

#endif /* ENEMYINIT_H */

/*
 * ico2/seki/include/EnemyInit.h
 *
 * The declarations of what EnemyInit.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ENEMYINIT_H
#define ENEMYINIT_H

#include <libvu0.h>

float (*enemy_GetPositionTable(int idx, int sub_idx))[4];
void enemy_Initialize(void);

extern int EnemyKindNum;

/* the stage table's record: a pointer and a count */
typedef struct EnemySet {        /* field names derived */
    struct EnemyModelSet **list; /* 0x0 */
    int n;                       /* 0x4 */
} EnemySet;                      /* derived name */

/* one kind's position list and the kind it places */
typedef struct EnemyKindRec { /* field names derived */
    int *list;                /* 0x0 */
    int kind;                 /* 0x4 */
} EnemyKindRec;               /* derived name */

/* a model file's placement set: its kind lists and its position table */
typedef struct EnemyModelSet { /* field names derived */
    EnemyKindRec *kinds;       /* 0x0 */
    int kindNum;               /* 0x4 */
    sceVu0FVECTOR *pos;        /* 0x8 */
    int posNum;                /* 0xC */
} EnemyModelSet;               /* derived name */

extern EnemyModelSet enemy_enemymodel01_enemymodel04;

/* the stages' set lists and their counts, enemy_Initialize's table: the
   data members enemy-model02-kindlist .. enemy-set-table that follow
   EnemyInit.o in the link */
extern EnemySet enemySetTable[]; /* derived name */

#endif /* ENEMYINIT_H */

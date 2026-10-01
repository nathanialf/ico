/*
 * ico2/sugipon/include/enemy.h
 *
 * The declarations of what enemy.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ENEMY_H
#define ENEMY_H

struct GObj;

/* enemy-random-def: one random enemy kind range, 8 bytes, for the kinds from
   0x10000 on: the first and the last row of randomEnemyVariationKind the
   kind draws from. */
typedef struct { /* field names derived */
    int first;   /* 0x00 */
    int last;    /* 0x04 */
} EnemyKindRange; /* derived name */

/* enemy-def: one enemy kind, 0x1C bytes, by kind: the model and the particle
   object it is drawn with, its life, the scale its model is drawn at, the
   dodge range, then the attribute word: the parameter row in bits 0-7, the
   fly type in bits 8-9 and the battle type in bits 10-11. */
typedef struct {    /* field names derived */
    int model;      /* 0x00, the model id, 0x610 for none */
    int particle;   /* 0x04, the particle object, -1 for none */
    float life;     /* 0x08 */
    float float0C;  /* 0x0C */
    float scale;    /* 0x10 */
    float dodge;    /* 0x14 */
    int paraIndex : 8;
    unsigned int flyType : 2;
    unsigned int battleType : 2;
} EnemyDef; /* derived name */

extern const EnemyDef enemyKind[];
extern const EnemyKindRange randomEnemyKind[];
extern const int randomEnemyVariationKind[];
int CanThisEnemyFly(struct GObj *a0);
int CheckEnemyHit(struct GObj *self, float *pos, float *a, float *b);
void EnemyDeleteParticle(struct GObj *self, float *dir, short *list);
void EnemySetfAppearAll(struct GObj *self);
int GetEnemyBattleType(struct GObj *a0);
float GetEnemyDefDodgeRange(struct GObj *a0);
float GetEnemyDefLife(struct GObj *a0);
int *GetEnemyHitNodeFlag(struct GObj *a0);
int RandomizeEnemy(struct GObj *self);
void ResetEnemyPositionInfo(struct GObj *self);
void ReviveEnemyParticle(struct GObj *a0, int a1);
void SetEnemyDissolve(struct GObj *self, float ratio);
void SetEnemyFootPrintSwitch(struct GObj *a0, int a1);
void dispEnemyObject(void *self);
int isExistEnemyParticle(struct GObj *a0, int a1);

#endif /* ENEMY_H */

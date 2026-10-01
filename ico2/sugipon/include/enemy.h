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

struct GObj;

/* enemy-random-def: one random enemy kind range, 8 bytes, for the kinds from
   0x10000 on: the first and the last row of randomEnemyVariationKind the
   kind draws from. */
typedef struct { /* field names derived */
    int first;   /* 0x00 */
    int last;    /* 0x04 */
} EnemyKindRange;

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
int GetEnemyHitNodeFlag(struct GObj *a0);
int RandomizeEnemy(struct GObj *self);
void ResetEnemyPositionInfo(struct GObj *self);
void ReviveEnemyParticle(struct GObj *a0, int a1);
void SetEnemyDissolve(struct GObj *self, float ratio);
void SetEnemyFootPrintSwitch(struct GObj *a0, int a1);
void dispEnemyObject(void *self);
int isExistEnemyParticle(struct GObj *a0, int a1);

#endif /* ENEMY_H */

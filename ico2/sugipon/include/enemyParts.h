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

/* RECONSTRUCTION, read from the ROM.  The 0x60-byte eye InitEnemyEye
   allocates: whether it trails a point blur, the blur, the eye's matrix (its
   translation row is the blur's point) and the three eye objects.  8-aligned:
   ROM copies the template with the MIPS back end's block-move LOOP (four ld /
   four sd per turn, 0x20 at a time). */
typedef struct EnemyEye {   /* field names derived */
    int blurOn;             /* 0x00 */
    struct PointBlur *blur; /* 0x04 */
    int pad8[2];            /* 0x08 */
    float mtx[4][4];        /* 0x10 */
    Sub15C *dobj[3];        /* 0x50 */
    int pad5C;              /* 0x5C */
} __attribute__((aligned(8))) EnemyEye;

/* RECONSTRUCTION, read from the ROM.  One footprint: the frames it has
   shown (-1 when the slot is free), its spread speed and where it lies.
   8-aligned: ROM copies the template with plain ld/sd. */
typedef struct EnemyFootPrint {
    int life;     /* 0x00 */
    float speed;  /* 0x04 */
    int pad8[2];  /* 0x08 */
    float pos[4]; /* 0x10 */
} __attribute__((aligned(8))) EnemyFootPrint;

typedef struct EnemyFootPrintHead { /* field names derived */
    int num;                        /* 0x00 */
    Sub15C *dobj;                   /* 0x04 */
    int idx;                        /* 0x08 */
    EnemyFootPrint *buf;            /* 0x0C */
} EnemyFootPrintHead;

int DispEnemyEye(EnemyEye *a0);
int DispEnemyFootPrints(EnemyFootPrintHead *a0);
int EntryEnemyFootPrint(EnemyFootPrintHead *self, void *pos);
int ExecEnemyFootPrints(EnemyFootPrintHead *self);
EnemyEye *InitEnemyEye(int num, int a1, int a2);
EnemyFootPrintHead *InitEnemyFootPrint(int num);
int ResetEnemyEye(EnemyEye *self);
int UpdateEnemyEye(EnemyEye *a0, void *m, float f);

#endif /* ENEMYPARTS_H */

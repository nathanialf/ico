/*
 * ico2/sugipon/include/pool.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what pool.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef POOL_H
#define POOL_H

#include "typedef.h"

/* RECONSTRUCTION, read from the ROM.  The record InitLayoutedPoolReflactionMesh
 * and SetLayoutedPoolReflactionMesh take: pool.c reads the first two words as
 * the grid's two counts and the word at 0x10 as a pointer to the mesh the
 * vertices hang off.  Size and alignment are the ROM's: the 0x20-byte copies
 * in ico2/script/src/st02a are ldl/ldr/sdl/sdr pairs, so the record is only
 * 4-aligned. */
typedef struct {
    int f_0;    /* 0x00, the row count */
    int f_4;    /* 0x04, the column count */
    int f_8;    /* 0x08 */
    int f_C;    /* 0x0C */
    void *f_10; /* 0x10 */
    int f_14;   /* 0x14 */
    int f_18;   /* 0x18 */
    int f_1C;   /* 0x1C */
} PoolMesh;

/* RECONSTRUCTION, read from the ROM.  The second argument of
 * InitLayoutedPoolReflactionMesh: pool.c interpolates between the quadwords at
 * 0x00 and 0x20 and between those at 0x10 and 0x30, so the record is the
 * layout quad's four corner points.  The 0x40-byte copies in
 * ico2/script/src/st02a are aligned ld/sd pairs, which is VECTOR's alignment. */
typedef struct {
    VECTOR corner[4];
} PoolMeshQuad;

int CheckPoolHasGridMesh(char *a0);
void DispLimitedPoolReflactionMesh(int *a0);
void GetPoolGlobalDrainVector(void *dst, char *a0);
float GetPoolGlobalHeight(char *a0);
float GetPoolGlobalHeightDetail(char *a0, float *pos);
void InitLayoutedPoolReflactionMesh(char *a0, char *a1);
void InitLimitedPoolReflactionMesh(char *a0);
void SetFallDownSplash(int pool, void *self);
void SetLayoutedPoolReflactionMesh(char *a0);
void SetLimitedPoolReflactionMesh(char *a0, char *a1, char *a2);
void copyToWork(int pri);
void dispPool(char *self);
void updatePoolGeo(char *self);

#endif /* POOL_H */

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
#include "Primitive.h"

/* RECONSTRUCTION, read from the ROM.  The reflection mesh the
 * *PoolReflactionMesh functions take: the grid's two counts, two sizes (boy.c
 * sets both to 300.0f; pool.c does not read them), the mesh, its per-vertex
 * ripple heights, the rows of the mesh's vertices and the colour
 * prim_InitMesh3D is given.  Size and alignment are the ROM's: the 0x20-byte
 * copies in ico2/script/src/st02a are ldl/ldr/sdl/sdr pairs, so the record is
 * only 4-aligned. */
typedef struct {
    int nrow;           /* 0x00 */
    int ncol;           /* 0x04 */
    float f_8;          /* 0x08 */
    float f_C;          /* 0x0C */
    Mesh3D *mesh;       /* 0x10 */
    float **height;     /* 0x14, nrow rows of ncol heights */
    Prim3DVec **row;    /* 0x18, the rows of mesh's vertices */
    unsigned int color; /* 0x1C */
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
void DispLimitedPoolReflactionMesh(PoolMesh *a0);
void GetPoolGlobalDrainVector(void *dst, char *a0);
float GetPoolGlobalHeight(char *a0);
float GetPoolGlobalHeightDetail(char *a0, float *pos);
void InitLayoutedPoolReflactionMesh(PoolMesh *a0, PoolMeshQuad *a1);
void InitLimitedPoolReflactionMesh(PoolMesh *a0);
void SetFallDownSplash(char *pool, char *self);
void SetLayoutedPoolReflactionMesh(PoolMesh *a0);
void SetLimitedPoolReflactionMesh(PoolMesh *a0, char *a1, char *a2);
void copyToWork(int pri);
void dispPool(char *self);
void updatePoolGeo(char *self);

#endif /* POOL_H */

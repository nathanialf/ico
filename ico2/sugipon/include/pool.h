/*
 * ico2/sugipon/include/pool.h
 *
 * The declarations of what pool.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef POOL_H
#define POOL_H

struct GObj;

#include "typedef.h"
#include "Primitive.h"

/* The reflection mesh the *PoolReflactionMesh functions take: the grid's
 * two counts, two sizes (boy.c sets both to 300.0f; pool.c does not read
 * them), the mesh, its per-vertex ripple heights, the rows of the mesh's
 * vertices and the colour prim_InitMesh3D is given.  The record is
 * 4-aligned. */
typedef struct {        /* field names derived */
    int nrow;           /* 0x00 */
    int ncol;           /* 0x04 */
    float sizeX;        /* 0x08 */
    float sizeZ;        /* 0x0C */
    Mesh3D *mesh;       /* 0x10 */
    float **height;     /* 0x14, nrow rows of ncol heights */
    Prim3DVec **row;    /* 0x18, the rows of mesh's vertices */
    unsigned int color; /* 0x1C */
} PoolMesh;             /* derived name */

/* The second argument of InitLayoutedPoolReflactionMesh: the layout quad's
 * four corner points.  pool.c interpolates between the quadwords at 0x00 and
 * 0x20 and between those at 0x10 and 0x30. */
typedef struct { /* field names derived */
    VECTOR corner[4];
} PoolMeshQuad; /* derived name */

#ifdef VERSION_AUG6
/* pool.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order;
 * poolRideFunc and getWave follow, declared in pool.c). */
void PoolGeo(void);
float GetPoolGlobalHeight(GObj *pool);
float GetPoolGlobalHeightDetail(GObj *pool, float *pos);
int CheckPoolHasGridMesh(GObj *pool);
void InitLayoutedPoolReflactionMesh(PoolMesh *refl, PoolMeshQuad *quad);
void DispLimitedPoolReflactionMesh(PoolMesh *refl);
void GetPoolGlobalDrainVector(void *dst, GObj *pool);
#else
int CheckPoolHasGridMesh(GObj *pool);
void DispLimitedPoolReflactionMesh(PoolMesh *refl);
void GetPoolGlobalDrainVector(void *dst, GObj *pool);
float GetPoolGlobalHeight(GObj *pool);
float GetPoolGlobalHeightDetail(GObj *pool, float *pos);
void InitLayoutedPoolReflactionMesh(PoolMesh *refl, PoolMeshQuad *quad);
#endif
void InitLimitedPoolReflactionMesh(PoolMesh *refl);
void SetFallDownSplash(GObj *pool, struct GObj *self);
void SetLayoutedPoolReflactionMesh(PoolMesh *refl);
void SetLimitedPoolReflactionMesh(PoolMesh *refl, GObj *pool, GObj *obj);

struct SObjSimpleSetting;

char *InitPoolGeo(char *self, struct SObjSimpleSetting *lay);
void PoolDL(GObj *self);
#ifndef VERSION_AUG6
void PoolGeo(void);
float getWave(float t);
#endif

#endif /* POOL_H */

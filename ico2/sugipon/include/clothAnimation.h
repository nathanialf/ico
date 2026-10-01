/*
 * ico2/sugipon/include/clothAnimation.h
 *
 * The declarations of what clothAnimation.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CLOTHANIMATION_H
#define CLOTHANIMATION_H

struct GObj;

#include "Primitive.h"

/* one cloth InitCloth4D builds (clothAnimation.c) */
typedef struct Cloth4D Cloth4D;

void DispCloth4D(Cloth4D *c, void *a1, void *a2);
void DispCloth4DWithAdd(Cloth4D *c, void *a1, void *a2);
void DispClothMesh(int *a0, void *a1, void *a2);
void DispMeshWire(Prim3DVec **rows, int nx, int ny);
void GetChainAnimation(void *chain, struct GObj *a, void *m);
float GetChainCollision(int *a0, void *pos, float r);
float GetChainNodeID(int a0, float f);
void GetCloth4D(void *a0, float x, float y);
void GetCloth4DWithDetail(void *a0, float x, float y, float z, float w);
void GetCloth4DWithTight(void *a0, float x, float y, float z, float w, void *a1, void *a2);

void GetClothAnimation(void *a0, void *a1, struct GObj *a2, void *m, int a4, int a5, void *a6,
                       int a7);

void GetClothAnimationFix4Points(void *a0, void *a1, int a2, void *m);
void *InitChains(char *a0);

/* One row of the table InitCloth4D's third argument points at: the skeleton
 * node a piece of cloth hangs from and the offsets the init scales by the
 * actor's own scale.  Only enable, node and ofsZ are read here (by
 * InitCloth4D); the cloth step reads the rest through its own record, so
 * float20 to float30 are named by their type.  The tables are boy.c's,
 * girl.c's and queen.c's. */
typedef struct { /* field names derived */
    int enable;  /* 0x00, -1 ends the table */
    float ofsX;  /* 0x04, scaled by the actor scale at init */
    float ofsY;  /* 0x08, likewise */
    float ofsZ;  /* 0x0C, likewise; the init also stores 1 / (ofsZ + ofsZ) at 0x34 */
    int node;    /* 0x10, the argument GetSkeltonFocusNode is called with */
    char pad14[12];
    float float20; /* 0x20 */
    float float24; /* 0x24 */
    char pad28[4];
    float float2C; /* 0x2C */
    float float30; /* 0x30 */
    char pad34[12];
} ClothHangCfg; /* derived name */

/* The generated cloth mesh InitCloth4D's second argument points at: one
 * column of the cloth, its attachment point and the pair of skeleton nodes the
 * column is blended between.  InitCloth4D reads the column's ny texture
 * coordinates through uv; the rest are read by the cloth step, so vec50 and
 * the config's word and float members are named by their type.  The tables
 * are boy.c's, girl.c's and queen.c's. */
typedef struct {  /* field names derived */
    float length; /* 0x00, the column's length, scaled by the actor scale */
    char pad04[12];
    float pos[4];   /* 0x10, the point the column hangs from */
    float dir[4];   /* 0x20, a unit vector */
    int node0;      /* 0x30, a skeleton node, blended with node1 */
    float weight0;  /* 0x34 */
    int node1;      /* 0x38, -1 when the column hangs from node0 alone */
    float weight1;  /* 0x3C */
    float (*uv)[2]; /* 0x40, ny texture coordinates */
    char pad44[12];
    float vec50[4];                        /* 0x50 */
} __attribute__((aligned(16))) Cloth4DCol; /* derived name */

/* The head of one generated cloth mesh: the mesh size, the colour
 * prim_InitMesh3D is given, the texture name and the nx columns.
 * clothAnimation.c carries the same record without the last two words. */
typedef struct { /* field names derived */
    int nx;
    int ny;
    int word08; /* 0x08 */
    int word0C; /* 0x0C */
    int r;      /* 0x10 */
    int g;      /* 0x14 */
    int b;      /* 0x18 */
    int a;      /* 0x1C */
    const char *tex;
    Cloth4DCol *cols;
    float float28; /* 0x28 */
    int word2C;    /* 0x2C */
} Cloth4DCfg;      /* derived name */

Cloth4D *InitCloth4D(struct GObj *g, void *a1, void *a2);
int InitClothes(char *p);
int InitClothesNoShade(char *p);
int SetChainExtendedWeight(int *a0, int idx, float w0, float w1);
void TestDispChainAnimation(int *a0);
void getCloth4D(void *a0, int **rows);

void getCloth4D_preProcess(void *a0, float x, float y, float z, float w, int tight, void *a6,
                           void *a7);

float getXZLength(void *p0);
float getXZInvLength(void *p0);
float getXZLengthSquare(void *p0);
float subAndGetInvLength(void *p0, void *p1, void *p2, void *p3);

#endif /* CLOTHANIMATION_H */

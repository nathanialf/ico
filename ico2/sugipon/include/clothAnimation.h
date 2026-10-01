/*
 * ico2/sugipon/include/clothAnimation.h
 *
 * The declarations of what clothAnimation.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CLOTHANIMATION_H
#define CLOTHANIMATION_H

struct GObj;

#include "typedef.h"
#include "Primitive.h"

/* One extended weight of a chain node: the chain position it sits at (a
   node index plus a fraction, negative while the slot is free), its point,
   its old point and its velocity, and the two lengths SetChainExtendedWeight
   is given. */
typedef struct { /* field names derived */
    float w;
    char pad[12];
    VECTOR v0;
    VECTOR v1;
    VECTOR v2;
    float len0; /* 0x40, SetChainExtendedWeight's w0 */
    float len1; /* 0x44, its w1 */
    char pad48[8];
} ExW; /* derived name */

/* the points of one chain InitChains builds, 0x1A0 bytes */
typedef struct { /* field names derived */
    char *pos;   /* 0x0, the chain's points, 16 bytes each */
    char *vel;   /* 0x4, their velocities */
    char *len;   /* 0x8, one float a point, the step down the chain */
    int exNum;   /* 0xC, the extended weights in use */
    ExW ex[5];
} ChainNode; /* derived name */

/* the chain system InitChains returns: the 80-byte parameter records it was
   built from (the list ends with num -1), the chain count and the chains */
typedef struct { /* field names derived */
    char *cfg;
    int num;
    ChainNode *nodes;
    int oddFrame; /* flipped every GetChainAnimation */
} ChainSet;       /* derived name */

/* The InitClothes config record, 0x1C bytes, built by clothTest.c and
   flag.c (rows, spacing, columns, anchors, texture, weight). */
typedef struct ClothCfg { /* field names derived */
    int num;              /* 0x00  rows, and -1 ends the array */
    float segLength;      /* 0x04  the spacing between rows */
    int div;              /* 0x08  columns */
    int wrap;             /* 0x0C  nonzero when the last column joins the first */
    void *anchors;        /* 0x10 */
    void *tex;            /* 0x14  null means the untextured mesh */
    float weight;         /* 0x18  the fall added to each point a step */
} ClothCfg;               /* derived name */

/* the texture record tex_GetTextureData returns, copied whole with
   doubleword moves */
typedef struct { /* field names derived */
    long long q[89];
} TexBlob; /* derived name */

/* one cloth InitClothes builds, 0x2E0 bytes: the mesh, the rows of points
   and velocities, a mark per point and the texture record copied in */
typedef struct {  /* field names derived */
    Mesh3D *mesh; /* 0x00 */
    VECTOR **pos; /* 0x04, one row a cloth row, into the mesh's positions */
    VECTOR **vel; /* 0x08, one row a cloth row */
    int **mark;   /* 0x0C, one row a cloth row, -1 each at init */
    int textured; /* 0x10, nonzero when the config names a texture */
    int pad14;
    TexBlob tex; /* 0x18 */
} ClothRec;      /* derived name */

/* the clothes InitClothes returns */
typedef struct { /* field names derived */
    int num;
    ClothRec *rec;
} ClothSet; /* derived name */

/* one cloth InitCloth4D builds (clothAnimation.c) */
typedef struct Cloth4D Cloth4D;

void DispCloth4D(Cloth4D *c, void *a1, void *a2);
void DispCloth4DWithAdd(Cloth4D *c, void *a1, void *a2);
void DispClothMesh(ClothRec *rec, void *a1, void *a2);
void DispMeshWire(Prim3DVec **rows, int nx, int ny);
void GetChainAnimation(ChainSet *sys, struct GObj *obj, float (*mtx)[4]);
float GetChainCollision(ChainSet *sys, void *pos, float r);
float GetChainNodeID(char *cfg, float f);
void GetCloth4D(void *a0, float x, float y);
void GetCloth4DWithDetail(void *a0, float x, float y, float z, float w);
void GetCloth4DWithTight(void *a0, float x, float y, float z, float w, void *a1, void *a2);

void GetClothAnimation(VECTOR **pos, VECTOR **vel, struct GObj *obj, void *m, ClothCfg *cfg,
                       int nwall, int wallOwner, int a7);

void GetClothAnimationFix4Points(VECTOR **pa, VECTOR **pv, ClothCfg *cfg, void *mtx);
ChainSet *InitChains(char *cfg);

/* One row of the table InitCloth4D's third argument points at: the skeleton
 * node a piece of cloth hangs from and the offsets the init scales by the
 * actor's own scale.  Only enable, node and the offsets are read by
 * InitCloth4D; the cloth step reads the rest through its own record, so
 * float20 to float30 are named by their type.  The tables are boy.c's,
 * girl.c's and queen.c's. */
typedef struct { /* field names derived */
    int enable;  /* 0x00, -1 ends the table */
    float ofsX;  /* 0x04, scaled by the actor scale at init */
    float ofsY;  /* 0x08, likewise */
    float ofsZ;  /* 0x0C, likewise */
    int node;    /* 0x10, the argument GetSkeltonFocusNode is called with */
    char pad14[12];
    float float20; /* 0x20 */
    float float24; /* 0x24 */
    char pad28[4];
    float float2C;  /* 0x2C */
    float float30;  /* 0x30 */
    char pad34[12]; /* 0x34, where the init's scaled copy keeps 1 / (ofsZ + ofsZ) */
} ClothHangCfg;     /* derived name */

/* The generated cloth mesh InitCloth4D's second argument points at: one
 * column of the cloth, its attachment point and the pair of skeleton nodes the
 * column is blended between, read by index.  InitCloth4D reads the column's ny texture
 * coordinates through uv; the rest are read by the cloth step, so vec50 and
 * the config's word and float members are named by their type.  The tables
 * are boy.c's, girl.c's and queen.c's. */
/* one skeleton node a column is blended from, and its weight */
typedef struct { /* field names derived */
    int node;
    float weight;
} Cloth4DLink; /* derived name */

typedef struct {  /* field names derived */
    float length; /* 0x00, the column's length, scaled by the actor scale */
    char pad04[12];
    float pos[4];        /* 0x10, the point the column hangs from */
    float dir[4];        /* 0x20, a unit vector */
    Cloth4DLink link[2]; /* 0x30, the second node -1 when the column hangs from the first alone */
    float (*uv)[2];      /* 0x40, ny texture coordinates */
    char pad44[12];
    float vec50[4];                        /* 0x50 */
} __attribute__((aligned(16))) Cloth4DCol; /* derived name */

/* The head of one generated cloth mesh: the mesh size, the colour
 * prim_InitMesh3D is given, the texture name and the nx columns. */
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

Cloth4D *InitCloth4D(struct GObj *g, Cloth4DCfg *cfg, ClothHangCfg *tbl);
ClothSet *InitClothes(ClothCfg *cfg);
ClothSet *InitClothesNoShade(ClothCfg *cfg);
int SetChainExtendedWeight(ChainNode *node, int idx, float w0, float w1);
void TestDispChainAnimation(ChainSet *sys);
float getXZLength(void *p0);
float getXZInvLength(void *p0);
float getXZLengthSquare(void *p0);
float subAndGetInvLength(void *d, const void *a, const void *b);

#endif /* CLOTHANIMATION_H */

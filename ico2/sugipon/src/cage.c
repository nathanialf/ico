#include "cage.h"
#include "gobj.h"
#include "DisplayP2O.h"
#include "clothAnimation.h"
#include "quaternion.h"
#include "tableSin.h"
#include <libvu0.h>
#include <math.h>
#include "ios.h"
#include "Matrix.h"
#include "geometryManager.h"
#include "matrixDrive.h"

/* RECONSTRUCTION, names ours: the cage's 80-byte work record, InitCageGeo's
   allocation, kept at +0x830 of the object's motion work: the cage and chain
   DObjs, the cage's rotation and turn, the chains InitChains builds and the
   swing state. */
typedef struct {  /* field names derived */
    Sub15C *dobj; /* 0x00 */
    char *dobj2;  /* 0x04 */
    char pad08[8];
    float rot[4];     /* 0x10 */
    char *chains;     /* 0x20 */
    int upperNode;    /* 0x24, the chain node weighted over 0 to 600 */
    int lowerNode;    /* 0x28, the chain node weighted over 500 to 1400 */
    int linkCount;    /* 0x2C, the chain's length over linkLength, the DObj node count */
    float linkLength; /* 0x30 */
    short angle;      /* 0x34 */
    short pad36;
    float mass;    /* 0x38, divides the impulse a rider gives */
    float damping; /* 0x3C, the per-frame velocity scale */
    int rideable;  /* 0x40, CageRideFunc's answer */
    char pad44[12];
} CageWork; /* derived name */

int CageRideFunc(char **self, char *rider)
{
    float v[4];
    float n[4];
    CageWork *w;
    float d;
    float t;

    w = GOBJ_SUB(*self)->f_830;
    CopyVector(v, (char *)GOBJ_SUB(rider) + 0xA0);
    v[1] = v[1] - 250.0f;
    sceVu0Normalize(n, v);
    d = FSqrt(n[0] * n[0] + n[2] * n[2]) * 50.0f;
    t = VectorLength(v) * d / 250.0f;
    if (t < 0.0f) {
        t = -t;
    }
    v[1] = 0.0f;
    sceVu0ScaleVector(v, v, t * 0.06f / w->mass);

    sceVu0AddVector((void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x40),
                    (void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x40), v);

    sceVu0SubVector((void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x40),
                    (void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x40), v);

    return 1;
}

void SetCageFixGeometry(char *self, void *pos, void *dir)
{
    CageWork *w = GOBJ_SUB(self)->f_830;

    CopyVector(*(char **)(w->chains) + 0x20, pos);
    CopyVector(w->rot, dir);
}

inline int GetCageChainPoint(char *a0, char *a1, char *a2)
{
    CageWork *w = GOBJ_SUB(a2)->f_830;
    CopyVector(a0, *(char **)(*(char **)(w->chains + 8)));
    CopyVector(a1, *(char **)(*(char **)(w->chains + 8)) + 0x10);
    *(float *)(a0 + 4) = *(float *)(a0 + 4) + 50.0f;
    *(float *)(a1 + 4) = *(float *)(a1 + 4) - 150.0f;
    return w->rideable;
}

/* kept local: void * (void *, int, char *, int) here, void * (IosMemPart *, int, char *, int) in memory.h */
extern void *iosMallocDebug(void *part, int size, char *file, int line);
/* kept local: void (void *) here, void * (void *) in memory.h */
extern void iosFree(void *p);

/* the game heap handles, declared int as sugipon's other TUs do
   (girlForceField.c, candle.c) and cast at the allocator calls */

/* RECONSTRUCTION: one 80-byte chain-parameter record per chain, the list
 * InitChains walks until num is -1.  The fields are the ones clothAnimation.c
 * reads (count 0x0, focus node 0x10, node spacing 0x14, root 0x20, the length
 * weight 0x40); the root is a homogeneous vector, which makes the record
 * 16-aligned and gives the ROM's doubleword block copy. */
typedef struct {
    int num;
    int pad04[3];
    int node;
    float step;
    int pad18[2];
    sceVu0FVECTOR root;
    int pad30[4];
    float length;
    int pad44[3];
} CageChainParam;

/* the cage's one chain, 2 nodes 500 apart hanging from the cage root */
static CageChainParam cageChainParam[2] = {
    {2, {0, 0, 0}, -1, 500.0f, {0, 0}, {0.0f, 0.0f, 0.0f, 1.0f}, {0, 0, 0, 0}, 100.0f},
    {-1},
};

/* the object-kind table, one 40-byte row per cage kind, the first two words of
 * the row being the two display-list ids the cage builds its DObjs from */
extern char D_002A79B8[];

/* listing rows sugipon/src/cage.c:96-132 */
char *InitCageGeo(char *self, char *lay)
{
    CageWork *w;
    char *ch;
    int i;
    float one;

    w = (CageWork *)iosMallocDebug((void *)ios_partition_sugipon, 80, __FILE__, 97);
    ch = (char *)iosMallocDebug((void *)ios_partition_sugipon, 160, __FILE__, 98);
    w->dobj = (Sub15C *)CSVSYSTEM_InitDObj(
        *(int *)(D_002A79B8 + ((SubHandle *)(self + 0x15C))->sub->f_844 * 40), (float *)lay);
    w->dobj2 = CSVSYSTEM_InitDObj(
        *(int *)(D_002A79B8 + ((SubHandle *)(self + 0x15C))->sub->f_844 * 40 + 4), (float *)lay);
    w->damping = 0.995f;
    w->mass = *(float *)(lay + 0x20);
    ((CageChainParam *)ch)[0] = cageChainParam[0];
    ((CageChainParam *)ch)[1] = cageChainParam[1];
    *(float *)(ch + 0x20) = *(float *)lay;
    *(float *)(ch + 0x24) = *(float *)(lay + 4);
    *(float *)(ch + 0x28) = *(float *)(lay + 8);
    *(float *)(ch + 0x14) = *(float *)(lay + 0x24);
    SetIdentityQuaternion(w->rot);
    w->chains = (char *)InitChains(ch);
    w->upperNode = SetChainExtendedWeight(*(int **)(w->chains + 8), 1, 0.0f, 600.0f);
    w->lowerNode = SetChainExtendedWeight(*(int **)(w->chains + 8), 1, 500.0f, 1400.0f);
    w->angle = (short)(-*(float *)(lay + 0x14) * 10430.378f);
    w->rideable = 1;
    one = 1.0f;
    {
        struct DObjNode *e = ((SubHandle *)(self + 0x15C))->sub->p_870;

        e->scale[0] = e->scale[1] = e->scale[2] = one;
    }
    {
        struct DObjNode *e = ((SubHandle *)(self + 0x15C))->sub->p_870;

        e->rot[0] = e->rot[1] = e->rot[2] = 0;
    }
    w->linkLength = *(float *)(lay + 0x28);
    w->linkCount = (int)(*(float *)(lay + 0x24) / w->linkLength);

    /* listing line 128 carries everything from here to the 0x84C store: one
       macro, the DObj buffer reallocation box.c, boy.c and omori's chain.c
       expand in the same statement order */
    if (*(void **)((char *)w->dobj + 0xC) != 0) {
        iosFree((void *)((int)*(void **)((char *)w->dobj + 0xC) & 0x0FFFFFFF));
    }
    if (w->dobj->f_10 != 0) {
        iosFree((void *)(w->dobj->f_10 & 0x0FFFFFFF));
    }
    *(char **)((char *)w->dobj + 0x10) = *(char **)((char *)w->dobj + 0xC) = 0;
    *(void **)((char *)w->dobj + 0xC) =
        iosMallocDebug((void *)ios_partition_seki, w->linkCount << 6, __FILE__, 128);
    *(void **)((char *)w->dobj + 0x10) =
        iosMallocDebug((void *)ios_partition_seki, w->linkCount << 4, __FILE__, 128);
    w->dobj->f_8 = w->linkCount;
    if (w->dobj->p_870 != 0) {
        iosFree((void *)((int)w->dobj->p_870 & 0x0FFFFFFF));
    }
    w->dobj->p_870 = iosMallocDebug((void *)ios_partition_seki, w->linkCount * 80, __FILE__, 128);
    for (i = 0; i < w->linkCount; i++) {
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->flags.ll &= ~1;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->flags.ll &= ~2;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->pos[0] = 0.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->pos[1] = 0.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->pos[2] = 0.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->pos[3] = 1.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->flags.ll &= ~4;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->fade = 0.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->alpha = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)w->dobj->p_870);
            *(short *)(e + 0x3A) = 0;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->scale[0] = 1.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->scale[1] = 1.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)w->dobj->p_870);
            e->scale[2] = 1.0f;
        }
    }
    w->dobj->dispType = 2;
    ((SubHandle *)(self + 0x15C))->sub->f_81C = (int)CageRideFunc;
    return (char *)w;
}

inline void SetCageChainHangableFlag(char *a0, int a1)
{
    *(int *)((char *)GOBJ_SUB(a0)->f_830 + 0x40) = a1;
}

void HotInitCageGeo(char *self)
{
    CageWork *w = GOBJ_SUB(self)->f_830;

    CopyVector((void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x40), ZeroVector);
    CopyVector((void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x40), ZeroVector);

    CopyVector((void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x30),
               *(char **)(w->chains) + 0x20);
    CopyVector((void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x30),
               *(char **)(w->chains) + 0x20);

    CopyVector(*(void **)(*(int *)(w->chains + 8)), *(char **)(w->chains) + 0x20);
    CopyVector((void *)(*(int *)(*(int *)(w->chains + 8)) + 0x10), *(char **)(w->chains) + 0x20);

    *(float *)(*(int *)(*(int *)(w->chains + 8)) + 0x14) =
        *(float *)(*(int *)(*(int *)(w->chains + 8)) + 0x14) + w->linkLength * (float)w->linkCount;

    *(float *)(*(int *)(w->chains + 8) + w->upperNode * 80 + 0x34) =
        *(float *)(*(int *)(w->chains + 8) + w->upperNode * 80 + 0x34) +
        w->linkLength * (float)w->linkCount;

    *(float *)(*(int *)(w->chains + 8) + w->lowerNode * 80 + 0x34) =
        *(float *)(*(int *)(w->chains + 8) + w->lowerNode * 80 + 0x34) +
        (w->linkLength * (float)w->linkCount + 500.0f);
}

inline void StabilizeAllLayoutedCage(void)
{
    void *gobj;

    gobj = isysGObjSearchFromObjKindID_begin(44);
    while (gobj != 0) {
        HotInitCageGeo(gobj);
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}

inline void SetCageVelocityFriction(char *a0, float a1)
{
    *(float *)((char *)GOBJ_SUB(a0)->f_830 + 0x3C) = a1;
}

/* kept local: void * (int, void *) here, int (void) in windField.h */
extern void *GetWindVector(int kind, void *pos);

/* the world down axis the chain's swing axis is taken against */
static sceVu0FVECTOR cageDown = {0.0f, -1.0f, 0.0f, 0.0f};

static inline void SetCageChainQuaternion(void *q, void *a, void *b)
{
    float d[4];
    float n[4];
    float axis[4];

    sceVu0SubVector(d, a, b);
    sceVu0Normalize(d, d);
    CopyVector(n, d);
    n[1] = 0.0f;
    sceVu0OuterProduct(axis, cageDown, n);
    SetQuaternionByAxisRotateV(
        q, (short)(atan2f(FSqrt(d[0] * d[0] + d[2] * d[2]), d[1]) * 10430.378f), axis);
}

static inline void AddCageWindForce(char *n, float k)
{
    float v[4];

    CopyVector(v, GetWindVector(0, n + 0x20));
    _ScaleVector(v, v, k / *(float *)(n + 0x44));
    _AddVector(n + 0x30, n + 0x30, v);
}

void CageGeo(char *self)
{
    CageWork *w;
    char *n0;
    char *n1;
    int i;

    w = GOBJ_SUB(self)->f_830;

    n0 = *(char **)(w->chains + 8) + (w->upperNode * 80 + 16);
    n1 = *(char **)(w->chains + 8) + (w->lowerNode * 80 + 16);
    AddCageWindForce(n0, 1.0f);
    AddCageWindForce(n1, 10.0f);

    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    GetChainAnimation(w->chains, 0, MatrixDrive_GetMatrix());

    {
        float v[4];
        int angle;
        float f;

        sceVu0SubVector(v, (void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x30),
                        (void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x30));
        sceVu0Normalize(v, v);
        angle = GetTableArcTan2(FSqrt(v[0] * v[0] + v[2] * v[2]), v[1]);
        if (angle >= 2731) {
            f = (float)angle / 2730.0f;
            v[1] = 0.0f;
            sceVu0ScaleVector(v, v, f);
            sceVu0SubVector((void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x40),
                            (void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x40), v);
            sceVu0AddVector((void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x40),
                            (void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x40), v);
        }
    }

    sceVu0ScaleVectorXYZ((void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x40),
                         (void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x40), w->damping);
    sceVu0ScaleVectorXYZ((void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x40),
                         (void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x40), w->damping);

    SetCageChainQuaternion((char *)GOBJ_SUB(self)->f_10,
                           (void *)(w->lowerNode * 80 + *(int *)(w->chains + 8) + 0x30),
                           (void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x30));
    RotQuaternionY((char *)GOBJ_SUB(self)->f_10, w->angle);
    MultiQuaternion((char *)GOBJ_SUB(self)->f_10, (char *)GOBJ_SUB(self)->f_10, w->rot);
    RegularizeQuaternion((char *)GOBJ_SUB(self)->f_10);
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), (char *)GOBJ_SUB(self)->f_10,
                               (void *)(w->upperNode * 80 + *(int *)(w->chains + 8) + 0x30));
    MatrixDrive_TransMatrix(0.0f, 0.0f, 0.0f);
    CopyMatrix((char *)GOBJ_SUB(self)->f_C, MatrixDrive_GetMatrix());

    {
        float q[4];

        SetCageChainQuaternion(q, *(char **)(*(char **)(w->chains + 8)) + 0x10,
                               *(char **)(*(char **)(w->chains + 8)));
        GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), q,
                                   *(char **)(*(char **)(w->chains + 8)));
        CopyVector((char *)MatrixDrive_GetMatrix() + 0x30,
                   *(char **)(*(char **)(w->chains + 8)) + 0x10);
    }
    MatrixDrive_TransMatrix(0.0f, -(w->linkLength * 0.5f - 20.0f), 0.0f);

    for (i = 0; i < w->linkCount; i++) {
        MatrixDrive_PushMatrix();
        MatrixDrive_RotMatrixX(-32768);
        CopyMatrix((char *)w->dobj->f_C + i * 64, MatrixDrive_GetMatrix());
        MatrixDrive_PopMatrix();
        MatrixDrive_TransMatrix(0.0f, -w->linkLength, 0.0f);
    }
}

void CageDL(char *self)
{
    CageWork *w = GOBJ_SUB(self)->f_830;

    p2o_DispVU1(self);
    p2o_DispVU1DObjMulti(w->dobj);
}

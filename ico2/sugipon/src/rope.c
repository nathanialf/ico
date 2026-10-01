#include "rope.h"
#include "debug.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "memory.h"
#include "sugiCommon.h"
#include <libvu0.h>
#include "debug_exception.h"
#include "main.h"
#include "fieldCollision.h"
#include "DisplayP2O.h"
#include "ios.h"
#include <assert.h>

/* float (void *, void *, float) here, float (int *, void *, float) in clothAnimation.h */
extern float GetChainCollision(void *a0, void *a1, float w);
/* int (void *) here, void * (char *) in clothAnimation.h */
extern int InitChains(void *c);

/* The chain template the rope starts from: two 0x50-byte records, the
   halves of the chain system record below, copied whole with doubleword
   moves, so the record carries 8-byte alignment (its zero doubleword at
   0x18 is spelled as one, as particleEffect.c's staging record does). */
typedef struct { /* field names derived */
    int n;       /* 0x00, the node count */
    int pad04[3];
    int node;        /* 0x10, the skeleton node the chain hangs from, -1 for none */
    float step;      /* 0x14, the length of one segment */
    long long pad18; /* 0x18 */
    float pos[4];    /* 0x20, where the chain starts */
    int pad30[4];
    float weight; /* 0x40, against the extended weights */
    int pad44[3];
} RopeTemplate; /* derived name */

/* the zero vector HoldRope clears the holder's offset with, then the
   template */
static float ropeZeroVector[4] = {0.0f, 0.0f, 0.0f, 0.0f}; /* derived name */

static RopeTemplate ropeChainInit[2] = {
    /* derived name */
    {55, {0, 0, 0}, -1, 20.0f, 0, {0.0f, 0.0f, 0.0f, 1.0f}, {0, 0, 0, 0}, 10.0f},
    {-1},
}; /* derived name */

typedef struct { /* field names derived */
    int a;
    int b;
} RopePair; /* derived name */

/* The chain system record the rope allocates (0xA0 bytes, two template halves). */
typedef struct { /* field names derived */
    /* 0x00 */ int n;
    /* 0x04 */ int pad04[4];
    /* 0x14 */ float step;
    /* 0x18 */ int pad18[2];
    /* 0x20 */ float pos[4];
    /* 0x30 */ int pad30[4];
    /* 0x40 */ float weight;
    /* 0x44 */ int pad44[23];
} RopeChainSys; /* derived name */

/* The wall-clip request, the same record ico2/omori/src/chain.c hands to
   ClipWall (endpoints at 0x00 and 0x10, hit flag at 0x88); the rope also reads
   the 8 bytes at 0x80. */
typedef struct { /* field names derived */
    /* 0x00 */ float from[4];
    /* 0x10 */ float to[4];
    /* 0x20 */ char _20[0x60];
    /* 0x80 */ RopePair out;
    /* 0x88 */ void *hit; /* the wall hit; fieldCollision.c reads it as a pointer */
    /* 0x8C */ char _8c[0x34];
} RopeClipWork; /* derived name */

typedef struct {                       /* field names derived */
    /* 0x00 */ int chains;             /* InitChains' chain system */
    /* 0x04 */ int upperWallClimbable; /* a wall was found above the rope */
    /* 0x08 */ RopePair wallSrc;       /* that wall's slot pair */
    /* 0x10 */ void *wall;             /* that wall */
} RopeGeoWork;                         /* derived name */

void *InitRopeGeo(GObj *o, const float *p)
{
    RopeChainSys *c;
    Sub15C *sub;
    RopeGeoWork *w;
    int i;

    sub = o->dobj;
    w = (RopeGeoWork *)iosMallocDebug(ios_partition_sugipon, 0x14, __FILE__, 38);
    c = (RopeChainSys *)iosMallocDebug(ios_partition_sugipon, 0xA0, __FILE__, 39);

    ((RopeTemplate *)c)[0] = ropeChainInit[0];
    ((RopeTemplate *)c)[1] = ropeChainInit[1];
    c->pos[0] = p[0];
    c->pos[1] = p[1];
    c->pos[2] = p[2];
    c->step = p[10];
    c->weight = p[8];
    c->n = (int)(p[9] / c->step);
    if (c->n == 0) {
        /* "The rope is too short. Change scale-y in the table." (EUC-JP) */
        debug_StdPrintfDummy("ロープの長さが短"
                             "すぎます。表のscale-y"
                             "を変更してくださ"
                             "い。\n");
        debug_assert(__FILE__, 51);
        __assert(__FILE__, 51, "0");
    }

    if (p[4] != 0.0f) {
        sceVu0FVECTOR v0 = {0.0f, 0.0f, -10.0f, 1.0f};
        sceVu0FVECTOR v1 = {0.0f, 0.0f, 10.0f, 1.0f};
        RopeClipWork cw;

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(p[0], p[1] + 10.0f, p[2]);
        MatrixDrive_RotMatrixY(p[5] * 10430.378f);
        sceVu0ApplyMatrix(cw.from, MatrixDrive_GetMatrix(), &v0);
        sceVu0ApplyMatrix(cw.to, MatrixDrive_GetMatrix(), &v1);
        ClipWall(&cw);
        if (cw.hit == 0) {
            /* "Cannot find the wall above the rope. Is the direction wrong, or
               is it placed where there is no wall?" (EUC-JP, in yellow) */
            debug_StdPrintfDummy("\033[33m鎖の上の壁を見"
                                 "付けることができ"
                                 "ません。\n方向が間"
                                 "違っているか、壁"
                                 "が無いところに置"
                                 "いていませんか?\033[m\n");
            debug_assert(__FILE__, 69);
            __assert(__FILE__, 69, "0");
        }
        w->wallSrc = cw.out;
        w->wall = cw.hit;
        w->upperWallClimbable = 1;
    } else {
        w->wallSrc.a = 0;
        w->wallSrc.b = 0;
        w->wall = 0;
        w->upperWallClimbable = 0;
    }

    if (sub->nodeMtx != 0) {
        iosFree((void *)(sub->nodeMtx & 0x0FFFFFFF));
    }
    if (sub->nodeQuat != 0) {
        iosFree((void *)(sub->nodeQuat & 0x0FFFFFFF));
    }
    *(void **)((char *)sub + 0xC) = 0;
    *(void **)((char *)sub + 0x10) = 0;
    *(void **)((char *)sub + 0xC) =
        iosMallocDebug(ios_partition_seki, (c->n - 1) * 64, __FILE__, 82);
    *(void **)((char *)sub + 0x10) =
        iosMallocDebug(ios_partition_seki, (c->n - 1) * 16, __FILE__, 82);
    sub->nodeNum = *(int *)c - 1;
    if ((int)sub->nodes != 0) {
        iosFree((void *)((int)sub->nodes & 0x0FFFFFFF));
    }
    sub->nodes = iosMallocDebug(ios_partition_seki, (c->n - 1) * 80, __FILE__, 82);
    for (i = 0; i < c->n - 1; i++) {
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->flags.ll &= ~1;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->flags.ll &= ~2;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->pos[0] = 0.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->pos[1] = 0.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->pos[2] = 0.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->pos[3] = 1.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->flags.ll &= ~4;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            /* a float store, where the other expansions of this reset write
               an int */
            e->fade = 0.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->alpha = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)sub->nodes);
            *(short *)(e + 0x3A) = 0;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->scale[0] = 1.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->scale[1] = 1.0f;
        }
        {
            struct DObjNode *e = (struct DObjNode *)(i * 80 + (int)sub->nodes);
            e->scale[2] = 1.0f;
        }
    }
    sub->dispType = 2;
    w->chains = InitChains(c);
    sub->nodes->scale[0] = sub->nodes->scale[1] = sub->nodes->scale[2] = 1.0f;
    sub->nodes->rot[0] = sub->nodes->rot[1] = sub->nodes->rot[2] = 0;
    return w;
}

inline int CheckRopeUpperWallClimbable(int a0, GObj *a1)
{
    return *(int *)((char *)GOBJ_SUB(a1)->work + 4);
}

void SetRopeFixPoint(GObj *a0, void *a1)
{
    CopyVector(**(char ***)((char *)GOBJ_SUB(a0)->work) + 0x20, a1);
}

/* The actor's 0x15C sub-object slot: the engine stores a different per-actor
   struct pointer in it depending on the actor, so it is a union of pointers. */
typedef union { /* field names derived */
    char *b;
    float *f;
    int *i;
} Sub15CRef; /* derived name */

/* float (void *) here, float (int, float) in clothAnimation.h */
extern float GetChainNodeID(void *n);
/* int (void *, int, float, float) here, int (int *, int, float, float) in clothAnimation.h */
extern int SetChainExtendedWeight(void *a0, int a1, float f12, float f13);

void HoldRope(void *a0, void *a1)
{
    float v[4];
    float u[4];
    void **p = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);
    void **sys = (void **)p[0];
    int n = (int)GetChainNodeID(sys[0]);
    int w1 = SetChainExtendedWeight(sys[2], n, 0.0f, 100.0f);
    int w2 = SetChainExtendedWeight(sys[2], n, 100.0f, 300.0f);

    GetRootPosition(v, a1);
    CopyVector(u, GOBJ_SUB(a1)->root.move);
    CopyVector((float *)((char *)sys[2] + (w1 * 0x50 + 0x10)) + 12, u);
    CopyVector((float *)((char *)sys[2] + (w2 * 0x50 + 0x10)) + 12, u);
    CopyVector((float *)((char *)sys[2] + (w1 * 0x50 + 0x10)) + 4, v);
    CopyVector((float *)((char *)sys[2] + (w2 * 0x50 + 0x10)) + 4, v);
    CopyVector((float *)((char *)sys[2] + (w1 * 0x50 + 0x10)) + 8, v);
    CopyVector((float *)((char *)sys[2] + (w2 * 0x50 + 0x10)) + 8, v);
    {
        float *q = (float *)((char *)sys[2] + w1 * 0x50);
        q[9] -= 100.0f;
        q[13] -= 100.0f;
    }
    CopyVector(((Sub15CRef *)((char *)a1 + 0x15C))->b + 0x130, ropeZeroVector);
    debug_StdPrintfDummy("HOLD ROPE\n");
}

inline void ReleaseRope(void) {}

/* as in clothAnimation.h, which this file does not include */
extern void GetChainAnimation(void *sys, int obj, void *mtx);

void ropeGeo(void *a0)
{
    void **obj = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);

    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    if (**(int **)((char *)a0 + 0x15C) != 0) {
        sceVu0MulMatrix(MatrixDrive_GetMatrix(),
                        *(char **)(*(char **)(**(char ***)((char *)a0 + 0x15C) + 0x15C) + 0xC) +
                            (*(int *)(*(char **)((char *)a0 + 0x15C) + 4) << 6),
                        MatrixDrive_GetMatrix());
    }
    GetChainAnimation(obj[0], 0, MatrixDrive_GetMatrix());
}

/* extra chains hung from the rope; none in the release build */
#define ROPE_EXTRA_CHAINS 0 /* derived name */

static inline void ropeChainCollision(void *a0) /* derived name */
{
    void *g = boyGObj;
    void **obj = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);
    float m[4];
    float w;
    int i;

    GetRootPosition(m, g);
    w = GetChainCollision(obj[0], m, 200.0f);
    if (0.0f < w) {
        *(float *)((char *)*(void **)((char *)g + 0x15C) + 0x618) = w;
        /* the rope's extra chains, none in the release build */
        for (i = 0; i < ROPE_EXTRA_CHAINS; i++) {
            w = GetChainCollision(obj[i + 1], m, w);
        }
    }
}

inline void RopeGeo(void *a0)
{
    ropeGeo(a0);
    ropeChainCollision(a0);
}

/* void (void *) here, void (int *) in clothAnimation.h */
extern void TestDispChainAnimation(void *a0);

void RopeDL(GObj *a0)
{
    unsigned short ax;
    unsigned short az;
    Sub15C *sub = a0->dobj;
    void **p = *(void ***)((char *)sub + 0x830);
    char *set = (char *)p[0];
    int i;
    int j;
    int n;
    float (*v)[4];

    p2o_SetDefaultEnviroment();
    for (i = 0; i < *(int *)(set + 4); i++) {
        n = *(int *)(*(char **)set + i * 0x50);
        v = (float (*)[4]) * (int *)(*(char **)(set + 8) + i * 0x1A0);
        for (j = 1; j < n; j++) {
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            MatrixDrive_TransMatrix(v[j][0], v[j][1], v[j][2]);
            MatrixDrive_GetTurnYAngleXZ(&ax, &az, v[j][0] - v[j - 1][0], v[j][1] - v[j - 1][1],
                                        v[j][2] - v[j - 1][2]);
            MatrixDrive_RotMatrixX(-ax);
            MatrixDrive_RotMatrixZ(-az);
            MatrixDrive_RotMatrixX(-0x8000);
            MatrixDrive_ScaleMatrix(1.0f, 1.0f, 1.0f);
            CopyMatrix(*(char **)((char *)sub + 0xC) + (j * 0x40 - 0x40), MatrixDrive_GetMatrix());
        }
        p2o_DispVU1DObjMulti(sub);
    }
    if (debug_skel_flag != 0) {
        TestDispChainAnimation(p[0]);
    }
}

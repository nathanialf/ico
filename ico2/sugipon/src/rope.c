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
#include "include_asm.h"

/* The chain functions are declared here, not through clothAnimation.h:
   HoldRope calls GetChainNodeID with the parameter record alone (it writes
   no $f12 before the call), where the definition takes the length as a
   second argument.  The chain system is held as a void * (RopeGeoWork). */
extern float GetChainCollision(void *sys, void *pos, float r);
extern void *InitChains(void *c);

/* The chain list the rope starts from, in clothAnimation.h's ChainCfg
   layout (unreachable here, above): two 0x50-byte records, the second
   ending the list, copied whole into the allocated list with doubleword
   moves, so the record carries 8-byte alignment (its zero doubleword at
   0x18 is spelled as one, as particleEffect.c's staging record does). */
typedef struct { /* field names derived */
    int num;     /* 0x00, the node count, -1 ends the list */
    int pad04[3];
    int node;        /* 0x10, the skeleton node the chain hangs from, -1 for none */
    float step;      /* 0x14, the length of one segment */
    long long pad18; /* 0x18 */
    float root[4];   /* 0x20, where the chain starts */
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

typedef struct {                       /* field names derived */
    /* 0x00 */ void *chains;           /* InitChains' chain system */
    /* 0x04 */ int upperWallClimbable; /* a wall was found above the rope */
    /* 0x08 */ ObjNode wallSrc;        /* that wall's object and node */
    /* 0x10 */ FcWallEnt *wall;        /* that wall */
} RopeGeoWork;                         /* derived name */

INCLUDE_ASM(InitRopeGeo);

inline int CheckRopeUpperWallClimbable(int unused, GObj *rope)
{
    RopeGeoWork *w = GOBJ_SUB(rope)->work;

    return w->upperWallClimbable;
}

void SetRopeFixPoint(GObj *rope, void *pos, int flag)
{
    CopyVector(**(char ***)((char *)GOBJ_SUB(rope)->work) + 0x20, pos);
}

extern float GetChainNodeID(void *cfg);
extern int SetChainExtendedWeight(void *node, int idx, float w0, float w1);

void HoldRope(GObj *rope, GObj *holder)
{
    float v[4];
    float u[4];
    RopeGeoWork *w = GOBJ_SUB(rope)->work;
    void **sys = w->chains;
    int n = (int)GetChainNodeID(sys[0]);
    int w1 = SetChainExtendedWeight(sys[2], n, 0.0f, 100.0f);
    int w2 = SetChainExtendedWeight(sys[2], n, 100.0f, 300.0f);

    GetRootPosition(v, holder);
    CopyVector(u, GOBJ_SUB(holder)->root.move);
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
    /* read through the SubHandle union: GOBJ_SUB's int read is hoisted
       above the float stores (measured) */
    CopyVector(((SubHandle *)&holder->dobj)->sub->root.move, ropeZeroVector);
    debug_StdPrintfDummy("HOLD ROPE\n");
}

inline void ReleaseRope(void) {}

extern void GetChainAnimation(void *sys, int obj, void *mtx);

static void ropeGeo(GObj *rope)
{
    RopeGeoWork *w = GOBJ_SUB(rope)->work;

    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    if (GOBJ_SUB(rope)->parent.obj != 0) {
        sceVu0MulMatrix(MatrixDrive_GetMatrix(),
                        (char *)GOBJ_SUB(GOBJ_SUB(rope)->parent.obj)->nodeMtx +
                            (GOBJ_SUB(rope)->parent.node << 6),
                        MatrixDrive_GetMatrix());
    }
    GetChainAnimation(w->chains, 0, MatrixDrive_GetMatrix());
}

/* extra chains hung from the rope; none in the release build */
#define ROPE_EXTRA_CHAINS 0 /* derived name */

static inline void ropeChainCollision(GObj *rope) /* derived name */
{
    GObj *g = boyGObj;
    void **obj = GOBJ_SUB(rope)->work;
    float m[4];
    float w;
    int i;

    GetRootPosition(m, g);
    w = GetChainCollision(obj[0], m, 200.0f);
    if (0.0f < w) {
        GOBJ_SUB(g)->ctrl.ropeHangPos = w;
        /* the rope's extra chains, none in the release build */
        for (i = 0; i < ROPE_EXTRA_CHAINS; i++) {
            w = GetChainCollision(obj[i + 1], m, w);
        }
    }
}

inline void RopeGeo(GObj *rope)
{
    ropeGeo(rope);
    ropeChainCollision(rope);
}

extern void TestDispChainAnimation(void *sys);

void RopeDL(GObj *rope)
{
    unsigned short ax;
    unsigned short az;
    Sub15C *sub = rope->dobj;
    RopeGeoWork *w = sub->work;
    char *set = w->chains;
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
            CopyMatrix((char *)sub->nodeMtx + (j * 64 - 64), MatrixDrive_GetMatrix());
        }
        p2o_DispVU1DObjMulti(sub);
    }
    if (debug_skel_flag != 0) {
        TestDispChainAnimation(w->chains);
    }
}

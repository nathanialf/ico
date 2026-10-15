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

void SetRopeFixPoint(GObj *rope, void *pos, int flag)
{
    CopyVector(**(char ***)((char *)GOBJ_SUB(rope)->work) + 0x20, pos);
}

extern float GetChainNodeID(void *cfg);
extern int SetChainExtendedWeight(void *node, int idx, float w0, float w1);

INCLUDE_ASM(HoldRope);

extern void GetChainAnimation(void *sys, int obj, void *mtx);

INCLUDE_ASM(ropeGeo);

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

extern void TestDispChainAnimation(void *sys);

INCLUDE_ASM(RopeDL);

INCLUDE_ASM(CheckRopeUpperWallClimbable);

INCLUDE_ASM(ReleaseRope);

INCLUDE_ASM(RopeGeo);

#include "cage.h"
#include "box.h"
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
#include "memory.h"
#include "windField.h"
#include "sceneManager.h"
#include "DObj.h"
#include "include_asm.h"

/* the cage's 80-byte work record, InitCageGeo's allocation, kept at +0x830
   of the object's motion work: the cage and chain DObjs, the cage's rotation
   and turn, the chains InitChains builds and the swing state */
typedef struct {   /* field names derived */
    Sub15C *dobj;  /* 0x00 */
    Sub15C *dobj2; /* 0x04 */
    char pad08[8];
    float rot[4];     /* 0x10 */
    ChainSet *chains; /* 0x20 */
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

INCLUDE_ASM(CageRideFunc);

INCLUDE_ASM(SetCageFixGeometry);

/* the cage's one chain, 2 nodes 500 apart hanging from the cage root */
static ChainCfg cageChainParam[2] = {
    {2, {0, 0, 0}, {-1, 500.0f, {0, 0}, {0.0f, 0.0f, 0.0f, 1.0f}, {0, 0, 0, 0}, 100.0f}},
    {-1},
}; /* derived name */

INCLUDE_ASM(InitCageGeo);

INCLUDE_ASM(HotInitCageGeo);

/* the world down axis the chain's swing axis is taken against */
static sceVu0FVECTOR cageDown = {0.0f, -1.0f, 0.0f, 0.0f}; /* derived name */

static inline void SetCageChainQuaternion(void *q, void *a, void *b) /* derived name */
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

static inline void AddCageWindForce(ExW *n, float k) /* derived name */
{
    float v[4];

    CopyVector(v, GetWindVector(0, &n->v1.x));
    _ScaleVector(v, v, k / n->len1);
    _AddVector(&n->v2, &n->v2, v);
}

INCLUDE_ASM(CageGeo);

INCLUDE_ASM(CageDL);

INCLUDE_ASM(GetCageChainPoint);

INCLUDE_ASM(SetCageVelocityFriction);

INCLUDE_ASM(StabilizeAllLayoutedCage);

INCLUDE_ASM(SetCageChainHangableFlag);

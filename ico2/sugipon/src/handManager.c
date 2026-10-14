#include "handManager.h"
#include "fieldCollision.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "motionManager2.h"
#include "tableSin.h"
#include "typedef.h"
#include "debug.h"
#include "Matrix.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "include_asm.h"

static void connectToTarget(struct GObj *obj, HandRec *hw, int na, int nb, int nc);

/* getBone is defined as a nested function inside connectToTarget below. */

INCLUDE_ASM(getBone_6);

INCLUDE_ASM(connectToTarget);

static inline void SetHandQuaternion(HandRec *hw, char *vec, float *ref) /* derived name */
{
    float *q = hw->ikQuat;
    Vec4 n;
    Vec4 v;
    short ang;

    v.f[0] = *(float *)(vec + 0);
    v.f[1] = *(float *)(vec + 4);
    v.f[2] = *(float *)(vec + 8);
    v.f[3] = 0.0f;
    n = v;
    _NormalizeVector(&n, &n);
    ang = GetTableArcCos(_InnerProduct(&n, ref));
    if (ang != 0) {
        _OuterProduct(&v, &n, ref);
        SetQuaternionByAxisRotateVWithNoRegularize(q, ang, v.f);
    } else {
        SetIdentityQuaternion(q);
    }
}

static inline void FollowHandMatrix(HandRec *hw, char *vec, float *ref) /* derived name */
{
    _ApplyMatrix(hw->ikDir, (char *)GOBJ_SUB(hw->obj)->nodeMtx + (hw->node << 6), hw->pos);
    SetHandQuaternion(hw, vec, ref);
}

static inline int SetHandOnWall(GObj *obj, HandRec *hw, char *vec, float *ref,
                                int node) /* derived name */
{
    Vec4 plane;

    if (GOBJ_SUB(obj)->root.wall.elem == 0) {
        return 0;
    }
    GetGlobalWallPlane(plane.f, &GOBJ_SUB(obj)->root.wall);
    GetProjectionOfPlane(hw->ikDir, &plane, (char *)GOBJ_SUB(obj)->nodeMtx + (node << 6) + 0x30);
    SetHandQuaternion(hw, vec, ref);
    return 1;
}

static inline int PutHandOnLadder(HandRec *hw, int node) /* derived name */
{
    CopyMatrix(MatrixDrive_GetMatrix(), (char *)GOBJ_SUB(hw->obj)->nodeMtx + (node << 6));
    MatrixDrive_TransMatrix(7.0f, -4.0f, 0.0f);
    CopyVector(hw->ikDir, MatrixDrive_GetMatrix()[3]);
    if (hw->ikReached == 0) {
        return 0;
    }
    ExecuteSEPackage(hw->obj, 102);
    return 1;
}

INCLUDE_ASM(_handManager);

/* not from motionOrientManager.h, which reaches ico2/fumi's files through
   typedef.h, where commonact.c declares the table char [] */
extern const MotionDef motionKind[];
extern char motionIKEffKind[];

/* the hand record at off in the display object, walked by offset: as
   HandRec fields the second GOBJ_SUB read merges with the first and
   HandManager loses its reload (measured) */
static inline void ResetHandTarget(GObj *obj, int off) /* derived name */
{
    char *h = (char *)(int)GOBJ_SUB(obj) + off;
    *(int *)(h + 0x20) = 0;
    *(int *)(h + 0x24) = 0;
    ((IntFloat *)(h + 0x50))->f = GOBJ_SUB(obj)->root.handRate;
}

INCLUDE_ASM(HandManager);

INCLUDE_ASM(func_001D2538);

INCLUDE_ASM(func_001D2540);

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

/* getBone is defined as a nested function inside connectToTarget below. */

void connectToTarget(GObj *obj, char *hw, int na, int nb, int nc)
{
    /* getBone is a nested function in the ROM: connectToTarget passes it a
     * static chain in $2 (STATIC_CHAIN_REGNUM) and getBone's prologue spills
     * it to 0(sp). */
    void getBone(float *out, GObj *o)
    {
        Sub15C *sub = GOBJ_SUB(o);
        float scale = sub->nodes->scale[0];
        SkelNode *nodes = sub->skel;
        float a;
        float b;
        float c;

        a = nodes[nodes[GetSkeltonFocusNode(o, 19)].child].pos[0];
        if (a < 0.0f) {
            a = -a;
        }
        a *= scale;
        out[0] = a;

        a = nodes[nodes[GetSkeltonFocusNode(o, 20)].child].pos[0];
        if (a < 0.0f) {
            a = -a;
        }
        out[1] = a;

        a = nodes[nodes[GetSkeltonFocusNode(o, 22)].child].pos[0];
        b = out[1];
        if (a < 0.0f) {
            c = b - a;
        } else {
            c = b + a;
        }
        c *= scale;
        out[1] = c;
    }
    float b0[4];
    float b1[4];
    float d[4];
    float n[4];
    float ax[4];
    float u[4];
    float q[4];
    float m[16];
    float v[4];
    float w[4];
    GObj *tgt;
    float sa;
    float sb;
    float len;

    tgt = (GObj *)*(int *)(hw + 4);
    getBone(b0, obj);
    getBone(b1, tgt);
    sa = b0[0] + b0[1];
    sb = b1[0] + b1[1];
    _SubVector(d, (char *)GOBJ_SUB(obj)->nodeMtx + (na << 6) + 0x30,
               (char *)GOBJ_SUB(tgt)->nodeMtx + (nc << 6) + 0x30);
    len = VectorLength(d);
    CopyVector(n, d);
    n[1] = 0.0f;
    _NormalizeVector(n, n);
    _OuterProduct(ax, n, YUnitVector);
    if (sa + sb < len) {
        _SubVector(u, (char *)GOBJ_SUB(tgt)->nodeMtx + (nb << 6) + 0x30,
                   (char *)GOBJ_SUB(obj)->nodeMtx + (na << 6) + 0x30);
        _NormalizeVector(u, u);
        _ScaleVector(u, u, sb);
        _SubVector(hw + 0x30, (char *)GOBJ_SUB(tgt)->nodeMtx + (nb << 6) + 0x30, u);
    } else {
        float ex = (sa + sb - len) * 0.0f;
        float l = len - ex * 0.0f;
        float ll = l * l;
        float s = sa - ex * 0.5f;
        float t = sb - ex * 0.5f;
        float ss = s * s;
        float tt = t * t;
        float l2 = l + l;

        sa = s;
        SetQuaternionByAxisRotateV(q, GetTableArcCos((ll + ss - tt) / (l2 * sa)), ax);
        GetMatrixFromQuaternion(m, q);
        _SubVector(v, (char *)GOBJ_SUB(tgt)->nodeMtx + (nb << 6) + 0x30,
                   (char *)GOBJ_SUB(obj)->nodeMtx + (na << 6) + 0x30);
        sb = v[0] * v[0] + v[2] * v[2];
        _NormalizeVector(v, v);
        _ScaleVector(v, v, sa);
        _ApplyMatrix(v, m, v);
        CopyVector(w, v);
        w[1] = 0.0f;
        if (sb < VectorLengthSquare(w)) {
            len = _Sqrt(sb);
            v[1] = 0.0f;
            _NormalizeVector(v, v);
            _ScaleVectorXYZ(v, v, len);
            v[1] = _Sqrt(ss - sb);
        }
        _AddVector(hw + 0x30, (char *)GOBJ_SUB(obj)->nodeMtx + (na << 6) + 0x30, v);
    }
}

static inline void SetHandQuaternion(char *hw, char *vec, char *ref)
{
    char *q = hw + 0x40;
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
        SetQuaternionByAxisRotateVWithNoRegularize(q, ang, &v);
    } else {
        SetIdentityQuaternion(q);
    }
}

static inline void FollowHandMatrix(char *hw, char *vec, char *ref)
{
    _ApplyMatrix(hw + 0x30,
                 (char *)*(int *)(*(int *)(*(int *)(hw + 4) + 0x15C) + 0xC) +
                     (*(int *)(hw + 8) << 6),
                 hw + 0x10);
    SetHandQuaternion(hw, vec, ref);
}

static inline int SetHandOnWall(GObj *obj, char *hw, char *vec, char *ref, int node)
{
    Vec4 plane;

    if (GOBJ_SUB(obj)->root.wall.n == 0) {
        return 0;
    }
    GetGlobalWallPlane(&plane, (char *)(int)GOBJ_SUB(obj) + 0x180);
    GetProjectionOfPlane(hw + 0x30, &plane, (char *)GOBJ_SUB(obj)->nodeMtx + (node << 6) + 0x30);
    SetHandQuaternion(hw, vec, ref);
    return 1;
}

static inline int PutHandOnLadder(char *hw, int node)
{
    CopyMatrix(MatrixDrive_GetMatrix(),
               (char *)*(int *)(*(int *)(*(int *)(hw + 4) + 0x15C) + 0xC) + (node << 6));
    MatrixDrive_TransMatrix(7.0f, -4.0f, 0.0f);
    CopyVector(hw + 0x30, MatrixDrive_GetMatrix()[3]);
    if (*(int *)(hw + 0x54) == 0) {
        return 0;
    }
    ExecuteSEPackage(*(int *)(hw + 4), 0x66);
    return 1;
}

float _handManager(GObj *obj, char *hw, char *vec, char *ref, int node)
{
    switch (*(int *)hw) {
    case 2:
        if (SetHandOnWall(obj, hw, vec, ref, node) != 0) {
            *(int *)(hw + 0x20) = 2;
        }
        break;
    case 3:
        FollowHandMatrix(hw, vec, ref);
        *(int *)(hw + 0x20) = 2;
        break;
    case 6:
        PutHandOnLadder(hw, GetSkeltonFocusNode(obj, 6));
        if (*(int *)(hw + 0x58) != 0) {
            *(float *)(hw + 0x50) = 0.5f;
            *(int *)(hw + 0x24) = 1;
        }
        *(int *)(hw + 0x20) = 1;
        break;
    case 5:
        connectToTarget(obj, hw, node, GetSkeltonFocusNode(obj, 0x13),
                        GetSkeltonFocusNode(obj, 0x13));
        *(int *)(hw + 0x20) = 1;
        break;
    case 1:
        _ApplyMatrix(hw + 0x30,
                     (char *)*(int *)(*(int *)(*(int *)(hw + 4) + 0x15C) + 0xC) +
                         (*(int *)(hw + 8) << 6),
                     hw + 0x10);
        if (*(int *)(hw + 0x54) != 0) {
            *(float *)(hw + 0x50) = 0.5f;
            *(int *)(hw + 0x24) = 1;
        }
        *(int *)(hw + 0x20) = 1;
        break;
    }
    return 1.0f;
}

/* kept local: motionOrientManager.h reaches ico2/fumi's TUs through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];
extern char motionIKEffKind[];

static inline void ResetHandTarget(GObj *obj, int off)
{
    char *h = (char *)(int)GOBJ_SUB(obj) + off;
    *(int *)(h + 0x20) = 0;
    *(int *)(h + 0x24) = 0;
    ((IntFloat *)(h + 0x50))->f = GOBJ_SUB(obj)->root.handRate;
}

void HandManager(GObj *obj)
{
    float t = 1.0f;

    if (debug_now_motion_viewer == 0) {
        ResetHandTarget(obj, 0x310);
        ResetHandTarget(obj, 0x2B0);
        if (GOBJ_SUB(obj)->root.handIK != 0) {
            const MotionDef *rec = &motionKind[GOBJ_SUB(obj)->ctrl.motion];
            _handManager(obj, (char *)(int)GOBJ_SUB(obj) + 0x310,
                         motionIKEffKind + ((rec->modeBits.word >> 8) & 0xF0), XUnitVector,
                         GetSkeltonFocusNode(obj, 0x13));
            t = _handManager(obj, (char *)(int)GOBJ_SUB(obj) + 0x2B0,
                             motionIKEffKind + ((rec->modeBits.word >> 4) & 0xF0), XUnitVector,
                             GetSkeltonFocusNode(obj, 3));
        }
        GOBJ_SUB(obj)->root.twistRate += (t - GOBJ_SUB(obj)->root.twistRate) * 0.1f;
    }
}

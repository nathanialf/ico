#include "common.h"

/* getBone is defined as a nested function inside connectToTarget below. */
extern char D_0028FF20[];
extern void _SubVector(void *dst, void *a, void *b);
extern void _AddVector(void *dst, void *a, void *b);
extern float VectorLength(void *v);
extern float VectorLengthSquare(void *v);
extern void _ScaleVector(void *dst, void *src, float k);
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
extern float _Sqrt(float x);
extern void SetQuaternionByAxisRotateV(void *dst, int ang, void *axis);
extern void GetMatrixFromQuaternion(void *dst, void *q);
extern void CopyVector(void *dst, void *src);
extern void _NormalizeVector(void *dst, void *src);
extern void _OuterProduct(void *dst, void *a, void *b);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern int GetTableArcCos(float x);
extern int GetSkeltonFocusNode(char *obj, int kind);

void connectToTarget(char *obj, char *hw, int na, int nb, int nc)
{
    /* getBone is a nested function in the ROM: connectToTarget passes it a
     * static chain in $2 (STATIC_CHAIN_REGNUM) and getBone's prologue spills
     * it to 0(sp). */
    void getBone(float *out, char *o)
    {
        int sub = *(int *)(o + 0x15C);
        float scale = *(float *)(*(int *)(sub + 0x870) + 0x20);
        int nodes = *(int *)(sub + 0x8C);
        float a;
        float b;
        float c;

        a = *(float *)((*(int *)((GetSkeltonFocusNode(o, 0x13) << 6) + nodes + 0x30) << 6) + nodes + 0x10);
        if (a < 0.0f) {
            a = -a;
        }
        a *= scale;
        out[0] = a;

        a = *(float *)((*(int *)((GetSkeltonFocusNode(o, 0x14) << 6) + nodes + 0x30) << 6) + nodes + 0x10);
        if (a < 0.0f) {
            a = -a;
        }
        out[1] = a;

        a = *(float *)((*(int *)((GetSkeltonFocusNode(o, 0x16) << 6) + nodes + 0x30) << 6) + nodes + 0x10);
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
    char *tgt;
    float sa;
    float sb;
    float len;

    tgt = (char *)*(int *)(hw + 4);
    getBone(b0, obj);
    getBone(b1, tgt);
    sa = b0[0] + b0[1];
    sb = b1[0] + b1[1];
    _SubVector(d,
               (char *)*(int *)(*(int *)(obj + 0x15C) + 0xC) + (na << 6) + 0x30,
               (char *)*(int *)(*(int *)(tgt + 0x15C) + 0xC) + (nc << 6) + 0x30);
    len = VectorLength(d);
    CopyVector(n, d);
    n[1] = 0.0f;
    _NormalizeVector(n, n);
    _OuterProduct(ax, n, D_0028FF20);
    if (sa + sb < len) {
        _SubVector(u,
                   (char *)*(int *)(*(int *)(tgt + 0x15C) + 0xC) + (nb << 6) + 0x30,
                   (char *)*(int *)(*(int *)(obj + 0x15C) + 0xC) + (na << 6) + 0x30);
        _NormalizeVector(u, u);
        _ScaleVector(u, u, sb);
        _SubVector(hw + 0x30,
                   (char *)*(int *)(*(int *)(tgt + 0x15C) + 0xC) + (nb << 6) + 0x30,
                   u);
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
        _SubVector(v,
                   (char *)*(int *)(*(int *)(tgt + 0x15C) + 0xC) + (nb << 6) + 0x30,
                   (char *)*(int *)(*(int *)(obj + 0x15C) + 0xC) + (na << 6) + 0x30);
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
        _AddVector(hw + 0x30,
                   (char *)*(int *)(*(int *)(obj + 0x15C) + 0xC) + (na << 6) + 0x30,
                   v);
    }
}
typedef union { float f[4]; long long ll[2]; } Vec4;

extern void GetGlobalWallPlane(void *a0, void *a1);
extern float GetProjectionOfPlane(void *a0, void *a1, void *a2);
extern void _NormalizeVector(void *a0, void *a1);
extern float _InnerProduct(void *a0, void *a1);
extern int GetTableArcCos(float a0);
extern void _OuterProduct(void *a0, void *a1, void *a2);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *a0, int a1, void *a2);
extern void SetIdentityQuaternion(void *a0);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrix(float a0, float a1, float a2);
extern void CopyMatrix(void *dst, void *src);
extern void CopyVector(void *dst, void *src);
extern void ExecuteSEPackage(int a0, int a1);
extern int GetSkeltonFocusNode(char *obj, int kind);
extern void connectToTarget(char *obj, char *hw, int node, int n0, int n1);

static inline void SetHandQuaternion(char *hw, char *vec, char *ref)
{
    char *q = hw + 0x40;
    Vec4 n;
    Vec4 v;
    int ang;

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
                 (char *)*(int *)(*(int *)(*(int *)(hw + 4) + 0x15C) + 0xC)
                     + (*(int *)(hw + 8) << 6),
                 hw + 0x10);
    SetHandQuaternion(hw, vec, ref);
}

static inline int SetHandOnWall(char *obj, char *hw, char *vec, char *ref, int node)
{
    Vec4 plane;

    if (*(int *)(*(int *)(obj + 0x15C) + 0x188) == 0) {
        return 0;
    }
    GetGlobalWallPlane(&plane, (char *)*(int *)(obj + 0x15C) + 0x180);
    GetProjectionOfPlane(hw + 0x30, &plane,
                         (char *)*(int *)(*(int *)(obj + 0x15C) + 0xC)
                             + (node << 6) + 0x30);
    SetHandQuaternion(hw, vec, ref);
    return 1;
}

static inline int PutHandOnLadder(char *hw, int node)
{
    CopyMatrix(MatrixDrive_GetMatrix(),
               (char *)*(int *)(*(int *)(*(int *)(hw + 4) + 0x15C) + 0xC)
                   + (node << 6));
    MatrixDrive_TransMatrix(7.0f, -4.0f, 0.0f);
    CopyVector(hw + 0x30, (char *)MatrixDrive_GetMatrix() + 0x30);
    if (*(int *)(hw + 0x54) == 0) {
        return 0;
    }
    ExecuteSEPackage(*(int *)(hw + 4), 0x66);
    return 1;
}

float _handManager(char *obj, char *hw, char *vec, char *ref, int node)
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
        connectToTarget(obj, hw, node,
                        GetSkeltonFocusNode(obj, 0x13),
                        GetSkeltonFocusNode(obj, 0x13));
        *(int *)(hw + 0x20) = 1;
        break;
    case 1:
        _ApplyMatrix(hw + 0x30,
                     (char *)*(int *)(*(int *)(*(int *)(hw + 4) + 0x15C) + 0xC)
                         + (*(int *)(hw + 8) << 6),
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
typedef union { int i; float f; } IntFloat;

extern int D_0063B198;
extern float D_0063952C;
extern char D_0055FE58[];
extern char D_005D1208[];
extern char D_0028FF10[];
extern int GetSkeltonFocusNode(char *obj, int kind);
extern float _handManager(char *obj, char *hand, char *bone, char *axis, int node);

static inline void ResetHandTarget(char *obj, int off)
{
    char *h = (char *)*(int *)(obj + 0x15C) + off;
    *(int *)(h + 0x20) = 0;
    *(int *)(h + 0x24) = 0;
    ((IntFloat *)(h + 0x50))->f = *(float *)(*(int *)(obj + 0x15C) + 0x460);
}

void HandManager(char *obj)
{
    float t = 1.0f;

    if (D_0063B198 == 0) {
        ResetHandTarget(obj, 0x310);
        ResetHandTarget(obj, 0x2B0);
        if (*(int *)(*(int *)(obj + 0x15C) + 0x400) != 0) {
            char *rec = D_0055FE58 + *(int *)(*(int *)(obj + 0x15C) + 0x4A0) * 0x194;
            _handManager(obj, (char *)*(int *)(obj + 0x15C) + 0x310,
                         D_005D1208 + ((*(unsigned int *)(rec + 0x188) >> 8) & 0xF0),
                         D_0028FF10, GetSkeltonFocusNode(obj, 0x13));
            t = _handManager(obj, (char *)*(int *)(obj + 0x15C) + 0x2B0,
                             D_005D1208 + ((*(unsigned int *)(rec + 0x188) >> 4) & 0xF0),
                             D_0028FF10, GetSkeltonFocusNode(obj, 3));
        }
        *(float *)(*(int *)(obj + 0x15C) + 0xF4) +=
            (t - *(float *)(*(int *)(obj + 0x15C) + 0xF4)) * D_0063952C;
    }
}

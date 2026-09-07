#include "common.h"

#include "ico/types.h"

#include "vu0.h"

#include "sugiCommon.h"

struct Pack32 { long long a, b, c, d; };

typedef struct { char _0; signed char f1; unsigned char f2; unsigned char f3; } FloorAttr;

typedef struct { long long w[62]; } _0x1F0;

typedef struct { long long d[2]; float q[4]; } StreamElem;
typedef struct { int idx; char pad[0x1C]; float q[4]; char pad2[0x10]; } StreamNode;

extern int GetFloorAttribute();
extern int CompareAttribute();
extern float GetPoolGlobalHeightDetail(int pool, float *pos);
extern void GetPoolGlobalDrainVector(float *dst, int pool);
extern float VectorLengthSquare(float *v);
extern void sceVu0AddVector(float *dst, float *a, float *b);
extern void AddVectorXYZ(float *dst, float *a, float *b);
extern void CopyVector();
extern int D_0028F4C0[];
extern char D_0028FEF0[];

int GetWaterReaction(float *outH, int *outFlag, char *info, float *pos, float *vel,
                     float h0, float h1, float h2, float scaleIn, float amp)
{
    float drain[4];
    float waterH;
    float scale;
    float r;
    int pool;

    if (outFlag != 0) {
        *outFlag = 0;
    }
    if (*(int *)(info + 0x94) != 0) {
        if (CompareAttribute(GetFloorAttribute(info), 0x50) != 0) {
            scale = scaleIn;
            pool = *(int *)(info + 0x8C);
            waterH = GetPoolGlobalHeightDetail(pool, pos);
            GetPoolGlobalDrainVector(drain, pool);
            if (outFlag != 0) {
                if (1.0000001e-06f < VectorLengthSquare(drain)) {
                    *outFlag = 1;
                }
            }
            if (waterH < h0) {
                vel[1] = vel[1] + amp;
            } else if (waterH < h1) {
                vel[1] = vel[1] + amp * (h1 - waterH) / (h1 - h0);
            } else if (waterH < h2) {
                r = (waterH - h1) / (h2 - h1);
                vel[1] = vel[1]
                       + (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f
                          * (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]))
                          + amp * (1.0f - r)) * r;
            } else {
                vel[1] = vel[1]
                       + 60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f
                         * (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
                scale = 1.0f;
                CopyVector(drain, D_0028FEF0);
            }
            vel[0] = vel[0] * scale;
            vel[1] = vel[1] * scale;
            vel[2] = vel[2] * scale;
            sceVu0AddVector(vel, vel, drain);
            AddVectorXYZ(pos, pos, vel);
            if (outH != 0) {
                *outH = waterH;
            }
            return 1;
        }
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", dispPlane);
extern void CopyVector();

void GetOrientOfWallOfGObj(int a0, int a1)
{
    CopyVector(a0, (int)((GObj *)(a1))->p_15C + 0x5C0);
}
void GetOrientOfCliffOfGObj(int a0, int a1)
{
    CopyVector(a0, (int)((GObj *)(a1))->p_15C + 0x590);
}
extern void LocalizeDirectionOrient(char *a0, void *a1);
extern void sceVu0Normalize(int *a0, int *a1);

void SetMotionDirection(void *a0, float *a1) {
    char *base = *(char **)((char *)a0 + 0x15C);
    char *s2 = base + 0x470;
    char *m;
    char *ctrl;
    if (a1[0] == 0.0f && a1[2] == 0.0f) {
        return;
    }
    m = base + 0x520;
    CopyVector((int)m, a1);
    *(float *)(s2 + 0xB4) = 0.0f;
    *(float *)(s2 + 0xBC) = 1.0f;
    sceVu0Normalize((int *)m, (int *)m);
    ctrl = *(char **)((char *)a0 + 0x15C);
    if (*(int *)ctrl == 0) {
        return;
    }
    LocalizeDirectionOrient(a0, ctrl);
}
extern void GetGlobalDirectionOrient();

void _GetMotionDirection(int a0, int a1)
{
    GetGlobalDirectionOrient(a0, a1, (int)((GObj *)(a1))->p_15C + 0x520);
}
extern void GetRootQuaternion(float *dst, void *self);
extern void GetInverseQuaternion(float *dst, float *src);
extern void GetMatrixFromQuaternion(float *m, float *q);
extern void sceVu0ApplyMatrix(float *dst, float *m, float *v);
extern void RotQuaternionY(void *q, short ang);
extern float atan2f(float y, float x);
extern float D_0028FF30[];

void SetMotionDirectionWithLimit(void *self, float *dir, float lim0, float lim1)
{
    float q[4];
    float inv[4];
    float m[16];
    float v[4];
    short ang;
    int a;

    GetRootQuaternion(q, self);
    GetInverseQuaternion(inv, q);
    GetMatrixFromQuaternion(m, inv);
    sceVu0ApplyMatrix(v, m, dir);
    sceVu0Normalize((int *)v, (int *)v);
    ang = atan2f(v[0], v[2]) * 10430.378f;
    a = (ang >= 0) ? ang : -ang;
    if (lim1 * 32768.0f / 180.0f < a) {
        return;
    }
    if (a < lim0 * 32768.0f / 180.0f) {
        SetMotionDirection(self, dir);
        return;
    }
    if (ang < 0) {
        RotQuaternionY(q, -(lim0 * 32768.0f / 180.0f));
    } else {
        RotQuaternionY(q, lim0 * 32768.0f / 180.0f);
    }
    GetMatrixFromQuaternion(m, q);
    sceVu0ApplyMatrix(v, m, D_0028FF30);
    SetMotionDirection(self, v);
}
extern void SubVectorXYZ();

void GetRootPosOfNextFrame(int a0, int *a1)
{
  int *p = (int *)((GObj *)(a1))->p_15C;
  char *new_var;
  new_var = ((char *) p) + 0xA0;
  CopyVector(a0, (int) (((char *) p) + 0x130));
  SubVectorXYZ(a0, a0, (int) new_var);
}
extern int D_0054D860[];
extern float GetYProjectionOfPlane();
extern void debug_StdPrintfDummy(void *msg);

void AdjustMotionHeightToField(int *a0) {
    char *o = (char *)a0[0x57];
    char *sub = o + 0xA0;
    *(float *)(sub + 0x1B4) = GetYProjectionOfPlane(o + 0x1D0, o + 0x250);
    debug_StdPrintfDummy(D_0054D860);
}
extern void ClipFloor();

void GetLowerPlaneCollision(int a0, int a1)
{
    CopyVector(a0, a1);
    CopyVector(a0 + 0x10, a0);
    *(float *)(a0 + 0x14) = *(float *)(a0 + 0x14) + 10000.0f;
    ClipFloor(a0);
}
extern void ClipFloorE();

void getLowerPlaneCollisionE(int a0, int a1)
{
    CopyVector(a0, a1);
    CopyVector(a0 + 0x10, a0);
    *(float *)(a0 + 0x14) = *(float *)(a0 + 0x14) + 10000.0f;
    ClipFloorE(a0);
}
typedef struct { int a, b, c; } MotAttr12;
extern void sceVu0CopyVector();
extern void GetRootPosition();

/* static inline in the ROM: inlined into AdjustMotionHeightToNearestField and
 * InitMotionGeoInfo, no out-of-line copy, so the name is ours. */
static inline int adjustMotionHeightToNearestField(char *o, float *pos)
{
    char buf[0xC0];
    float p[4];
    char *sub = o + 0xA0;

    CopyVector((int)p, (int)pos);
    p[1] = p[1] - 100.0f;
    if (*(int *)(sub + 0x120) != 0) {
        *(MotAttr12 *)(buf + 0x74) = *(MotAttr12 *)(o + 0x1C0);
        getLowerPlaneCollisionE((int)buf, (int)p);
    } else {
        GetLowerPlaneCollision((int)buf, (int)p);
    }
    if (*(int *)(buf + 0x94) == 0) {
        return 0;
    }
    CopyVector((int)(sub + 0x130), (int)(buf + 0xA0));
    sceVu0CopyVector(sub + 0x1B0, buf + 0x20);
    *(float *)(sub + 0x1BC) = 1.0f;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", calcFootIK);
typedef struct { long long d[122]; } _0x3D0;
extern _0x3D0 D_00290080;
extern void RotQuaternionX(void *q, short ang);
extern void RotQuaternionZ(void *q, short ang);
extern void RegularizeQuaternion(void *q);
extern void SetSimplePlane(void *plane, float x, float y, float z, float d);

void InitMotionGeoInfo(char *self, float x, float y, float z, float rx, float ry, float rz)
{
    *(_0x3D0 *)self = D_00290080;
    *(float *)(self + 0x0) = x;
    *(float *)(self + 0x4) = y;
    *(float *)(self + 0x8) = z;
    CopyVector((int)(self + 0x150), (int)self);
    CopyVector((int)(self + 0x70), (int)self);
    CopyVector((int)(self + 0x160), (int)self);
    RotQuaternionY(self + 0x30, -(int)(ry * 10430.378f));
    RotQuaternionX(self + 0x30, -(int)(rx * 10430.378f));
    RotQuaternionZ(self + 0x30, -(int)(rz * 10430.378f));
    RegularizeQuaternion(self + 0x30);
    adjustMotionHeightToNearestField(self - 0xA0, (float *)self);
    SetSimplePlane(self + 0x130, 0.0f, -1.0f, 0.0f, y);
    CopyVector((int)(self + 0x1B0), (int)self);
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", dispSkeltonHierarchy);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DispSkelton);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SlopeIKControl);
ASM_LIT4_SLOT(D_00638B50, 0.2f);
ASM_LIT4_SLOT(D_00638B54, 0.45f);
ASM_LIT4_SLOT(D_00638B58, 1.1f);
ASM_LIT4_SLOT(D_00638B5C, 0.3f);
ASM_LIT4_SLOT(D_00638B60, 0.3f);
ASM_LIT4_SLOT(D_00638B64, 0.2f);
ASM_LIT4_SLOT(D_00638B68, 0.45f);
ASM_LIT4_SLOT(D_00638B6C, 1.1f);
ASM_LIT4_SLOT(D_00638B70, 0.3f);
ASM_LIT4_SLOT(D_00638B74, 0.1f);
extern void sceVu0SubVector(float *dst, float *a, float *b);
extern void sceVu0OuterProduct(float *dst, float *a, float *b);
extern void sceVu0ScaleVectorXYZ(float *dst, float *a, float s);
extern float sceVu0InnerProduct(float *a, float *b);
extern void SetSimplePlane(void *plane, float x, float y, float z, float d);
extern float GetYDistanceFromPlane();
extern void GetWallGlobalInfo();
extern void debug_assertMessage(char *file, int line, char *msg);
extern void __assert(char *file, int line, char *expr);
extern char D_0054D920[];
extern char D_00639F10[];
extern char D_00639F18[];
extern float D_00639F1C[];
extern int D_00290670[];

int GetPureVerticalPlaneOfCurrentPosition(void *plane0, void *plane1, float *ptsIn, int *cfg,
                                          int flip, float *pos)
{
    float local[4][4];
    float nrm[4];
    float best[4];
    float bestNrm[4];
    float plane[4];
    float work[4];
    float *pts;
    int i;
    int bestIdx;
    int *t;
    int *tbl;
    float bestDist;
    float d;
    int *obj;
    int sh;
    int *p15c;
    int v_c;

    tbl = D_00290670;
    pts = (ptsIn != 0) ? ptsIn : (float *)local;
    bestIdx = -1;

    bestDist = D_00639F1C[0];

    obj = (int *)cfg[0];
    sh = cfg[1] << 6;
    p15c = (int *)((GObj *)(obj))->p_15C;
    v_c = p15c[0xC / 4];
    GetWallGlobalInfo(pts, nrm, cfg[2], v_c + sh);
    nrm[1] = 0;
    sceVu0Normalize((int *)nrm, (int *)nrm);
    t = tbl;
    for (i = 0; i < 4; i++, t++) {
        sceVu0SubVector(work, pts + t[1] * 4, pts + t[0] * 4);
        sceVu0Normalize((int *)work, (int *)work);
        sceVu0OuterProduct(work, work, nrm);
        if (flip != 0) {
            sceVu0ScaleVectorXYZ(work, work, -1.0f);
        }
        if (work[1] < -0.1f) {
            SetSimplePlane(plane, work[0], work[1], work[2],
                           -sceVu0InnerProduct(work, pts + t[0] * 4));
            d = GetYDistanceFromPlane(plane, pos);
            if (d < 0.0f) {
                d = -d;
            }
            if (d < bestDist) {
                bestIdx = i;
                CopyVector(best, work);
                CopyVector(bestNrm, nrm);
                bestDist = d;
            }
        }
    }
    if (bestIdx == -1) {
        debug_assertMessage(D_0054D920, 1360, D_00639F10);
        __assert(D_0054D920, 1360, D_00639F18);
    }
    if (plane0 != 0) {
        SetSimplePlane(plane0, best[0], best[1], best[2],
                       -sceVu0InnerProduct(best, pts + tbl[bestIdx] * 4));
    }
    if (plane1 != 0) {
        SetSimplePlane(plane1, bestNrm[0], bestNrm[1], bestNrm[2],
                       -sceVu0InnerProduct(bestNrm, pts + tbl[bestIdx] * 4));
    }
    return bestIdx;
}
extern void GetWallGlobalInfo();
extern void _NormalizeVector();

void getVerticalElementOfWallNormal(int *self, int *p, int *cfg)
{
    int *obj = (int *)cfg[0];
    int sh = cfg[1] << 6;
    int *p15c = (int *)((GObj *)(obj))->p_15C;
    int v_c = p15c[0xC / 4];

    GetWallGlobalInfo(self, p, cfg[2], v_c + sh);
    p[1] = 0;
    _NormalizeVector(p, p);
}
extern void _SetCurrentMatrix(void *m);
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern void _OuterProduct(float *dst, float *a, float *b);
extern float _InnerProduct(float *a, float *b);
extern void _InterVectorXYZ(float *dst, float *a, float *b, float t);
extern void GetProjectionOfPlane(float *dst, float *plane, float *pos);
extern float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float t);
extern char D_0054D998[];
extern float D_00290690[];
extern float D_0028FF20[];

void AdjustVerticalSidePlaneOfWall(float *out, int *cfg, float *pos, float t)
{
    float pts[4][4];
    float nrm[4];
    float v[4];
    float pa[4];
    float pb[4];
    float p0[4];
    float p1[4];
    int maxIdx;
    int minIdx;
    int i;
    float minV;
    float maxV;
    float d;
    float t2;
    float d0;
    float d1;

    t2 = t + t;
    minIdx = 0;
    maxIdx = 0;
    getVerticalElementOfWallNormal((int *)pts, (int *)nrm, cfg);
    D_00290690[0] = D_00290690[10] = nrm[2];
    D_00290690[2] = nrm[0];
    D_00290690[8] = -nrm[0];
    _SetCurrentMatrix(D_00290690);
    _ApplyCurrentMatrix(v, pts);
    maxV = minV = v[0];
    for (i = 1; i < 4; i++) {
        _ApplyCurrentMatrix(v, pts[i]);
        if (maxV < v[0]) {
            maxV = v[0];
            maxIdx = i;
        }
        if (v[0] < minV) {
            minV = v[0];
            minIdx = i;
        }
    }
    _OuterProduct(pa, D_0028FF20, nrm);
    pa[3] = -_InnerProduct(pa, pts[minIdx]);
    _OuterProduct(pb, nrm, D_0028FF20);
    pb[3] = -_InnerProduct(pb, pts[maxIdx]);
    d0 = plane_distance(pos, pa);
    d1 = plane_distance(pos, pb);
    d = pa[3] + pb[3];
    if (((d < 0.0f) ? -d : d) < t2) {
        GetProjectionOfPlane(p0, pa, pos);
        GetProjectionOfPlane(p1, pb, pos);
        _InterVectorXYZ(out, p0, p1, 0.5f);
        debug_StdPrintfDummy(D_0054D998);
    } else if (d0 < t) {
        GetProjectionOfPlaneWithKeepAway(out, pa, pos, t);
    } else if (d1 < t) {
        GetProjectionOfPlaneWithKeepAway(out, pb, pos, t);
    } else {
        CopyVector(out, pos);
    }
    out[3] = 1.0f;
}
extern void sceVu0SubVector(float *dst, float *a, float *b);
extern void sceVu0OuterProduct(float *dst, float *a, float *b);
extern void sceVu0ScaleVectorXYZ(float *dst, float *a, float s);
extern float sceVu0InnerProduct(float *a, float *b);
extern void SetSimplePlane(void *plane, float x, float y, float z, float d);
extern int D_00290670[];

int GetPureVerticalPlane(void *plane0, void *plane1, float *ptsIn, int *cfg, int flip)
{
    float local[4][4];
    float up[4];
    float best[4];
    float bestUp[4];
    float work[4];
    float *pts;
    int i;
    int bestIdx;
    int *t;
    int *tbl;

    tbl = D_00290670;
    pts = (ptsIn != 0) ? ptsIn : (float *)local;
    bestIdx = 0;
    getVerticalElementOfWallNormal((int *)pts, (int *)up, cfg);
    for (i = 0, t = tbl; i < 4; i++, t++) {
        sceVu0SubVector(work, pts + t[1] * 4, pts + t[0] * 4);
        sceVu0Normalize((int *)work, (int *)work);
        sceVu0OuterProduct(work, work, up);
        if (flip != 0) {
            sceVu0ScaleVectorXYZ(work, work, -1.0f);
        }
        if (i == 0 || work[1] < best[1]) {
            CopyVector(best, work);
            bestIdx = i;
            CopyVector(bestUp, up);
        }
    }
    if (plane0 != 0) {
        SetSimplePlane(plane0, best[0], best[1], best[2],
                       -sceVu0InnerProduct(best, pts + tbl[bestIdx] * 4));
    }
    if (plane1 != 0) {
        SetSimplePlane(plane1, bestUp[0], bestUp[1], bestUp[2],
                       -sceVu0InnerProduct(bestUp, pts + tbl[bestIdx] * 4));
    }
    return bestIdx;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getS16MotRotElem);
ASM_LIT4_SLOT(D_00638B7C, 0.001f);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getMotion);
extern void memset(void *a0, int a1, int a2);
extern void CopyQuaternion();
extern void RotQuaternionX(void *q, short ang);
extern void _getS16MotRotElem(void *dst, void *src);
extern void MultiQuaternion(void *a0, void *a1, void *a2);
extern float D_0028FF00[];

/* dev lines 1552-1558: the shared root-position helper GetMotionRootPos (1564)
   and GetStreamMotion (1815) both expand.  INTERIM stand-in, see
   getSkeltonFocusNode above. */
static inline void getRootPos(float *dst, float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = 1.0f;

    dst[0] = -dst[0];
    dst[1] = -dst[1];
}

int GetStreamMotion(char *dst, float *out, char *node, char *info)
{
    float quat[4];
    int i;
    int n = *(unsigned char *)(node + 2);

    memset(quat, 0, 16);
    quat[3] = 1.0f;

    if (*(signed char *)(node + 1) == 0) {
        getRootPos(out, (float *)(node + 4));

        RotQuaternionX(quat, -0x8000);
        RotQuaternionY(quat, -0x8000);

        for (i = 0; i < n; i++) {
            _getS16MotRotElem(dst + i * 0x20, node + 0x10 + i * 8);
            if (*(int *)(info + 0x38 + i * 0x40) == -1) {
                MultiQuaternion(dst + i * 0x20 + 0x10, quat, dst + i * 0x20 + 0x10);
            }
            *(int *)(dst + i * 0x20) = 0;
        }
        return 1;
    }
    for (i = 0; i < n; i++) {
        CopyVector(out, D_0028FF00);
        *(int *)(dst + i * 0x20) = 0;
        CopyQuaternion(dst + i * 0x20 + 0x10, quat);
    }
    return 0;
}
/* copyMotionWithNodeHrc is a nested function inside CopyMotionWithNodeHrc: the
 * parent passes it a static chain in $2 (STATIC_CHAIN_REGNUM) which the nested
 * function spills to 0(sp) and uses to reach dst/src/flag/hrc. */
void CopyMotionWithNodeHrc(struct Pack32 *dst, struct Pack32 *src, char *hrc, int node, int flag)
{
    inline void copyMotionWithNodeHrc(int n)
    {
        dst[n] = src[n];
        if (flag == 0) {
            *(int *)&dst[n] = 250;
        }
        if (*(int *)(hrc + n * 64 + 0x30) != -1) {
            copyMotionWithNodeHrc(*(int *)(hrc + n * 64 + 0x30));
        }
        if (*(int *)(hrc + n * 64 + 0x34) != -1) {
            copyMotionWithNodeHrc(*(int *)(hrc + n * 64 + 0x34));
        }
    }

    dst[node] = src[node];
    if (flag == 0) {
        *(int *)&dst[node] = 250;
    }
    if (*(int *)(hrc + node * 64 + 0x30) != -1) {
        copyMotionWithNodeHrc(*(int *)(hrc + node * 64 + 0x30));
    }
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetFloatingMotion);
extern void GetInverseQuaternion(float *dst, float *src);
extern void GetMirrorQuaternion(float *a0, float *a1, unsigned int a2);
extern void MultiQuaternion(void *a0, void *a1, void *a2);

int MakeMirrorMotion(StreamElem *a, StreamNode *b) {
    int i;
    int n;
    float buf[4];
    StreamElem tmp;

    for (i = 0; b[i].idx != -1; i++) {
        n = b[i].idx;
        if (i < n) {
            continue;
        }
        if (i != n) {
            goto swap;
        }
        GetInverseQuaternion(buf, b[i].q);
        MultiQuaternion(buf, buf, a[i].q);
        GetMirrorQuaternion(buf, buf, 4);
        MultiQuaternion(a[i].q, b[i].q, buf);
        continue;
    swap:
        {
            StreamElem *pn = (StreamElem *)((char *)a + n * 0x20);
            StreamElem *pi = (StreamElem *)((char *)a + i * 0x20);
            tmp = *pi;
            *pi = *pn;
            *pn = tmp;
        }
        GetMirrorQuaternion(a[i].q, a[i].q, 4);
        GetMirrorQuaternion(a[b[i].idx].q, a[b[i].idx].q, 4);
    }
}
/* INTERIM (same reason as getSkeltonFocusNode above): the listing inlines
   GetShapeMotion (line 2052) into GetFloatingShapeMotion, so it is `inline` in
   the dev's TU; while this tail still has asm members a deferred inline would
   land at the object end instead of at its ROM slot, so the public body stays a
   plain definition there and this caller uses the stand-in.
   Collapses to one `inline` definition at layout. */
static inline void getShapeMotion(float *dst, char *a1, int idx, int count)
{
    int i = 0;
    int m = *(int *)a1 - 1;
    idx = idx - m * (idx / m);
    for (; i < count; i++) {
        char *t = *(char **)(a1 + 0x10);
        int *elem = *(int **)(*(char **)(t + 4) + i * 4);
        if (elem != 0) {
            dst[i] = ((float *)elem)[idx];
        } else {
            dst[i] = 0;
        }
    }
}

void GetFloatingShapeMotion(float *dst, char *m, float t, int count)
{
    int i;
    float frac;

    t = t - (*(int *)m - 1) * (int)(t / (*(int *)m - 1));
    frac = t - (int)t;
    if (frac == 0.0f) {
        getShapeMotion(dst, m, (int)t, count);
    } else {
        float buf0[count], buf1[count];

        getShapeMotion(buf0, m, (int)t, count);
        getShapeMotion(buf1, m, (int)t + 1, count);
        for (i = 0; i < count; i++) {
            dst[i] = buf0[i] * (1.0f - frac) + buf1[i] * frac;
        }
    }
}
typedef struct { int a; int b; int c; } WallWork;
void FeedbackWallWorkInfoToBrainSystem(char *a0) {
    char *p = *(char **)(a0 + 0x15C);
    char *d = *(char **)(a0 + 0x164);
    *(WallWork *)(p + 0x180) = *(WallWork *)(p + 0x1A0);
    *(WallWork *)(d + 0x620) = *(WallWork *)(p + 0x1A0);
}
void *GetMotionPointer(char *self) {
    return (char *)((GObj *)(self))->p_15C + 0x680;
}
int GetCollisionOfLastActiveField(char *self) {
    return ((GObj *)(self))->p_15C->f_1E0;
}
extern int GetFloorAttribute();
extern int CompareAttribute();
extern float GetPoolGlobalHeight(int pool);
extern void SetFallDownSplash(int pool, void *self);

int CheckFieldContact(char *info, char *self, float *pos, float lim)
{
    float h;
    float dy;
    float ph;
    float d;

    if (*(int *)(info + 0x94) != 0) {
        h = *(float *)(*(int *)(self + 0x15C) + 0x134);
        dy = *(float *)(info + 0x24) - pos[1];
        if (CompareAttribute(GetFloorAttribute(info), 0x50) != 0) {
            if (h >= 0.0f) {
                ph = GetPoolGlobalHeight(*(int *)(info + 0x8C));
                d = *(float *)(info + 0x24) - ph;
                if (dy < lim) {
                    if (d > 0.0f) {
                        if ((*(int *)(*(int *)(self + 0x15C) + 0x64C) & 1) == 0 && h > 5.0f) {
                            SetFallDownSplash(*(int *)(info + 0x8C), self);
                            *(int *)(*(int *)(self + 0x15C) + 0x64C) |= 1;
                        }
                    }
                    return 1;
                }
                if (d > 0.0f) {
                    if (ph - pos[1] < lim * 0.8f) {
                        if ((*(int *)(*(int *)(self + 0x15C) + 0x64C) & 1) == 0 && h > 5.0f) {
                            SetFallDownSplash(*(int *)(info + 0x8C), self);
                            *(int *)(*(int *)(self + 0x15C) + 0x64C) |= 1;
                        }
                        return 2;
                    }
                }
            }
        } else {
            if (dy < lim) {
                return 1;
            }
        }
    }
    return 0;
}
extern int D_00290640[];
extern int D_00290660[];
extern void DrawLineG(void *a0, void *a1, void *a2, void *a3, int a4);
extern void gif_StartPacketPri(int pri);
extern void gif_SetAlpha(int a, int b, int c);
extern void MatrixDrive_PushMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void gif_EndPacket(void);

/* INTERIM (same reason as getSkeltonFocusNode above): the listing inlines
   DebugDisp1CollisionWithColor (its body carries DebugDisp1Collision's rows)
   so it is `inline` in the dev's TU; while this tail still has asm members a
   deferred inline would land at the object end instead of at its ROM slot
   right after this function, so the public body stays a plain definition there
   and this caller uses the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline void debugDisp1CollisionWithColor(int *cfg, void *color)
{
    float pts[5][4];
    int i;
    int *obj = (int *)cfg[0];
    int sh = cfg[1] << 6;
    int *p15c = (int *)((GObj *)(obj))->p_15C;
    int v_c = p15c[0xC / 4];

    GetWallGlobalInfo(pts, pts[4], cfg[2], v_c + sh);
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < 4; i++) {
        DrawLineG(pts[D_00290640[i]], color, pts[D_00290640[i + 1]], color, -1);
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}
void DebugDisp1Collision(int *cfg)
{
    debugDisp1CollisionWithColor(cfg, D_00290660);
}
void DebugDisp1CollisionWithColor(int *cfg, void *color)
{
    float pts[5][4];
    int i;
    int *obj = (int *)cfg[0];
    int sh = cfg[1] << 6;
    int *p15c = (int *)((GObj *)(obj))->p_15C;
    int v_c = p15c[0xC / 4];

    GetWallGlobalInfo(pts, pts[4], cfg[2], v_c + sh);
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < 4; i++) {
        DrawLineG(pts[D_00290640[i]], color, pts[D_00290640[i + 1]], color, -1);
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}
/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
   GetSkeltonFocusNode (line 534) into SetMotionBlendlessNode, so it is `inline`
   in the dev's TU; while this tail still has asm members a deferred inline
   would land at the object end instead of at its ROM slot (between
   AdjustMotionHeightToNearestField's neighbours), so the public body stays a
   plain definition there and every C caller the listing shows inlining it
   (SetMotionBlendlessNode, the two GetDifferenceFromWall*Plane, the node fix
   mode setter) calls this static stand-in.
   Collapses to one `inline` definition at layout. */
static inline int getSkeltonFocusNode(char *a0, int a1) {
    return *(char *)(*(int *)(*(int *)(a0 + 0x15C) + 0x840) + a1);
}
extern void ClearMotionBlendlessNode(char *a0);
void SetMotionBlendlessNode(char *self, int *node)
{
    char *blend;
    int i;

    blend = *(char **)(*(char **)(self + 0x15C) + 0x820);
    ClearMotionBlendlessNode(self);
    for (i = 0; node[i] != -1; i++) {
        int idx = getSkeltonFocusNode(self, node[i]);
        if (idx != -1) {
            blend[idx] = 1;
        }
    }
}
void ClearMotionBlendlessNode(char *a0) {
    int i = 0;
    char *arr = *(char **)(*(char **)(a0 + 0x15C) + 0x820);
    while (i < *(int *)(*(char **)(a0 + 0x15C) + 0x88)) {
        arr[i] = 0;
        i++;
    }
}
extern _0x1F0 D_00290450;
extern int soundSeGroupGet(void);

void InitMotionStateInfo(_0x1F0 *self) {
    *self = D_00290450;
    *(int *)((char *)self + 0x1AC) = soundSeGroupGet();
    *(int *)((char *)self + 0x1B0) = soundSeGroupGet();
}
int GetSkeltonFocusNode(char *a0, int a1) {
    return *(char *)(*(int *)(*(int *)(a0 + 0x15C) + 0x840) + a1);
}
int AdjustMotionHeightToNearestField(char *self)
{
    float pos[4];
    char *o = *(char **)(self + 0x15C);

    GetRootPosition(pos, self);
    return adjustMotionHeightToNearestField(o, pos);
}
void SetRootUpdateMode(char *self, int val) {
    ((GObj *)(self))->p_15C->f_4D8 = val;
}
float ForMotionViewer_GetCurrentAnimationFrame(char *self) {
    return *(float *)(*(char **)(self + 0x15C) + 0x4AC);
}
int ForMotionViewer_GetCurrentMotion(char *self) {
    return ((GObj *)(self))->p_15C->f_4A0;
}
void EnableMotionOrientUpdate(char *self) {
    ((GObj *)(self))->p_15C->f_4E4 = 0;
}
void DisableMotionOrientUpdate(char *self) {
    ((GObj *)(self))->p_15C->f_4E4 = 1;
}
extern int CompareAttribute();

int CheckFloorAttribute(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return CompareAttribute(*(int *)(sub + 0x5F8));
}
int CheckWallAttribute(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return CompareAttribute(*(int *)(sub + 0x5F4));
}
int CheckPureWallAttribute(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return CompareAttribute(*(int *)(sub + 0x5EC));
}
int CheckPureCliffAttribute(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return CompareAttribute(*(int *)(sub + 0x5F0));
}
int GetStreamShapeMotion(float *dst, FloorAttr *a1) {
    int i, n, f2; float *src, *p;
    if (a1->f1 == 0 && (f2 = a1->f2, (n = a1->f3)) != 0) {
        int o = f2 * 8 + 0x10;
        src = (float *)o;
        p = (float *)((char *)a1 + (int)src);
        src = p;
        for (i = 0; i < n; i++) *dst++ = *src++;
        return 1;
    }
    return 0;
}
extern float GetYDistanceFromPlane(void *a0, void *a1);
float GetDifferenceFromWallUpperField(char *a0, int a1) {
    char *e = *(char **)(a0 + 0x15C);
    int idx = (*(char **)(e + 0x840))[a1];
    return GetYDistanceFromPlane(e + 0x3F0, *(char **)(e + 0xC) + idx * 0x40 + 0x30);
}
float GetDifferenceFromLastField(char *a0, int a1) {
    char *e = *(char **)(a0 + 0x15C);
    int idx = (*(char **)(e + 0x840))[a1];
    return GetYDistanceFromPlane(e + 0x1D0, *(char **)(e + 0xC) + idx * 0x40 + 0x30);
}
extern float D_00639F20[];
float GetDifferenceFromLowerField(char *a0, int a1) {
    char buf[0xC0];
    char *ctrl;
    int idx;
    ctrl = *(char **)(a0 + 0x15C);
    idx = (*(signed char **)(ctrl + 0x840))[a1];
    GetLowerPlaneCollision((int)buf, *(int *)(ctrl + 0xC) + (idx << 6) + 0x30);
    if (*(int *)(buf + 0x94) == 0) {
        return D_00639F20[0];
    }
    return *(float *)(buf + 0x24) - *(float *)(buf + 0x4);
}

float GetDifferenceFromWallLowerPlane(char *self, int node)
{
    float pos[4];
    float pts[4][4];
    int idx;

    idx = getSkeltonFocusNode(self, node);
    GetPureVerticalPlane(pos, 0, pts, *(char **)(self + 0x15C) + 0x180, 1);
    return GetYDistanceFromPlane(pos, *(char **)(*(char **)(self + 0x15C) + 0xC) + idx * 0x40 + 0x30);
}
float GetDifferenceFromWallUpperPlane(char *self, int node)
{
    float pos[4];
    float pts[4][4];
    int idx;

    idx = getSkeltonFocusNode(self, node);
    GetPureVerticalPlane(pos, 0, pts, *(char **)(self + 0x15C) + 0x180, 0);
    return GetYDistanceFromPlane(pos, *(char **)(*(char **)(self + 0x15C) + 0xC) + idx * 0x40 + 0x30);
}
void DisableChangeRootUpdateMode(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    *(int *)(sub + 0x4D0) = 1;
}
void EnableChangeRootUpdateMode(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    *(int *)(sub + 0x4D0) = 0;
}
float GetRopeHangablePos(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(float *)(sub + 0x618);
}
int GetMotionFrameFlag1(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(int *)(sub + 0x600);
}
int GetMotionFrameFlag2(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(int *)(sub + 0x604);
}
float GetHeightOfFieldPlaneDifference(int *a, int *b)
{
    int *pa;
    int *pb;
    float r1;
    float r2;
    pa = (int *)((GObj *)(a))->p_15C;
    r1 = GetYProjectionOfPlane((int *)((char *)pa + 0x1D0), (int *)((char *)pa + 0xA0));
    pb = (int *)((GObj *)(b))->p_15C;
    r2 = GetYProjectionOfPlane((int *)((char *)pb + 0x1D0), (int *)((char *)pb + 0xA0));
    return r1 - r2;
}
float GetHeightOfWallFromGObj(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(float *)(sub + 0x5A0);
}
float GetHeightOfCliffFromGObj(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(float *)(sub + 0x580);
}
extern void SetIdentityQuaternion();

void InitMotionRotElem(int *a0, int count)
{
    int *p;
    int i;
    if (count <= 0) return;
    p = a0;
    i = count;
loop:
    p[0] = 0;
    {
        int *call_arg = p + 4;
        p += 8;
        SetIdentityQuaternion(call_arg);
    }
    --i;
    if (i != 0) goto loop;
}
extern void CopyQuaternion();

void SetMotionNodeFixModeParameter(char *self, char *obj, float x, float y, float z,
                                   int mode, int node, float w, void *quat)
{
    float vec[4] = { x, y, z, 1.0f };

    *(int *)(*(int *)(self + 0x15C) + 0x424) = (int)obj;
    *(int *)(*(int *)(self + 0x15C) + 0x428) = getSkeltonFocusNode(obj, node);
    *(int *)(*(int *)(self + 0x15C) + 0x454) = mode;
    CopyVector(*(int *)(self + 0x15C) + 0x440, vec);
    CopyQuaternion(*(int *)(self + 0x15C) + 0x430, quat);
    *(float *)(*(int *)(self + 0x15C) + 0x450) = w;
}
extern void GetRootPosition();

void GetRootProjectionPosOfGObj(int a0, int a1)
{
    GetRootPosition(a0, a1);
    *(float *)(a0 + 0x4) += *(float *)((int)((GObj *)(a1))->p_15C + 0x270);
}
void SetMotionPlaySpeedRatio(char *self, float val) {
    *(float *)(*(char **)(self + 0x15C) + 0x4B8) = val;
}
extern char D_0028FEF0[];
extern void sceVu0AddVector();

void ClearMotionGeometryInfo(int *self)
{
  int *p = (int *)((GObj *)(self))->p_15C;
  int *p1 = (int *) (((char *) p) + 0x230);
  int *p2 = (int *) (((char *) p) + 0xA0);
  int ret;
  CopyVector(p1, D_0028FEF0);
  sceVu0AddVector((int *) (((char *) p) + 0x250), p2, p1);
  ret = -1;
  *((int *) (((char *) p2) + 0x180)) = ret;
  return ret;
}
extern int D_00639F08;

void SetSkeltonDispSwitch(int val) {
    D_00639F08 = val;
}
void CopyMotion(struct Pack32 *dst, struct Pack32 *src, int n)
{
    if (n <= 0) return;
    do {
        *dst = *src;
        n--;
        src++;
        dst++;
    } while (n != 0);
}
void GetMotionRootPos(float *dst, void *a1, int idx) /* `inline` once GetFloatingMotionRootPos, which the listing shows inlining it, is C; plain until then (deferred inlines land at the object end) */
{
    float *src = (float *)(*(int *)((char *)a1 + 4) + idx * 0xC);
    getRootPos(dst, src);
}
/* INTERIM (same reason as getSkeltonFocusNode above): the listing inlines
   GetMotionRootPos and GetBlendedMotionRootPos into their callers, so both are
   `inline` in the dev's TU; while this tail still has asm members a deferred
   inline would land at the object end instead of at its ROM slot, so the public
   bodies stay plain definitions there and the callers use these stand-ins.
   Collapses to one `inline` definition each at layout. */
static inline void getMotionRootPos(float *dst, void *a1, int idx)
{
    float *src = (float *)(*(int *)((char *)a1 + 4) + idx * 0xC);
    getRootPos(dst, src);
}
static inline void getBlendedMotionRootPos(float *dst, float *a, float *b, float t)
{
    float u = 1.0f - t;
    dst[0] = a[0] * t + b[0] * u;
    dst[1] = a[1] * t + b[1] * u;
    dst[2] = a[2] * t + b[2] * u;
}
extern int D_002906D0[];
extern void _getMotion(void *dst, void *m, int node, int idx);

void GetMotion(char *dst, float *root, void *motion, int idx, unsigned char *mask, int count, char *hrc)
{
    int i;

    if (mask != 0) {
        for (i = 0; i < count; i++) {
            if (mask[i] == 0) {
                _getMotion(dst + i * 0x20, motion, i, idx);
            }
        }
    } else {
        for (i = 0; i < count; i++) {
            _getMotion(dst + i * 0x20, motion, i, idx);
        }
    }

    if (hrc != 0) {
        i = 0;
        do {
            MultiQuaternion(dst + i * 0x20 + 0x10, D_002906D0, dst + i * 0x20 + 0x10);
            i = *(int *)(hrc + i * 0x40 + 0x34);
        } while (i != -1);
    } else {
        for (i = 0; i < count; i++) {
            MultiQuaternion(dst + i * 0x20 + 0x10, D_002906D0, dst + i * 0x20 + 0x10);
        }
    }
    if (root != 0) {
        getMotionRootPos(root, motion, idx);
    }
}
extern void GetSlerpQuaternionNoRegularize(float *dst, float *a, float *b, float t);

void GetBlendedMotion(StreamElem *dst, float *root, StreamElem *a, float *rootA,
                      StreamElem *b, float *rootB, unsigned char *mask, int count, float t)
{
    int i;
    float u = 1.0f - t;

    if (mask != 0) {
        for (i = 0; i < count; i++) {
            if (mask[i] != 0) {
                dst[i] = a[i];
            } else {
                *(int *)&dst[i] = (float)*(int *)&a[i] * t + (float)*(int *)&b[i] * u;
                GetSlerpQuaternionNoRegularize(dst[i].q, a[i].q, b[i].q, t);
            }
        }
    } else {
        for (i = 0; i < count; i++) {
            dst[i] = a[i];
        }
    }
    if (root != 0) {
        getBlendedMotionRootPos(root, rootA, rootB, t);
    }
}
void GetFloatingMotionRootPos(float *dst, void *m, float t)
{
    float buf0[4];
    float buf1[4];
    int n = *(int *)m - 1;
    int i;

    t = t - n * (int)(t / n);
    i = (int)t;

    getMotionRootPos(buf0, m, i);
    getMotionRootPos(buf1, m, i + 1);

    getBlendedMotionRootPos(dst, buf0, buf1, 1.0f - (t - i));
}
void GetShapeMotion(float *dst, char *a1, int idx, int count)
{
    int i = 0;
    int m = *(int *)a1 - 1;
    idx = idx - m * (idx / m);
    for (; i < count; i++) {
        char *t = *(char **)(a1 + 0x10);
        int *elem = *(int **)(*(char **)(t + 4) + i * 4);
        if (elem != 0) {
            dst[i] = ((float *)elem)[idx];
        } else {
            dst[i] = 0;
        }
    }
}
void LockForceGroundParent(void) {}
void UnlockForceGroundParent(void) {}
extern void GetGlobalWallPlane(void *a0, void *a1);
extern float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float t);
extern void GetRootPosition__pn(void *a0, void *a1) __asm__("GetRootPosition");
extern void SetDirectRootPosition(void *a0, void *a1);

void GetOutOutsideOfWall(void *obj, float threshold) {
    int buf0[4];
    int buf1[4];
    if (*(int *)(*(char **)((char *)obj + 0x15C) + 0x188) != 0) {
        float dot;
        GetRootPosition__pn(buf0, obj);
        GetGlobalWallPlane(buf1, *(char **)((char *)obj + 0x15C) + 0x180);
        /* The sugiCommon.h line-69 helper, hand-expanded: calling
         * plane_distance(buf0, buf1) costs one extra `daddu v0,s0,zero`
         * because ee-gcc's inliner copies the frame-address actual `&buf1`
         * into a fresh parameter pseudo that copy-prop then fails to
         * coalesce with the s0 the preceding call already put it in.
         * See decomp/HEADERS.md. */
        {
            int t;
            VU0_LSV_R(lqc2, 1, 0x0, buf0);
            VU0_LSV_R(lqc2, 2, 0x0, buf1);
            VU0_V3OP(vmul.xyz, 3, 1, 2);
            VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
            VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
            VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
            __asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(t));
            __asm__ __volatile__("mtc1 %1, %0" : "=f"(dot) : "r"(t));
        }
        if (dot < threshold) {
            GetProjectionOfPlaneWithKeepAway(buf0, buf1, buf0, threshold);
        }
        SetDirectRootPosition(obj, buf0);
    }
}
extern void ClipWall(void *a0);
extern char D_0054D938[];
extern void memset(void *a0, int a1, int a2);

void AdjustRootPositionToVerticalSidePlaneOfWall(void *a0, void *a1, float f) {
    char buf[0xC0];
    memset(buf, 0, 0xC0);
    GetRootPosition__pn(buf, a0);
    AdjustVerticalSidePlaneOfWall(buf + 0x10, a1, buf, f);
    ClipWall(buf);
    if (*(int *)(buf + 0x88) != 0) {
        SetDirectRootPosition(a0, buf + 0x20);
        debug_StdPrintfDummy(D_0054D938);
    } else {
        SetDirectRootPosition(a0, buf + 0x10);
    }
}
void fitYToPlane(long long *src, int *dest) {
    long long buf[2];
    buf[0] = src[0];
    buf[1] = src[1];
    *(float *)((char *)dest + 4) = GetYProjectionOfPlane((int *)buf, dest);
}
extern float FSqrt(float a0);

void GetBlendedMotionRootPos(float *dst, float *a, float *b, float t) /* same note as GetMotionRootPos */
{
    float u = 1.0f - t;
    dst[0] = a[0] * t + b[0] * u;
    dst[1] = a[1] * t + b[1] * u;
    dst[2] = a[2] * t + b[2] * u;
}
void _getMotRotElem(char *dst, char *src)
{
    float sum;

    sum = *(float *)(src + 0x4) * *(float *)(src + 0x4)
        + *(float *)(src + 0x8) * *(float *)(src + 0x8)
        + *(float *)(src + 0xC) * *(float *)(src + 0xC);
    sum = (sum > 1.0f) ? 1.0f : sum;
    *(int *)dst = *(unsigned char *)src;
    *(float *)(dst + 0x1C) = FSqrt(1.0f - sum);
    *(float *)(dst + 0x10) = *(float *)(src + 0x4);
    *(float *)(dst + 0x14) = *(float *)(src + 0x8);
    *(float *)(dst + 0x18) = *(float *)(src + 0xC);
    if (*(signed char *)(src + 1) < 0) {
        *(float *)(dst + 0x1C) = -*(float *)(dst + 0x1C);
    }
}

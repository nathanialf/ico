#include "common.h"

#include "ico/types.h"

#include "vu0.h"

#include "sugiCommon.h"

struct Pack32 { long long a, b, c, d; };

typedef struct { char _0; signed char f1; unsigned char f2; unsigned char f3; } FloorAttr;

typedef struct { long long w[62]; } _0x1F0;

typedef struct { long long d[2]; float q[4]; } StreamElem;
typedef struct { int idx; char pad[0x1C]; float q[4]; char pad2[0x10]; } StreamNode;

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetWaterReaction);
ASM_LIT4_SLOT(D_00638B3C, 1.0000001e-06f);
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
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionDirectionWithLimit);
ASM_LIT4_SLOT(D_00638B40, 10430.378f);
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
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", calcFootIK);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", InitMotionGeoInfo);
ASM_LIT4_SLOT(D_00638B4C, 10430.378f);
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
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetPureVerticalPlaneOfCurrentPosition);
ASM_LIT4_SLOT(D_00638B78, -0.1f);
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
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", AdjustVerticalSidePlaneOfWall);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetPureVerticalPlane);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getS16MotRotElem);
ASM_LIT4_SLOT(D_00638B7C, 0.001f);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetStreamMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", copyMotionWithNodeHrc);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CopyMotionWithNodeHrc);
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
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetFloatingShapeMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", FeedbackWallWorkInfoToBrainSystem);
void *GetMotionPointer(char *self) {
    return (char *)((GObj *)(self))->p_15C + 0x680;
}
int GetCollisionOfLastActiveField(char *self) {
    return ((GObj *)(self))->p_15C->f_1E0;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckFieldContact);
ASM_LIT4_SLOT(D_00638B80, 0.8f);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DebugDisp1Collision);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DebugDisp1CollisionWithColor);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionBlendlessNode);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", ClearMotionBlendlessNode);
extern _0x1F0 D_00290450;
extern int soundSeGroupGet(void);

void InitMotionStateInfo(_0x1F0 *self) {
    *self = D_00290450;
    *(int *)((char *)self + 0x1AC) = soundSeGroupGet();
    *(int *)((char *)self + 0x1B0) = soundSeGroupGet();
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetSkeltonFocusNode);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", AdjustMotionHeightToNearestField);
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
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromWallUpperField);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromLastField);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromLowerField);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromWallLowerPlane);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromWallUpperPlane);
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
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionNodeFixModeParameter);
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
void GetMotionRootPos(float *dst, void *a1, int idx)
{
    float *src = (float *)(*(int *)((char *)a1 + 4) + idx * 0xC);
    float t1, t0;
    t0 = src[0];
    dst[0] = t0;
    t0 = -t0;
    t1 = src[1];
    dst[1] = t1;
    t1 = -t1;
    dst[2] = src[2];
    dst[3] = 1.0f;
    dst[0] = t0;
    dst[1] = t1;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", func_0010A5D8);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetBlendedMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetFloatingMotionRootPos);
void GetShapeMotion(float *dst, char *a1, int idx, int count)
{
    int i = 0;
    int m = *(int *)a1 - 1;
    int rem = idx - m * (idx / m);
    for (; i < count; i++) {
        char *t = *(char **)(a1 + 0x10);
        int *elem = *(int **)(*(char **)(t + 4) + i * 4);
        if (elem != 0) {
            dst[i] = ((float *)elem)[rem];
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
extern void AdjustVerticalSidePlaneOfWall(void *a0, void *a1, void *a2, float f);
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
void GetBlendedMotionRootPos(float *dst, float *a, float *b, float t)
{
    float u = 1.0f - t;
    dst[0] = a[0] * t + b[0] * u;
    dst[1] = a[1] * t + b[1] * u;
    dst[2] = a[2] * t + b[2] * u;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getMotRotElem);

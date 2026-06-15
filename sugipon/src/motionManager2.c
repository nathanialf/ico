#include "common.h"

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void GetWaterReaction(int a0, char *a1) {
    MatrixDrive_TurnObjectMatrix(a0, *(char **)(a1 + 0x15C) + 0x5B0);
}


void CheckFieldContact(int a0, char *a1) {
    MatrixDrive_TurnObjectMatrix(a0, *(char **)(a1 + 0x15C) + 0x580);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", dispPlane);

extern void GetRootMatrixRotOffset(int a0, void *a1, void *a2);

void GetOrientOfWallOfGObj(int a0, int **a1) {
    GetRootMatrixRotOffset(a0, a1, (char *)a1[0x57] + 0x510);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetOrientOfCliffOfGObj);

extern void MatrixDrive_GetTurnXAngleZY(void *a0, void *a1, void *a2);

void SetMotionDirection(int a0, char *a1) {
    char *sub = *(char **)(a1 + 0x15C);
    char *t = sub + 0xA0;
    MatrixDrive_TurnObjectMatrix(a0, sub + 0x120);
    MatrixDrive_GetTurnXAngleZY((void *)a0, (void *)a0, t);
}

extern float func_00166A48(void *a0, void *a1);
extern void debug_assertMessage(void *msg);
extern int D_0054DF28[];

void _GetMotionDirection(int *a0) {
    char *o = (char *)a0[0x57];
    char *sub = o + 0xA0;
    *(float *)(sub + 0x1A4) = func_00166A48(o + 0x1C0, o + 0x240);
    debug_assertMessage(D_0054DF28);
}

extern void ChangeFieldCollisionDebugMode(int a0);
extern float D_00628C48;

void SetMotionDirectionWithLimit(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, a1);
    MatrixDrive_TurnObjectMatrix(a0 + 0x10, a0);
    *(float *)(a0 + 0x14) = *(float *)(a0 + 0x14) + D_00628C48;
    ChangeFieldCollisionDebugMode(a0);
}

extern void LoadCollision(int a0);
extern float D_00628C4C;

void GetRootPosOfNextFrame(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, a1);
    MatrixDrive_TurnObjectMatrix(a0 + 0x10, a0);
    *(float *)(a0 + 0x14) = *(float *)(a0 + 0x14) + D_00628C4C;
    LoadCollision(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", AdjustMotionHeightToField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetLowerPlaneCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", getLowerPlaneCollisionE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", calcFootIK);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", InitMotionGeoInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", dispSkeltonHierarchy);

extern void func_00166910();
extern void _SetCurrentMatrix();

void DispSkelton(int a0, char *a1, char *a2) {
    func_00166910(a0, a1, *(int *)(a2 + 8),
        *(int *)(*(char **)(*(char **)a2 + 0x15C) + 0xC) + (*(int *)(a2 + 4) << 6));
    *(int *)(a1 + 4) = 0;
    _SetCurrentMatrix(a1, a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SlopeIKControl);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetPureVerticalPlaneOfCurrentPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", getVerticalElementOfWallNormal);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", AdjustVerticalSidePlaneOfWall);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetPureVerticalPlane);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", _getS16MotRotElem);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", _getMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetStreamMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", copyMotionWithNodeHrc);

typedef struct { long long x; int y; } __attribute__((packed, aligned(4))) HrcNode;

void CopyMotionWithNodeHrc(void *a0) {
    char *p = *(char **)((char *)a0 + 0x15C);
    char *d = *(char **)((char *)a0 + 0x164);
    *(HrcNode *)(p + 0x170) = *(HrcNode *)(p + 0x190);
    *(HrcNode *)(d + 0x610) = *(HrcNode *)(p + 0x190);
}

void *GetFloatingMotion(int **a0) {
    return (char *)a0[0x57] + 0x670;
}

int MakeMirrorMotion(int **a0) {
    return a0[0x57][0x74];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetFloatingShapeMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", FeedbackWallWorkInfoToBrainSystem);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetMotionPointer);

void GetCollisionOfLastActiveField(void *a0) {
    char *base = *(char **)((char *)*(int **)((char *)a0 + 0x15C) + 0x7E0);
    int i;
    for (i = 0; i < *(int *)((char *)*(int **)((char *)a0 + 0x15C) + 0x88); i++) {
        base[i] = 0;
    }
}

extern int soundSePlayModeStop(void);
typedef struct { long long w[62]; } _0x1F0;
extern _0x1F0 D_00272120;

void DebugDisp1Collision(_0x1F0 *self) {
    *self = D_00272120;
    *(int *)((char *)self + 0x1AC) = soundSePlayModeStop();
    *(int *)((char *)self + 0x1B0) = soundSePlayModeStop();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", DebugDisp1CollisionWithColor);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SetMotionBlendlessNode);

void ClearMotionBlendlessNode(int **a0, int a1) {
    int *p = a0[0x57];
    p[0x132] = a1;
}

float InitMotionStateInfo(int **a0) {
    int *p = a0[0x57];
    return *(float *)((char *)p + 0x49C);
}

int GetSkeltonFocusNode(int **a0) {
    return a0[0x57][0x124];
}

void AdjustMotionHeightToNearestField(int **a0) {
    int *p = a0[0x57];
    p[0x135] = 0;
}

void SetRootUpdateMode(int **a0) {
    int *p = a0[0x57];
    p[0x135] = 1;
}

int ForMotionViewer_GetCurrentAnimationFrame(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return func_001668B0(*(int *)((char *)p + 0x5E8));
}

extern int func_001668B0(int a0);

int ForMotionViewer_GetCurrentMotion(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return func_001668B0(*(int *)((char *)p + 0x5E4));
}

int EnableMotionOrientUpdate(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return func_001668B0(*(int *)((char *)p + 0x5DC));
}

int DisableMotionOrientUpdate(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return func_001668B0(*(int *)((char *)p + 0x5E0));
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CheckFloorAttribute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CheckWallAttribute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CheckPureWallAttribute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CheckPureCliffAttribute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetStreamShapeMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetDifferenceFromWallUpperField);

void GetDifferenceFromLastField(int **a0) {
    int *p = a0[0x57];
    p[0x130] = 1;
}

void GetDifferenceFromLowerField(int **a0) {
    int *p = a0[0x57];
    p[0x130] = 0;
}

float GetDifferenceFromWallLowerPlane(int **a0) {
    int *p = a0[0x57];
    return *(float *)((char *)p + 0x608);
}

int GetDifferenceFromWallUpperPlane(int **a0) {
    return a0[0x57][0x17C];
}

int DisableChangeRootUpdateMode(int **a0) {
    return a0[0x57][0x17D];
}

float EnableChangeRootUpdateMode(char *a0, char *a1) {
    float x = func_00166A48(*(char **)(a0 + 0x15C) + 0x1C0, *(char **)(a0 + 0x15C) + 0xA0);
    return x - func_00166A48(*(char **)(a1 + 0x15C) + 0x1C0, *(char **)(a1 + 0x15C) + 0xA0);
}

float GetRopeHangablePos(int **a0) {
    int *p = a0[0x57];
    return *(float *)((char *)p + 0x590);
}

float GetMotionFrameFlag1(int **a0) {
    int *p = a0[0x57];
    return *(float *)((char *)p + 0x570);
}

extern void GetMatrixFromQuaternion(void *m);

void GetMotionFrameFlag2(void *a0, int n) {
    int *p;
    int i;
    if (n <= 0) return;
    p = (int *)a0;
    i = n;
    do {
        *p = 0;
        GetMatrixFromQuaternion((char *)p + 0x10);
        p = (int *)((char *)p + 0x20);
    } while (--i != 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetHeightOfFieldPlaneDifference);

extern void GetRootMatrixByDObj(int *a0);

void GetHeightOfWallFromGObj(int *a0, int **a1) {
    do {
        GetRootMatrixByDObj(a0);
    } while (0);
    *(float *)((char *)a0 + 0x4) += *(float *)((char *)a1[0x57] + 0x260);
}

void GetHeightOfCliffFromGObj(int **a0, float a1) {
    int *p = a0[0x57];
    *(float *)((char *)p + 0x4A8) = a1;
}

extern void func_0023FFF0();
extern char D_00271BD0[];

void InitMotionRotElem(char *a0) {
    char *sub = *(char **)(a0 + 0x15C);
    char *q = sub + 0x220;
    char *p = sub + 0xA0;
    MatrixDrive_TurnObjectMatrix((int)q, D_00271BD0);
    func_0023FFF0(sub + 0x240, p, q);
    *(int *)(p + 0x170) = -1;
}

extern int D_00629E4C;

void SetMotionNodeFixModeParameter(int a0) {
    D_00629E4C = a0;
}

typedef struct { long long a, b, c, d; } Block20;

void GetRootProjectionPosOfGObj(Block20 *dst, Block20 *src, int n) {
    if (n > 0) {
        do {
            *dst++ = *src++;
        } while (--n);
    }
}

void SetMotionPlaySpeedRatio(float *dst, void *a1, int idx)
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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", ClearMotionGeometryInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SetSkeltonDispSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CopyMotion);

void GetMotionRootPos(float *dst, char *a1, int idx, int count)
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


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00272340;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054E0E0;  /* stride 0x4 */

/* end struct shapes */

#include "common.h"
#include "box.h"
#include "switch.c.inc"
#include "DObj.h"
#include "debug.h"
#include "gamesys.h"
#include "generator.h"
#include "frameDependSequence.h"
#include "item.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include <libvu0.h>
#include <string.h>

void landingSE(int a0)
{
    ExecuteSEPackage(a0, 0x2);
}

void fallDownStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x24);
}

void pushStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x4);
}

void pullStartSE(int a0)
{
    ExecuteSEPackage(a0, 0xD);
}

void wallHitSE(int a0)
{
    ExecuteSEPackage(a0, 0x1E);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", initFallDown);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", checkFieldContact);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", execNormalMove);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", execAutoMove);

static inline float getAlign(float v, float g)
{
    if (0.0f <= v) {
        return (float)(int)((v + g * 0.5f) / g) * g;
    }
    return -getAlign(-v, g);
}

static inline void alignPosition(char *self, float *dst, float *src, float grid)
{
    float npos[4];
    char *n = (char *)*(int *)(self + 0x15C);
    float cx = *(float *)(n + 0x50);
    float cz = *(float *)(n + 0x58);

    CopyVector(npos, src);
    npos[0] = getAlign(src[0] - cx, grid) + cx;
    npos[2] = getAlign(src[2] - cz, grid) + cz;

    CopyVector(dst, npos);
}

/* kept local: this TU's uses of GetInverseQuaternion do not fit the prototype in quaternion.h */
extern void GetInverseQuaternion(void *dst, void *src);
/* kept local: this TU's uses of SetRootQuaternion do not fit the prototype in geometryManager.h */
extern void SetRootQuaternion(void *obj, void *q);
/* kept local: this TU's uses of SetDirectRootPosition do not fit the prototype in geometryManager.h */
extern void SetDirectRootPosition(void *obj, void *pos);

int AlignBox(char *a0, float grid)
{
    float pos[4];
    float quat[4];
    char *sub = *(char **)(a0 + 0x15C);
    char *q = *(char **)(sub + 0x830);

    GetInverseQuaternion(quat, sub + 0x60);
    SetRootQuaternion(a0, quat);
    GetRootPosition(pos, a0);
    alignPosition(a0, pos, pos, grid);
    SetDirectRootPosition(a0, pos);
    *(int *)(q + 0x20) = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", initWheels);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", dispWheels);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", getNearestPosition);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", onPathInitialize);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", onPath);

/* kept local: this TU's uses of FSqrt do not fit the prototype in matrixDrive.h */
extern float FSqrt(float f);

inline float GetDistanceOfGObj(void *a0, void *a1)
{
    char v[0x10];
    char w[0x10];
    GetRootPosition(v, a1);
    GetRootPosition(w, a0);
    sceVu0SubVector(v, v, w);
    return FSqrt(sceVu0InnerProduct(v, v));
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", playAnimationCore);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", MoveFloatingBox);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", avoidCharGObj);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", execFloating);

/* kept local: this TU's uses of IdentityQuaternion do not fit the prototype in quaternion.h */
extern char IdentityQuaternion[];
/* kept local: this TU's uses of ZeroVector do not fit the prototype in matrixDrive.h */
extern char ZeroVector[];
extern char D_004E62A0[];
/* kept local: this TU's uses of CopyQuaternion do not fit the prototype in quaternion.h */
extern void CopyQuaternion(void *dst, void *src);

void initFloating(char *a0)
{
    char *p = (char *)*(int *)(*(int *)(a0 + 0x15C) + 0x830);

    *(int *)(*(int *)(a0 + 0x15C) + 0x70) = *(int *)(*(int *)(p + 0x160) + 0x70);
    *(int *)(*(int *)(a0 + 0x15C) + 0x78) = 1;
    CopyQuaternion((char *)*(int *)(a0 + 0x15C) + 0xC0, IdentityQuaternion);
    SetRootQuaternion(a0, IdentityQuaternion);
    CopyVector(p + 0xE0, ZeroVector);
    CopyVector(p + 0xC0, ZeroVector);
    CopyVector(p + 0xD0, ZeroVector);
    GetRootPosition(p + 0x100, a0);
    CopyVector((char *)*(int *)(a0 + 0x15C) + 0x520, D_004E62A0);
    *(short *)(p + 0x118) = 0;
    execFloating(a0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", _checkItemBreak);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", initLanding);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", execFallDown);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", inertiaMove);

inline int IsThisBoxTruck(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x58);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", action);

/* kept local: this TU's uses of GetRootMatrix do not fit the prototype in geometryManager.h */
extern void GetRootMatrix();

inline void GetBoxGlobalHoldPoint(void *a0, void *a1, void *a2)
{
    float buf[16];
    GetRootMatrix(buf, a1);
    sceVu0ApplyMatrix(a0, buf, a2);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", GetBoxHoldPoint);

inline int CanHoldBox(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x20) == 0;
}

/* kept local: this TU's uses of AddVectorXYZ do not fit the prototype in matrixDrive.h */
extern void AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of _SubVector do not fit the prototype in Matrix.h */
extern void _SubVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *dst, void *src, float k);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
/* kept local: this TU's uses of SetSimplePlane do not fit the prototype in fieldCollision.h */
extern void SetSimplePlane(void *plane, float x, float y, float z, float d);
/* kept local: this TU's uses of GetDistanceFromPlane do not fit the prototype in fieldCollision.h */
extern float GetDistanceFromPlane(void *plane, void *pos);
/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
/* kept local: this TU's uses of GetCharGObjList do not fit the prototype in geometryManager.h */
extern char **GetCharGObjList(void);
/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *a0);
/* kept local: this TU's uses of ClipWallBoxStop do not fit the prototype in fieldCollision.h */
extern void ClipWallBoxStop(void *a0);
/* kept local: this TU's uses of UpdateRootMatrix do not fit the prototype in geometryManager.h */
extern void UpdateRootMatrix(void *a0);
extern int moveXPlus(float *a0, float f12, float f13, float f14);
extern int moveXMinus(float *a0, float f12, float f13, float f14);
extern int moveZPlus(float *a0, float f12, float f13, float f14);
extern int moveZMinus(float *a0, float f12, float f13, float f14);
extern int stage_no;
/* kept local: this TU's uses of ZeroVector do not fit the prototype in matrixDrive.h */
extern char ZeroVector[];
extern int D_0028F4C0[];
extern char D_0061F080[];

typedef struct {
    float x, y, z;
} BoxVec3;

static inline void setupClipWork(char *w, char *obj, float *dir, float len, float h)
{
    float t[4];

    _ScaleVector(t, dir, len);
    GetRootPosition(w, obj);
    *(float *)(w + 4) += h;
    _AddVectorXYZ(w + 0x10, w, t);
}

static inline int checkBoxStopWall(char *obj, float *dir)
{
    char w[0xC0];
    int r = 1;

    memset(w, 0, 0xC0);
    setupClipWork(w, obj, dir, 145.0f, 40.0f);
    ClipWallBoxStop(w);
    if (*(int *)(w + 0x88) != 0) {
        r = 0;
    }
    return r;
}

static inline int checkMoveWall(char *obj, float *dir)
{
    char w[0xC0];
    int r = 1;

    memset(w, 0, 0xC0);
    setupClipWork(w, obj, dir, 245.0f, 0.0f);
    ClipWall(w);
    if (*(int *)(w + 0x88) != 0) {
        r = 0;
    }
    return r;
}

static inline int moveXPlus(float *a0, float f12, float f13, float f14)
{
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13)
            goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13)
            goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[0])) {
        rv = 0;
        goto end;
    }
    if (a0[0] < f12 + f13)
        return 1;
    rv = 0;
end:
    return rv;
}

static inline int moveXMinus(float *a0, float f12, float f13, float f14)
{
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13)
            goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13)
            goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < -a0[0])) {
        rv = 0;
        goto end;
    }
    if (-a0[0] < f12 + f13)
        return 1;
    rv = 0;
end:
    return rv;
}

static inline int moveZPlus(float *a0, float f12, float f13, float f14)
{
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[0];
    if (w < 0.0f) {
        if (-w < f13)
            goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13)
            goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[2])) {
        rv = 0;
        goto end;
    }
    if (a0[2] < f12 + f13)
        return 1;
    rv = 0;
end:
    return rv;
}

static inline int moveZMinus(float *a0, float f12, float f13, float f14)
{
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[0];
    if (w < 0.0f) {
        if (-w < f13)
            goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13)
            goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < -a0[2])) {
        rv = 0;
        goto end;
    }
    if (-a0[2] < f12 + f13)
        return 1;
    rv = 0;
end:
    return rv;
}

static inline int checkCharGObjs(char *obj, char *holder, float *dir)
{
    float pos[4];
    float pos2[4];
    float d[4];
    char **list;
    int (*move)(float *, float, float, float);
    float w = 50.0f;

    list = GetCharGObjList();
    GetRootPosition(pos, obj);
    if ((dir[0] < 0.0f ? -dir[0] : dir[0]) > (dir[2] < 0.0f ? -dir[2] : dir[2])) {
        if (0.0f <= dir[0]) {
            move = moveXPlus;
        } else {
            move = moveXMinus;
        }
    } else if (0.0f <= dir[2]) {
        move = moveZPlus;
    } else {
        move = moveZMinus;
    }
    while (*list != 0) {
        if (*list != holder) {
            GetRootPosition(pos2, *list);
            _SubVector(d, pos2, pos);
            if (move(d, w + w, w, *(float *)(*(char **)(*list + 0x15C) + 0x3D8) + 5.0f) != 0) {
                return 0;
            }
        }
        list++;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", _checkItemCollision);

static inline int checkItemHit(char *obj, float *dir)
{
    float pos[4];
    float d[4];
    float to[4];

    _ScaleVectorXYZ(d, dir, 100.0f);
    GetRootPosition(pos, obj);
    _AddVectorXYZ(to, pos, d);
    return _checkItemCollision(to);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", moveBoxAutoMatic);

int MoveBoxWithHoldPoint(char *a0, void *a1, char *a2, int a3, float *a4)
{
    float plane[4];
    float nv[4];
    float hp[4];
    float pos[4];
    float mv[4];
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int idx;
    int hit;
    float dot;
    float dist;

    CopyVector(q + 0x190, a4);
    GetBoxGlobalHoldPoint(hp, a0, a1);
    GetRootPosition(pos, a0);
    sceVu0SubVector(nv, hp, pos);
    sceVu0Normalize(nv, nv);

    dot = sceVu0InnerProduct(nv, hp);
    SetSimplePlane(plane, nv[0], nv[1], nv[2], -dot);

    idx = GetSkeltonFocusNode(a2, a3);
    dist =
        GetDistanceFromPlane(plane, *(char **)(*(char **)(a2 + 0x15C) + 0xC) + (idx << 6) + 0x30);

    sceVu0ScaleVector(mv, nv, dist);

    if (*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x58) != 0) {
        float m[16];

        _ScaleVector(mv, mv, 0.05f);
        MatrixDrive_SetTransposeMatrix(m, *(void **)(*(char **)(a0 + 0x15C) + 0xC));
        sceVu0ApplyMatrix(mv, m, mv);
        AddVectorXYZ(q + 0x40, q + 0x40, mv);
        if (onPath(a0) != 0) {
            CopyVector(q + 0x40, ZeroVector);
        }
        if (stage_no == 8) {
            if (*(int *)q == 0 && *(int *)(q + 0x114) == 0) {
                pushStartSE((int)a0);
            }
        }
        ReviveCarryableItemsWithBoundary(pos, 100.0f);
    } else if (checkCharGObjs(a0, a2, a4) && checkBoxStopWall(a0, a4) &&
               CheckGeneratorCollision(a0, a4) && checkItemHit(a0, a4)) {
        *(int *)(q + 0x30) = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] *
                             (GetNbMotionFrames(*(int *)(*(char **)(a2 + 0x15C) + 0x4A0)) - 1) /
                             0x1E;
        _ScaleVectorXYZ(q + 0x40, a4, 100.0f / (float)*(int *)(q + 0x30));

        hit = checkMoveWall(a0, a4);
        if (hit) {
            *(int *)(q + 0x20) = 1;
        } else {
            float npos[4];
            float d[4];

            GetRootPosition(npos, a0);
            _ScaleVector(d, a4, 100.0f);
            _AddVectorXYZ(npos, npos, d);
            *(int *)(q + 0x20) = 6;
            alignPosition(a0, npos, npos, 100.0f);
            npos[1] -= 1.0f;
            debug_StdPrintfDummy(D_0061F080, npos[0], npos[1], npos[2]);
            CopyVector(*(char **)(*(char **)(*(char **)(q + 0x180) + 0x15C) + 0xC) + 0x30, npos);
            *(int *)(*(char **)(q + 0x180) + 0x16C) = 1;
        }
        if (*(int *)(*(char **)(a2 + 0x15C) + 0x56C) != 0) {
            *(BoxVec3 *)(q + 0x60) = *(BoxVec3 *)(*(char **)(a2 + 0x15C) + 0x190);
        }
    } else {
        return 0;
    }
    UpdateRootMatrix(a0);
    {
        int rv = execNormalMove(a0, 1);
        UpdateRootMatrix(a0);
        return rv;
    }
}

inline int BoxRideFunc(int *a0, char *a1)
{
    char *obj = (char *)*a0;
    char *p15c = *(char **)(obj + 0x15C);
    char *s0 = *(char **)(p15c + 0x830);
    char buf[0x20];
    if (*(int *)(s0 + 0x20) != 5) {
        return 0;
    }
    *(float *)(p15c + 0x134) += 0.5f;
    GetRootPosition(buf + 0x10, obj);
    CopyVector(buf, *(char **)(a1 + 0x15C) + 0xA0);
    *(int *)(buf + 4) = 0;
    sceVu0AddVector(s0 + 0xD0, s0 + 0xD0, buf);
    return 1;
}

inline void ExecBoxMoveStartReaction(char *a0, int a1)
{
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(int *)(q + 0x58) != 0) {
        if (*(int *)(q + 0x110) != 0) {
            goto end;
        }
    }
    if (a1 >= 0) {
        pushStartSE((int)a0);
        *(int *)(q + 0x114) = 0;
    } else {
        pullStartSE((int)a0);
        *(int *)(q + 0x114) = 0;
    }
end:
    *(int *)(q + 0x110) = 1;
}

inline void ExecBoxMoveEndReaction(char *a0)
{
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(int *)(q + 0x58) == 0 || *(int *)(q + 0x110) != 0) {
        StopSEPackage((int)a0);
        StopSEPackageWithGroupVariation((int)a0, 1);
        ExecuteSEPackage((int)a0, 0x16);
        if (*(int *)(q + 0x140) != 0) {
            wallHitSE((int)a0);
            *(int *)(q + 0x140) = 0;
        }
    }
    *(int *)(q + 0x110) = 0;
}

extern char D_0061F0A0[];
extern char D_0061F0B0[];
extern char D_0061F128[];
extern char D_0061F138[];

void ReInitBoxGeo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    debug_StdPrintfDummy(D_0061F0A0);
    *(int *)(*(char **)(a0 + 0x15C) + 0x70) = *(int *)(p + 0x2C);
    if (checkFieldContact(a0, 100000.0f) == 0) {
        debug_StdPrintfDummy(D_0061F0B0);
    } else {
        int m = *(int *)(*(char **)(a0 + 0x15C) + 0x5F8);

        if (m == 0x40 || m == 0x50) {
            initFloating(a0);
            *(int *)(p + 0x20) = 5;
            debug_StdPrintfDummy(D_0061F128);
        } else {
            *(int *)(p + 0x20) = 0;
            AlignBox(a0, 100.0f);
            execNormalMove(a0, 1);
            debug_StdPrintfDummy(D_0061F138);
        }
    }
    UpdateRootMatrix(a0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", InitBoxGeo);

void BoxGeo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    action(a0);
    UpdateRootMatrix(a0);
    if ((*(int *)p)++ >= 0x1F) {
        *(int *)p = 0;
        gamesysObjInfoUniqDataSet(a0);
    }
}

/* kept local: this TU's uses of p2o_SetDefaultEnviroment do not fit the prototype in DisplayP2O.h */
extern int p2o_SetDefaultEnviroment(int a0);
/* kept local: this TU's uses of p2o_DispVU1 do not fit the prototype in DisplayP2O.h */
extern void p2o_DispVU1(void *a0);
extern int D_0028F4D4[];

inline void BoxDL(char *a0)
{
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    p2o_SetDefaultEnviroment((int)a0);
    p2o_DispVU1(a0);
    if (*(int *)(q + 0x58) != 0) {
        dispWheels(a0);
    }
    if (D_0028F4D4[0] != 0) {
        StopSEPackageWithGroupVariation((int)a0, 1);
        *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x138) = 0;
    }
}

extern char D_0061F148[];

inline int BoxGeoRestore(float *a0, float *a1)
{
    a0[0] = a1[4];
    a0[1] = a1[5];
    a0[2] = a1[6];
    a0[4] = a1[8];
    a0[5] = a1[9];
    a0[6] = a1[10];
    debug_StdPrintfDummy(D_0061F148, a0[8], a0[9], a0[10]);
    return 1;
}

inline int BoxExtGeoRestore(void)
{
    return 1;
}

inline int BoxMemoryFunc(void)
{
    return 1;
}

int GetBoxMode(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x20);
}

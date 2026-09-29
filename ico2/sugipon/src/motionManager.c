#include "common.h"
#include "typedef.h"
#include "sugiCommon.h"
#include "debug_exception.h"
#include "obj_manager.h"
#include "Primitive.h"
#include "lineManager.h"
#include "motionManager2.h"

typedef struct {
    char b[0x20];
} ShiftBlk;

/* .sbss, owned by motionManager.o (0x38, the run and MAIN.MAP's own size; MAIN.MAP
   names no symbol in it, so all fourteen words are file statics), in the ROM's run
   order. The still-asm functions reach them by these symbol names. */
static float D_0063C474;

static char *D_0063C478;

static char *D_0063C47C;

static char *D_0063C480;

static char *D_0063C484;

static char *D_0063C488;

static int D_0063C48C;

static char *D_0063C490;

static char *D_0063C494;

static int D_0063C498;

static int D_0063C49C;

static char *D_0063C4A0;

static char *D_0063C4A4;

static char *D_0063C4A8;

/* .data, owned by motionManager.o (VMA 0x4EC950..0x4ECBE0), in the ROM's run
   order, which is the source order of each object's first user. MAIN.MAP names
   none of them; the ones a still-asm function reaches are not static until it
   lands. */
static float D_004EC950[4] = {-3.0f, 0.0f, -3.0f, 0.0f};

static float D_004EC960[4] = {3.0f, 0.0f, 3.0f, 0.0f};

static float D_004EC970[4] = {-3.0f, 0.0f, 3.0f, 0.0f};

static float D_004EC980[4] = {3.0f, 0.0f, -3.0f, 0.0f};

static sceVu0IVECTOR D_004EC990 = {0xFF, 0x80, 0x00, 0x80};

static float D_004EC9A0[4] = {-4.0f, 0.0f, -4.0f, 0.0f};

static float D_004EC9B0[4] = {4.0f, 0.0f, 4.0f, 0.0f};

static float D_004EC9C0[4] = {-4.0f, 0.0f, 4.0f, 0.0f};

static float D_004EC9D0[4] = {4.0f, 0.0f, -4.0f, 0.0f};

static float D_004EC9E0[4] = {0.0f, 0.0f, 0.0f, 1.0f};

static float D_004EC9F0[4] = {0.0f, 0.0f, 0.0f, 1.0f};

static float D_004ECA00[4] = {0.0f, 0.0f, 0.0f, 1.0f};

static float D_004ECA10[4] = {0.0f, -40.0f, 0.0f, 1.0f};

static float D_004ECA20[4] = {0.0f, 0.0f, 300.0f, 1.0f};

static float D_004ECA30[4] = {0.0f, 10.0f, 0.0f, 1.0f};

static float D_004ECA40[4] = {0.0f, 0.0f, 300.0f, 1.0f};

static sceVu0IVECTOR D_004ECA50 = {0xFF, 0x80, 0x00, 0x80};

static sceVu0IVECTOR D_004ECA60 = {0x00, 0x80, 0xFF, 0x80};

static float D_004ECA70[4] = {0.0f, 0.0f, 0.0f, 0.0f};

static float D_004ECA80[4] = {0.0f, 0.0f, 10.0f, 0.0f};

static float D_004ECA90[4] = {0.0f, 0.0f, -50.0f, 1.0f};

static float D_004ECAA0[4] = {0.0f, 0.0f, 50.0f, 1.0f};

static float D_004ECAB0[4] = {-30.0f, 0.0f, 0.0f, 1.0f};

static float D_004ECAC0[4] = {30.0f, 0.0f, 0.0f, 1.0f};

static float D_004ECAD0[4] = {0.0f, 0.0f, -50.0f, 1.0f};

static float D_004ECAE0[4] = {0.0f, 0.0f, 50.0f, 1.0f};

static float D_004ECAF0[4] = {-40.0f, 0.0f, 0.0f, 1.0f};

static float D_004ECB00[4] = {40.0f, 0.0f, 0.0f, 1.0f};

static int D_004ECB10[] = {51, 47, 52, 48, -1};

static int D_004ECB28[] = {51, 47, 52, 48, 22, 6, 11, 27, -1};

static sceVu0IVECTOR D_004ECB50 = {0x40, 0x60, 0x80, 0x80};

static sceVu0IVECTOR D_004ECB60 = {0xFF, 0x60, 0x40, 0x80};

static float D_004ECB70[4] = {0.0f, 1.0f, 0.0f, 0.0f};

static float D_004ECB80[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
};

static sceVu0IVECTOR D_004ECBC0 = {0xFF, 0x60, 0x40, 0x80};

static sceVu0IVECTOR D_004ECBD0 = {0x00, 0x60, 0xFF, 0x80};

/* .bss, owned by motionManager.o (0xA0 = MAIN.MAP's), in the ROM's run order;
   MAIN.MAP names none of them, so they are file statics the stubs reach by
   these names. */
static float D_00720180[4];

static float D_00720190[4];

static float D_007201A0[16];

static float D_007201E0[4];

static float D_007201F0[4];

static float D_00720200[4];

static float D_00720210[4];

extern char *D_0063B938;
extern int D_0063B93C;
/* kept local: this TU's uses of MatrixDrive_GetMatrix do not fit the prototype in matrixDrive.h */
extern int MatrixDrive_GetMatrix(void);
/* kept local: this TU's uses of CopyMatrix do not fit the prototype in matrixDrive.h */
extern void CopyMatrix(void *dst, void *src);
/* kept local: this TU's uses of MatrixDrive_PopMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_PopMatrix(void);
/* kept local: this TU's uses of GetCurrentQuaternion do not fit the prototype in quaternion.h */
extern void *GetCurrentQuaternion(void);
/* kept local: this TU's uses of MatrixDrive_PushMatrixWithNoCopy do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_PushMatrixWithNoCopy(void);
/* kept local: this TU's uses of PushQuaternionWithNoCopy do not fit the prototype in quaternion.h */
extern void PushQuaternionWithNoCopy(void);
/* kept local: this TU's uses of ZUnitVector do not fit the prototype in matrixDrive.h */
extern char ZUnitVector[];
/* kept local: this TU's uses of MatrixDrive_PushMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_PushMatrix(void);
/* kept local: this TU's uses of SetQuaternionByAxisRotateV do not fit the prototype in quaternion.h */
extern void SetQuaternionByAxisRotateV(void *dst, short ang, void *v);
/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(void *a0, int a1, char *a2);
/* a plain float (GetGeometryOfMotion and GetMatrixOfMotion write it):
 * _getFinalMatrix reloads it after calls; setIKAndAdjustRootHeight keeps it
 * across its stores to the geo block because those are structure members. */
extern float D_0063B900;
/* kept local: this TU's uses of GetMatrixFromQuaternion do not fit the prototype in quaternion.h */
extern void GetMatrixFromQuaternion(void *a0, void *a1);
/* kept local: this TU's uses of GetMatrixFromQuaternionPos do not fit the prototype in quaternion.h */
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
/* kept local: this TU's uses of MatrixDrive_GetLastMatrix do not fit the prototype in matrixDrive.h */
extern void *MatrixDrive_GetLastMatrix(void);
/* kept local: this TU's uses of _MulMatrix do not fit the prototype in Matrix.h */
extern void _MulMatrix(void *a0, void *a1, void *a2);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *buf, void *p1, float f);
/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *a0);
/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector(void *dst, void *src);
/* kept local: this TU's uses of GetPointDistance do not fit the prototype in matrixDrive.h */
extern float GetPointDistance(void *a0, void *a1);
/* kept local: this TU's uses of MatrixDrive_TransMatrixV do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_TransMatrixV(void *a0);
extern void sceVu0ApplyMatrix(int *a0, int a1, char *a2);
/* kept local: this TU's uses of GetYProjectionOfPlane do not fit the prototype in fieldCollision.h */
extern float GetYProjectionOfPlane(int a0, int a1);
/* kept local: this TU's uses of MatrixDrive_TransMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_TransMatrix(float, float, float);
/* kept local: this TU's uses of MultiMatrixByQuaternion do not fit the prototype in quaternion.h */
extern void MultiMatrixByQuaternion(char *p);
/* kept local: this TU's uses of _UnitMatrix do not fit the prototype in Matrix.h */
extern void _UnitMatrix(int a0);
/* kept local: this TU's uses of ClipWallFuchiHangWalkStop do not fit the prototype in fieldCollision.h */
extern void ClipWallFuchiHangWalkStop(void *a0);
/* kept local: this TU's uses of GetWallAttribute do not fit the prototype in fieldCollision.h */
extern int GetWallAttribute(void *a0);
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(int a0, int a1, void *a2);
extern void sceVu0UnitMatrix(int);

typedef struct {
    int a;
    int b;
} MotShift;

extern char D_0061FDC0[];
extern char D_0061FFD8[];
extern char D_0063B920[];
/* kept local: this TU's uses of PushQuaternion do not fit the prototype in quaternion.h */
extern void PushQuaternion(void);
/* kept local: this TU's uses of PopQuaternion do not fit the prototype in quaternion.h */
extern void PopQuaternion(void);
/* kept local: this TU's uses of SetIdentityQuaternion do not fit the prototype in quaternion.h */
extern void SetIdentityQuaternion(void *q);
/* kept local: this TU's uses of RotQuaternionY do not fit the prototype in quaternion.h */
extern void RotQuaternionY(void *q, short ang);
/* kept local: this TU's uses of SetCurrentQuaternion do not fit the prototype in quaternion.h */
extern void SetCurrentQuaternion(void *q);
/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *a0, int a1);
extern void sceVu0Normalize(void *dst, void *src);
extern void __assert(char *file, int line, char *expr);
extern MotShift rootUpdateDirectPlayForStream(void);
extern MotShift rootUpdateXZ(int a0, int a1);
extern MotShift rootUpdateXZ_MotPos(int a0, int a1);
extern MotShift rootUpdateStepSolution(int a0);
extern MotShift rootUpdateHang(int a0, int a1, int a2);
extern MotShift rootUpdateSwim(void);
extern MotShift rootUpdateNodeFix(void);
extern MotShift rootUpdateY(void);
extern MotShift rootUpdateY_Rope(int a0);
extern MotShift rootUpdateTrueMotion(int a0);
extern MotShift rootUpdateDirectPlay(int a0);
extern MotShift rootUpdateFly(void);
extern MotShift rootUpdateEnemyFly(void);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket();
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha();
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri();
/* kept local: this TU's uses of _SubVectorXYZ do not fit the prototype in Matrix.h */
extern void _SubVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of VectorLengthSquare do not fit the prototype in matrixDrive.h */
extern float VectorLengthSquare(void *v);
/* kept local: this TU's uses of UnitRotation do not fit the prototype in matrixDrive.h */
extern void UnitRotation(int m);
/* kept local: this TU's uses of _Sqrt do not fit the prototype in Matrix.h */
extern float _Sqrt(float x);
/* kept local: this TU's uses of DrawGObjWallCollision do not fit the prototype in fieldCollision.h */
extern void DrawGObjWallCollision(int a0, int a1);
extern char D_0061FDD8[];

/* FLT_MAX word in .sdata (D_0063B924 holds 0x7F7FFFFF). Only an alias-set-0
   (union member) read reproduces ROM's hoist of this load above the four int
   stores in _checkCliffAndWall. clearCollisionStatus's own word at D_0063B91C
   is the constant pool of its float literal (see clearCliffStatus), which is
   what this one likely is too. */
typedef union {
    float f;
    int i;
} FltWord;

extern FltWord D_0063B924[];
extern unsigned char D_002C2DC8[];
extern int D_0063B158;
/* kept local: this TU's uses of MatrixDrive_RotMatrixZ do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_RotMatrixZ(int a0);
/* kept local: this TU's uses of AddVectorXYZ do not fit the prototype in matrixDrive.h */
extern void AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of _SubVector do not fit the prototype in Matrix.h */
extern void _SubVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *dst, void *a);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *dst, void *a, float s);
/* kept local: this TU's uses of _AddVector do not fit the prototype in Matrix.h */
extern void _AddVector(void *dst, void *a, void *b);

typedef struct {
    int obj;
    int node;
} ActPt;

extern int D_00639EA4;
/* kept local: this TU's uses of _InterVectorXYZ do not fit the prototype in Matrix.h */
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);

/* The wall-hit record at ClipBuf+0x80: the object and its node, then the hit
   count.  GetPureVerticalPlane reads it as its `int *cfg` argument (see
   getVerticalElementOfWallNormal in src/motionManager2) and the character
   record keeps a copy at +0xE0.  The object/node pair is its own member: the
   ROM copies it as an eight-byte block and the count as a separate word. */
typedef struct {
    int obj;
    int node;
} WallObj;

typedef struct {
    WallObj o;
    int n;
} WallCfg;

/* RECONSTRUCTION: the 0xC0-byte field/wall clip request block.  The sweep
   radius at +0x70 is broken out because _wallHitReaction builds one with an
   initialiser whose single non-zero element is that field; +0x74 is the
   12-byte wall filter _wallCollisionPreProcess copies in (its FieldBlk12). */
typedef struct {
    long long b[14]; /* 0x00 */
    float rad;       /* 0x70 */
    WallCfg filter;  /* 0x74 */
    long long c[8];  /* 0x80 */
} ClipBuf;

extern char D_0061FD00[];
/* kept local: this TU's uses of ClipWallField do not fit the prototype in fieldCollision.h */
extern void ClipWallField(void *a0);
/* kept local: this TU's uses of DrawCollisionRay do not fit the prototype in fieldCollision.h */
extern void DrawCollisionRay(void *a0);
/* kept local: this TU's uses of SubVectorXYZ do not fit the prototype in matrixDrive.h */
extern void SubVectorXYZ(void *dst, void *a, void *b);
extern float sceVu0InnerProduct(void *a, void *b);
/* kept local: this TU's uses of FSqrt do not fit the prototype in matrixDrive.h */
extern float FSqrt(float x);
/* kept local: this TU's uses of MatrixDrive_ScaleMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_ScaleMatrix(float, float, float);
extern int D_0063B148;
/* kept local: this TU's uses of p2o_DispVU1 do not fit the prototype in DisplayP2O.h */
extern void p2o_DispVU1();
/* kept local: this TU's uses of MatrixDrive_RotMatrixX do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_RotMatrixX(int a0);
static void getInitialMatrix(int a0, int a1);
extern void sceVu0MulMatrix(int a0, int a1, int a2);
extern int D_0063B8F8;
extern int D_0063B8FC;
/* kept local: this TU's uses of IdentityQuaternion do not fit the prototype in quaternion.h */
extern char IdentityQuaternion[];
/* kept local: this TU's uses of ClipFloor do not fit the prototype in fieldCollision.h */
extern void ClipFloor();

#include "motionManager.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

static inline void dispSquare(int alpha)
{
    int col[4] = {0, 128 * alpha / 255, alpha, 128};
    DrawLineG(D_004EC950, col, D_004EC970, col, -1);
    DrawLineG(D_004EC970, col, D_004EC960, col, -1);
    DrawLineG(D_004EC960, col, D_004EC980, col, -1);
    DrawLineG(D_004EC980, col, D_004EC950, col, -1);
}

void dispSquare2(int alpha)
{
    DrawLineG(D_004EC9A0, D_004EC990, D_004EC9C0, D_004EC990, -1);
    DrawLineG(D_004EC9C0, D_004EC990, D_004EC9B0, D_004EC990, -1);
    DrawLineG(D_004EC9B0, D_004EC990, D_004EC9D0, D_004EC990, -1);
    DrawLineG(D_004EC9D0, D_004EC990, D_004EC9A0, D_004EC990, -1);
}

#include "motMan_getFinalMatrix.c.inc"

inline void SetHitCollisionDisplay(int a, int b)
{
    D_0063B8F8 = a;
    D_0063B8FC = b;
}

static inline int findActPointOrder(int *list, int kind)
{
    int *p = list;
    int i = 1;
    while (*p != -1) {
        if (*p++ == kind) {
            return i;
        }
        i++;
    }
    return 0;
}

int findActPoint(int *list)
{
    int bestOrder = 255;
    int minVal = 249;
    int ret = -1;
    int i;

    if (*(int *)(D_0063C490 + 0x308) != 0) {
        return -1;
    }
    for (i = 0; i < D_0063C48C; i++) {
        int order = findActPointOrder(list, *(int *)(D_0063B938 + i * 0x40 + 4));
        int v;
        if (order == 0) {
            continue;
        }
        if (*(int *)(D_0063C490 + 0x230) != 0) {
            int k = *(int *)(D_0063B938 + i * 0x40 + 4);
            if (k == 6 || k == 11) {
                continue;
            }
        }
        if (*(int *)(D_0063C490 + 0x290) != 0) {
            int k = *(int *)(D_0063B938 + i * 0x40 + 4);
            if (k == 22 || k == 27) {
                continue;
            }
        }
        v = *(int *)(D_0063C478 + i * 0x20);
        if (v < minVal || (v == minVal && order < bestOrder)) {
            ret = i;
            minVal = v;
            bestOrder = order;
        }
    }
    return ret;
}

int checkActPointWithHeight(int kind, float h)
{
    int i;

    if (*(int *)(D_0063C490 + 0x230) != 0) {
        if (kind == 6 || kind == 11) {
            return -1;
        }
    }
    if (*(int *)(D_0063C490 + 0x290) != 0) {
        if (kind == 22 || kind == 27) {
            return -1;
        }
    }
    for (i = 0; i < D_0063C48C; i++) {
        if (*(int *)(D_0063B938 + i * 0x40 + 4) == kind) {
            float d;
            if (*(int *)(D_0063C478 + i * 0x20) >= 249) {
                return -1;
            }
            d = *(float *)(D_0063C484 + i * 0x10 + 4) + D_007201F0[1];
            if ((d < 0.0f ? -d : d) < h) {
                return kind;
            }
            return -1;
        }
    }
    return -1;
}

inline void GetWallVector(int a0, int a1)
{
    CopyVector(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}

/* listing lines 203-209: inlined here and into _checkCliffAndWall, never emitted out of
   line (name ours). The float limit is a literal: ee-gcc keeps a single-precision
   constant above 1.0e38 in the function's .sdata constant pool. */
static inline void clearCliffStatus(void)
{
    *(unsigned int *)(D_0063C494 + 0x14) &= ~0x10;
    *(int *)(D_0063C494 + 0x104) = 0;
    *(int *)(D_0063C494 + 0xF8) = 0;
    *(int *)(D_0063C494 + 0xFC) = 0;
    *(int *)(D_0063C494 + 0x100) = 0;
    *(float *)(D_0063C494 + 0x110) = 3.40282347e+38f;
    *(float *)(D_0063C494 + 0x114) = 3.40282347e+38f;
}

void clearCollisionStatus(void)
{
    clearCliffStatus();

    *(unsigned int *)(D_0063C494 + 0x14) &= ~0x20;
    *(int *)(D_0063C494 + 0xF4) = 0;
    *(float *)(D_0063C494 + 0x138) = 3.40282347e+38f;
    *(float *)(D_0063C494 + 0x130) = 3.40282347e+38f;
    *(float *)(D_0063C494 + 0x134) = 3.40282347e+38f;
    *(void **)(D_0063C490 + 0x144) = 0;

    *(int *)(D_0063C494 + 0x10C) = 0;
    *(float *)(D_0063C494 + 0x174) = 3.40282347e+38f;
    *(int *)(D_0063C494 + 0x178) = 0;

    *(unsigned int *)(D_0063C494 + 0x14) &= ~0x1000;
    *(int *)(D_0063C494 + 0x108) = 0;
    *(float *)(D_0063C494 + 0x170) = 3.40282347e+38f;

    *(int *)(D_0063C494 + 0x1B8) = *(int *)(D_0063C494 + 0x1B4);
    *(int *)(D_0063C494 + 0x1B4) = 0;
    *(int *)(D_0063C494 + 0x1D4) = 0;

    *(int *)(D_0063C494 + 0x1CC) = 0;
}

void checkUpperWallState(void)
{
    char buf[0xC0];
    memset(buf, 0, 0xC0);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(D_004ECA10);
    CopyVector((void *)buf, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(buf + 0x10), MatrixDrive_GetMatrix(), D_004ECA20);
    MatrixDrive_PopMatrix();
    ClipWall(buf);
    if (*(int *)(buf + 0x88) != 0) {
        float a;
        int *D;
        a = GetPointDistance(buf + 0x20, buf);
        D = (int *)D_0063C494;
        *(float *)((char *)D + 0x170) = a;
        *(int *)((char *)D + 0x108) = 1;
        *(int *)((char *)D + 0x14) = *(int *)((char *)D + 0x14) | 0x1000;
    }
}

void checkWallSideState(void)
{
    ClipBuf buf = *(ClipBuf *)D_0061FD00;
    float v[4];
    char *p = (char *)&buf;

    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(D_004ECA10);
    CopyVector((void *)p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(p + 0x10), MatrixDrive_GetMatrix(), D_004ECA20);
    MatrixDrive_PopMatrix();

    if (*(int *)(D_0063C490 + 0x320) != 0) {
        ClipWallField(p);
    } else {
        ClipWall(p);
    }
    if (D_0063B8FC != 0) {
        DrawCollisionRay(p);
    }
    if (*(int *)(p + 0x88) != 0) {
        SubVectorXYZ(v, p + 0x20, p);
        *(float *)(D_0063C494 + 0x174) = FSqrt(sceVu0InnerProduct(v, v)) + 50.0f;
        *(int *)(D_0063C494 + 0x10C) = 1;
        CopyVector((void *)(D_0063C494 + 0x160), (void *)(p + 0xA0));
    }
}

extern void sceVu0ScaleVector(void *dst, void *src, float s);
/* kept local: this TU's uses of GetYDistanceFromPlane do not fit the prototype in fieldCollision.h */
extern float GetYDistanceFromPlane(void *plane, void *pos);
/* kept local: this TU's uses of SetSimplePlane do not fit the prototype in fieldCollision.h */
extern void SetSimplePlane(void *plane, float x, float y, float z, float d);
/* kept local: this TU's uses of ClipFloorR do not fit the prototype in fieldCollision.h */
extern void ClipFloorR(void *a0);
/* kept local: this TU's uses of GetOrientOfWall do not fit the prototype in fieldCollision.h */
extern void GetOrientOfWall(void *out, void *wall, void *vec);

void checkWallState(int flag)
{
    ClipBuf buf;
    char *p;
    float wv[4];
    ClipBuf tmp;
    float sv[4];
    WallCfg cfg;
    WallCfg cfg2;

    memset(&buf, 0, 0xC0);
    p = (char *)&buf; /* after the memset: the ROM's copy of $sp is the insn
                           the assembler pulls into PushMatrix's delay slot */
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(D_004ECA10);
    CopyVector((void *)p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(p + 0x10), MatrixDrive_GetMatrix(), D_004ECA20);
    MatrixDrive_PopMatrix();

    if (*(int *)(D_0063C490 + 0x320) != 0) {
        ClipWallField(p);
    } else {
        ClipWall(p);
    }
    if (D_0063B8FC != 0) {
        DrawCollisionRay(p);
    }
    if (*(int *)(p + 0x88) != 0) {
        tmp = *(ClipBuf *)p;
        GetWallVector((int)wv, (int)p);
        sceVu0ScaleVector(sv, wv, -200.0f);
        AddVectorXYZ(p + 0x10, p, sv);
        if (*(int *)(D_0063C490 + 0x320) != 0) {
            ClipWallField(p);
        } else {
            ClipWall(p);
        }
        if (*(int *)(p + 0x88) != 0) {
            if (*(int *)(p + 0x88) != ((WallCfg *)((char *)&tmp + 0x80))->n ||
                *(int *)(p + 0x80) != ((WallCfg *)((char *)&tmp + 0x80))->o.obj ||
                *(int *)(p + 0x84) != ((WallCfg *)((char *)&tmp + 0x80))->o.node) {
                if (distance_squared(p, p + 0x20) > distance_squared(&tmp, (char *)&tmp + 0x20)) {
                    *(ClipBuf *)p = tmp;
                }
            }
            if (D_0063B8FC != 0) {
                DrawCollisionRay(p);
            }
            /* One statement, SRCFILE.TXT line 387: the record is filled a
               member at a time (an eight-byte block move, then a word) and
               the whole twelve bytes are then copied out as one unit. */
            cfg = (cfg2.o = ((WallCfg *)(p + 0x80))->o, cfg2.n = ((WallCfg *)(p + 0x80))->n, cfg2);
            if (flag & 1) {
                float v[4];

                SubVectorXYZ(v, p + 0x20, p);
                *(float *)(D_0063C494 + 0x138) = FSqrt(sceVu0InnerProduct(v, v));
                sceVu0ScaleVector(D_0063C494 + 0x140, v, 1.0f / *(float *)(D_0063C494 + 0x138));
                *(int *)(D_0063C494 + 0x14) = *(int *)(D_0063C494 + 0x14) | 0x20;
                *(int *)(D_0063C494 + 0x17C) = *(int *)(D_0063C494 + 0x184) = GetWallAttribute(p);
                /* The hit count reaches GetOrientOfWall as a pointer-typed
                   load, which is what lets it issue ahead of the two int
                   stores above it. */
                GetOrientOfWall(D_0063C494 + 0x150, *(void **)(p + 0x88), p + 0x80);
                *(WallCfg *)(D_0063C490 + 0xE0) = cfg;
                *(int *)(D_0063C490 + 0xEC) = -1;
                if (*(int *)(D_0063C490 + 0x320) != 0 && *(int *)(D_0063C494 + 0x184) == 0x10000) {
                    *(int *)(D_0063C494 + 0x104) = 1;
                } else {
                    *(int *)(D_0063C494 + 0xF4) = 1;
                }
            }
            if (flag & 2) {
                float v2[4];
                float plane[4];

                GetPureVerticalPlane(plane, 0, 0, (int *)&cfg, 0);
                *(float *)(D_0063C494 + 0x134) = -GetYDistanceFromPlane(plane, p) + -40.0f;
                sceVu0ScaleVector(v2, wv, -10.0f);
                AddVectorXYZ(p, p + 0x20, v2);
                CopyVector((void *)(p + 0x10), (void *)p);
                *(float *)(p + 0x14) = *(float *)(p + 0x14) - 10000.0f;
                ClipFloorR(p);
                if (*(int *)(p + 0x94) != 0) {
                    *(float *)(D_0063C494 + 0x130) =
                        (*(float *)(p + 0x24) - *(float *)(p + 0x4)) + -40.0f;
                    SetSimplePlane(D_0063C490 + 0x350, 0.0f, -1.0f, 0.0f, *(float *)(p + 0x24));
                    *(int *)(D_0063C490 + 0x144) = *(int *)(p + 0x94);
                }
            }
        }
    }
}

extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern float GetDistanceFromPlane(void *plane, void *pos);
extern void ClipWallR(void *a0);
extern void ClipFloorIH(void *a0);

void checkCliffState(int a0)
{
    char buf[0xC0];
    float mv[4];
    char *p;
    float k;

    memset(buf, 0, 0xC0);
    p = buf;
    k = (D_0063B93C == D_00639EA4) ? -20.0f : 0.0f;
    D_004ECA30[2] = k;
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(D_004ECA30);
    CopyVector(p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(p + 0x10), MatrixDrive_GetMatrix(), D_004ECA40);
    _ApplyMatrix(mv, MatrixDrive_GetMatrix(), ZUnitVector);
    MatrixDrive_PopMatrix();
    if (D_0063B8FC != 0) {
        DrawCollisionRay(p);
    }
    ClipWallR(p);
    if (*(int *)(p + 0x88) != 0) {
        float wv[4];
        float sc[4];
        float hit[4];
        char fp[0xC0];
        float plane[4];
        WallCfg pl;
        WallCfg t;
        float d;
        float dd;

        GetWallVector((int)wv, (int)p);
        sceVu0ScaleVector(sc, wv, 300.0f);
        AddVectorXYZ(p + 0x10, p, sc);
        ClipWallR(p);
        if (D_0063B8FC != 0) {
            DrawCollisionRay(p);
        }
        if (*(int *)(p + 0x88) != 0) {
            sceVu0ScaleVector(sc, wv, 10.0f);
            sceVu0AddVector(fp + 0x10, p + 0x20, sc);
            CopyVector(fp, fp + 0x10);
            pl = (t.o = ((WallCfg *)(p + 0x80))->o, t.n = ((WallCfg *)(p + 0x80))->n, t);
            GetPureVerticalPlane(plane, 0, 0, (int *)&pl, 0);
            d = GetDistanceFromPlane(plane, p + 0x20);
            *(float *)(fp + 4) += d - 10.0f;
            ClipFloor(fp);
            if (D_0063B8FC != 0) {
                DrawCollisionRay(fp);
            }
            CopyVector(hit, p + 0x20);
            if (*(int *)(fp + 0x94) == 0) {
                float dv[4];
                float nv[4];
                ClipBuf w2;
                float ip;

                CopyVector(dv, wv);
                sc[1] = 0.0f;
                _NormalizeVector(nv, dv);
                ip = _InnerProduct(nv, mv);
                *(float *)(D_0063C494 + 0x114) = GetPointDistance(p + 0x20, p) + k * ip;
                *(int *)(D_0063C494 + 0xFC) = 1;
                /* The wall-hit word is copied as the pointer it is (checkWallState
                   reads it the same way): its load issues ahead of the int store
                   above it, as in the ROM. */
                *(void **)(D_0063C490 + 0xF8) = *(void **)(p + 0x88);
                *(WallObj *)(D_0063C490 + 0xF0) = *(WallObj *)(p + 0x80);
                *(int *)(D_0063C490 + 0xFC) = -1;
                w2 = *(ClipBuf *)p;
                d = GetPointDistance(p + 0x20, p);
                _ScaleVector(sc, wv, d + 10.0f);
                _AddVectorXYZ((int)((char *)&w2 + 0x10), (int)&w2, sc);
                *(float *)((char *)&w2 + 4) = *(float *)((char *)&w2 + 4) - 30.0f;
                *(float *)((char *)&w2 + 0x14) = *(float *)((char *)&w2 + 0x14) - 30.0f;
                ClipWall(&w2);
                if (D_0063B8FC != 0) {
                    DrawCollisionRay(&w2);
                }
                if (*(int *)((char *)&w2 + 0x88) == 0) {
                    *(int *)(D_0063C494 + 0xF8) = 1;
                    *(int *)(D_0063C494 + 0x14) |= 0x10;
                }
            }
            *(int *)(D_0063C494 + 0x180) = *(int *)(D_0063C494 + 0x184) = GetWallAttribute(p);
            GetOrientOfWall(D_0063C494 + 0x120, *(void **)(p + 0x88), p + 0x80);
            if (*(float *)(D_0063C494 + 0x114) < 30.0f) {
                sceVu0ScaleVector(sc, wv, 10.0f);
                SubVectorXYZ(p, hit, sc);
                sceVu0ScaleVector(sc, wv, 300.0f);
                AddVectorXYZ(p + 0x10, p, sc);
                ClipWall(p);
                if (D_0063B8FC != 0) {
                    DrawCollisionRay(p);
                }
                if (*(int *)(p + 0x88) != 0) {
                    dd = distance_squared(p + 0x20, p);
                    *(int *)(D_0063C494 + 0x100) = 1;
                    d = FSqrt(dd);
                    if (a0 == 0) {
                        if (d < *(float *)(D_0063C494 + 0x138)) {
                            *(float *)(D_0063C494 + 0x138) = d;
                        }
                    } else {
                        *(float *)(D_0063C494 + 0x138) = d;
                    }
                    sceVu0ScaleVector(sc, wv, 10.0f);
                    AddVectorXYZ(p, p + 0x20, sc);
                    CopyVector(p + 0x10, p);
                    *(float *)(p + 0x14) = *(float *)(p + 0x14) - 10000.0f;
                    ClipFloorR(p);
                    if (D_0063B8FC != 0) {
                        DrawCollisionRay(p);
                    }
                    if (*(int *)(p + 0x94) != 0) {
                        *(float *)(D_0063C494 + 0x130) =
                            (*(float *)(p + 0x24) - *(float *)(p + 4)) + 10.0f;
                    }
                }
            }
            sceVu0ScaleVector(sc, wv, 10.0f);
            AddVectorXYZ(p, hit, sc);
            CopyVector(p + 0x10, p);
            *(float *)(p + 0x14) = *(float *)(p + 0x14) + 10000.0f;
            ClipFloorIH(p);
            if (D_0063B8FC != 0) {
                DrawCollisionRay(p);
            }
            if (*(int *)(p + 0x94) != 0) {
                *(float *)(D_0063C494 + 0x110) = (*(float *)(p + 0x24) - *(float *)(p + 4)) + 10.0f;
            }
        }
    }
}

void _checkCliffAndWall(void)
{
    float v[4];
    float d;
    float t;

    if (*(int *)(D_0063C494 + 0xDC) == 1 ||
        (*(int *)(D_0063C494 + 0xDC) == 2 && *(int *)(D_0063C494 + 0xE8) == 0)) {
        MatrixDrive_PushMatrix();
        checkCliffState(1);
        MatrixDrive_PopMatrix();
    }
    if (*(int *)(D_0063C494 + 0xDC) == 1 ||
        (*(int *)(D_0063C494 + 0xDC) == 2 && *(int *)(D_0063C494 + 0xE8) == 1)) {
        MatrixDrive_PushMatrix();
        checkWallState(3);
        MatrixDrive_PopMatrix();
    }
    if (*(int *)(D_0063C494 + 0xDC) == 1) {
        if ((*(int *)(D_0063C494 + 0x14) & 0x20) == 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, -30.0f, 0.0f);
            checkWallState(3);
            MatrixDrive_PopMatrix();

            if ((*(int *)(D_0063C494 + 0x14) & 0x20) != 0) {
                *(float *)(D_0063C494 + 0x130) += 30.0f;
                *(float *)(D_0063C494 + 0x134) += 30.0f;
            }
        }
        if (D_0063B93C == D_00639EA4 && *(int *)((int)GOBJ_SUB(D_0063B93C) + 0x568) == 0) {
            _SubVectorXYZ(v, D_0063C490, D_0063C490 + 0x150);
            v[1] = 0.0f;
            d = VectorLengthSquare(v);
            if (0.01f < d) {
                MatrixDrive_PushMatrix();
                UnitRotation(MatrixDrive_GetMatrix());
                _ScaleVectorXYZ(v, v, 1.0f / _Sqrt(d));
                *(float *)(MatrixDrive_GetMatrix() + 0x00) =
                    *(float *)(MatrixDrive_GetMatrix() + 0x28) = v[2];
                *(float *)(MatrixDrive_GetMatrix() + 0x08) = -v[0];
                *(float *)(MatrixDrive_GetMatrix() + 0x20) =
                    -*(float *)(MatrixDrive_GetMatrix() + 0x08);
                checkCliffState(0);
                MatrixDrive_PopMatrix();
            }
        }
        if (*(int *)(D_0063C494 + 0xF4) != 0 && *(int *)(D_0063C494 + 0xF8) != 0) {
            t = *(float *)(D_0063C494 + 0x138) - *(float *)(D_0063C494 + 0x114);
            if ((t < 0.0f ? -t : t) < 10.0f) {
                *(unsigned int *)(D_0063C494 + 0x14) &= ~0x10;
                *(int *)(D_0063C494 + 0x104) = 0;
                *(int *)(D_0063C494 + 0xF8) = 0;
                *(int *)(D_0063C494 + 0xFC) = 0;
                *(int *)(D_0063C494 + 0x100) = 0;
                *(float *)(D_0063C494 + 0x114) = *(float *)(D_0063C494 + 0x110) = D_0063B924[0].f;
            }
        }
    }
    if (D_0063B8FC != 0) {
        if (*(int *)(D_0063C494 + 0xF4) != 0) {
            DrawGObjWallCollision(*(int *)(D_0063C490 + 0xE0), 0);
        }
    }
    if (*(int *)((int)GOBJ_SUB(D_0063B93C) + 0x564) != 0 && GOBJ_SUB(D_0063B93C)->f_188 == 0) {
        debug_assertMessage(D_0061FDC0, 822, D_0061FDD8);
        __assert(D_0061FDC0, 822, D_0063B920);
    }
}

void checkCliffAndWallStateOfLastPlane(void)
{
    _UnitMatrix(MatrixDrive_GetMatrix());
    {
        register float *p = (float *)D_0063C490;
        float r = GetYProjectionOfPlane((int)(D_0063C490 + 0x130), (int)D_0063C490);
        MatrixDrive_TransMatrix(p[0], r, *(float *)(D_0063C490 + 8));
    }
    MultiMatrixByQuaternion((char *)D_0063C490 + 0x30);
    MatrixDrive_PushMatrix();
    _checkCliffAndWall();
    MatrixDrive_PopMatrix();
    if (*(int *)(D_0063C494 + 0xE4) != 0) {
        MatrixDrive_PushMatrix();
        checkWallSideState();
        MatrixDrive_PopMatrix();
    }
}

void checkCliffAndWallStateAtJump(void)
{
    _UnitMatrix(MatrixDrive_GetMatrix());
    {
        register float *p = (float *)D_0063C490;
        MatrixDrive_TransMatrix(p[0], p[1] + p[116] + 10.0f, p[2]);
    }
    MultiMatrixByQuaternion((char *)D_0063C490 + 0x30);
    _checkCliffAndWall();
}

void dispActNode(int id)
{
    if (id == -1) {
        return;
    }
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    CopyVector((void *)(MatrixDrive_GetMatrix() + 0x30),
               (void *)(*(char **)((char *)GOBJ_SUB(D_0063B93C) + 0xC) + id * 0x40 + 0x30));
    MatrixDrive_ScaleMatrix(5.0f, 5.0f, 5.0f);
    dispSquare(0xFF);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

void dispLastNode(void)
{
    float *p;
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    p = (float *)D_0063C490;
    MatrixDrive_TransMatrix(p[0x6C], p[0x6D], p[0x6E]);
    MatrixDrive_ScaleMatrix(8.0f, 8.0f, 8.0f);
    dispSquare2(0xFF);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

#include "motMan_rootUpdate.c.inc"

static inline void calcMaxNodeHeight(int n)
{
    int i;
    *(float *)(D_0063C490 + 0x1D0) = 0.0f;
    for (i = 0; i < n; i++) {
        if (*(float *)(D_0063C490 + 0x1D0) < *(float *)(D_0063C488 + i * 0x10 + 4)) {
            *(float *)(D_0063C490 + 0x1D0) = *(float *)(D_0063C488 + i * 0x10 + 4);
        }
    }
}

void _getGeometryOfMotion(MotShift *out, int second)
{
    float v[4];
    char q[0x10];
    int save180 = *(int *)(D_0063C490 + 0x180);

    MatrixDrive_PushMatrix();
    PushQuaternion();
    CopyVector((void *)v, (void *)(D_0063C494 + 0xB0));
    SetIdentityQuaternion(q);
    sceVu0Normalize((void *)v, (void *)v);
    RotQuaternionY(q, atan2f(v[0], v[2]) * 10430.378f);
    CopyQuaternion((char *)D_0063C490 + 0x30, q);
    GetMatrixFromQuaternion((void *)MatrixDrive_GetMatrix(), (char *)D_0063C490 + 0x30);
    SetCurrentQuaternion((char *)D_0063C490 + 0x30);

    D_0063C4A4 = D_0063C478;
    D_0063C4A0 = D_0063C484;
    pursueNaturalGeometry(0);

    if (second) {
        D_0063C4A4 = D_0063C47C;
        D_0063C4A0 = D_0063C488;
        pursueNaturalGeometry(0);
    } else {
        int i;
        for (i = 0; i < D_0063C48C; i++) {
            CopyVector((void *)(D_0063C488 + i * 0x10), (void *)(D_0063C484 + i * 0x10));
        }
    }
    calcMaxNodeHeight(D_0063C48C);

    clearCollisionStatus();
    {
        char *fp = (char *)D_0063C490;
        *(int *)(fp + 0x204) = 0;
        *(int *)(fp + 0x208) = 0;
        *(int *)(fp + 0x20C) = 0;
        CopyVector(fp + 0x60, fp);
    }

    if (*(int *)D_0063C494 != -1) {
        *out = rootUpdateDirectPlayForStream();
    } else {
        char *pm;
        MatrixDrive_PushMatrix();
        pm = (char *)D_0063C494;
        switch (*(int *)(pm + 0x68)) {
        default: {
            char buf[0x400];
            sprintf(buf, D_0061FFD8, D_0063C4A8 + 0xC0, *(int *)(pm + 0x30), *(int *)(pm + 0x68));
            debug_assertMessage(D_0061FDC0, 997, buf);
            __assert(D_0061FDC0, 997, D_0063B920);
        } break;
        case 1:
        case 20:
            *out = rootUpdateXZ(*(int *)(pm + 0x68), findActPoint(D_004ECB10));
            break;
        case 2:
        case 17:
            *out = rootUpdateXZ_MotPos(*(int *)(pm + 0x68), findActPoint(D_004ECB10));
            break;
        case 7:
        case 8:
        case 9:
        case 13:
        case 16:
            *out = rootUpdateStepSolution(*(int *)(pm + 0x68));
            break;
        case 10:
        case 15:
            *out = rootUpdateHang(*(int *)(pm + 0x68), checkActPointWithHeight(6, 10.0f),
                                  checkActPointWithHeight(0x16, 10.0f));
            break;
        case 11:
            *out = rootUpdateSwim();
            break;
        case 5:
            *out = rootUpdateNodeFix();
            break;
        case 4:
            rootUpdateY_Rope(findActPoint(D_004ECB28));
            break;
        case 3:
            *out = rootUpdateY();
            break;
        case 0:
        case 19:
            *out = rootUpdateTrueMotion(*(int *)(pm + 0x68));
            break;
        case 6:
        case 14:
            *out = rootUpdateDirectPlay(*(int *)(pm + 0x68));
            break;
        case 12:
            *out = rootUpdateFly();
            break;
        case 18:
            *out = rootUpdateEnemyFly();
            break;
        }
        MatrixDrive_PopMatrix();
    }

    *(float *)(D_0063C494 + 0xF0) =
        *(float *)(D_0063C490 + 4) + *(float *)(D_0063B938 + 0x14) - *(float *)(D_0063C490 + 0x1B4);

    MatrixDrive_PushMatrix();
    MatrixDrive_SetTransposeMatrix((void *)MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix((int *)(D_0063C490 + 0x170), MatrixDrive_GetMatrix(),
                      (char *)D_0063C490 + 0x90);
    MatrixDrive_PopMatrix();

    MatrixDrive_PopMatrix();
    PopQuaternion();

    if (*(int *)(D_0063C490 + 0x180) != -1 && save180 == -1) {
        *(int *)(D_0063C494 + 0x1CC) = 1;
    }
}

inline void getGeometryOfMotion(MotShift *out, int second)
{
    ShiftBlk buf;
    char *p;
    buf = *(ShiftBlk *)(*(char **)((char *)D_0063B93C + 0x15C) + 0x180);
    _getGeometryOfMotion(out, second);
    p = *(char **)((char *)D_0063B93C + 0x15C);
    if (*(int *)(p + 0x634) != 0) {
        *(ShiftBlk *)(p + 0x180) = buf;
    }
}

void execPositionReserver(char *self, MotShift m)
{
    int ext;
    float buf[4];
    float buf2[4];
    int flg;

    ext = (int)GOBJ_SUB(self);
    if (*(int *)(ext + 0x4F0) == 1) {
        if (*(int *)(ext + 0x4EC) == 0 || *(int *)(ext + 0x4EC) != *(int *)(ext + 0x4F0)) {
            if (m.a != 0) {
                if (!(*(int *)(D_0063C494 + 0x1BC) != 0 &&
                      (*(int *)(D_0063C494 + 0x188) & 0xF00000)) &&
                    !(*(long long *)(D_0063C494 + 0x10) & ((long long)0x8008 << 30))) {
                    *(int *)(ext + 0x4EC) = *(int *)(ext + 0x4F0);
                    CopyVector(D_0063C490 + 0x70, D_0063C490);
                    *(MotShift *)(D_0063C490 + 0x80) = m;
                    *(int *)(D_0063C494 + 0x84) = 0;
                }
            }
        } else {
            *(int *)(D_0063C494 + 0x84) = 2;
            CopyVector(D_0063C490, D_0063C490 + 0x70);
        }
    }
    *(int *)(D_0063C494 + 0x88) = 1;
    if (GOBJ_SUB(self)->f_4EC == 1) {
        if (m.a != 0) {
            CopyVector(buf, D_0063C490 + 0x70);
            _ApplyMatrix(buf, (int)(*(char **)(*(char **)(m.a + 0x15C) + 0xC) + m.b * 0x40),
                         (char *)buf);
            if (distance_squared(buf, D_0063C490 + 0x1C0) == 0.0f) {
                *(int *)(D_0063C494 + 0x88) = 0;
            }
            buf[3] = 1.0f;
            CopyVector(D_0063C490 + 0x1C0, buf);
        }
        flg = *(int *)(D_0063C494 + 0x14);
        if ((flg & 0x2000) || m.a != *(int *)(D_0063C490 + 0x80) ||
            m.b != *(int *)(D_0063C490 + 0x84) ||
            (*(int *)(D_0063C494 + 0x1BC) != 0 && (*(int *)(D_0063C494 + 0x188) & 0xF00000)) ||
            (flg & 2)) {
            GOBJ_SUB(self)->f_4EC = 0;
        } else if (*(int *)(D_0063C494 + 0x84) != 0) {
            _InterVectorXYZ(D_0063C490, D_0063C490 + 0x70, D_0063C490,
                            1.0f - (float)*(int *)(D_0063C494 + 0x84) * 0.5f);
            *(int *)(D_0063C494 + 0x84) -= 1;
        }
    }
    if (D_0063B148 != 0) {
        if (D_0063B93C == D_00639EA4) {
            CopyVector(buf2, D_0063C490 + 0x70);
            _UnitMatrix(MatrixDrive_GetMatrix());
            if (m.a != 0) {
                _ApplyMatrix(buf2, (int)(*(char **)(*(char **)(m.a + 0x15C) + 0xC) + m.b * 0x40),
                             (char *)buf2);
                MatrixDrive_TransMatrixV(buf2);
                gif_StartPacketPri(0xB);
                if (GOBJ_SUB(self)->f_4EC == 1) {
                    prim_DispWireSphere(50.0f, D_004ECB50, 0x10, 8);
                } else {
                    prim_DispWireSphere(50.0f, D_004ECB60, 0x10, 8);
                }
                gif_EndPacket();
            }
        }
    }
}

extern void UnlinkParentOfDObj(void *a0);
extern void LinkParentOfDObj(void *a0, MotShift *a1);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void dispPlane(void *plane, void *pos);
extern void gif_SetZTest(int a0);
extern char D_0055FE58[];
extern MotShift D_0063A810;
extern int D_0063B150;
void GetMatrixOfMotion(char *self, char *tbl, void *ofs);

typedef enum { MOTIONNO_0 = 0 } MotionNo;

typedef struct MotNodeTag MotNode;

typedef struct MotHdrTag MotHdr;

/* RECONSTRUCTION, the type and macro names are ours (motionOrientManager.c
   spells the same work-pointer read this way): the object's work pointer at
   0x15C is read through a union member, so the read has alias set 0 and every
   float store through it orders against it, while a store to a work field
   leaves the loads of the D_ pointer globals alone. */
typedef union MotWorkRef {
    char *p;
    int i;
} MotWorkRef;

#define MOWORK(self) (((MotWorkRef *)((char *)(self) + 0x15C))->p)

void GetGeometryOfMotion(void *self, void *m0, void *m1, float *v, float r, char *tbl, int k)
{
    MotShift sh;
    float v2[4];

    sh = *(MotShift *)MOWORK(self);
    D_0063C49C = k;
    if (*(char **)(MOWORK(self) + 0x800) != 0) {
        *(float *)(MOWORK(self) + 0x7EC) = 1.0f;
        CopyVector(v2, MOWORK(self) + 0x7E0);
        sceVu0ApplyMatrix((int *)v2,
                          *(int *)(*(int *)(*(char **)(MOWORK(self) + 0x800) + 0x15C) + 0xC) +
                              *(int *)(MOWORK(self) + 0x804) * 0x40,
                          (char *)v2);
    } else {
        AddVectorXYZ(MOWORK(self) + 0x7E0, MOWORK(self) + 0x7E0, MOWORK(self) + 0x7F0);
        CopyVector(v2, MOWORK(self) + 0x7E0);
    }
    v2[1] = v2[1] + *(float *)(MOWORK(self) + 0x808);
    v2[3] = 1.0f;
    UnlinkParentOfDObj(self);

    D_0063C48C = *(int *)(MOWORK(self) + 0x88);
    {
        float wk0[D_0063C48C][4], wk1[D_0063C48C][4];

        D_0063B93C = (int)self;
        D_0063C484 = (char *)wk0;
        D_0063C488 = (char *)wk1;
        D_0063C478 = m0;
        D_0063C47C = m1;
        D_0063B900 = *(float *)((char *)*(MotHdr **)(MOWORK(self) + 0x870) + 0x20);
        D_0063C490 = MOWORK(self) + 0xA0;
        D_0063C494 = MOWORK(self) + 0x470;
        D_0063B938 = (char *)*(MotNode **)(MOWORK(self) + 0x8C);
        D_0063C4A8 = D_0055FE58 + *(MotionNo *)(D_0063C494 + 0x30) * 404;
        CopyVector(D_007201F0, v);
        CopyVector(D_00720200, tbl);
        *(int *)(D_0063C494 + 0x14) = 0;
        sceVu0SubVector(D_00720210, D_0063C490 + 0x150, D_0063C490 + 0x160);
        if (*(int *)(MOWORK(self) + 0x638) != 0) {
            MotShift tmp;
            getGeometryOfMotion(&tmp, r != 1.0f);
        } else {
            getGeometryOfMotion(&sh, r != 1.0f);
        }
        CopyVector(D_0063C490 + 0x160, D_0063C490 + 0x150);
        if (*(int *)(MOWORK(self) + 0x4E8) == 1) {
            sh = D_0063A810;
        }
        AddVectorXYZ(MOWORK(self) + 0x7C0, D_0063C490, D_0063C490 + 0x10);
        *(float *)(MOWORK(self) + 0x7CC) = 1.0f;
        *(float *)(MOWORK(self) + 0x7C4) =
            *(float *)(MOWORK(self) + 0x7C4) * r + v2[1] * (1.0f - r);
        GetMatrixOfMotion(self, m1, MOWORK(self) + 0x7C0);
    }
    if (D_0063B150 != 0) {
        gif_StartPacketPri(0xB);
        gif_SetAlpha(1, 5, 0x80);
        gif_SetZTest(0);
        gif_EndPacket();
        dispPlane(MOWORK(self) + 0x1D0, MOWORK(self) + 0xA0);
        gif_StartPacketPri(0xB);
        gif_SetZTest(1);
        gif_EndPacket();
    }
    *(float *)(D_0063C490 + 0x15C) = 1.0f;
    *(float *)(D_0063C490 + 0x16C) = 1.0f;
    *(float *)(D_0063C490 + 0xC) = 1.0f;
    *(float *)(D_0063C490 + 0x9C) = 0.0f;
    if (sh.a != 0) {
        LinkParentOfDObj(self, &sh);
        if (*(int *)(*(int *)(sh.a + 0x15C) + 0x81C) != 0) {
            (*(void (**)(MotShift *, char *))(*(int *)(sh.a + 0x15C) + 0x81C))(&sh, self);
        }
    } else {
        *(float *)(MOWORK(self) + 0xA4) =
            *(float *)(MOWORK(self) + 0xA4) - *(float *)(MOWORK(self) + 0x160);
        *(float *)(MOWORK(self) + 0x1F4) =
            *(float *)(MOWORK(self) + 0x1F4) - *(float *)(MOWORK(self) + 0x160);
    }
    *(float *)(MOWORK(self) + 0x7C4) =
        *(float *)(MOWORK(self) + 0x7C4) - *(float *)(D_0063C490 + 0xC0);
    if (sh.a != 0) {
        float m[0x10];
        MatrixDrive_SetTransposeMatrix((void *)m,
                                       *(int *)(*(int *)(sh.a + 0x15C) + 0xC) + sh.b * 0x40);
        sceVu0ApplyMatrix((int *)(MOWORK(self) + 0x7C0), (int)m, MOWORK(self) + 0x7C0);
    }
    execPositionReserver(self, sh);
}

/* GObj+8 is the index into D_002C2DC8, the 0x4C-byte GenGeo table (ebrain.c
   types that array `GenGeo D_002C2DC8[]`; enemy_act.c indexes it with the same
   `obj[2]` field).  ROM proves the field is NOT read in the `int` alias set:
   the load is issued ABOVE the line-1484 `int` store to D_0063C48C, which an
   int-typed read cannot cross.  An enumerated kind is the type that both fits
   the data model and reproduces the hoist. */
typedef enum { GENGEO_KIND_0 = 0 } GenGeoKind;

void GetMatrixOfMotion(char *self, char *tbl, void *ofs)
{
    float v[4];
    float w[4];
    float p1[4];
    float p2[4];
    int i;

    /* The sub-object fields are read as `int` addresses (not `char **`): as
       pointer-typed reads they share the alias set of the five pointer globals
       stored just below, and gcc can no longer issue every load ahead of the
       nine gp stores the way ROM does. */
    D_0063C478 = tbl;
    D_0063C480 = (char *)GOBJ_SUB(self)->f_10;
    D_0063B938 = (char *)*(int *)((int)GOBJ_SUB(self) + 0x8C);
    D_0063B900 = *(float *)(*(int *)((int)GOBJ_SUB(self) + 0x870) + 0x20);
    D_0063C490 = (char *)((int)GOBJ_SUB(self) + 0xA0);
    D_0063C494 = (char *)((int)GOBJ_SUB(self) + 0x470);
    D_0063C48C = GOBJ_SUB(self)->f_88;
    D_0063C498 = D_002C2DC8[*(GenGeoKind *)(self + 8) * 0x4C + 0x46];
    D_0063B93C = (int)self;
    MatrixDrive_PushMatrix();
    PushQuaternion();

    GetMatrixFromQuaternion((void *)MatrixDrive_GetMatrix(), D_0063C490 + 0x30);
    SetCurrentQuaternion(D_0063C490 + 0x30);

    MatrixDrive_PushMatrix();

    D_004ECB70[1] = *(float *)(D_0063C490 + 0xC0);
    MatrixDrive_RotMatrixZ(*(short *)(D_0063C490 + 0x50));

    sceVu0ApplyMatrix((int *)v, MatrixDrive_GetMatrix(), (char *)D_004ECB70);

    v[1] -= *(float *)(D_0063C490 + 0xC0);
    v[0] *= 0.5f;
    v[2] *= 0.5f;
    MatrixDrive_PopMatrix();

    if (*(int *)(D_0063C494 + 0xE0) != 0) {
        getFinalMatrix(0);
    } else {
        getFinalMatrixWithNaturalGeometry(0);
    }

    D_004ECB80[0] = D_004ECB80[5] = D_004ECB80[10] = D_0063B900;

    AddVectorXYZ(w, ofs, v);
    for (i = 0; i < D_0063C48C; i++) {
        char *nd = *(char **)((char *)GOBJ_SUB(D_0063B93C) + 0xC) + i * 0x40;
        char *pos = nd + 0x30;
        sceVu0MulMatrix((int)nd, (int)nd, (int)D_004ECB80);
        AddVectorXYZ(pos, pos, w);
    }
    MatrixDrive_PopMatrix();
    PopQuaternion();

    if (D_0063B158 != 0) {
        dispActNode(*(int *)(D_0063C490 + 0x180));
        dispLastNode();
    }
    if (D_0063B148 != 0) {
        int n;

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        gif_StartPacketPri(0xB);
        n = GetSkeltonFocusNode(self, 0x23);
        CopyVector(w, *(char **)((char *)GOBJ_SUB(D_0063B93C) + 0xC) + n * 0x40 + 0x30);
        CopyVector(p1, D_0063C490 + 0x2F0);
        _SubVector(p2, p1, w);
        _NormalizeVector(p2, p2);
        _ScaleVector(p2, p2, 100.0f);
        _AddVector(p1, w, p2);
        gif_SetAlpha(1, 5, 0x80);
        if (*(int *)(D_0063C490 + 0x318) != 0 && *(int *)(D_0063C490 + 0x2E0) != 0) {
            DrawLineG(w, D_004ECBC0, p1, D_004ECBC0, -1);
        } else {
            DrawLineG(w, D_004ECBD0, p1, D_004ECBD0, -1);
        }
        gif_EndPacket();
    }
}

/* census file static (def line 1592); ico2/sugipon/src/motionManager2 holds the
   other static of that name. */
static void dispSkeltonHierarchy(int node)
{
    if (*(int *)(D_0063B938 + node * 64 + 0x38) != -1) {
        float o[3] = {0.0f, 0.0f, 0.0f};
        float p[3] = {*(float *)(D_0063B938 + node * 64 + 0x10),
                      *(float *)(D_0063B938 + node * 64 + 0x14),
                      *(float *)(D_0063B938 + node * 64 + 0x18)};
        float ax[3] = {0.0f, 5.0f, 0.0f};
        float ay[3] = {0.0f, 0.0f, 5.0f};
        float az[3] = {5.0f, 0.0f, 0.0f};
        sceVu0IVECTOR c0 = {0x40, 0x40, 0x40, 0x80};
        sceVu0IVECTOR c1 = {0x00, 0xFF, 0x00, 0x80};
        sceVu0IVECTOR c2 = {0x00, 0x80, 0xFF, 0x80};
        sceVu0IVECTOR c3 = {0xFF, 0x00, 0x00, 0x80};

        DrawLineG(o, c0, p, c0, -1);
        DrawLineG(o, c0, ax, c1, -1);
        DrawLineG(o, c0, ay, c2, -1);
        DrawLineG(o, c0, az, c3, -1);
    }
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(),
               *(char **)(*(char **)(D_0063B93C + 0x15C) + 0xC) + node * 64);
    if (*(int *)(D_0063B938 + node * 64 + 0x30) == -1) {
        float o2[3] = {0.0f, 0.0f, 0.0f};
        float e[3] = {10.0f, 0.0f, 0.0f};
        sceVu0IVECTOR c = {0xFF, 0xFF, 0xFF, 0x80};

        DrawLineG(o2, c, e, c, -1);
    }
    if (*(int *)(D_0063B938 + node * 64 + 0x30) != -1) {
        dispSkeltonHierarchy(*(int *)(D_0063B938 + node * 64 + 0x30));
    }
    MatrixDrive_PopMatrix();
    if (*(int *)(D_0063B938 + node * 64 + 0x34) != -1) {
        dispSkeltonHierarchy(*(int *)(D_0063B938 + node * 64 + 0x34));
    }
}

/* census sugipon/src/motionManager.c getInitialMatrix, def line 1625 (1625-1647),
   a file static: MAIN.MAP carries no global of that name, so the twin in
   ico2/sugipon/src/geometryManager is a static too and `static` here keeps this
   one's ELF symbol local.  No INCLUDE_ASM sibling in this TU calls it. */
/* kept local: this TU's uses of MatrixDrive_RotMatrixY do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_RotMatrixY(int a0);
extern unsigned char D_0028F8F0[];

static void getInitialMatrix(int obj, int idx)
{
    char *nd;
    char *mtx;

    nd = *(char **)(obj + 0x8C) + idx * 0x40;
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(nd + 0x10);
    MultiMatrixByQuaternion(nd + 0x20);
    switch (*(int *)(nd + 4)) {
    case 19:
    case 20:
    case 22:
        MatrixDrive_RotMatrixY((short)((D_0028F8F0[0x54] - 0x80) << 7));
        MatrixDrive_RotMatrixZ((short)((D_0028F8F0[0x55] - 0x80) << 7));
        break;
    }
    mtx = *(char **)(obj + 0xC) + idx * 0x40;
    CopyMatrix(mtx, (void *)MatrixDrive_GetMatrix());
    if (*(int *)(nd + 0x30) != -1) {
        getInitialMatrix(obj, *(int *)(nd + 0x30));
    }
    MatrixDrive_PopMatrix();
    if (*(int *)(nd + 0x34) != -1) {
        getInitialMatrix(obj, *(int *)(nd + 0x34));
    }
}

/* K&R definition: it declares no prototype, which is what lets SkelTest and
 * SkelTestGeo below call this function with one argument, as ROM does. */
void dispSkelton()
{
    int v;
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix(v);
    dispSkeltonHierarchy(0);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

void SkelTest(char *a0)
{
    int sub = (int)GOBJ_SUB(a0);
    int v;
    D_0063B93C = (int)a0;
    v = *(int *)(sub + 0x8C);
    D_0063B938 = (char *)v;
    if (v != 0) {
        p2o_DispVU1();
        if (D_0063B148 != 0) {
            dispSkelton(a0);
        }
    }
}

void SkelTestGeo(char *a0)
{
    int sub = (int)GOBJ_SUB(a0);
    int v;
    int i;
    D_0063B93C = (int)a0;
    v = *(int *)(sub + 0x8C);
    D_0063B938 = (char *)v;
    if (v != 0) {
        int s2;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_RotMatrixX(-0x8000);
        getInitialMatrix((int)GOBJ_SUB(a0), 0);
        s2 = (int)GOBJ_SUB(a0);
        for (i = 0; i < *(int *)(s2 + 0x88); i++) {
            int e = *(int *)(s2 + 0xC) + i * 0x40;
            sceVu0MulMatrix(e, s2 + 0x20, e);
            s2 = (int)GOBJ_SUB(a0);
        }
        if (D_0063B148 != 0) {
            dispSkelton(a0);
        }
    }
}

#include "typedef.h"
#include "sugiCommon.h"
#include "main.h"
#include "debug_exception.h"
#include "obj_manager.h"
#include "Primitive.h"
#include "lineManager.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "debug.h"
#include "pool.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "tableSin.h"
#include "Matrix.h"
#include "gv.h"

typedef struct {
    char b[0x20];
} ShiftBlk;

/* .sbss, owned by motionManager.o (0x38, the run and MAIN.MAP's own size; MAIN.MAP
   names no symbol in it, so all fourteen words are file statics), in the ROM's run
   order. */
static float ikSlerpRate; /* derived name */

static char *skelMotion; /* derived name */

static char *skelMotion2; /* derived name */

static char *skelQuat; /* derived name */

static char *nodePos; /* derived name */

static char *nodePos2; /* derived name */

static int skelNodeNum; /* derived name */

static char *skelRoot; /* derived name */

static char *skelMotCtrl; /* derived name */

static int skelGeoType; /* derived name */

static int stepFocusNode; /* derived name */

static char *naturalNodePos; /* derived name */

static char *naturalMotion; /* derived name */

static char *skelMotDef; /* derived name */

/* .data, owned by motionManager.o (VMA 0x4EC950..0x4ECBE0), in the ROM's run
   order, which is the source order of each object's first user. MAIN.MAP names
   none of them. */
static float squareP0[4] = {-3.0f, 0.0f, -3.0f, 0.0f}; /* derived name */

static float squareP1[4] = {3.0f, 0.0f, 3.0f, 0.0f}; /* derived name */

static float squareP2[4] = {-3.0f, 0.0f, 3.0f, 0.0f}; /* derived name */

static float squareP3[4] = {3.0f, 0.0f, -3.0f, 0.0f}; /* derived name */

static sceVu0IVECTOR square2Color = {0xFF, 0x80, 0x00, 0x80}; /* derived name */

static float square2P0[4] = {-4.0f, 0.0f, -4.0f, 0.0f}; /* derived name */

static float square2P1[4] = {4.0f, 0.0f, 4.0f, 0.0f}; /* derived name */

static float square2P2[4] = {-4.0f, 0.0f, 4.0f, 0.0f}; /* derived name */

static float square2P3[4] = {4.0f, 0.0f, -4.0f, 0.0f}; /* derived name */

static float twistQuat[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float twistQuatLow[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float twistQuatHigh[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float wallCheckBase[4] = {0.0f, -40.0f, 0.0f, 1.0f}; /* derived name */

static float wallCheckAhead[4] = {0.0f, 0.0f, 300.0f, 1.0f}; /* derived name */

static float cliffCheckBase[4] = {0.0f, 10.0f, 0.0f, 1.0f}; /* derived name */

static float cliffCheckAhead[4] = {0.0f, 0.0f, 300.0f, 1.0f}; /* derived name */

static sceVu0IVECTOR wallHitColor = {0xFF, 0x80, 0x00, 0x80}; /* derived name */

static sceVu0IVECTOR wallHitColor2 = {0x00, 0x80, 0xFF, 0x80}; /* derived name */

static float floorSlope[4] = {0.0f, 0.0f, 0.0f, 0.0f}; /* derived name */

static float sideWallProbe[4] = {0.0f, 0.0f, 10.0f, 0.0f}; /* derived name */

static float hangBack[4] = {0.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static float hangFront[4] = {0.0f, 0.0f, 50.0f, 1.0f}; /* derived name */

static float hangLeft[4] = {-30.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float hangRight[4] = {30.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float clipWallBack[4] = {0.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static float clipWallFront[4] = {0.0f, 0.0f, 50.0f, 1.0f}; /* derived name */

static float avoidLeft[4] = {-40.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float avoidRight[4] = {40.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static int footActPoints[] = {51, 47, 52, 48, -1}; /* derived name */

static int ropeActPoints[] = {51, 47, 52, 48, 22, 6, 11, 27, -1}; /* derived name */

static sceVu0IVECTOR reserverColor = {0x40, 0x60, 0x80, 0x80}; /* derived name */

static sceVu0IVECTOR reserverColor2 = {0xFF, 0x60, 0x40, 0x80}; /* derived name */

static float rootHeightVec[4] = {0.0f, 1.0f, 0.0f, 0.0f}; /* derived name */

static float scaleMatrix[16] = {
    /* derived name */
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
};

static sceVu0IVECTOR dirColor = {0xFF, 0x60, 0x40, 0x80}; /* derived name */

static sceVu0IVECTOR dirColor2 = {0x00, 0x60, 0xFF, 0x80}; /* derived name */

/* .bss, owned by motionManager.o (0xA0 = MAIN.MAP's), in the ROM's run order;
   MAIN.MAP names none of them, so they are file statics. */
static float ikXAxis[4]; /* derived name */

static float ikBendQuat[4]; /* derived name */

static float naturalMatrix[16]; /* derived name */

static float naturalTrans[4]; /* derived name */

static float rootMove[4]; /* derived name */

static float rootStep[4]; /* derived name */

static float rootDelta[4]; /* derived name */

/* The skeleton the motion being computed belongs to: its node array and its
   object.  Declared here for the functions above; the definitions follow
   motMan_rootUpdate.c.inc, where the TU's .sdata has them, after that file's
   MotShift template. */
static char *skelNode; /* derived name */

static int skelGObj; /* derived name */

/* The TU's .sdata opens with the collision display switches
   SetHitCollisionDisplay sets (the second one draws the wall and cliff rays)
   and the skeleton's scale. */
static int hitColDisp = 0; /* derived name */

static int hitColRayDisp = 0; /* derived name */

/* a plain float (GetGeometryOfMotion and GetMatrixOfMotion write it):
 * _getFinalMatrix reloads it after calls; setIKAndAdjustRootHeight keeps it
 * across its stores to the geo block because those are structure members. */
static float skelScale = 1.0f; /* derived name */

/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipWall(void *a0);
/* kept local: void (int *, int, char *) here, void (void *, void *, void *) in libvu0.h */
extern void sceVu0ApplyMatrix(int *a0, int a1, char *a2);
/* kept local: float (int, int) here, float (float *, float *) in fieldCollision.h */
extern float GetYProjectionOfPlane(int a0, int a1);
/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipWallFuchiHangWalkStop(void *a0);
/* kept local: int (void *) here, int (int) in fieldCollision.h */
extern int GetWallAttribute(void *a0);
/* kept local: void (int) here, void (void *) in libvu0.h */
extern void sceVu0UnitMatrix(int);

typedef struct {
    int a;
    int b;
} MotShift;

/* kept local: agrees with libvu0.h, which this TU does not include (sceVu0ApplyMatrix, sceVu0MulMatrix differ) */
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
/* kept local: agrees with GifPacket.h; including it here moves this TU's bytes */
extern void gif_EndPacket();
/* kept local: agrees with GifPacket.h; including it here moves this TU's bytes */
extern void gif_SetAlpha();
/* kept local: agrees with GifPacket.h; including it here moves this TU's bytes */
extern void gif_StartPacketPri();
/* kept local: void (int, int) here, void (char *, int) in fieldCollision.h */
extern void DrawGObjWallCollision(int a0, int a1);
extern unsigned char objLayout[];

typedef struct {
    int obj;
    int node;
} ActPt;

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
   12-byte wall filter _wallCollisionPreProcess copies in (its FieldBlk12).
   The block is quadword aligned: the ROM's constant initialiser of one
   (checkWallSideState's, at 0x61FD00 in .rodata) sits on a 16-byte boundary
   after EditRotEmphasys's 8-aligned strings, the alignment of the points the
   block opens with. */
typedef struct {
    long long b[14]; /* 0x00 */
    float rad;       /* 0x70 */
    WallCfg filter;  /* 0x74 */
    long long c[8];  /* 0x80 */
} __attribute__((aligned(16))) ClipBuf;

/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipWallField(void *a0);
/* kept local: void (void *) here, void (char *) in fieldCollision.h */
extern void DrawCollisionRay(void *a0);
/* kept local: agrees with libvu0.h, which this TU does not include (sceVu0ApplyMatrix, sceVu0MulMatrix differ) */
extern float sceVu0InnerProduct(void *a, void *b);
/* kept local: DisplayP2O.h does not compile in this TU (too few arguments to function `p2o_DispVU1') */
extern void p2o_DispVU1();
static void getInitialMatrix(int a0, int a1);
/* kept local: void (int, int, int) here, void (void *, void *, void *) in libvu0.h */
extern void sceVu0MulMatrix(int a0, int a1, int a2);
/* kept local: void () here, void (void *) in fieldCollision.h */
extern void ClipFloor();

#include "motionManager.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

static inline void dispSquare(int alpha)
{
    int col[4] = {0, 128 * alpha / 255, alpha, 128};
    DrawLineG(squareP0, col, squareP2, col, -1);
    DrawLineG(squareP2, col, squareP1, col, -1);
    DrawLineG(squareP1, col, squareP3, col, -1);
    DrawLineG(squareP3, col, squareP0, col, -1);
}

void dispSquare2(int alpha)
{
    DrawLineG(square2P0, square2Color, square2P2, square2Color, -1);
    DrawLineG(square2P2, square2Color, square2P1, square2Color, -1);
    DrawLineG(square2P1, square2Color, square2P3, square2Color, -1);
    DrawLineG(square2P3, square2Color, square2P0, square2Color, -1);
}

#include "motMan_getFinalMatrix.c.inc"

inline void SetHitCollisionDisplay(int a, int b)
{
    hitColDisp = a;
    hitColRayDisp = b;
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

    if (*(int *)(skelRoot + 0x308) != 0) {
        return -1;
    }
    for (i = 0; i < skelNodeNum; i++) {
        int order = findActPointOrder(list, *(int *)(skelNode + i * 0x40 + 4));
        int v;
        if (order == 0) {
            continue;
        }
        if (*(int *)(skelRoot + 0x230) != 0) {
            int k = *(int *)(skelNode + i * 0x40 + 4);
            if (k == 6 || k == 11) {
                continue;
            }
        }
        if (*(int *)(skelRoot + 0x290) != 0) {
            int k = *(int *)(skelNode + i * 0x40 + 4);
            if (k == 22 || k == 27) {
                continue;
            }
        }
        v = *(int *)(skelMotion + i * 0x20);
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

    if (*(int *)(skelRoot + 0x230) != 0) {
        if (kind == 6 || kind == 11) {
            return -1;
        }
    }
    if (*(int *)(skelRoot + 0x290) != 0) {
        if (kind == 22 || kind == 27) {
            return -1;
        }
    }
    for (i = 0; i < skelNodeNum; i++) {
        if (*(int *)(skelNode + i * 0x40 + 4) == kind) {
            float d;
            if (*(int *)(skelMotion + i * 0x20) >= 249) {
                return -1;
            }
            d = *(float *)(nodePos + i * 0x10 + 4) + rootMove[1];
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
    *(unsigned int *)(skelMotCtrl + 0x14) &= ~0x10;
    *(int *)(skelMotCtrl + 0x104) = 0;
    *(int *)(skelMotCtrl + 0xF8) = 0;
    *(int *)(skelMotCtrl + 0xFC) = 0;
    *(int *)(skelMotCtrl + 0x100) = 0;
    *(float *)(skelMotCtrl + 0x110) = 3.40282347e+38f;
    *(float *)(skelMotCtrl + 0x114) = 3.40282347e+38f;
}

void clearCollisionStatus(void)
{
    clearCliffStatus();

    *(unsigned int *)(skelMotCtrl + 0x14) &= ~0x20;
    *(int *)(skelMotCtrl + 0xF4) = 0;
    *(float *)(skelMotCtrl + 0x138) = 3.40282347e+38f;
    *(float *)(skelMotCtrl + 0x130) = 3.40282347e+38f;
    *(float *)(skelMotCtrl + 0x134) = 3.40282347e+38f;
    *(void **)(skelRoot + 0x144) = 0;

    *(int *)(skelMotCtrl + 0x10C) = 0;
    *(float *)(skelMotCtrl + 0x174) = 3.40282347e+38f;
    *(int *)(skelMotCtrl + 0x178) = 0;

    *(unsigned int *)(skelMotCtrl + 0x14) &= ~0x1000;
    *(int *)(skelMotCtrl + 0x108) = 0;
    *(float *)(skelMotCtrl + 0x170) = 3.40282347e+38f;

    *(int *)(skelMotCtrl + 0x1B8) = *(int *)(skelMotCtrl + 0x1B4);
    *(int *)(skelMotCtrl + 0x1B4) = 0;
    *(int *)(skelMotCtrl + 0x1D4) = 0;

    *(int *)(skelMotCtrl + 0x1CC) = 0;
}

void checkUpperWallState(void)
{
    char buf[0xC0];
    memset(buf, 0, 0xC0);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(wallCheckBase);
    CopyVector((void *)buf, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(buf + 0x10), MatrixDrive_GetMatrix(), wallCheckAhead);
    MatrixDrive_PopMatrix();
    ClipWall(buf);
    if (*(int *)(buf + 0x88) != 0) {
        float a;
        int *D;
        a = GetPointDistance(buf + 0x20, buf);
        D = (int *)skelMotCtrl;
        *(float *)((char *)D + 0x170) = a;
        *(int *)((char *)D + 0x108) = 1;
        *(int *)((char *)D + 0x14) = *(int *)((char *)D + 0x14) | 0x1000;
    }
}

void checkWallSideState(void)
{
    ClipBuf buf = {{0}, 50.0f};
    float v[4];
    char *p = (char *)&buf;

    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(wallCheckBase);
    CopyVector((void *)p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(p + 0x10), MatrixDrive_GetMatrix(), wallCheckAhead);
    MatrixDrive_PopMatrix();

    if (*(int *)(skelRoot + 0x320) != 0) {
        ClipWallField(p);
    } else {
        ClipWall(p);
    }
    if (hitColRayDisp != 0) {
        DrawCollisionRay(p);
    }
    if (*(int *)(p + 0x88) != 0) {
        SubVectorXYZ(v, p + 0x20, p);
        *(float *)(skelMotCtrl + 0x174) = FSqrt(sceVu0InnerProduct(v, v)) + 50.0f;
        *(int *)(skelMotCtrl + 0x10C) = 1;
        CopyVector((void *)(skelMotCtrl + 0x160), (void *)(p + 0xA0));
    }
}

/* kept local: agrees with libvu0.h, which this TU does not include (sceVu0ApplyMatrix, sceVu0MulMatrix differ) */
extern void sceVu0ScaleVector(void *dst, void *src, float s);
/* kept local: float (void *, void *) here, float (float *, float *) in fieldCollision.h */
extern float GetYDistanceFromPlane(void *plane, void *pos);
/* kept local: void (void *, float, float, float, float) here, void (float *, float, float, float, float) in fieldCollision.h */
extern void SetSimplePlane(void *plane, float x, float y, float z, float d);
/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipFloorR(void *a0);
/* kept local: void (void *, void *, void *) here, void (void *, void *, int *) in fieldCollision.h */
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
    MatrixDrive_TransMatrixV(wallCheckBase);
    CopyVector((void *)p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(p + 0x10), MatrixDrive_GetMatrix(), wallCheckAhead);
    MatrixDrive_PopMatrix();

    if (*(int *)(skelRoot + 0x320) != 0) {
        ClipWallField(p);
    } else {
        ClipWall(p);
    }
    if (hitColRayDisp != 0) {
        DrawCollisionRay(p);
    }
    if (*(int *)(p + 0x88) != 0) {
        tmp = *(ClipBuf *)p;
        GetWallVector((int)wv, (int)p);
        sceVu0ScaleVector(sv, wv, -200.0f);
        AddVectorXYZ(p + 0x10, p, sv);
        if (*(int *)(skelRoot + 0x320) != 0) {
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
            if (hitColRayDisp != 0) {
                DrawCollisionRay(p);
            }
            /* One statement, SRCFILE.TXT line 387: the record is filled a
               member at a time (an eight-byte block move, then a word) and
               the whole twelve bytes are then copied out as one unit. */
            cfg = (cfg2.o = ((WallCfg *)(p + 0x80))->o, cfg2.n = ((WallCfg *)(p + 0x80))->n, cfg2);
            if (flag & 1) {
                float v[4];

                SubVectorXYZ(v, p + 0x20, p);
                *(float *)(skelMotCtrl + 0x138) = FSqrt(sceVu0InnerProduct(v, v));
                sceVu0ScaleVector(skelMotCtrl + 0x140, v, 1.0f / *(float *)(skelMotCtrl + 0x138));
                *(int *)(skelMotCtrl + 0x14) = *(int *)(skelMotCtrl + 0x14) | 0x20;
                *(int *)(skelMotCtrl + 0x17C) = *(int *)(skelMotCtrl + 0x184) = GetWallAttribute(p);
                /* The hit count reaches GetOrientOfWall as a pointer-typed
                   load, which is what lets it issue ahead of the two int
                   stores above it. */
                GetOrientOfWall(skelMotCtrl + 0x150, *(void **)(p + 0x88), p + 0x80);
                *(WallCfg *)(skelRoot + 0xE0) = cfg;
                *(int *)(skelRoot + 0xEC) = -1;
                if (*(int *)(skelRoot + 0x320) != 0 && *(int *)(skelMotCtrl + 0x184) == 0x10000) {
                    *(int *)(skelMotCtrl + 0x104) = 1;
                } else {
                    *(int *)(skelMotCtrl + 0xF4) = 1;
                }
            }
            if (flag & 2) {
                float v2[4];
                float plane[4];

                GetPureVerticalPlane(plane, 0, 0, (int *)&cfg, 0);
                *(float *)(skelMotCtrl + 0x134) = -GetYDistanceFromPlane(plane, p) + -40.0f;
                sceVu0ScaleVector(v2, wv, -10.0f);
                AddVectorXYZ(p, p + 0x20, v2);
                CopyVector((void *)(p + 0x10), (void *)p);
                *(float *)(p + 0x14) = *(float *)(p + 0x14) - 10000.0f;
                ClipFloorR(p);
                if (*(int *)(p + 0x94) != 0) {
                    *(float *)(skelMotCtrl + 0x130) =
                        (*(float *)(p + 0x24) - *(float *)(p + 0x4)) + -40.0f;
                    SetSimplePlane(skelRoot + 0x350, 0.0f, -1.0f, 0.0f, *(float *)(p + 0x24));
                    *(int *)(skelRoot + 0x144) = *(int *)(p + 0x94);
                }
            }
        }
    }
}

/* kept local: agrees with libvu0.h, which this TU does not include (sceVu0ApplyMatrix, sceVu0MulMatrix differ) */
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
/* kept local: agrees with fieldCollision.h, which this TU does not include (ClipFloor, ClipFloorIH differ) */
extern float GetDistanceFromPlane(void *plane, void *pos);
/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipWallR(void *a0);
/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipFloorIH(void *a0);

void checkCliffState(int a0)
{
    char buf[0xC0];
    float mv[4];
    char *p;
    float k;

    memset(buf, 0, 0xC0);
    p = buf;
    k = (skelGObj == boyGObj) ? -20.0f : 0.0f;
    cliffCheckBase[2] = k;
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(cliffCheckBase);
    CopyVector(p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(p + 0x10), MatrixDrive_GetMatrix(), cliffCheckAhead);
    _ApplyMatrix(mv, MatrixDrive_GetMatrix(), ZUnitVector);
    MatrixDrive_PopMatrix();
    if (hitColRayDisp != 0) {
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
        if (hitColRayDisp != 0) {
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
            if (hitColRayDisp != 0) {
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
                *(float *)(skelMotCtrl + 0x114) = GetPointDistance(p + 0x20, p) + k * ip;
                *(int *)(skelMotCtrl + 0xFC) = 1;
                /* The wall-hit word is copied as the pointer it is (checkWallState
                   reads it the same way): its load issues ahead of the int store
                   above it, as in the ROM. */
                *(void **)(skelRoot + 0xF8) = *(void **)(p + 0x88);
                *(WallObj *)(skelRoot + 0xF0) = *(WallObj *)(p + 0x80);
                *(int *)(skelRoot + 0xFC) = -1;
                w2 = *(ClipBuf *)p;
                d = GetPointDistance(p + 0x20, p);
                _ScaleVector(sc, wv, d + 10.0f);
                _AddVectorXYZ((int)((char *)&w2 + 0x10), (int)&w2, sc);
                *(float *)((char *)&w2 + 4) = *(float *)((char *)&w2 + 4) - 30.0f;
                *(float *)((char *)&w2 + 0x14) = *(float *)((char *)&w2 + 0x14) - 30.0f;
                ClipWall(&w2);
                if (hitColRayDisp != 0) {
                    DrawCollisionRay(&w2);
                }
                if (*(int *)((char *)&w2 + 0x88) == 0) {
                    *(int *)(skelMotCtrl + 0xF8) = 1;
                    *(int *)(skelMotCtrl + 0x14) |= 0x10;
                }
            }
            *(int *)(skelMotCtrl + 0x180) = *(int *)(skelMotCtrl + 0x184) = GetWallAttribute(p);
            GetOrientOfWall(skelMotCtrl + 0x120, *(void **)(p + 0x88), p + 0x80);
            if (*(float *)(skelMotCtrl + 0x114) < 30.0f) {
                sceVu0ScaleVector(sc, wv, 10.0f);
                SubVectorXYZ(p, hit, sc);
                sceVu0ScaleVector(sc, wv, 300.0f);
                AddVectorXYZ(p + 0x10, p, sc);
                ClipWall(p);
                if (hitColRayDisp != 0) {
                    DrawCollisionRay(p);
                }
                if (*(int *)(p + 0x88) != 0) {
                    dd = distance_squared(p + 0x20, p);
                    *(int *)(skelMotCtrl + 0x100) = 1;
                    d = FSqrt(dd);
                    if (a0 == 0) {
                        if (d < *(float *)(skelMotCtrl + 0x138)) {
                            *(float *)(skelMotCtrl + 0x138) = d;
                        }
                    } else {
                        *(float *)(skelMotCtrl + 0x138) = d;
                    }
                    sceVu0ScaleVector(sc, wv, 10.0f);
                    AddVectorXYZ(p, p + 0x20, sc);
                    CopyVector(p + 0x10, p);
                    *(float *)(p + 0x14) = *(float *)(p + 0x14) - 10000.0f;
                    ClipFloorR(p);
                    if (hitColRayDisp != 0) {
                        DrawCollisionRay(p);
                    }
                    if (*(int *)(p + 0x94) != 0) {
                        *(float *)(skelMotCtrl + 0x130) =
                            (*(float *)(p + 0x24) - *(float *)(p + 4)) + 10.0f;
                    }
                }
            }
            sceVu0ScaleVector(sc, wv, 10.0f);
            AddVectorXYZ(p, hit, sc);
            CopyVector(p + 0x10, p);
            *(float *)(p + 0x14) = *(float *)(p + 0x14) + 10000.0f;
            ClipFloorIH(p);
            if (hitColRayDisp != 0) {
                DrawCollisionRay(p);
            }
            if (*(int *)(p + 0x94) != 0) {
                *(float *)(skelMotCtrl + 0x110) =
                    (*(float *)(p + 0x24) - *(float *)(p + 4)) + 10.0f;
            }
        }
    }
}

void _checkCliffAndWall(void)
{
    float v[4];
    float d;
    float t;

    if (*(int *)(skelMotCtrl + 0xDC) == 1 ||
        (*(int *)(skelMotCtrl + 0xDC) == 2 && *(int *)(skelMotCtrl + 0xE8) == 0)) {
        MatrixDrive_PushMatrix();
        checkCliffState(1);
        MatrixDrive_PopMatrix();
    }
    if (*(int *)(skelMotCtrl + 0xDC) == 1 ||
        (*(int *)(skelMotCtrl + 0xDC) == 2 && *(int *)(skelMotCtrl + 0xE8) == 1)) {
        MatrixDrive_PushMatrix();
        checkWallState(3);
        MatrixDrive_PopMatrix();
    }
    if (*(int *)(skelMotCtrl + 0xDC) == 1) {
        if ((*(int *)(skelMotCtrl + 0x14) & 0x20) == 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, -30.0f, 0.0f);
            checkWallState(3);
            MatrixDrive_PopMatrix();

            if ((*(int *)(skelMotCtrl + 0x14) & 0x20) != 0) {
                *(float *)(skelMotCtrl + 0x130) += 30.0f;
                *(float *)(skelMotCtrl + 0x134) += 30.0f;
            }
        }
        if (skelGObj == boyGObj && *(int *)((int)GOBJ_SUB(skelGObj) + 0x568) == 0) {
            _SubVectorXYZ(v, skelRoot, skelRoot + 0x150);
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
        if (*(int *)(skelMotCtrl + 0xF4) != 0 && *(int *)(skelMotCtrl + 0xF8) != 0) {
            t = *(float *)(skelMotCtrl + 0x138) - *(float *)(skelMotCtrl + 0x114);
            if ((t < 0.0f ? -t : t) < 10.0f) {
                clearCliffStatus();
            }
        }
    }
    if (hitColRayDisp != 0) {
        if (*(int *)(skelMotCtrl + 0xF4) != 0) {
            DrawGObjWallCollision(*(int *)(skelRoot + 0xE0), 0);
        }
    }
    if (*(int *)((int)GOBJ_SUB(skelGObj) + 0x564) != 0 && GOBJ_SUB(skelGObj)->f_188 == 0) {
        debug_assertMessage(__FILE__, 822, "NOT ENTRY WCL\n");
        __assert(__FILE__, 822, "e");
    }
}

void checkCliffAndWallStateOfLastPlane(void)
{
    _UnitMatrix(MatrixDrive_GetMatrix());
    {
        register float *p = (float *)skelRoot;
        float r = GetYProjectionOfPlane((int)(skelRoot + 0x130), (int)skelRoot);
        MatrixDrive_TransMatrix(p[0], r, *(float *)(skelRoot + 8));
    }
    MultiMatrixByQuaternion((char *)skelRoot + 0x30);
    MatrixDrive_PushMatrix();
    _checkCliffAndWall();
    MatrixDrive_PopMatrix();
    if (*(int *)(skelMotCtrl + 0xE4) != 0) {
        MatrixDrive_PushMatrix();
        checkWallSideState();
        MatrixDrive_PopMatrix();
    }
}

void checkCliffAndWallStateAtJump(void)
{
    _UnitMatrix(MatrixDrive_GetMatrix());
    {
        register float *p = (float *)skelRoot;
        MatrixDrive_TransMatrix(p[0], p[1] + p[116] + 10.0f, p[2]);
    }
    MultiMatrixByQuaternion((char *)skelRoot + 0x30);
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
               (void *)(*(char **)((char *)GOBJ_SUB(skelGObj) + 0xC) + id * 0x40 + 0x30));
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
    p = (float *)skelRoot;
    MatrixDrive_TransMatrix(p[0x6C], p[0x6D], p[0x6E]);
    MatrixDrive_ScaleMatrix(8.0f, 8.0f, 8.0f);
    dispSquare2(0xFF);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

#include "motMan_rootUpdate.c.inc"

static char *skelNode = 0;

static int skelGObj = 0;

static inline void calcMaxNodeHeight(int n)
{
    int i;
    *(float *)(skelRoot + 0x1D0) = 0.0f;
    for (i = 0; i < n; i++) {
        if (*(float *)(skelRoot + 0x1D0) < *(float *)(nodePos2 + i * 0x10 + 4)) {
            *(float *)(skelRoot + 0x1D0) = *(float *)(nodePos2 + i * 0x10 + 4);
        }
    }
}

void _getGeometryOfMotion(MotShift *out, int second)
{
    float v[4];
    char q[0x10];
    int save180 = *(int *)(skelRoot + 0x180);

    MatrixDrive_PushMatrix();
    PushQuaternion();
    CopyVector((void *)v, (void *)(skelMotCtrl + 0xB0));
    SetIdentityQuaternion(q);
    sceVu0Normalize((void *)v, (void *)v);
    RotQuaternionY(q, atan2f(v[0], v[2]) * 10430.378f);
    CopyQuaternion((char *)skelRoot + 0x30, q);
    GetMatrixFromQuaternion((void *)MatrixDrive_GetMatrix(), (char *)skelRoot + 0x30);
    SetCurrentQuaternion((char *)skelRoot + 0x30);

    naturalMotion = skelMotion;
    naturalNodePos = nodePos;
    pursueNaturalGeometry(0);

    if (second) {
        naturalMotion = skelMotion2;
        naturalNodePos = nodePos2;
        pursueNaturalGeometry(0);
    } else {
        int i;
        for (i = 0; i < skelNodeNum; i++) {
            CopyVector((void *)(nodePos2 + i * 0x10), (void *)(nodePos + i * 0x10));
        }
    }
    calcMaxNodeHeight(skelNodeNum);

    clearCollisionStatus();
    {
        char *fp = (char *)skelRoot;
        *(int *)(fp + 0x204) = 0;
        *(int *)(fp + 0x208) = 0;
        *(int *)(fp + 0x20C) = 0;
        CopyVector(fp + 0x60, fp);
    }

    if (*(int *)skelMotCtrl != -1) {
        *out = rootUpdateDirectPlayForStream();
    } else {
        char *pm;
        MatrixDrive_PushMatrix();
        pm = (char *)skelMotCtrl;
        switch (*(int *)(pm + 0x68)) {
        default: {
            char buf[0x400];
            sprintf(
                buf,
                "MAY BE MOTION ORIENT DATA WAS BROKEN\n(MOTIONNAME:\"%s\" ID:%d: rootUpdateMode:%d)\n",
                skelMotDef + 0xC0, *(int *)(pm + 0x30), *(int *)(pm + 0x68));
            debug_assertMessage(__FILE__, 997, buf);
            __assert(__FILE__, 997, "e");
        } break;
        case 1:
        case 20:
            *out = rootUpdateXZ(*(int *)(pm + 0x68), findActPoint(footActPoints));
            break;
        case 2:
        case 17:
            *out = rootUpdateXZ_MotPos(*(int *)(pm + 0x68), findActPoint(footActPoints));
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
            rootUpdateY_Rope(findActPoint(ropeActPoints));
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

    *(float *)(skelMotCtrl + 0xF0) =
        *(float *)(skelRoot + 4) + *(float *)(skelNode + 0x14) - *(float *)(skelRoot + 0x1B4);

    MatrixDrive_PushMatrix();
    MatrixDrive_SetTransposeMatrix((void *)MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix((int *)(skelRoot + 0x170), MatrixDrive_GetMatrix(), (char *)skelRoot + 0x90);
    MatrixDrive_PopMatrix();

    MatrixDrive_PopMatrix();
    PopQuaternion();

    if (*(int *)(skelRoot + 0x180) != -1 && save180 == -1) {
        *(int *)(skelMotCtrl + 0x1CC) = 1;
    }
}

inline void getGeometryOfMotion(MotShift *out, int second)
{
    ShiftBlk buf;
    char *p;
    buf = *(ShiftBlk *)(*(char **)((char *)skelGObj + 0x15C) + 0x180);
    _getGeometryOfMotion(out, second);
    p = *(char **)((char *)skelGObj + 0x15C);
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
                if (!(*(int *)(skelMotCtrl + 0x1BC) != 0 &&
                      (*(int *)(skelMotCtrl + 0x188) & 0xF00000)) &&
                    !(*(long long *)(skelMotCtrl + 0x10) & ((long long)0x8008 << 30))) {
                    *(int *)(ext + 0x4EC) = *(int *)(ext + 0x4F0);
                    CopyVector(skelRoot + 0x70, skelRoot);
                    *(MotShift *)(skelRoot + 0x80) = m;
                    *(int *)(skelMotCtrl + 0x84) = 0;
                }
            }
        } else {
            *(int *)(skelMotCtrl + 0x84) = 2;
            CopyVector(skelRoot, skelRoot + 0x70);
        }
    }
    *(int *)(skelMotCtrl + 0x88) = 1;
    if (GOBJ_SUB(self)->f_4EC == 1) {
        if (m.a != 0) {
            CopyVector(buf, skelRoot + 0x70);
            _ApplyMatrix(buf, (int)(*(char **)(*(char **)(m.a + 0x15C) + 0xC) + m.b * 0x40),
                         (char *)buf);
            if (distance_squared(buf, skelRoot + 0x1C0) == 0.0f) {
                *(int *)(skelMotCtrl + 0x88) = 0;
            }
            buf[3] = 1.0f;
            CopyVector(skelRoot + 0x1C0, buf);
        }
        flg = *(int *)(skelMotCtrl + 0x14);
        if ((flg & 0x2000) || m.a != *(int *)(skelRoot + 0x80) ||
            m.b != *(int *)(skelRoot + 0x84) ||
            (*(int *)(skelMotCtrl + 0x1BC) != 0 && (*(int *)(skelMotCtrl + 0x188) & 0xF00000)) ||
            (flg & 2)) {
            GOBJ_SUB(self)->f_4EC = 0;
        } else if (*(int *)(skelMotCtrl + 0x84) != 0) {
            _InterVectorXYZ(skelRoot, skelRoot + 0x70, skelRoot,
                            1.0f - (float)*(int *)(skelMotCtrl + 0x84) * 0.5f);
            *(int *)(skelMotCtrl + 0x84) -= 1;
        }
    }
    if (debug_skel_flag != 0) {
        if (skelGObj == boyGObj) {
            CopyVector(buf2, skelRoot + 0x70);
            _UnitMatrix(MatrixDrive_GetMatrix());
            if (m.a != 0) {
                _ApplyMatrix(buf2, (int)(*(char **)(*(char **)(m.a + 0x15C) + 0xC) + m.b * 0x40),
                             (char *)buf2);
                MatrixDrive_TransMatrixV(buf2);
                gif_StartPacketPri(0xB);
                if (GOBJ_SUB(self)->f_4EC == 1) {
                    prim_DispWireSphere(50.0f, reserverColor, 0x10, 8);
                } else {
                    prim_DispWireSphere(50.0f, reserverColor2, 0x10, 8);
                }
                gif_EndPacket();
            }
        }
    }
}

/* kept local: agrees with DObj.h, which this TU does not include (LinkParentOfDObj differs) */
extern void UnlinkParentOfDObj(void *a0);
/* kept local: void (void *, MotShift *) here, void (void *, PackedLL_19CAF0 *) in DObj.h */
extern void LinkParentOfDObj(void *a0, MotShift *a1);
/* kept local: agrees with libvu0.h, which this TU does not include (sceVu0ApplyMatrix, sceVu0MulMatrix differ) */
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void dispPlane(void *plane, void *pos);
/* kept local: agrees with GifPacket.h; including it here moves this TU's bytes */
extern void gif_SetZTest(int a0);
extern char motionKind[];
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
    stepFocusNode = k;
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

    skelNodeNum = *(int *)(MOWORK(self) + 0x88);
    {
        float wk0[skelNodeNum][4], wk1[skelNodeNum][4];

        skelGObj = (int)self;
        nodePos = (char *)wk0;
        nodePos2 = (char *)wk1;
        skelMotion = m0;
        skelMotion2 = m1;
        skelScale = *(float *)((char *)*(MotHdr **)(MOWORK(self) + 0x870) + 0x20);
        skelRoot = MOWORK(self) + 0xA0;
        skelMotCtrl = MOWORK(self) + 0x470;
        skelNode = (char *)*(MotNode **)(MOWORK(self) + 0x8C);
        skelMotDef = motionKind + *(MotionNo *)(skelMotCtrl + 0x30) * 404;
        CopyVector(rootMove, v);
        CopyVector(rootStep, tbl);
        *(int *)(skelMotCtrl + 0x14) = 0;
        sceVu0SubVector(rootDelta, skelRoot + 0x150, skelRoot + 0x160);
        if (*(int *)(MOWORK(self) + 0x638) != 0) {
            MotShift tmp;
            getGeometryOfMotion(&tmp, r != 1.0f);
        } else {
            getGeometryOfMotion(&sh, r != 1.0f);
        }
        CopyVector(skelRoot + 0x160, skelRoot + 0x150);
        if (*(int *)(MOWORK(self) + 0x4E8) == 1) {
            sh = InitialObjPointer;
        }
        AddVectorXYZ(MOWORK(self) + 0x7C0, skelRoot, skelRoot + 0x10);
        *(float *)(MOWORK(self) + 0x7CC) = 1.0f;
        *(float *)(MOWORK(self) + 0x7C4) =
            *(float *)(MOWORK(self) + 0x7C4) * r + v2[1] * (1.0f - r);
        GetMatrixOfMotion(self, m1, MOWORK(self) + 0x7C0);
    }
    if (debug_wallcheck_flag != 0) {
        gif_StartPacketPri(0xB);
        gif_SetAlpha(1, 5, 0x80);
        gif_SetZTest(0);
        gif_EndPacket();
        dispPlane(MOWORK(self) + 0x1D0, MOWORK(self) + 0xA0);
        gif_StartPacketPri(0xB);
        gif_SetZTest(1);
        gif_EndPacket();
    }
    *(float *)(skelRoot + 0x15C) = 1.0f;
    *(float *)(skelRoot + 0x16C) = 1.0f;
    *(float *)(skelRoot + 0xC) = 1.0f;
    *(float *)(skelRoot + 0x9C) = 0.0f;
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
        *(float *)(MOWORK(self) + 0x7C4) - *(float *)(skelRoot + 0xC0);
    if (sh.a != 0) {
        float m[0x10];
        MatrixDrive_SetTransposeMatrix((void *)m,
                                       *(int *)(*(int *)(sh.a + 0x15C) + 0xC) + sh.b * 0x40);
        sceVu0ApplyMatrix((int *)(MOWORK(self) + 0x7C0), (int)m, MOWORK(self) + 0x7C0);
    }
    execPositionReserver(self, sh);
}

/* GObj+8 is the index into objLayout, the 0x4C-byte GenGeo table (ebrain.c
   types that array `GenGeo objLayout[]`; enemy_act.c indexes it with the same
   `obj[2]` field).  ROM proves the field is NOT read in the `int` alias set:
   the load is issued ABOVE the line-1484 `int` store to skelNodeNum, which an
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
    skelMotion = tbl;
    skelQuat = (char *)GOBJ_SUB(self)->f_10;
    skelNode = (char *)*(int *)((int)GOBJ_SUB(self) + 0x8C);
    skelScale = *(float *)(*(int *)((int)GOBJ_SUB(self) + 0x870) + 0x20);
    skelRoot = (char *)((int)GOBJ_SUB(self) + 0xA0);
    skelMotCtrl = (char *)((int)GOBJ_SUB(self) + 0x470);
    skelNodeNum = GOBJ_SUB(self)->f_88;
    skelGeoType = objLayout[*(GenGeoKind *)(self + 8) * 0x4C + 0x46];
    skelGObj = (int)self;
    MatrixDrive_PushMatrix();
    PushQuaternion();

    GetMatrixFromQuaternion((void *)MatrixDrive_GetMatrix(), skelRoot + 0x30);
    SetCurrentQuaternion(skelRoot + 0x30);

    MatrixDrive_PushMatrix();

    rootHeightVec[1] = *(float *)(skelRoot + 0xC0);
    MatrixDrive_RotMatrixZ(*(short *)(skelRoot + 0x50));

    sceVu0ApplyMatrix((int *)v, MatrixDrive_GetMatrix(), (char *)rootHeightVec);

    v[1] -= *(float *)(skelRoot + 0xC0);
    v[0] *= 0.5f;
    v[2] *= 0.5f;
    MatrixDrive_PopMatrix();

    if (*(int *)(skelMotCtrl + 0xE0) != 0) {
        getFinalMatrix(0);
    } else {
        getFinalMatrixWithNaturalGeometry(0);
    }

    scaleMatrix[0] = scaleMatrix[5] = scaleMatrix[10] = skelScale;

    AddVectorXYZ(w, ofs, v);
    for (i = 0; i < skelNodeNum; i++) {
        char *nd = *(char **)((char *)GOBJ_SUB(skelGObj) + 0xC) + i * 0x40;
        char *pos = nd + 0x30;
        sceVu0MulMatrix((int)nd, (int)nd, (int)scaleMatrix);
        AddVectorXYZ(pos, pos, w);
    }
    MatrixDrive_PopMatrix();
    PopQuaternion();

    if (debug_actnode_flag != 0) {
        dispActNode(*(int *)(skelRoot + 0x180));
        dispLastNode();
    }
    if (debug_skel_flag != 0) {
        int n;

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        gif_StartPacketPri(0xB);
        n = GetSkeltonFocusNode(self, 0x23);
        CopyVector(w, *(char **)((char *)GOBJ_SUB(skelGObj) + 0xC) + n * 0x40 + 0x30);
        CopyVector(p1, skelRoot + 0x2F0);
        _SubVector(p2, p1, w);
        _NormalizeVector(p2, p2);
        _ScaleVector(p2, p2, 100.0f);
        _AddVector(p1, w, p2);
        gif_SetAlpha(1, 5, 0x80);
        if (*(int *)(skelRoot + 0x318) != 0 && *(int *)(skelRoot + 0x2E0) != 0) {
            DrawLineG(w, dirColor, p1, dirColor, -1);
        } else {
            DrawLineG(w, dirColor2, p1, dirColor2, -1);
        }
        gif_EndPacket();
    }
}

/* census file static (def line 1592); ico2/sugipon/src/motionManager2 holds the
   other static of that name. */
static void dispSkeltonHierarchy(int node)
{
    if (*(int *)(skelNode + node * 64 + 0x38) != -1) {
        float o[3] = {0.0f, 0.0f, 0.0f};
        float p[3] = {*(float *)(skelNode + node * 64 + 0x10),
                      *(float *)(skelNode + node * 64 + 0x14),
                      *(float *)(skelNode + node * 64 + 0x18)};
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
    CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(*(char **)(skelGObj + 0x15C) + 0xC) + node * 64);
    if (*(int *)(skelNode + node * 64 + 0x30) == -1) {
        float o2[3] = {0.0f, 0.0f, 0.0f};
        float e[3] = {10.0f, 0.0f, 0.0f};
        sceVu0IVECTOR c = {0xFF, 0xFF, 0xFF, 0x80};

        DrawLineG(o2, c, e, c, -1);
    }
    if (*(int *)(skelNode + node * 64 + 0x30) != -1) {
        dispSkeltonHierarchy(*(int *)(skelNode + node * 64 + 0x30));
    }
    MatrixDrive_PopMatrix();
    if (*(int *)(skelNode + node * 64 + 0x34) != -1) {
        dispSkeltonHierarchy(*(int *)(skelNode + node * 64 + 0x34));
    }
}

/* census sugipon/src/motionManager.c getInitialMatrix, def line 1625 (1625-1647),
   a file static: MAIN.MAP carries no global of that name, so the twin in
   ico2/sugipon/src/geometryManager is a static too and `static` here keeps this
   one's ELF symbol local.  No INCLUDE_ASM sibling in this TU calls it. */

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
        MatrixDrive_RotMatrixY((short)((pad[0].ana[0] - 0x80) << 7));
        MatrixDrive_RotMatrixZ((short)((pad[0].ana[1] - 0x80) << 7));
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
    skelGObj = (int)a0;
    v = *(int *)(sub + 0x8C);
    skelNode = (char *)v;
    if (v != 0) {
        p2o_DispVU1();
        if (debug_skel_flag != 0) {
            dispSkelton(a0);
        }
    }
}

void SkelTestGeo(char *a0)
{
    int sub = (int)GOBJ_SUB(a0);
    int v;
    int i;
    skelGObj = (int)a0;
    v = *(int *)(sub + 0x8C);
    skelNode = (char *)v;
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
        if (debug_skel_flag != 0) {
            dispSkelton(a0);
        }
    }
}

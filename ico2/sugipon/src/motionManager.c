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
#include "motionManager.h"
#include <libvu0.h>
#include <assert.h>

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

static struct MotRoot *skelRoot; /* derived name */

static struct MotCtrl *skelMotCtrl; /* derived name */

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
   ObjNode template. */
static char *skelNode; /* derived name */

/* the object being skeletonised, held as a word: GetMatrixOfMotion's store
   of it keeps its place among the display-object reads only as an int store
   (a GObj pointer lets two of them pass it), so its uses convert it */
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
/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern float GetYProjectionOfPlane(float *plane, float *pos);
/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipWallFuchiHangWalkStop(void *a0);
/* kept local: int (void *) here, int (int) in fieldCollision.h */
extern int GetWallAttribute(void *a0);
extern ObjNode rootUpdateDirectPlayForStream(void);
extern ObjNode rootUpdateXZ(int a0, int a1);
extern ObjNode rootUpdateXZ_MotPos(int a0, int a1);
extern ObjNode rootUpdateStepSolution(int a0);
extern ObjNode rootUpdateHang(int a0, int a1, int a2);
extern ObjNode rootUpdateSwim(void);
extern ObjNode rootUpdateNodeFix(void);
extern ObjNode rootUpdateY(void);
extern ObjNode rootUpdateY_Rope(int a0);
extern ObjNode rootUpdateTrueMotion(int a0);
extern ObjNode rootUpdateDirectPlay(int a0);
extern ObjNode rootUpdateFly(void);
extern ObjNode rootUpdateEnemyFly(void);
/* kept local: void (int, int) here, void (char *, int) in fieldCollision.h */
extern void DrawGObjWallCollision(int a0, int a1);
extern unsigned char objLayout[];

typedef struct {
    int obj;
    int node;
} ActPt;

/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipWallField(void *a0);
/* kept local: void (void *) here, void (char *) in fieldCollision.h */
extern void DrawCollisionRay(void *a0);
/* kept local: DisplayP2O.h does not compile in this TU (too few arguments to function `p2o_DispVU1') */
extern void p2o_DispVU1();
static void getInitialMatrix(int a0, int a1);
/* kept local: void () here, void (void *) in fieldCollision.h */
extern void ClipFloor();

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

    if (skelRoot->noStepSearch != 0) {
        return -1;
    }
    for (i = 0; i < skelNodeNum; i++) {
        int order = findActPointOrder(list, *(int *)(skelNode + i * 0x40 + 4));
        int v;
        if (order == 0) {
            continue;
        }
        if (skelRoot->hand1IKMode != 0) {
            int k = *(int *)(skelNode + i * 0x40 + 4);
            if (k == 6 || k == 11) {
                continue;
            }
        }
        if (skelRoot->hand0IKMode != 0) {
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

    if (skelRoot->hand1IKMode != 0) {
        if (kind == 6 || kind == 11) {
            return -1;
        }
    }
    if (skelRoot->hand0IKMode != 0) {
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

inline void GetWallVector(float *v, ClipBuf *w)
{
    CopyVector(v, &w->normal);
    v[3] = 0.0f;
}

/* listing lines 203-209: inlined here and into _checkCliffAndWall, never emitted out of
   line (name ours). The float limit is a literal: ee-gcc keeps a single-precision
   constant above 1.0e38 in the function's .sdata constant pool. */
static inline void clearCliffStatus(void)
{
    skelMotCtrl->flags &= ~0x10;
    skelMotCtrl->fieldWallHit = 0;
    skelMotCtrl->cliffEdge = 0;
    skelMotCtrl->cliffWallHit = 0;
    skelMotCtrl->cliffBack = 0;
    skelMotCtrl->cliffHeight = 3.40282347e+38f;
    skelMotCtrl->cliffDist = 3.40282347e+38f;
}

void clearCollisionStatus(void)
{
    clearCliffStatus();

    skelMotCtrl->flags &= ~0x20;
    skelMotCtrl->wallHit = 0;
    skelMotCtrl->wallDist = 3.40282347e+38f;
    skelMotCtrl->wallFloorHeight = 3.40282347e+38f;
    skelMotCtrl->wallTopHeight = 3.40282347e+38f;
    skelRoot->cliffFloor = 0;

    skelMotCtrl->sideWall = 0;
    skelMotCtrl->sideWallDist = 3.40282347e+38f;
    skelMotCtrl->cliffDepth = 0.0f;

    skelMotCtrl->flags &= ~0x1000;
    skelMotCtrl->upperWall = 0;
    skelMotCtrl->upperWallDist = 3.40282347e+38f;

    skelMotCtrl->lastSlipFlags = skelMotCtrl->slipFlags;
    skelMotCtrl->slipFlags = 0;
    skelMotCtrl->waterDepth = 0.0f;

    skelMotCtrl->word1CC = 0;
}

void checkUpperWallState(void)
{
    ClipBuf buf;
    memset(&buf, 0, 0xC0);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(wallCheckBase);
    CopyVector(&buf, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)buf.pt[1], MatrixDrive_GetMatrix(), wallCheckAhead);
    MatrixDrive_PopMatrix();
    ClipWall(&buf);
    if (buf.wall.n != 0) {
        float a;
        struct MotCtrl *D;
        a = GetPointDistance(buf.pt[2], &buf);
        D = skelMotCtrl;
        D->upperWallDist = a;
        D->upperWall = 1;
        D->flags = D->flags | 0x1000;
    }
}

void checkWallSideState(void)
{
    ClipBuf buf = {{0}, {0}, 50.0f};
    float v[4];
    ClipBuf *p = &buf;

    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(wallCheckBase);
    CopyVector((void *)p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)p->pt[1], MatrixDrive_GetMatrix(), wallCheckAhead);
    MatrixDrive_PopMatrix();

    if (skelRoot->fieldWall != 0) {
        ClipWallField(p);
    } else {
        ClipWall(p);
    }
    if (hitColRayDisp != 0) {
        DrawCollisionRay(p);
    }
    if (p->wall.n != 0) {
        SubVectorXYZ(v, p->pt[2], p);
        skelMotCtrl->sideWallDist = FSqrt(sceVu0InnerProduct(v, v)) + 50.0f;
        skelMotCtrl->sideWall = 1;
        CopyVector((void *)skelMotCtrl->sideWallNormal, (void *)&p->normal);
    }
}

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
    ClipBuf *p;
    float wv[4];
    ClipBuf tmp;
    float sv[4];
    WallCfg cfg;
    WallCfg cfg2;

    memset(&buf, 0, 0xC0);
    p = &buf; /* after the memset: the ROM's copy of $sp is the insn
                           the assembler pulls into PushMatrix's delay slot */
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(wallCheckBase);
    CopyVector((void *)p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)p->pt[1], MatrixDrive_GetMatrix(), wallCheckAhead);
    MatrixDrive_PopMatrix();

    if (skelRoot->fieldWall != 0) {
        ClipWallField(p);
    } else {
        ClipWall(p);
    }
    if (hitColRayDisp != 0) {
        DrawCollisionRay(p);
    }
    if (p->wall.n != 0) {
        tmp = *p;
        GetWallVector(wv, p);
        sceVu0ScaleVector(sv, wv, -200.0f);
        AddVectorXYZ(p->pt[1], p, sv);
        if (skelRoot->fieldWall != 0) {
            ClipWallField(p);
        } else {
            ClipWall(p);
        }
        if (p->wall.n != 0) {
            if (p->wall.n != tmp.wall.n || p->wall.o.obj != tmp.wall.o.obj ||
                p->wall.o.node != tmp.wall.o.node) {
                if (distance_squared(p, p->pt[2]) > distance_squared(&tmp, tmp.pt[2])) {
                    *p = tmp;
                }
            }
            if (hitColRayDisp != 0) {
                DrawCollisionRay(p);
            }
            /* One statement, SRCFILE.TXT line 387: the record is filled a
               member at a time (an eight-byte block move, then a word) and
               the whole twelve bytes are then copied out as one unit. */
            cfg = (cfg2.o = ((WallCfg *)&p->wall)->o, cfg2.n = ((WallCfg *)&p->wall)->n, cfg2);
            if (flag & 1) {
                float v[4];

                SubVectorXYZ(v, p->pt[2], p);
                skelMotCtrl->wallDist = FSqrt(sceVu0InnerProduct(v, v));
                sceVu0ScaleVector(skelMotCtrl->wallDir, v, 1.0f / skelMotCtrl->wallDist);
                skelMotCtrl->flags = skelMotCtrl->flags | 0x20;
                skelMotCtrl->pureWallAttr = skelMotCtrl->wallAttr = GetWallAttribute(p);
                /* The hit count reaches GetOrientOfWall as a pointer-typed
                   load, which is what lets it issue ahead of the two int
                   stores above it. */
                GetOrientOfWall(skelMotCtrl->wallNormal, p->wall.n, &p->wall);
                skelRoot->wall = cfg;
                skelRoot->wallCount = -1;
                if (skelRoot->fieldWall != 0 && skelMotCtrl->wallAttr == 0x10000) {
                    skelMotCtrl->fieldWallHit = 1;
                } else {
                    skelMotCtrl->wallHit = 1;
                }
            }
            if (flag & 2) {
                float v2[4];
                float plane[4];

                GetPureVerticalPlane(plane, 0, 0, (int *)&cfg, 0);
                skelMotCtrl->wallTopHeight = -GetYDistanceFromPlane(plane, p) + -40.0f;
                sceVu0ScaleVector(v2, wv, -10.0f);
                AddVectorXYZ(p, p->pt[2], v2);
                CopyVector((void *)p->pt[1], (void *)p);
                p->pt[1][1] = p->pt[1][1] - 10000.0f;
                ClipFloorR(p);
                if (p->floor.n != 0) {
                    skelMotCtrl->wallFloorHeight = (p->pt[2][1] - p->pt[0][1]) + -40.0f;
                    SetSimplePlane(skelRoot->cliffPlane, 0.0f, -1.0f, 0.0f, p->pt[2][1]);
                    skelRoot->cliffFloor = p->floor.n;
                }
            }
        }
    }
}

/* kept local: agrees with fieldCollision.h, which this TU does not include (ClipFloor, ClipFloorIH differ) */
extern float GetDistanceFromPlane(void *plane, void *pos);
/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipWallR(void *a0);
/* kept local: agrees with fieldCollision.h, which this TU does not include (InitialColInfo, InitialObjPointer differ) */
extern void ClipFloorIH(void *a0);

void checkCliffState(int a0)
{
    ClipBuf buf;
    float mv[4];
    ClipBuf *p;
    float k;

    memset(&buf, 0, 0xC0);
    p = &buf;
    k = (skelGObj == boyGObj) ? -20.0f : 0.0f;
    cliffCheckBase[2] = k;
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(cliffCheckBase);
    CopyVector(p, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)p->pt[1], MatrixDrive_GetMatrix(), cliffCheckAhead);
    _ApplyMatrix(mv, MatrixDrive_GetMatrix(), ZUnitVector);
    MatrixDrive_PopMatrix();
    if (hitColRayDisp != 0) {
        DrawCollisionRay(p);
    }
    ClipWallR(p);
    if (p->wall.n != 0) {
        float wv[4];
        float sc[4];
        float hit[4];
        ClipBuf fp;
        float plane[4];
        WallCfg pl;
        WallCfg t;
        float d;
        float dd;

        GetWallVector(wv, p);
        sceVu0ScaleVector(sc, wv, 300.0f);
        AddVectorXYZ(p->pt[1], p, sc);
        ClipWallR(p);
        if (hitColRayDisp != 0) {
            DrawCollisionRay(p);
        }
        if (p->wall.n != 0) {
            sceVu0ScaleVector(sc, wv, 10.0f);
            sceVu0AddVector(fp.pt[1], p->pt[2], sc);
            CopyVector(&fp, fp.pt[1]);
            pl = (t.o = p->wall.o, t.n = p->wall.n, t);
            GetPureVerticalPlane(plane, 0, 0, (int *)&pl, 0);
            d = GetDistanceFromPlane(plane, p->pt[2]);
            fp.pt[0][1] += d - 10.0f;
            ClipFloor(&fp);
            if (hitColRayDisp != 0) {
                DrawCollisionRay(&fp);
            }
            CopyVector(hit, p->pt[2]);
            if (fp.floor.n == 0) {
                float dv[4];
                float nv[4];
                ClipBuf w2;
                float ip;

                CopyVector(dv, wv);
                sc[1] = 0.0f;
                _NormalizeVector(nv, dv);
                ip = _InnerProduct(nv, mv);
                skelMotCtrl->cliffDist = GetPointDistance(p->pt[2], p) + k * ip;
                skelMotCtrl->cliffWallHit = 1;
                /* The wall-hit word is copied as the pointer it is (checkWallState
                   reads it the same way): its load issues ahead of the int store
                   above it, as in the ROM. */
                skelRoot->cliffWall.n = p->wall.n;
                skelRoot->cliffWall.o = p->wall.o;
                skelRoot->cliffWallCount = -1;
                w2 = *p;
                d = GetPointDistance(p->pt[2], p);
                _ScaleVector(sc, wv, d + 10.0f);
                _AddVectorXYZ((w2.pt[1]), &w2, sc);
                w2.pt[0][1] = w2.pt[0][1] - 30.0f;
                w2.pt[1][1] = w2.pt[1][1] - 30.0f;
                ClipWall(&w2);
                if (hitColRayDisp != 0) {
                    DrawCollisionRay(&w2);
                }
                if (w2.wall.n == 0) {
                    skelMotCtrl->cliffEdge = 1;
                    skelMotCtrl->flags |= 0x10;
                }
            }
            skelMotCtrl->pureCliffAttr = skelMotCtrl->wallAttr = GetWallAttribute(p);
            GetOrientOfWall(skelMotCtrl->cliffNormal, p->wall.n, &p->wall);
            if (skelMotCtrl->cliffDist < 30.0f) {
                sceVu0ScaleVector(sc, wv, 10.0f);
                SubVectorXYZ(p, hit, sc);
                sceVu0ScaleVector(sc, wv, 300.0f);
                AddVectorXYZ(p->pt[1], p, sc);
                ClipWall(p);
                if (hitColRayDisp != 0) {
                    DrawCollisionRay(p);
                }
                if (p->wall.n != 0) {
                    dd = distance_squared(p->pt[2], p);
                    skelMotCtrl->cliffBack = 1;
                    d = FSqrt(dd);
                    if (a0 == 0) {
                        if (d < skelMotCtrl->wallDist) {
                            skelMotCtrl->wallDist = d;
                        }
                    } else {
                        skelMotCtrl->wallDist = d;
                    }
                    sceVu0ScaleVector(sc, wv, 10.0f);
                    AddVectorXYZ(p, p->pt[2], sc);
                    CopyVector(p->pt[1], p);
                    p->pt[1][1] = p->pt[1][1] - 10000.0f;
                    ClipFloorR(p);
                    if (hitColRayDisp != 0) {
                        DrawCollisionRay(p);
                    }
                    if (p->floor.n != 0) {
                        skelMotCtrl->wallFloorHeight = (p->pt[2][1] - p->pt[0][1]) + 10.0f;
                    }
                }
            }
            sceVu0ScaleVector(sc, wv, 10.0f);
            AddVectorXYZ(p, hit, sc);
            CopyVector(p->pt[1], p);
            p->pt[1][1] = p->pt[1][1] + 10000.0f;
            ClipFloorIH(p);
            if (hitColRayDisp != 0) {
                DrawCollisionRay(p);
            }
            if (p->floor.n != 0) {
                skelMotCtrl->cliffHeight = (p->pt[2][1] - p->pt[0][1]) + 10.0f;
            }
        }
    }
}

void _checkCliffAndWall(void)
{
    float v[4];
    float d;
    float t;

    if (skelMotCtrl->wordDC == 1 || (skelMotCtrl->wordDC == 2 && skelMotCtrl->wordE8 == 0)) {
        MatrixDrive_PushMatrix();
        checkCliffState(1);
        MatrixDrive_PopMatrix();
    }
    if (skelMotCtrl->wordDC == 1 || (skelMotCtrl->wordDC == 2 && skelMotCtrl->wordE8 == 1)) {
        MatrixDrive_PushMatrix();
        checkWallState(3);
        MatrixDrive_PopMatrix();
    }
    if (skelMotCtrl->wordDC == 1) {
        if ((skelMotCtrl->flags & 0x20) == 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, -30.0f, 0.0f);
            checkWallState(3);
            MatrixDrive_PopMatrix();

            if ((skelMotCtrl->flags & 0x20) != 0) {
                skelMotCtrl->wallFloorHeight += 30.0f;
                skelMotCtrl->wallTopHeight += 30.0f;
            }
        }
        if (skelGObj == boyGObj && GOBJ_SUB(skelGObj)->word568 == 0) {
            _SubVectorXYZ(v, skelRoot->pos, skelRoot->last);
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
        if (skelMotCtrl->wallHit != 0 && skelMotCtrl->cliffEdge != 0) {
            t = skelMotCtrl->wallDist - skelMotCtrl->cliffDist;
            if ((t < 0.0f ? -t : t) < 10.0f) {
                clearCliffStatus();
            }
        }
    }
    if (hitColRayDisp != 0) {
        if (skelMotCtrl->wallHit != 0) {
            DrawGObjWallCollision(skelRoot->wall.o.obj, 0);
        }
    }
    if (GOBJ_SUB(skelGObj)->wallHit != 0 && GOBJ_SUB(skelGObj)->wallPlane == 0) {
        debug_assertMessage(__FILE__, 822, "NOT ENTRY WCL\n");
        __assert(__FILE__, 822, "e");
    }
}

void checkCliffAndWallStateOfLastPlane(void)
{
    _UnitMatrix(MatrixDrive_GetMatrix());
    {
        register float *p = skelRoot->pos;
        float r = GetYProjectionOfPlane(skelRoot->plane.f, skelRoot->pos);
        MatrixDrive_TransMatrix(p[0], r, skelRoot->pos[2]);
    }
    MultiMatrixByQuaternion(skelRoot->quat);
    MatrixDrive_PushMatrix();
    _checkCliffAndWall();
    MatrixDrive_PopMatrix();
    if (skelMotCtrl->wordE4 != 0) {
        MatrixDrive_PushMatrix();
        checkWallSideState();
        MatrixDrive_PopMatrix();
    }
}

void checkCliffAndWallStateAtJump(void)
{
    _UnitMatrix(MatrixDrive_GetMatrix());
    {
        register float *p = skelRoot->pos;
        MatrixDrive_TransMatrix(p[0], p[1] + skelRoot->projHeight + 10.0f, p[2]);
    }
    MultiMatrixByQuaternion(skelRoot->quat);
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
               (void *)((char *)GOBJ_SUB(skelGObj)->nodeMtx + id * 0x40 + 0x30));
    MatrixDrive_ScaleMatrix(5.0f, 5.0f, 5.0f);
    dispSquare(0xFF);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

void dispLastNode(void)
{
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(skelRoot->footPos[0], skelRoot->footPos[1], skelRoot->footPos[2]);
    MatrixDrive_ScaleMatrix(8.0f, 8.0f, 8.0f);
    dispSquare2(0xFF);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

#include "motMan_rootUpdate.c.inc"
/* GifPacket.h is read here, after dispActNode: that function calls the gif
   packet functions undeclared, as the ROM's argument setup shows (with
   gif_SetAlpha's long long prototype in scope its registers change) */
#include "GifPacket.h"
#include "DObj.h"

static char *skelNode = 0;

static int skelGObj = 0;

static inline void calcMaxNodeHeight(int n)
{
    int i;
    skelRoot->projHeight = 0.0f;
    for (i = 0; i < n; i++) {
        if (skelRoot->projHeight < *(float *)(nodePos2 + i * 0x10 + 4)) {
            skelRoot->projHeight = *(float *)(nodePos2 + i * 0x10 + 4);
        }
    }
}

void _getGeometryOfMotion(ObjNode *out, int second)
{
    float v[4];
    char q[0x10];
    int save180 = skelRoot->standNode;

    MatrixDrive_PushMatrix();
    PushQuaternion();
    CopyVector((void *)v, (void *)skelMotCtrl->dir);
    SetIdentityQuaternion(q);
    sceVu0Normalize((void *)v, (void *)v);
    RotQuaternionY(q, atan2f(v[0], v[2]) * 10430.378f);
    CopyQuaternion(skelRoot->quat, q);
    GetMatrixFromQuaternion((void *)MatrixDrive_GetMatrix(), skelRoot->quat);
    SetCurrentQuaternion(skelRoot->quat);

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
        skelRoot->word204 = 0;
        skelRoot->lift[0] = 0.0f;
        skelRoot->lift[1] = 0.0f;
        CopyVector(skelRoot->up, skelRoot->pos);
    }

    if (skelMotCtrl->stream != -1) {
        *out = rootUpdateDirectPlayForStream();
    } else {
        struct MotCtrl *pm;
        MatrixDrive_PushMatrix();
        pm = skelMotCtrl;
        switch (pm->rootUpdateMode) {
        default: {
            char buf[0x400];
            sprintf(
                buf,
                "MAY BE MOTION ORIENT DATA WAS BROKEN\n(MOTIONNAME:\"%s\" ID:%d: rootUpdateMode:%d)\n",
                skelMotDef + 0xC0, pm->motion, pm->rootUpdateMode);
            debug_assertMessage(__FILE__, 997, buf);
            __assert(__FILE__, 997, "e");
        } break;
        case 1:
        case 20:
            *out = rootUpdateXZ(pm->rootUpdateMode, findActPoint(footActPoints));
            break;
        case 2:
        case 17:
            *out = rootUpdateXZ_MotPos(pm->rootUpdateMode, findActPoint(footActPoints));
            break;
        case 7:
        case 8:
        case 9:
        case 13:
        case 16:
            *out = rootUpdateStepSolution(pm->rootUpdateMode);
            break;
        case 10:
        case 15:
            *out = rootUpdateHang(pm->rootUpdateMode, checkActPointWithHeight(6, 10.0f),
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
            *out = rootUpdateTrueMotion(pm->rootUpdateMode);
            break;
        case 6:
        case 14:
            *out = rootUpdateDirectPlay(pm->rootUpdateMode);
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

    skelMotCtrl->groundHeight =
        skelRoot->pos[1] + *(float *)(skelNode + 0x14) - skelRoot->footPos[1];

    MatrixDrive_PushMatrix();
    MatrixDrive_SetTransposeMatrix((void *)MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix((int *)skelRoot->stepMove, MatrixDrive_GetMatrix(), skelRoot->move);
    MatrixDrive_PopMatrix();

    MatrixDrive_PopMatrix();
    PopQuaternion();

    if (skelRoot->standNode != -1 && save180 == -1) {
        skelMotCtrl->word1CC = 1;
    }
}

inline void getGeometryOfMotion(ObjNode *out, int second)
{
    ShiftBlk buf;
    Sub15C *p;
    buf = *(ShiftBlk *)(*(char **)((char *)skelGObj + 0x15C) + 0x180);
    _getGeometryOfMotion(out, second);
    p = ((GObj *)skelGObj)->dobj;
    if (p->keepWall != 0) {
        *(ShiftBlk *)((char *)p + 0x180) = buf;
    }
}

void execPositionReserver(GObj *self, ObjNode m)
{
    int ext;
    float buf[4];
    float buf2[4];
    int flg;

    ext = (int)GOBJ_SUB(self);
    if (*(int *)(ext + 0x4F0) == 1) {
        if (*(int *)(ext + 0x4EC) == 0 || *(int *)(ext + 0x4EC) != *(int *)(ext + 0x4F0)) {
            if (m.obj != 0) {
                if (!(skelMotCtrl->slipOn != 0 && (skelMotCtrl->floorAttr & 0xF00000)) &&
                    !(*(long long *)&skelMotCtrl->ctrlFlags & ((long long)0x8008 << 30))) {
                    *(int *)(ext + 0x4EC) = *(int *)(ext + 0x4F0);
                    CopyVector(skelRoot->savePos, skelRoot->pos);
                    skelRoot->hitObj = m;
                    skelMotCtrl->reserveBlend = 0;
                }
            }
        } else {
            skelMotCtrl->reserveBlend = 2;
            CopyVector(skelRoot->pos, skelRoot->savePos);
        }
    }
    skelMotCtrl->reserveMoved = 1;
    if (GOBJ_SUB(self)->posReserve == 1) {
        if (m.obj != 0) {
            CopyVector(buf, skelRoot->savePos);
            _ApplyMatrix(buf, ((char *)GOBJ_SUB(m.obj)->nodeMtx + m.node * 0x40), (char *)buf);
            if (distance_squared(buf, skelRoot->reservePos) == 0.0f) {
                skelMotCtrl->reserveMoved = 0;
            }
            buf[3] = 1.0f;
            CopyVector(skelRoot->reservePos, buf);
        }
        flg = skelMotCtrl->flags;
        if ((flg & 0x2000) || m.obj != skelRoot->hitObj.obj || m.node != skelRoot->hitObj.node ||
            (skelMotCtrl->slipOn != 0 && (skelMotCtrl->floorAttr & 0xF00000)) || (flg & 2)) {
            GOBJ_SUB(self)->posReserve = 0;
        } else if (skelMotCtrl->reserveBlend != 0) {
            _InterVectorXYZ(skelRoot->pos, skelRoot->savePos, skelRoot->pos,
                            1.0f - (float)skelMotCtrl->reserveBlend * 0.5f);
            skelMotCtrl->reserveBlend -= 1;
        }
    }
    if (debug_skel_flag != 0) {
        if (skelGObj == boyGObj) {
            CopyVector(buf2, skelRoot->savePos);
            _UnitMatrix(MatrixDrive_GetMatrix());
            if (m.obj != 0) {
                _ApplyMatrix(buf2, ((char *)GOBJ_SUB(m.obj)->nodeMtx + m.node * 0x40),
                             (char *)buf2);
                MatrixDrive_TransMatrixV(buf2);
                gif_StartPacketPri(0xB);
                if (GOBJ_SUB(self)->posReserve == 1) {
                    prim_DispWireSphere(50.0f, reserverColor, 0x10, 8);
                } else {
                    prim_DispWireSphere(50.0f, reserverColor2, 0x10, 8);
                }
                gif_EndPacket();
            }
        }
    }
}

extern void dispPlane(void *plane, void *pos);
extern char motionKind[];
void GetMatrixOfMotion(GObj *self, char *tbl, void *ofs);

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
    Sub15C *sub;
} MotWorkRef;

#define MOWORK(self) (((MotWorkRef *)((char *)(self) + 0x15C))->sub)

void GetGeometryOfMotion(void *self, void *m0, void *m1, float *v, float r, char *tbl, int k)
{
    ObjNode sh;
    float v2[4];

    sh = *(ObjNode *)MOWORK(self);
    stepFocusNode = k;
    if ((char *)MOWORK(self)->localObj != 0) {
        MOWORK(self)->localPos[3] = 1.0f;
        CopyVector(v2, (char *)MOWORK(self) + 0x7E0);
        sceVu0ApplyMatrix((int *)v2,
                          *(int *)(*(int *)((char *)MOWORK(self)->localObj + 0x15C) + 0xC) +
                              MOWORK(self)->localNode * 0x40,
                          (char *)v2);
    } else {
        AddVectorXYZ((char *)MOWORK(self) + 0x7E0, (char *)MOWORK(self) + 0x7E0,
                     (char *)MOWORK(self) + 0x7F0);
        CopyVector(v2, (char *)MOWORK(self) + 0x7E0);
    }
    v2[1] = v2[1] + MOWORK(self)->localHeight;
    v2[3] = 1.0f;
    UnlinkParentOfDObj(self);

    skelNodeNum = MOWORK(self)->skelNodeNum;
    {
        float wk0[skelNodeNum][4], wk1[skelNodeNum][4];

        skelGObj = (int)self;
        nodePos = (char *)wk0;
        nodePos2 = (char *)wk1;
        skelMotion = m0;
        skelMotion2 = m1;
        skelScale = MOWORK(self)->nodes->scale[0];
        skelRoot = (struct MotRoot *)((char *)MOWORK(self) + 0xA0);
        skelMotCtrl = (struct MotCtrl *)((char *)MOWORK(self) + 0x470);
        skelNode = (char *)*(MotNode **)((char *)MOWORK(self) + 0x8C);
        skelMotDef = motionKind + skelMotCtrl->motion * 404;
        CopyVector(rootMove, v);
        CopyVector(rootStep, tbl);
        skelMotCtrl->flags = 0;
        sceVu0SubVector(rootDelta, skelRoot->last, skelRoot->clipFrom);
        if (MOWORK(self)->word638 != 0) {
            ObjNode tmp;
            getGeometryOfMotion(&tmp, r != 1.0f);
        } else {
            getGeometryOfMotion(&sh, r != 1.0f);
        }
        CopyVector(skelRoot->clipFrom, skelRoot->last);
        if (MOWORK(self)->word4E8 == 1) {
            sh = InitialObjPointer;
        }
        AddVectorXYZ((char *)MOWORK(self) + 0x7C0, skelRoot->pos, skelRoot->trans);
        MOWORK(self)->motionPos[3] = 1.0f;
        MOWORK(self)->motionPos[1] = MOWORK(self)->motionPos[1] * r + v2[1] * (1.0f - r);
        GetMatrixOfMotion(self, m1, (char *)MOWORK(self) + 0x7C0);
    }
    if (debug_wallcheck_flag != 0) {
        gif_StartPacketPri(0xB);
        gif_SetAlpha(1, 5, 0x80);
        gif_SetZTest(0);
        gif_EndPacket();
        dispPlane((char *)MOWORK(self) + 0x1D0, (char *)MOWORK(self) + 0xA0);
        gif_StartPacketPri(0xB);
        gif_SetZTest(1);
        gif_EndPacket();
    }
    skelRoot->last[3] = 1.0f;
    skelRoot->clipFrom[3] = 1.0f;
    skelRoot->pos[3] = 1.0f;
    skelRoot->move[3] = 0.0f;
    if (sh.obj != 0) {
        LinkParentOfDObj(self, &sh);
        if (GOBJ_SUB(sh.obj)->rideFunc != 0) {
            (*(void (**)(ObjNode *, char *))(*(int *)&sh.obj->dobj + 0x81C))(&sh, self);
        }
    } else {
        MOWORK(self)->rootPosY = MOWORK(self)->rootPosY - MOWORK(self)->height;
        MOWORK(self)->lastPos[1] = MOWORK(self)->lastPos[1] - MOWORK(self)->height;
    }
    MOWORK(self)->motionPos[1] = MOWORK(self)->motionPos[1] - skelRoot->height;
    if (sh.obj != 0) {
        float m[0x10];
        MatrixDrive_SetTransposeMatrix((void *)m, GOBJ_SUB(sh.obj)->nodeMtx + sh.node * 0x40);
        sceVu0ApplyMatrix((int *)((char *)MOWORK(self) + 0x7C0), m, (char *)MOWORK(self) + 0x7C0);
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

void GetMatrixOfMotion(GObj *self, char *tbl, void *ofs)
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
    skelQuat = (char *)GOBJ_SUB(self)->nodeQuat;
    skelNode = (char *)*(int *)((int)GOBJ_SUB(self) + 0x8C);
    skelScale = GOBJ_SUB(self)->nodes->scale[0];
    skelRoot = (struct MotRoot *)((int)GOBJ_SUB(self) + 0xA0);
    skelMotCtrl = (struct MotCtrl *)((int)GOBJ_SUB(self) + 0x470);
    skelNodeNum = GOBJ_SUB(self)->skelNodeNum;
    skelGeoType = objLayout[*(GenGeoKind *)(((char *)self) + 8) * 0x4C + 0x46];
    skelGObj = (int)self;
    MatrixDrive_PushMatrix();
    PushQuaternion();

    GetMatrixFromQuaternion((void *)MatrixDrive_GetMatrix(), skelRoot->quat);
    SetCurrentQuaternion(skelRoot->quat);

    MatrixDrive_PushMatrix();

    rootHeightVec[1] = skelRoot->height;
    MatrixDrive_RotMatrixZ(skelRoot->twist);

    sceVu0ApplyMatrix((int *)v, MatrixDrive_GetMatrix(), (char *)rootHeightVec);

    v[1] -= skelRoot->height;
    v[0] *= 0.5f;
    v[2] *= 0.5f;
    MatrixDrive_PopMatrix();

    if (skelMotCtrl->catchBoy != 0) {
        getFinalMatrix(0);
    } else {
        getFinalMatrixWithNaturalGeometry(0);
    }

    scaleMatrix[0] = scaleMatrix[5] = scaleMatrix[10] = skelScale;

    AddVectorXYZ(w, ofs, v);
    for (i = 0; i < skelNodeNum; i++) {
        char *nd = (char *)GOBJ_SUB(skelGObj)->nodeMtx + i * 0x40;
        char *pos = nd + 0x30;
        sceVu0MulMatrix(nd, nd, scaleMatrix);
        AddVectorXYZ(pos, pos, w);
    }
    MatrixDrive_PopMatrix();
    PopQuaternion();

    if (debug_actnode_flag != 0) {
        dispActNode(skelRoot->standNode);
        dispLastNode();
    }
    if (debug_skel_flag != 0) {
        int n;

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        gif_StartPacketPri(0xB);
        n = GetSkeltonFocusNode(self, 0x23);
        CopyVector(w, (char *)GOBJ_SUB(skelGObj)->nodeMtx + n * 0x40 + 0x30);
        CopyVector(p1, skelRoot->lookPos);
        _SubVector(p2, p1, w);
        _NormalizeVector(p2, p2);
        _ScaleVector(p2, p2, 100.0f);
        _AddVector(p1, w, p2);
        gif_SetAlpha(1, 5, 0x80);
        if (skelRoot->lookIK != 0 && skelRoot->lookMode != 0) {
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
    CopyMatrix(MatrixDrive_GetMatrix(), (char *)GOBJ_SUB(skelGObj)->nodeMtx + node * 64);
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
    float *v;
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix(v);
    dispSkeltonHierarchy(0);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

void SkelTest(GObj *a0)
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

void SkelTestGeo(GObj *a0)
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

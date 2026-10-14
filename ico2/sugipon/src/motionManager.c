#include "typedef.h"
#include "sugiCommon.h"
#include "main.h"
#include "debug_exception.h"
#include "obj_manager.h"
#include "Primitive.h"
#include "lineManager.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "geometryManager.h"
#include "debug.h"
#include "pool.h"
#include "weapon.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "tableSin.h"
#include "Matrix.h"
#include "gv.h"
#include "fieldCollision.h"
#include "motionManager.h"
#include "DisplayP2O.h"
#include <libvu0.h>
#include <assert.h>

/* the motion being computed: its IK slerp rate, motions, quaternions, node
   positions, root and motion control, and the natural-geometry buffers */
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

/* the current motion's motionKind record, read through a byte pointer */
static const MotionDef *skelMotDef; /* derived name */

/* in the order of each object's first user */
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
}; /* derived name */

static sceVu0IVECTOR dirColor = {0xFF, 0x60, 0x40, 0x80}; /* derived name */

static sceVu0IVECTOR dirColor2 = {0x00, 0x60, 0xFF, 0x80}; /* derived name */

static sceVu0FVECTOR ikXAxis; /* derived name */

static sceVu0FVECTOR ikBendQuat; /* derived name */

static float naturalMatrix[16]; /* derived name */

static sceVu0FVECTOR naturalTrans; /* derived name */

static sceVu0FVECTOR rootMove; /* derived name */

static sceVu0FVECTOR rootStep; /* derived name */

static sceVu0FVECTOR rootDelta; /* derived name */

/* The skeleton the motion being computed belongs to: its node array and its
   object.  Declared here for the functions above; the definitions follow
   motMan_rootUpdate.c.inc's ObjNode template. */
static SkelNode *skelNode; /* derived name */

/* the object being skeletonised, held as a word: GetMatrixOfMotion's store
   of it keeps its place among the display-object reads only as an int store
   (a GObj pointer lets two of them pass it), so its uses convert it */
static int skelGObj; /* derived name */

/* the collision display switches SetHitCollisionDisplay sets (the second
   one draws the wall and cliff rays) and the skeleton's scale */
static int hitColDisp = 0; /* derived name */

static int hitColRayDisp = 0; /* derived name */

/* GetGeometryOfMotion and GetMatrixOfMotion write it */
static float skelScale = 1.0f; /* derived name */

static ObjNode rootUpdateDirectPlayForStream(void);
static ObjNode rootUpdateXZ(int kind, int no);
static ObjNode rootUpdateXZ_MotPos(int kind, int no);
static ObjNode rootUpdateStepSolution(int kind);
static ObjNode rootUpdateHang(int kind, int hand1Pt, int hand0Pt);
static ObjNode rootUpdateSwim(void);
static ObjNode rootUpdateNodeFix(void);
static ObjNode rootUpdateY(void);
static ObjNode rootUpdateY_Rope(int actPt);
static ObjNode rootUpdateTrueMotion(int kind);
static ObjNode rootUpdateDirectPlay(int mode);
static ObjNode rootUpdateFly(void);
static ObjNode rootUpdateEnemyFly(void);
extern unsigned char objLayout[];

typedef struct { /* field names derived */
    int obj;
    int node;
} ActPt; /* derived name */

static void getInitialMatrix(Sub15C *obj, int idx);

#include <string.h>
#include <math.h>
#include <stdio.h>

static inline void dispSquare(int alpha) /* derived name */
{
    int col[4] = {0, 128 * alpha / 255, alpha, 128};
    DrawLineG(squareP0, col, squareP2, col, -1);
    DrawLineG(squareP2, col, squareP1, col, -1);
    DrawLineG(squareP1, col, squareP3, col, -1);
    DrawLineG(squareP3, col, squareP0, col, -1);
}

static void dispSquare2(int alpha)
{
    DrawLineG(square2P0, square2Color, square2P2, square2Color, -1);
    DrawLineG(square2P2, square2Color, square2P1, square2Color, -1);
    DrawLineG(square2P1, square2Color, square2P3, square2Color, -1);
    DrawLineG(square2P3, square2Color, square2P0, square2Color, -1);
}

#include "motMan_getFinalMatrix.c.inc"
#include "include_asm.h"

static inline int findActPointOrder(int *list, int kind) /* derived name */
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

INCLUDE_ASM(findActPoint);

INCLUDE_ASM(checkActPointWithHeight);

/* inlined here and into _checkCliffAndWall; the float limit is a
   literal */
static inline void clearCliffStatus(void) /* derived name */
{
    skelMotCtrl->flags &= ~0x10;
    skelMotCtrl->fieldWallHit = 0;
    skelMotCtrl->cliffEdge = 0;
    skelMotCtrl->cliffWallHit = 0;
    skelMotCtrl->cliffBack = 0;
    skelMotCtrl->cliffHeight = 3.40282347e+38f;
    skelMotCtrl->cliffDist = 3.40282347e+38f;
}

INCLUDE_ASM(clearCollisionStatus);

static void checkUpperWallState(void)
{
    ClipWork buf;
    memset(&buf, 0, sizeof(buf));
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(wallCheckBase);
    CopyVector(&buf, (void *)(MatrixDrive_GetMatrix()[3]));
    sceVu0ApplyMatrix(buf.pt[1], MatrixDrive_GetMatrix(), wallCheckAhead);
    MatrixDrive_PopMatrix();
    ClipWall(&buf);
    if (buf.wall.elem != 0) {
        float a;
        struct MotCtrl *D;
        a = GetPointDistance(buf.pt[2], &buf);
        D = skelMotCtrl;
        D->upperWallDist = a;
        D->upperWall = 1;
        D->flags = D->flags | 0x1000;
    }
}

INCLUDE_ASM(checkWallSideState);

INCLUDE_ASM(checkWallState);

INCLUDE_ASM(checkCliffState);

INCLUDE_ASM(_checkCliffAndWall);

INCLUDE_ASM(checkCliffAndWallStateOfLastPlane);

INCLUDE_ASM(checkCliffAndWallStateAtJump);

static void dispActNode(int id)
{
    if (id == -1) {
        return;
    }
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 128);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    CopyVector((void *)(MatrixDrive_GetMatrix()[3]),
               (void *)((char *)GOBJ_SUB(skelGObj)->nodeMtx + id * 64 + 48));
    MatrixDrive_ScaleMatrix(5.0f, 5.0f, 5.0f);
    dispSquare(255);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

INCLUDE_ASM(dispLastNode);

#include "motMan_rootUpdate.c.inc"
/* GifPacket.h is read here, after dispActNode, which calls the gif packet
   functions undeclared */
#include "GifPacket.h"
#include "DObj.h"

INCLUDE_ASM(D_0062D5D0);

static SkelNode *skelNode = 0; /* derived name */

static int skelGObj = 0; /* derived name */

static inline void calcMaxNodeHeight(int n) /* derived name */
{
    int i;
    skelRoot->projHeight = 0.0f;
    for (i = 0; i < n; i++) {
        if (skelRoot->projHeight < *(float *)(nodePos2 + i * 16 + 4)) {
            skelRoot->projHeight = *(float *)(nodePos2 + i * 16 + 4);
        }
    }
}

INCLUDE_ASM(_getGeometryOfMotion);

INCLUDE_ASM(execPositionReserver);

typedef struct MotHdrTag MotHdr; /* derived name */

/* the object's display object, read through geometryManager.h's SubHandle
   union, as motionOrientManager.c reads it */
#define MOWORK(self) (((SubHandle *)&((GObj *)(self))->dobj)->sub) /* derived name */

INCLUDE_ASM(GetGeometryOfMotion);

/* GObj+8 is the index into objLayout, the 76-byte GenGeo table (ebrain.c
   types that array `GenGeo objLayout[]`; enemy_act.c indexes it with the same
   `obj[2]` field), read as an enumerated kind. */
typedef enum { GENGEO_KIND_0 = 0 } GenGeoKind; /* derived name */

INCLUDE_ASM(GetMatrixOfMotion);

/* a file static; ico2/sugipon/src/motionManager2.c has its own of the same
   name */
static void dispSkeltonHierarchy(int node)
{
    if (skelNode[node].parent != -1) {
        float o[3] = {0.0f, 0.0f, 0.0f};
        float p[3] = {skelNode[node].pos[0], skelNode[node].pos[1], skelNode[node].pos[2]};
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
    if (skelNode[node].child == -1) {
        float o2[3] = {0.0f, 0.0f, 0.0f};
        float e[3] = {10.0f, 0.0f, 0.0f};
        sceVu0IVECTOR c = {0xFF, 0xFF, 0xFF, 0x80};

        DrawLineG(o2, c, e, c, -1);
    }
    if (skelNode[node].child != -1) {
        dispSkeltonHierarchy(skelNode[node].child);
    }
    MatrixDrive_PopMatrix();
    if (skelNode[node].sibling != -1) {
        dispSkeltonHierarchy(skelNode[node].sibling);
    }
}

/* a file static; ico2/sugipon/src/geometryManager.c has its own of the
   same name */

static void getInitialMatrix(Sub15C *obj, int idx)
{
    SkelNode *nd;
    char *mtx;

    nd = &obj->skel[idx];
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(nd->pos);
    MultiMatrixByQuaternion(nd->quat);
    switch (nd->kind) {
    case 19:
    case 20:
    case 22:
        MatrixDrive_RotMatrixY((short)((pad[0].ana[0] - 128) << 7));
        MatrixDrive_RotMatrixZ((short)((pad[0].ana[1] - 128) << 7));
        break;
    }
    mtx = (char *)obj->nodeMtx + idx * 64;
    CopyMatrix(mtx, (void *)MatrixDrive_GetMatrix());
    if (nd->child != -1) {
        getInitialMatrix(obj, nd->child);
    }
    MatrixDrive_PopMatrix();
    if (nd->sibling != -1) {
        getInitialMatrix(obj, nd->sibling);
    }
}

/* SkelTest and SkelTestGeo pass their object, which it does not read */
static void dispSkelton(GObj *self)
{
    float (*v)[4];
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 128);
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix(v);
    dispSkeltonHierarchy(0);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

void SkelTest(GObj *self)
{
    Sub15C *sub = GOBJ_SUB(self);
    SkelNode *v;
    skelGObj = (int)self;
    v = sub->skel;
    skelNode = v;
    if (v != 0) {
        p2o_DispVU1(self);
        if (debug_skel_flag != 0) {
            dispSkelton(self);
        }
    }
}

void SkelTestGeo(GObj *self)
{
    Sub15C *sub = GOBJ_SUB(self);
    SkelNode *v;
    int i;
    skelGObj = (int)self;
    v = sub->skel;
    skelNode = v;
    if (v != 0) {
        Sub15C *s2;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_RotMatrixX(-32768);
        getInitialMatrix(GOBJ_SUB(self), 0);
        s2 = GOBJ_SUB(self);
        for (i = 0; i < s2->skelNodeNum; i++) {
            int e = s2->nodeMtx + i * 64;
            sceVu0MulMatrix(e, &s2->matrix, e);
            s2 = GOBJ_SUB(self);
        }
        if (debug_skel_flag != 0) {
            dispSkelton(self);
        }
    }
}

INCLUDE_ASM(SetHitCollisionDisplay);

INCLUDE_ASM(ResetMotionProgramInterpInfo);

INCLUDE_ASM(SetDirectMotionProgramInterpInfo);

INCLUDE_ASM(getFinalMatrixCore);

INCLUDE_ASM(pursueNaturalGeometry);

INCLUDE_ASM(GetWallVector);

INCLUDE_ASM(upperFieldCheck);

INCLUDE_ASM(getGeometryOfMotion);

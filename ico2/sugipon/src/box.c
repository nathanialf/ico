#include "box.h"
#include "sugiCommon.h"
#include "main.h"
#include "matrixDrive.h"
#include "fieldCollision.h"
#include "quaternion.h"
#include "DObj.h"
#include "Primitive.h"
#include "debug.h"
#include "gamesys.h"
#include "generator.h"
#include "frameDependSequence.h"
#include "item.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "tableSin.h"
#include <libvu0.h>
#include <string.h>
#include "motionFileManager.h"
#include "sceneManager.h"
#include "Matrix.h"
#include "motionManager.h"
#include "GifPacket.h"
#include <math.h>
#include "stageMultiBgaManager.h"
#include "DisplayP2O.h"
#include "lineManager.h"
#include "attackhit.h"
#include "obj_manager.h"
#include "memory.h"
#include "geometryManager.h"
#include "ios.h"
#include "particleEffect.h"
#include "objact.h"
#include "gobj.h"
#include "switch.c.inc"
#include "include_asm.h"

/* The 416-byte box work block InitBoxGeo allocates and seeds from the
   template below, aligned(8). */
typedef struct BoxWork { /* field names derived */
    int serial;          /* 0x000, the box's number, mod 30 */
    GObj *holder;        /* 0x004, the character holding the box, mailed 25 when it falls */
    char pad008[8];
    float holdPoint[4]; /* 0x010, the hold point GetBoxHoldPoint last reported */
    int mode;     /* 0x020, 0 still, 1 auto move, 2 falling, 3 to 5 the fall's phases, 6 aligning */
    float scaleX; /* 0x024, the layout's X scale */
    float scaleZ; /* 0x028, the layout's Z scale */
    int colData;  /* 0x02C, the collision ReInitBoxGeo restores */
    int moveFrames; /* 0x030, the frames left of an auto move */
    char pad034[12];
    float vel[4];   /* 0x040, the move per frame */
    int frontPoint; /* 0x050, the path point nearest the front axle */
    int rearPoint;  /* 0x054, the path point nearest the rear axle */
    int route;      /* 0x058, the routeTable index */
    int pointCount; /* 0x05C, the route's point count */
    WallCfg wall;   /* 0x060, the wall the box last hit */
    char pad06C[4];
    float mtx[4][4];      /* 0x070, the box's matrix */
    float waterHeight[4]; /* 0x0B0, the water height GetWaterReaction reports */
    float tilt[4];        /* 0x0C0, the floating box's tilt */
    float tiltVel[4];     /* 0x0D0, the tilt's velocity */
    float lastOffset[4];  /* 0x0E0, the last frame's float offset */
    float tiltForce[4];   /* 0x0F0, the force added to the tilt each frame */
    float lastPos[4];     /* 0x100, the last frame's position */
    int moving;           /* 0x110, set while a push or pull is under way */
    int seStopped;        /* 0x114, set once the move sound has been stopped at the path's end */
    short floatPhase;     /* 0x118, the bob's sine phase */
    short pad11A;
    Sub15C *wheelDObj; /* 0x11C, the wheel DObj dispWheels draws */
    short wheelAngle;  /* 0x120, the wheels' X rotation */
    short pad122;
    float wheelRadius; /* 0x124 */
    float wheelHeight; /* 0x128 */
    float wheelFront;  /* 0x12C, the front axle's Z */
    float wheelRear;   /* 0x130, the rear axle's Z */
    float friction;    /* 0x134, the move's damping, 0.85 or 0.98 */
    int autoDir;       /* 0x138, the direction moveBoxAutoMatic last moved in */
    char pad13C[4];
    int stopWall; /* 0x140, set while a box-stop wall is ahead */
    char pad144[12];
    float tiltQuat[4];  /* 0x150, the slope tilt the root quaternion takes */
    Sub15C *effectDObj; /* 0x160, the effect DObj */
    int charHit;        /* 0x164, set when a character pushed the floating box this frame */
    char pad168[8];
    float floatAnchor[4]; /* 0x170, the floating box's resting X and Z */
    int subGObj;          /* 0x180, the layouted sub GObj, held as a word */
    char pad184[12];
    float moveDir[4];                  /* 0x190, the direction of the last push */
} __attribute__((aligned(8))) BoxWork; /* derived name */

static void landingSE(GObj *self)
{
    ExecuteSEPackage(self, 0x2);
}

INCLUDE_ASM(fallDownStartSE);

static void pushStartSE(GObj *self)
{
    ExecuteSEPackage(self, 0x4);
}

INCLUDE_ASM(pullStartSE);

static void wallHitSE(GObj *self);

INCLUDE_ASM(wallHitSE);

/* inlined into onPath and into ExecBoxMoveEndReaction */
static inline void stopBoxMoveSE(GObj *self) /* derived name */
{
    BoxWork *q = GOBJ_SUB(self)->work;

    StopSEPackage(self);
    StopSEPackageWithGroupVariation(self, 1);

    ExecuteSEPackage(self, 0x16);
    if (q->stopWall != 0) {
        wallHitSE(self);
        q->stopWall = 0;
    }
}

INCLUDE_ASM(initFallDown);

INCLUDE_ASM(checkFieldContact);

INCLUDE_ASM_LIT(InitFloorLeverGeo);

INCLUDE_ASM(func_001AF060);

INCLUDE_ASM(func_001AF590);

INCLUDE_ASM(func_001AF6D8);

/* Inlined into execNormalMove twice (once with ClipWall, once with
   ClipWallBoxStop) and into inertiaMove once; the two constant arguments
   fold, so each inlining carries only one of the two clip calls.  The work
   buffer and the root-position scratch are the caller's: execNormalMove's
   two expansions get two separate work buffers and share one output
   vector. */
static inline void checkBoxWallHit(GObj *self, ClipWork *w, float *base, float *out,
                                   int stop) /* derived name */
{
    BoxWork *p = GOBJ_SUB(self)->work;

    GetRootPosition(base, self);
    if (out != 0) {
        CopyVector(out, base);
    }
    w->radius = (p->scaleX < p->scaleZ ? p->scaleX : p->scaleZ) * 50.0f - 5.0f;
    base[1] += 40.0f;
    CopyVector(w->pt[0], base);
    CopyVector(w->pt[1], base);
    if (stop != 0) {
        ClipWallBoxStop(w);
    } else {
        ClipWall(w);
    }
    w->pt[2][1] -= 40.0f;
}

/* this file's uses of these do not fit the prototypes in the headers that
   declare them */

/* the two debug lines the wall fit prints; the second is EUC-JP, "this
   terrain is wrong (it is not cut to 100cm)" */

/* the record the clip work reports at +0x80: the contact point's x and z,
   and the hit flag the caller has just tested at +0x88.  The staging copy
   fills the point and the flag with two assignments; the read back is one
   assignment of the whole record. */
typedef struct { /* field names derived */
    float x;
    float z;
} BoxWallPt; /* derived name */

typedef struct { /* field names derived */
    BoxWallPt pt;
    int hit;
} BoxWallRec; /* derived name */

/* inlined once, into execAutoMove */
static inline void setBoxStopWallFlag(GObj *self, float *vel) /* derived name */
{
    ClipWork w;
    float dir[4];
    BoxWork *p = GOBJ_SUB(self)->work;

    memset(&w, 0, 0xC0);
    _NormalizeVector(dir, vel);
    _ScaleVector(dir, dir, (p->scaleX < p->scaleZ ? p->scaleX : p->scaleZ) * 50.0f + 25.0f);
    GetRootPosition(w.pt[0], self);
    AddVectorXYZ(w.pt[1], w.pt[0], dir);
    ClipWallBoxStop(&w);
    if (w.wall.elem != 0) {
        p->stopWall = 1;
    } else {
        p->stopWall = 0;
    }
}

static int execAutoMove(GObj *self);
static inline float getAlign(float v, float g);

static inline void alignPosition(GObj *self, float *dst, float *src, float grid) /* derived name */
{
    float npos[4];
    char *n = (char *)(int)GOBJ_SUB(self);
    float cx = *(float *)(n + 0x50);
    float cz = *(float *)(n + 0x58);

    CopyVector(npos, src);
    npos[0] = getAlign(src[0] - cx, grid) + cx;
    npos[2] = getAlign(src[2] - cz, grid) + cz;

    CopyVector(dst, npos);
}

/* Lines 558 to 560 are one call-site line, the same DObj-buffer setup
   ico2/omori/src/chain.c expands by hand in InitChainGeo: the wheel count is
   2 here, so the three allocation sizes are 2<<6, 2<<4 and 2*80 bytes, and
   the 560 the allocator records is the line of the call. */
/* inlined once, into action's case 0.  10430.3779f is 65536 / (2 * pi),
   the radian-to-angle-table factor (ico2/seki/src/Primitive.c spells it the
   same way). */
static inline void updateBoxWheelAngle(GObj *self) /* derived name */
{
    BoxWork *p = GOBJ_SUB(self)->work;

    if (p->wheelDObj != 0) {
        p->wheelAngle = (short)((float)p->wheelAngle - p->vel[2] * 10430.3779f / p->wheelRadius);
    }
}

INCLUDE_ASM(dispWheels);

INCLUDE_ASM(func_001AFA30);

INCLUDE_ASM(func_001AFD88);

INCLUDE_ASM(func_001AFF70);

INCLUDE_ASM(func_001B03B8);

/* one 16-byte route point */
typedef float PathPt[4]; /* derived name */

/* The routes a box can be pushed along: each a list of points ending in one
   whose fourth word is the largest float (countPathPoints stops at a fourth
   word of 10.0f or more).  Routes 9 and 18 to 29 are empty. */
static PathPt route1[] = {
    {-3380.0f, -3500.0f, 100.0f, 1.0f},  {-3380.0f, -3500.0f, 5700.0f, 1.0f},
    {-3337.0f, -3500.0f, 5890.0f, 1.0f}, {-3200.0f, -3500.0f, 6050.0f, 1.0f},
    {-3150.0f, -3500.0f, 6090.0f, 1.0f}, {-2930.0f, -3500.0f, 6150.0f, 1.0f},
    {-1000.0f, -3500.0f, 6150.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route2[] = {
    {0.0f, -50.0f, 0.0f, 1.0f},          {-300.0f, -50.0f, 0.0f, 1.0f},
    {-1000.0f, -50.0f, 700.0f, 1.0f},    {-1000.0f, -50.0f, 1400.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route3[] = {
    {-525.0f, 1450.0f, -1650.0f, 1.0f},
    {-2150.0f, 1450.0f, -1650.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route4[] = {
    {6500.0f, -3470.0f, -1450.0f, 1.0f},
    {6500.0f, -3470.0f, 3400.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route5[] = {
    {500.0f, 2650.0f, -2050.0f, 1.0f},
    {500.0f, 2650.0f, -2600.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route6[] = {
    {-2890.0f, -3510.0f, 6150.0f, 1.0f},
    {1000.0f, -3510.0f, 6150.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route7[] = {
    {-3400.0f, -3450.0f, -2300.0f, 1.0f}, {-3400.0f, -3450.0f, 5680.0f, 1.0f},
    {-3290.0f, -3450.0f, 6000.0f, 1.0f},  {-3000.0f, -3450.0f, 6150.0f, 1.0f},
    {1100.0f, -3450.0f, 6150.0f, 1.0f},   {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route8[] = {
    {-4750.0f, 650.0f, 3300.0f, 1.0f},
    {-4750.0f, 650.0f, 3900.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route9[] = {
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route10[] = {
    {-390.0f, -50.0f, -570.0f, 1.0f},
    {-220.0f, -50.0f, -570.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route11[] = {
    {-390.0f, -50.0f, -1370.0f, 1.0f},
    {-220.0f, -50.0f, -1370.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route12[] = {
    {-390.0f, -50.0f, -2170.0f, 1.0f},
    {-220.0f, -50.0f, -2170.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route13[] = {
    {-390.0f, -50.0f, -2970.0f, 1.0f},
    {-220.0f, -50.0f, -2970.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route14[] = {
    {390.0f, -50.0f, -570.0f, 1.0f},
    {220.0f, -50.0f, -570.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route15[] = {
    {390.0f, -50.0f, -1370.0f, 1.0f},
    {220.0f, -50.0f, -1370.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route16[] = {
    {390.0f, -50.0f, -2170.0f, 1.0f},
    {220.0f, -50.0f, -2170.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route17[] = {
    {390.0f, -50.0f, -2970.0f, 1.0f},
    {220.0f, -50.0f, -2970.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route18[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route19[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route20[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route21[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route22[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route23[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route24[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route25[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route26[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route27[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route28[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

static PathPt route29[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}}; /* derived name */

/* the route a box's layout names (the low half of its kind word) indexes
   this table; route 0 is no route and the last two slots are empty */
static PathPt *routeTable[32] = {
    0,       route1,  route2,  route3,  route4,  route5,  route6,  route7,  route8,  route9,
    route10, route11, route12, route13, route14, route15, route16, route17, route18, route19,
    route20, route21, route22, route23, route24, route25, route26, route27, route28, route29,
}; /* derived name */

/* GetBoxHoldPoint's four hold-point candidates in the box's local frame and
   the four offsets added back after they are scaled by the box's half
   extents */
static float holdPointLocal[4][4] = {
    {0.0f, 0.0f, 50.0f, 1.0f},
    {50.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, -50.0f, 1.0f},
    {-50.0f, 0.0f, 0.0f, 1.0f},
}; /* derived name */

static float holdPointOffset[4][4] = {
    {0.0f, 0.0f, 10.0f, 1.0f},
    {10.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, -10.0f, 1.0f},
    {-10.0f, 0.0f, 0.0f, 1.0f},
}; /* derived name */

INCLUDE_ASM(boxWorkInit);

/* the Y axis the side plane is built from */
static float yAxis[4] = {0.0f, 1.0f, 0.0f, 0.0f}; /* derived name */

/* inlined once, into InitBoxGeo; a route array ends at the first point
   whose fourth word is 10.0f or more */
static inline int countPathPoints(int route) /* derived name */
{
    PathPt *pts = routeTable[route];
    int i;

    for (i = 1; pts[i][3] < 10.0f; i++) {}

    return i;
}

/* The signed plane distance is what the projection is scaled by and its
   magnitude is what the nearest test keeps.  0.707 is the 45 degree axis
   test. */
/* this file's uses of these do not fit the prototypes in the headers that
   declare them */

/* the debug switch the wall-fit trace is printed under */

/* the four trace lines */

/* the two route colours onPath draws the route and its end points in, one
   word per channel, RGBA */
static int routeFrontColor[4] = {0, 128, 255, 128}; /* derived name */

static int routeRearColor[4] = {255, 128, 0, 128}; /* derived name */

/* 10430.378 is 32768 / pi, the radian-to-angle-table factor.  The
   quaternion's initialiser is mostly zero, and each wheel offset is a VECTOR
   record built by an initialiser, as onPathInitialize's are. */
/* no caller; float as sugipon's scalar getters */
static int playAnimationCore(GObj *self);

/* inlined once, into execFallDown's case 3; the frame-rate divisor is the
   one moveBoxAutoMatic uses */
static inline void execBoxFall(GObj *self) /* derived name */
{
    float v[4];

    GetRootPosition(v, self);
    ((IntFloat *)(*(char **)(((char *)self) + 0x15C) + 0x134))->f +=
        60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f *
        (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
    AddVectorXYZ(v, v, GOBJ_SUB(self)->root.move);
    SetRootPosition(self, v);
    if (LimitExistGeometry(v, GOBJ_SUB(self)->root.move) != 0) {
        ((BoxWork *)GOBJ_SUB(self)->work)->mode = -1;
    }
}

/* the local Z axis the floating box's facing is rebuilt from */
static float floatFacingAxis[4] = {0.0f, 0.0f, 1.0f, 0.0f}; /* derived name */

/* 0.31830987 is 1 / pi */
INCLUDE_ASM(MoveFloatingBox);

INCLUDE_ASM(func_001B07F0);

INCLUDE_ASM(func_001B0910);

INCLUDE_ASM(func_001B0DD0);

INCLUDE_ASM(func_001B0EA0);

INCLUDE_ASM(func_001B0F90);

INCLUDE_ASM(func_001B1118);

/* the eight horizontal push-out directions the floating box is tested along */
static float floatPushDir[8][4] = {
    {0.0f, 0.0f, 1.0f, 1.0f},  {0.0f, 0.0f, -1.0f, 1.0f},  {1.0f, 0.0f, 0.0f, 1.0f},
    {-1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, -1.0f, 1.0f}, {1.0f, 0.0f, -1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 1.0f},  {-1.0f, 0.0f, 1.0f, 1.0f},
}; /* derived name */

/* inlined once, into execFloating; the clip work, the matrix and the two
   scratch vectors are the caller's */
static inline void pushOutFloatingBox(ClipWork *cw, float *m, float *sv, float *dv, float *pos,
                                      float *q, float r) /* derived name */
{
    float *dir;
    float len;
    int i;

    memset(cw, 0, sizeof(ClipWork));
    /* the counter is only read by the test; the direction pointer walks
       up */
    for (i = 0, dir = floatPushDir[0]; i < 8; i++, dir += 4) {
        CopyVector(cw->pt[0], pos);
        GetMatrixFromQuaternionPos(m, q, pos);
        _ScaleVectorXYZ(sv, dir, r);
        _ApplyMatrix(cw->pt[1], m, sv);
        ClipWall(cw);
        if (cw->wall.elem != 0) {
            _SubVectorXYZ(dv, cw->pt[2], cw->pt[1]);
            len = VectorLengthSquare(dv);
            if (1.0f < len) {
                _ScaleVector(dv, dv, 1.0f / _Sqrt(len));
            }
            _AddVectorXYZ(pos, pos, dv);
        }
    }
}

/* the same prototype fieldCollision.h gives */

/* the two characters the floating box has to keep clear of, the boy and the
   girl, as sceneManager.c sets them */

/* the world Y axis the box's tilt is measured around */
static float floatTiltAxis[4] = {0.0f, 1.0f, 0.0f, 0.0f}; /* derived name */

static void execFloating(GObj *self);

/* the facing a floating box starts with */
static float floatInitFacing[4] = {0.0f, 0.0f, 1.0f, 0.0f}; /* derived name */

/* two half-unit Z vectors func_001B1658 reads */
INCLUDE_ASM(D_004DEF70);

/* both are inlined once, into action's case 4, the inner one inside the
   outer one */
static inline void resetBoxRootQuaternion(GObj *self, float *q) /* derived name */
{
    GetInverseQuaternion(q, (char *)GOBJ_SUB(self) + 0x60);
    SetRootQuaternion(self, q);
    GOBJ_SUB(self)->colRotate = 1;
}

static inline void playBoxAnimation(GObj *self, float *q) /* derived name */
{
    if (playAnimationCore(self) != 0) {
        BoxWork *p = GOBJ_SUB(self)->work;

        p->mode = 0;
        resetBoxRootQuaternion(self, q);
    }
}

/* inlined once, into execFallDown */
static inline void attackBoxFallCenter(GObj *self) /* derived name */
{
    float plane[4];
    float pos[4];
    BoxWork *q = GOBJ_SUB(self)->work;

    if (q->wall.elem != 0) {
        GetPureVerticalPlane(0, plane, 0, &q->wall, 1);
        plane[3] = 0.0f;
        GetRootPosition(pos, self);
        pos[1] += 50.0f;
        AttackCenter_WithDir(self, 17, pos, plane, 60.0f);
    }
}

static void execFallDown(GObj *self);
static void inertiaMove(GObj *self);

INCLUDE_ASM(action);

INCLUDE_ASM(func_001B1410);

INCLUDE_ASM(func_001B1658);

INCLUDE_ASM(func_001B1778);

INCLUDE_ASM(func_001B1BA8);

INCLUDE_ASM(func_001B1BC0);

/* the box serial counter */
static unsigned char boxSerial = 0; /* derived name */

INCLUDE_ASM(InitBoxGeo);

/* The clip work buffer is declared in a block of its own after the
   candidate loop.  The first iteration measures with sugiCommon.h's
   distance_squared_b, the rest with distance_squared. */
static inline void setupClipWork(ClipWork *w, GObj *obj, float *dir, float len,
                                 float h) /* derived name */
{
    float t[4];

    _ScaleVector(t, dir, len);
    GetRootPosition(w->pt[0], obj);
    w->pt[0][1] += h;
    _AddVectorXYZ(w->pt[1], w->pt[0], t);
}

static inline int checkBoxStopWall(GObj *obj, float *dir) /* derived name */
{
    ClipWork w;
    int r = 1;

    memset(&w, 0, 0xC0);
    setupClipWork(&w, obj, dir, 145.0f, 40.0f);
    ClipWallBoxStop(&w);
    if (w.wall.elem != 0) {
        r = 0;
    }
    return r;
}

static inline int checkMoveWall(GObj *obj, float *dir) /* derived name */
{
    ClipWork w;
    int r = 1;

    memset(&w, 0, 0xC0);
    setupClipWork(&w, obj, dir, 245.0f, 0.0f);
    ClipWall(&w);
    if (w.wall.elem != 0) {
        r = 0;
    }
    return r;
}

static inline int moveXPlus(float *ofs, float dist, float half, float radius);
static inline int moveXMinus(float *ofs, float dist, float half, float radius);
static inline int moveZPlus(float *ofs, float dist, float half, float radius);
static inline int moveZMinus(float *ofs, float dist, float half, float radius);

static inline int checkCharGObjs(GObj *obj, GObj *holder, float *dir) /* derived name */
{
    float pos[4];
    float pos2[4];
    float d[4];
    GObj **list;
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
            if (move(d, w + w, w, GOBJ_SUB(*list)->root.radius + 5.0f) != 0) {
                return 0;
            }
        }
        list++;
    }
    return 1;
}

static int _checkItemCollision(void *pos);

static inline int checkItemHit(GObj *obj, float *dir) /* derived name */
{
    float pos[4];
    float d[4];
    float to[4];

    _ScaleVectorXYZ(d, dir, 100.0f);
    GetRootPosition(pos, obj);
    _AddVectorXYZ(to, pos, d);
    return _checkItemCollision(to);
}

/* the layout record's object word packs the route number in its low half
   and the sub-box model in its high half */
INCLUDE_ASM(BoxGeo);

INCLUDE_ASM(GetBoxMode);

INCLUDE_ASM(AlignBox);

INCLUDE_ASM(CanHoldBox);

INCLUDE_ASM(BoxDL);

INCLUDE_ASM(GetBoxGlobalHoldPoint);

INCLUDE_ASM(IsThisBoxTruck);

INCLUDE_ASM(func_001B2368);

INCLUDE_ASM(BoxGeoRestore);

INCLUDE_ASM(BoxExtGeoRestore);

INCLUDE_ASM(BoxMemoryFunc);

INCLUDE_ASM(InitSwitchGeo);

INCLUDE_ASM(SwitchGeo);

INCLUDE_ASM(SwitchDL);

INCLUDE_ASM(SetSwitchTriggerFunc);

INCLUDE_ASM(SetFloorLeverWithNodePoint);

INCLUDE_ASM(func_001B2598);

INCLUDE_ASM(InitFloorLeverGeo);

INCLUDE_ASM(func_001B26C0);

INCLUDE_ASM(SetWallLeverWithNodePoint);

INCLUDE_ASM(func_001B27C8);

INCLUDE_ASM(IsWallLeverStatus);

INCLUDE_ASM(InitWallLeverGeo);

INCLUDE_ASM(func_001B2938);

INCLUDE_ASM(func_001B2948);

INCLUDE_ASM(getAlign);

INCLUDE_ASM(GetDistanceOfGObj);

INCLUDE_ASM(moveXPlus);

INCLUDE_ASM(moveXMinus);

INCLUDE_ASM(moveZPlus);

INCLUDE_ASM(moveZMinus);

INCLUDE_ASM(BoxRideFunc);

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
#include "include_asm.h"
#include "switch.c.inc"

/* The 400-byte box work block InitBoxGeo allocates and seeds from the
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
} __attribute__((aligned(8))) BoxWork; /* derived name */

INCLUDE_ASM(switchOnSE);

INCLUDE_ASM(switchReleaseSE);

INCLUDE_ASM(GetFloorLeverGlobalHoldPoint);

INCLUDE_ASM(FloorLeverTriStateGeo);

INCLUDE_ASM(FloorLeverGeo);

INCLUDE_ASM(FloorLeverDL);

INCLUDE_ASM(GetWallLeverGlobalHoldPoint);

INCLUDE_ASM(WallLeverGeo);

INCLUDE_ASM(WallLeverDL);

INCLUDE_ASM(CheckReadyAllSwitches);

static void landingSE(GObj *self)
{
    ExecuteSEPackage(self, 0x2);
}

static void fallDownStartSE(GObj *self)
{
    ExecuteSEPackage(self, 0x24);
}

static void pushStartSE(GObj *self)
{
    ExecuteSEPackage(self, 0x4);
}

static void pullStartSE(GObj *self)
{
    ExecuteSEPackage(self, 0xD);
}

static void wallHitSE(GObj *self)
{
    ExecuteSEPackage(self, 0x1E);
}

INCLUDE_ASM(initFallDown);

INCLUDE_ASM(checkFieldContact);

INCLUDE_ASM(execNormalMove);

INCLUDE_ASM(execAutoMove);

INCLUDE_ASM(AlignBox);

INCLUDE_ASM(initWheels);

INCLUDE_ASM(dispWheels);

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

static float getAlign(float v, float g);

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
    {-1700.0f, 1450.0f, -1650.0f, 1.0f},
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
    {-380.0f, -50.0f, -570.0f, 1.0f},
    {-220.0f, -50.0f, -570.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route11[] = {
    {-380.0f, -50.0f, -1370.0f, 1.0f},
    {-220.0f, -50.0f, -1370.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route12[] = {
    {-380.0f, -50.0f, -2170.0f, 1.0f},
    {-220.0f, -50.0f, -2170.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route13[] = {
    {-380.0f, -50.0f, -2970.0f, 1.0f},
    {-220.0f, -50.0f, -2970.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route14[] = {
    {380.0f, -50.0f, -570.0f, 1.0f},
    {220.0f, -50.0f, -570.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route15[] = {
    {380.0f, -50.0f, -1370.0f, 1.0f},
    {220.0f, -50.0f, -1370.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route16[] = {
    {380.0f, -50.0f, -2170.0f, 1.0f},
    {220.0f, -50.0f, -2170.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
}; /* derived name */

static PathPt route17[] = {
    {380.0f, -50.0f, -2970.0f, 1.0f},
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

static BoxWork boxWorkInit = {
    0,
    0,
    {0},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    1.0f,
    1.0f,
    0,
    0,
    {0},
    {0.0f, 0.0f, 0.0f, 0.0f},
    2,
    1,
    0,
    0,
    {{0, -1}, 0},
    {0},
    {{0.0f}},
    {0},
    {0.0f},
    {0.0f},
    {0.0f},
    {0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    10.0f,
    30.0f,
    50.0f,
    -50.0f,
    0.9f,
    0,
    {0},
    0,
    {0},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    0,
    {0},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    {0},
}; /* derived name */

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
static int getNearestPosition(float *out, int *pidx, int *path)
{
    float pos[4];
    float seg[4];
    float dir[4];
    float proj[4];
    float pl[4];
    float foot[4];
    PathPt *pts = routeTable[path[0]];
    float best = 3.40282347e+38f;
    int bi = -1;
    int start;
    int end;
    int i;
    float dist;
    float ad;
    float t;

    if (*pidx != -1) {
        start = *pidx - 1;
        start = 0 < start ? start : 1;
        end = *pidx + 2;
        end = path[1] < end ? path[1] : end;
    } else {
        start = 0;
        end = path[1] - 1;
    }

    for (i = start; i < end; i++) {
        sceVu0SubVector(seg, pts[i], pts[i - 1]);
        seg[1] = 0.0f;
        sceVu0Normalize(dir, seg);
        sceVu0OuterProduct(pl, yAxis, dir);
        pl[1] = 0.0f;
        sceVu0Normalize(pl, pl);
        pl[3] = -(pl[0] * pts[i][0] + pl[2] * pts[i][2]);
        dist = pl[0] * out[0] + pl[2] * out[2] + pl[3];
        ad = dist < 0.0f ? -dist : dist;
        pl[1] = 0.0f;
        pl[3] = 0.0f;
        sceVu0ScaleVector(proj, pl, dist);
        SubVectorXYZ(foot, out, proj);

        if (0.707f < (dir[0] < 0.0f ? -dir[0] : dir[0])) {
            t = (foot[0] - pts[i - 1][0]) / seg[0];
        } else {
            t = (foot[2] - pts[i - 1][2]) / seg[2];
        }
        if (0.0f <= t && t <= 1.0f) {
            CopyVector(out, foot);
            *pidx = i;
            return 0;
        }
        if (ad < best) {
            best = ad;
            bi = i;
            if (t < 0.0f) {
                CopyVector(pos, pts[i - 1]);
            } else {
                CopyVector(pos, pts[i]);
            }
        }
    }
    out[0] = pos[0];
    out[2] = pos[2];
    out[3] = 1.0f;

    *pidx = bi;
    return 1;
}

INCLUDE_ASM(onPathInitialize);

INCLUDE_ASM(onPath);

INCLUDE_ASM(playAnimationCore);

INCLUDE_ASM(MoveFloatingBox);

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

static void avoidCharGObj(GObj *self, GObj *chara)
{
    ClipWork w;
    float pos[4];
    int hit;

    w.radius = (30.0f < GOBJ_SUB(chara)->root.radius) ? GOBJ_SUB(chara)->root.radius : 30.0f;
    GetRootPosition(pos, chara);
    pos[1] += GOBJ_SUB(chara)->root.projHeight + 10.0f;
    CopyVector(&w, pos);
    CopyVector(w.pt[1], pos);
    w.filter.o.obj = self;
    w.filter.o.node = -1;
    w.filter.elem = 0;
    ClipWallE(&w);
    if (w.wall.elem != 0) {
        switch (GOBJ_SUB(chara)->ctrl.rootUpdateMode) {
        case 7:
        case 8:
        case 10:
        case 15:
        case 16:
            hit = GOBJ_SUB(chara)->root.wall.o.obj == self;
            break;
        default:
            hit = 1;
            break;
        }
        if (hit != 0) {
            GetCylinderCollisionWithExceptOwnCollision(self, chara, (w.radius + 50.0f) * 1.414f,
                                                       100.0f, 0.5f, 0.0f, 1);
            UpdateRootMatrix(self);
        }
    }
}

INCLUDE_ASM(execFloating);

INCLUDE_ASM(initFloating);

/* the two characters the floating box has to keep clear of, the boy and the
   girl, as sceneManager.c sets them */

/* the world Y axis the box's tilt is measured around */
static float floatTiltAxis[4] = {0.0f, 1.0f, 0.0f, 0.0f}; /* derived name */

/* the facing a floating box starts with */
static float floatInitFacing[4] = {0.0f, 0.0f, 1.0f, 0.0f}; /* derived name */

static int _checkItemBreak(void *pos)
{
    float p[4];
    float d[4];
    GObj *o;

    /* a nested inline: the range test, the range an integer converted at
       each compare */
    inline int isNearItem(float *v, int r) /* derived name */
    {
        if ((v[0] < 0.0f ? -v[0] : v[0]) < r && (v[1] < 0.0f ? -v[1] : v[1]) < r &&
            (v[2] < 0.0f ? -v[2] : v[2]) < r) {
            return 1;
        }
        return 0;
    }

    for (o = isysGObjSearchFromObjKindID_begin(19); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        if (CheckItemDead(o) != 0) {
            continue;
        }
        GetRootPosition(p, o);
        _SubVectorXYZ(d, p, pos);
        if (isNearItem(d, 50) != 0) {
            BreakItemFromOutside(o);
        }
    }
    return 1;
}

INCLUDE_ASM(initLanding);

INCLUDE_ASM(execFallDown);

INCLUDE_ASM(inertiaMove);

INCLUDE_ASM(action);

INCLUDE_ASM(GetBoxHoldPoint);

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

static int moveXPlus(float *ofs, float dist, float half, float radius);
static int moveXMinus(float *ofs, float dist, float half, float radius);
static int moveZPlus(float *ofs, float dist, float half, float radius);
static int moveZMinus(float *ofs, float dist, float half, float radius);

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

static int _checkItemCollision(void *pos)
{
    float p[4];
    float d[4];
    GObj *o;

    /* the same nested range test as _checkItemBreak's */
    inline int isNearItem(float *v, int r) /* derived name */
    {
        if ((v[0] < 0.0f ? -v[0] : v[0]) < r && (v[1] < 0.0f ? -v[1] : v[1]) < r &&
            (v[2] < 0.0f ? -v[2] : v[2]) < r) {
            return 1;
        }
        return 0;
    }

    for (o = isysGObjSearchFromObjKindID_begin(19); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        if (CheckItemDead(o) != 0) {
            continue;
        }
        GetRootPosition(p, o);
        _SubVectorXYZ(d, p, pos);
        if (isNearItem(d, 50) != 0) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM(D_004BF7D0);

INCLUDE_ASM(D_004BF7E0);

INCLUDE_ASM(moveBoxAutoMatic);

INCLUDE_ASM(MoveBoxWithHoldPoint);

INCLUDE_ASM(ReInitBoxGeo);

INCLUDE_ASM(InitBoxGeo);

INCLUDE_ASM(BoxGeo);

INCLUDE_ASM(GetBoxMode);

INCLUDE_ASM(CanHoldBox);

INCLUDE_ASM(BoxDL);

INCLUDE_ASM(GetBoxGlobalHoldPoint);

INCLUDE_ASM(IsThisBoxTruck);

INCLUDE_ASM(ExecBoxMoveStartReaction);

INCLUDE_ASM(ExecBoxMoveEndReaction);

INCLUDE_ASM(BoxGeoRestore);

INCLUDE_ASM(BoxExtGeoRestore);

INCLUDE_ASM(BoxMemoryFunc);

INCLUDE_ASM(InitSwitchGeo);

INCLUDE_ASM(SwitchGeo);

INCLUDE_ASM(SwitchDL);

INCLUDE_ASM(SetSwitchTriggerFunc);

INCLUDE_ASM(SetSwitchState);

INCLUDE_ASM(SetFloorLeverWithNodePoint);

INCLUDE_ASM(CanFloorLeverPull);

INCLUDE_ASM(InitFloorLeverGeo);

INCLUDE_ASM(GetFloorLeverAngle);

INCLUDE_ASM(SetWallLeverWithNodePoint);

INCLUDE_ASM(CanWallLeverPull);

INCLUDE_ASM(IsWallLeverStatus);

INCLUDE_ASM(InitWallLeverGeo);

INCLUDE_ASM(GetWallLeverAngle);

INCLUDE_ASM(initParentize);

INCLUDE_ASM(getAlign);

INCLUDE_ASM(GetDistanceOfGObj);

INCLUDE_ASM(moveXPlus);

INCLUDE_ASM(moveXMinus);

INCLUDE_ASM(moveZPlus);

INCLUDE_ASM(moveZMinus);

INCLUDE_ASM(BoxRideFunc);

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

/* the box serial counter */
static unsigned char boxSerial = 0; /* derived name */

/* the layout record's object word packs the route number in its low half
   and the sub-box model in its high half */

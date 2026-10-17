#include "typedef.h"
#include "sugiCommon.h"
#include "debug.h"
#include "debug_exception.h"
#include "s_init.h"
#include "lineManager.h"
#include "tableSin.h"
#include <string.h>
#include <math.h>
#include "pool.h"
#include "geometryManager.h"
#include "main.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "fieldCollision.h"
#include "GifPacket.h"
#include "Matrix.h"
#include "motionManager.h"
#include "motionManager2.h"
#include <libvu0.h>
#include <assert.h>
#include "include_asm.h"

/* The head of one stream motion frame GetStreamShapeMotion reads the shape
   weights from: the weights follow the 16-byte head and skipNum 8-byte words,
   shapeNum of them, and only a frame whose shapeMode is 0 carries them. */
typedef struct StreamShapeHdr { /* field names derived */
    char pad0[1];
    signed char shapeMode;
    unsigned char skipNum;
    unsigned char shapeNum;
} StreamShapeHdr; /* derived name */

INCLUDE_ASM(GetWaterReaction);

INCLUDE_ASM(CheckFieldContact);

#define ABSF(x) ((x) < 0.0f ? -(x) : (x)) /* derived name */

/* a one-line by-value wrapper: each of the six call sites copies the plane
   into its own frame slot and passes that address */
static inline float getPlaneY(Vec4 pl, float *p) /* derived name */
{
    return GetYProjectionOfPlane(pl.f, p);
}

/* The loop counts 0..10 and offsets by 5.  `plane` is retargeted at the
   local copy, so the six by-value argument copies and the CopyVector read
   through one pointer. */
void dispPlane(Vec4 *plane, float *pos)
{
    Vec4 pl = *plane;
    Col4 tmpl = {{0x00, 0x80, 0xFF, 0x80}};
    Col4 col;
    Col4 black;
    Vec4 buf[12];
    float p0[4];
    float p1[4];
    float p2[4];
    float grid[4];
    int i;

    plane = &pl;
    memset(&black, 0, sizeof(black));
    black.c[3] = 0x80;
    CopyVector(grid, pos);
    grid[0] = (float)(int)(pos[0] / 50.0f) * 50.0f;
    grid[2] = (float)(int)(pos[2] / 50.0f) * 50.0f;
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    gif_SetAlpha(1, 5, 128);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < 11; i++) {
        float ax = 1.0f - ABSF(pos[0] - (grid[0] + (float)(i - 5) * 50.0f)) / 250.0f;
        float az = 1.0f - ABSF(pos[2] - (grid[2] + (float)(i - 5) * 50.0f)) / 250.0f;

        ax = (ax < 0.0f) ? 0.0f : ax;
        az = (az < 0.0f) ? 0.0f : az;
        CopyVector(&buf[10], plane);
        CopyIVector(col.c, tmpl.c);
        col.c[0] = (int)((float)col.c[0] * ax);
        col.c[1] = (int)((float)col.c[1] * ax);
        col.c[2] = (int)((float)col.c[2] * ax);
        CopyVector(p0, grid);
        p0[0] = p0[0] + (float)(i - 5) * 50.0f;
        p0[2] = pos[2] - 250.0f;
        p0[1] = getPlaneY(*plane, p0);
        CopyVector(p1, grid);
        p1[0] = p1[0] + (float)(i - 5) * 50.0f;
        p1[2] = pos[2] + 250.0f;
        p1[1] = getPlaneY(*plane, p1);
        CopyVector(p2, grid);
        p2[0] = p2[0] + (float)(i - 5) * 50.0f;
        p2[2] = pos[2];
        p2[1] = getPlaneY(*plane, p2);
        DrawLineG(p0, &black, p2, &col, 0);
        DrawLineG(p1, &black, p2, &col, 0);
        CopyIVector(col.c, tmpl.c);
        col.c[0] = (int)((float)col.c[0] * az);
        col.c[1] = (int)((float)col.c[1] * az);
        col.c[2] = (int)((float)col.c[2] * az);
        CopyVector(p0, grid);
        p0[0] = pos[0] - 250.0f;
        p0[2] = p0[2] + (float)(i - 5) * 50.0f;
        p0[1] = getPlaneY(*plane, p0);
        CopyVector(p1, grid);
        p1[0] = pos[0] + 250.0f;
        p1[2] = p1[2] + (float)(i - 5) * 50.0f;
        p1[1] = getPlaneY(*plane, p1);
        CopyVector(p2, grid);
        p2[0] = pos[0];
        p2[2] = p2[2] + (float)(i - 5) * 50.0f;
        p2[1] = getPlaneY(*plane, p2);
        DrawLineG(p0, &black, p2, &col, 0);
        DrawLineG(p1, &black, p2, &col, 0);
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

INCLUDE_ASM(GetOrientOfWallOfGObj);

INCLUDE_ASM(GetOrientOfCliffOfGObj);

void SetMotionDirection(GObj *self, float *dir);

INCLUDE_ASM(SetMotionDirection);

INCLUDE_ASM(_GetMotionDirection);

void SetMotionDirectionWithLimit(GObj *self, float *dir, float lim0, float lim1)
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
    sceVu0ApplyMatrix(v, m, ZUnitVector);
    SetMotionDirection(self, v);
}

INCLUDE_ASM(GetRootPosOfNextFrame);

INCLUDE_ASM_LIT(SlopeIKControl);

INCLUDE_ASM(AdjustMotionHeightToField);

INCLUDE_ASM(AdjustMotionHeightToNearestField);

void GetLowerPlaneCollision(ClipWork *w, float *pos);
static void getLowerPlaneCollisionE(ClipWork *w, float *pos);

/* inlined into AdjustMotionHeightToNearestField and InitMotionGeoInfo */
static inline int adjustMotionHeightToNearestField(struct MotRoot *r, float *pos) /* derived name */
{
    ClipWork buf;
    float p[4];

    CopyVector(p, pos);
    p[1] = p[1] - 100.0f;
    if (r->filter.o.obj != 0) {
        buf.filter = r->filter;
        getLowerPlaneCollisionE(&buf, p);
    } else {
        GetLowerPlaneCollision(&buf, p);
    }
    if (buf.floor.elem == 0) {
        return 0;
    }
    CopyVector((&r->plane), (&buf.normal));
    sceVu0CopyVector(r->footPos, buf.pt[2]);
    r->footPos[3] = 1.0f;
    return 1;
}

/* RotQuaternionZ's second parameter is `int`, not `short`: calcFootIK's dev line
   1035 passes the raw GetTableArcSin result with no sign extension, and its 1040
   site sign-extends explicitly.  InitMotionGeoInfo's site carries the (short). */

static int calcFootIK(SkelNode *skel, char *arg, int node, float scale, float ratio)
{
    float q0[4];
    float q1[4];
    float qa[4];
    float qb[4];
    float qc[4];
    float qi[4];
    float v[4];
    float dir[4];
    float qt[4];
    float qu[4];
    float qv[4];
    SkelNode *p;
    char *dstq;
    char *qk;
    float *m;
    int i;
    int j;
    int k;
    int n;
    short ang;
    short ang2;

    memset(qa, 0, 16);
    qa[3] = 1.0f;
    memset(qb, 0, 16);
    qb[3] = 1.0f;
    memset(qc, 0, 16);
    qc[3] = 1.0f;

    SetIdentityQuaternion(qi);
    RotQuaternionX(qi, -0x8000);
    RotQuaternionY(qi, -0x8000);

    i = node;
    while (i != -1) {
        MultiQuaternion(qb, arg + i * 32 + 16, qb);
        MultiQuaternion(qc, skel[i].quat, qc);
        i = skel[i].parent;
    }
    MultiQuaternion(qc, qi, qc);

    i = skel[node].parent;
    while (i != -1) {
        MultiQuaternion(qa, arg + i * 32 + 16, qa);
        i = skel[i].parent;
    }

    DivQuaternion(q0, qc, qa);
    DivQuaternion(q1, qb, qc);

    p = &skel[node];

    GetMatrixFromQuaternion(MatrixDrive_GetMatrix(), qc);
    MatrixDrive_PushMatrix();
    MultiMatrixByQuaternion(q1);
    for (n = 0; n < 2; n++) {
        j = p->child;
        if (j == -1) {
            return 0;
        }
        p = &skel[j];
        sceVu0ScaleVectorXYZ(v, p->pos, scale);
        MatrixDrive_TransMatrixV(v);
        MultiMatrixByQuaternion(arg + j * 32 + 16);
    }
    CopyVector(dir, (MatrixDrive_GetMatrix()[3]));
    MatrixDrive_PopMatrix();

    m = (float *)MatrixDrive_GetMatrix();
    sceVu0TransposeMatrix(m, m);
    sceVu0ApplyMatrix(dir, m, dir);
    sceVu0Normalize((int *)dir, (int *)dir);
    ang = GetTableArcSin(dir[1]);
    ang2 = -GetTableArcSin(dir[2]);

    CopyQuaternion(qt, qc);
    RotQuaternionZ(qt, ang);
    RotQuaternionY(qt, ang2);
    DivQuaternion(qt, qb, qt);

    dstq = arg + node * 32 + 16;
    CopyQuaternion(dstq, q0);
    RotQuaternionZ(dstq, (short)((float)ang * ratio));
    RotQuaternionY(dstq, ang2);
    MultiQuaternion(dstq, dstq, qt);

    CopyQuaternion(qv, qb);
    k = node;
    for (n = 1; n >= 0; n--) {
        k = skel[k].child;
        qk = arg + k * 32 + 16;
        MultiQuaternion(qv, qv, qk);
    }
    CopyQuaternion(qu, qa);
    MultiQuaternion(qu, qu, arg + node * 32 + 16);
    MultiQuaternion(qu, qu, arg + skel[node].child * 32 + 16);
    DivQuaternion(qk, qv, qu);
    return ang;
}

/* The motion geometry record the actor sub-object carries at its own +0xA0,
   and the default every actor starts from: the same block typedef.h's MotRoot
   describes, and its fields carry MotRoot's names (the readers and writers
   are motionManager.c's and the rootUpdates').  This build's record has no
   up vector at 0x60: InitMotionGeoInfo copies 0x3C0 bytes and copies the
   position to savePos at 0x60, last at 0x140 and clipFrom at 0x150, so from
   savePos on every field sits 0x10 below MotRoot's.  InitMotionGeoInfo
   writes the position at 0x0 and the root quaternion at 0x30.  The two hand
   records at 0x200 and 0x260 are typedef.h's HandRec.  MotRoot leaves the
   words at 0xFC to 0x10F and 0x1D0 to 0x1EF here unread; this default puts
   -1 and -1.0f there, so those words keep type-and-offset names.  The
   default is this record and not a struct MotRoot because MotRoot is 16-byte
   aligned (its plane) and the default is 8-byte aligned in the object's
   .data. */
typedef struct {     /* field names derived */
    Vec4 pos;        /* 0x0, the position InitMotionGeoInfo is handed */
    Vec4 trans;      /* 0x10 */
    Vec4 baseQuat;   /* 0x20 */
    Vec4 rot;        /* 0x30, the root quaternion */
    Vec4 motionQuat; /* 0x40 */
    short twist;     /* 0x50 */
    char pad52[2];
    float twistRate; /* 0x54 */
    char pad58[8];
    Vec4 savePos;   /* 0x60, takes a copy of the initial position */
    ObjNode hitObj; /* 0x70 */
    char pad78[8];
    Vec4 nextPos;  /* 0x80, the root position of the next frame */
    Vec4 step;     /* 0x90 */
    Vec4 itemQuat; /* 0xA0 */
    float height;  /* 0xB0 */
    char padB4[12];
    Vec4 delta;         /* 0xC0 */
    WallCfg wall;       /* 0xD0 */
    int wallCount;      /* 0xDC */
    WallCfg cliffWall;  /* 0xE0 */
    int cliffWallCount; /* 0xEC */
    WallCfg aheadWall;  /* 0xF0 */
    int wordFC;
    WallCfg wall100;
    int word10C;
    WallCfg filter; /* 0x110 */
    char pad11C[4];
    Vec4 plane;       /* 0x120, the field plane under the actor */
    int lastField;    /* 0x130 */
    void *cliffFloor; /* 0x134 */
    char pad138[8];
    Vec4 last;     /* 0x140, takes a copy of the initial position */
    Vec4 clipFrom; /* 0x150, takes a copy of the initial position */
    Vec4 stepMove; /* 0x160 */
    int standNode; /* 0x170, -1 for none */
    char pad174[12];
    Vec4 focusPos;    /* 0x180 */
    Vec4 focusLocal;  /* 0x190 */
    Vec4 fieldPos;    /* 0x1A0, the position projected onto the field plane */
    Vec4 reservePos;  /* 0x1B0 */
    float projHeight; /* 0x1C0 */
    char pad1C4[12];
    Vec4 vec1D0;
    Vec4 vec1E0;
    int liftOn;    /* 0x1F0 */
    int lifting;   /* 0x1F4 */
    float lift[2]; /* 0x1F8 */
    HandRec hand1; /* 0x200 */
    HandRec hand0; /* 0x260 */
    Vec4 armTwist; /* 0x2C0 */
    int lookMode;  /* 0x2D0 */
    char pad2D4[12];
    Vec4 lookPos; /* 0x2E0 */
    short h;      /* 0x2F0 */
    short p;      /* 0x2F2 */
    short b;      /* 0x2F4 */
    char pad2F6[2];
    int noStepSearch; /* 0x2F8 */
    int gravity;      /* 0x2FC */
    int slopeIK;      /* 0x300 */
    int stairStep;    /* 0x304 */
    int lookIK;       /* 0x308 */
    int handTurnIK;   /* 0x30C */
    int fieldWall;    /* 0x310 */
    int fuchiMode;    /* 0x314 */
    int cylinder;     /* 0x318 */
    int avgWallPlane; /* 0x31C */
    int flag330;      /* 0x320 */
    int flag334;      /* 0x324 */
    float radius;     /* 0x328 */
    float radiusTo;   /* 0x32C */
    float radiusFrom; /* 0x330 */
    char pad334[12];
    Vec4 cliffPlane; /* 0x340 */
    int handIK;      /* 0x350 */
    int stepNode;    /* 0x354 */
    char pad358[8];
    Vec4 holdPoint; /* 0x360 */
    int ropeState;  /* 0x370 */
    int fixObj;     /* 0x374 */
    int fixNode;    /* 0x378 */
    char pad37C[4];
    Vec4 fixQuat;         /* 0x380 */
    Vec4 fixPos;          /* 0x390 */
    float fixWeight;      /* 0x3A0 */
    unsigned int fixMode; /* 0x3A4 */
    float footIKRate;     /* 0x3A8 */
    float ikRate0;        /* 0x3AC */
    float handRate;       /* 0x3B0 */
    float ikRate1;        /* 0x3B4 */
    float ikRate2;        /* 0x3B8 */
    char pad3BC[4];
} MotionGeoInfo; /* derived name */

/* the record InitMotionGeoInfo copies over every new actor's geometry
   state */
static MotionGeoInfo motionGeoInfoTemplate = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    0,
    {0},
    1.0f,
    {0},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {0, -1},
    {0},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    0.0f,
    {0},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0, -1}, 0},
    -1,
    {{0, -1}, 0},
    -1,
    {{0, -1}, 0},
    -1,
    {{0, -1}, 0},
    -1,
    {{0, -1}, 0},
    {0},
    {{0.0f, -1.0f, 0.0f, 0.0f}},
    0,
    0,
    {0},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    -1,
    {0},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    0.0f,
    {0},
    {{0.0f, -1.0f, 0.0f, 0.0f}},
    {{0.0f, -1.0f, 0.0f, 0.0f}},
    1,
    0,
    {0.0f, 0.0f},
    {0,
     0,
     -1,
     {0},
     {0.0f, 0.0f, 0.0f, 1.0f},
     0,
     0,
     {0},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     0.5f,
     0,
     0},
    {0,
     0,
     -1,
     {0},
     {0.0f, 0.0f, 0.0f, 1.0f},
     0,
     0,
     {0},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     0.5f,
     0,
     0},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    0,
    {0},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    0,
    0,
    0,
    {0},
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    {0},
    {{0.0f, -1.0f, 0.0f, 0.0f}},
    1,
    0,
    {0},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    0,
    0,
    0,
    {0},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    0.0f,
    0,
    1.0f,
    0.09f,
    0.15f,
    0.1f,
    0.1f,
}; /* derived name */

/* The motion state record the actor sub-object carries at its own +0x470,
   and the default every actor starts from: the block typedef.h's MotCtrl
   describes, with MotCtrl's names at the same offsets.  SetMotionDirection
   writes the direction at 0xB0, SetMotionPlaySpeedRatio the ratio at 0x48,
   ForMotionViewer_GetCurrentMotion and ForMotionViewer_GetCurrentAnimationFrame
   read the motion at 0x30 and the frame at 0x3C, CheckPureWallAttribute,
   CheckPureCliffAttribute, CheckWallAttribute and CheckFloorAttribute the four
   attributes at 0x17C to 0x188, GetRopeHangablePos the height at 0x1A8, and
   InitMotionStateInfo itself writes the two sound groups at 0x1AC.  Its
   vectors are Vec4, so the default is 8-byte aligned; with MotCtrl's float
   arrays the template copy is a word copy with an alignment test (measured). */
typedef struct MotionStateInfo { /* field names derived */
    int stream;                  /* 0x0 */
    int oriFrom;                 /* 0x4 */
    int oriTo;                   /* 0x8 */
    int shifted;                 /* 0xC */
    int ctrlFlags;               /* 0x10 */
    unsigned int flags;          /* 0x14 */
    int shiftStop;               /* 0x18 */
    int *shiftReq;               /* 0x1C */
    int *shiftNext;              /* 0x20 */
    int shiftFrom;               /* 0x24 */
    int shiftMode;               /* 0x28 */
    int request;                 /* 0x2C */
    int motion;                  /* 0x30 */
    int noAlt;                   /* 0x34 */
    int shiftReady;              /* 0x38 */
    float animFrame;             /* 0x3C */
    float lastFrame;             /* 0x40 */
    float playTime;              /* 0x44 */
    float speedRatio;            /* 0x48 */
    float playRate;              /* 0x4C */
    float frameRatio;            /* 0x50 */
    int waterDrag;               /* 0x54 */
    int justShifted;             /* 0x58 */
    int frameEnd;                /* 0x5C */
    int keepUpdateMode;          /* 0x60 */
    int updateModeChanged;       /* 0x64 */
    int rootUpdateMode;          /* 0x68 */
    int parallelEnded;           /* 0x6C */
    int parallel;                /* 0x70 */
    int orientUpdateOff;         /* 0x74 */
    int noStand;                 /* 0x78 */
    int posReserve;              /* 0x7C */
    int loopFlag;                /* 0x80 */
    int reserveBlend;            /* 0x84 */
    int reserveMoved;            /* 0x88 */
    int step;                    /* 0x8C */
    int orientReq;               /* 0x90 */
    int lastMotion;              /* 0x94 */
    int lastNoAlt;               /* 0x98 */
    int shiftFrame;              /* 0x9C */
    int blendCount;              /* 0xA0 */
    int blendFrames;             /* 0xA4 */
    char padA8[8];
    Vec4 dir;           /* 0xB0 */
    Vec4 lastDir;       /* 0xC0 */
    int orientKind;     /* 0xD0 */
    int floorFit;       /* 0xD4 */
    int wallReact;      /* 0xD8 */
    int cliffWallCheck; /* 0xDC */
    int catchBoy;       /* 0xE0 */
    int sideWallCheck;  /* 0xE4 */
    int variation;      /* 0xE8 */
    float fallHeight;   /* 0xEC */
    float groundHeight; /* 0xF0 */
    int wallHit;        /* 0xF4 */
    int cliffEdge;      /* 0xF8 */
    int cliffWallHit;   /* 0xFC */
    int cliffBack;      /* 0x100 */
    int fieldWallHit;   /* 0x104 */
    int upperWall;      /* 0x108 */
    int sideWall;       /* 0x10C */
    float cliffHeight;  /* 0x110 */
    float cliffDist;    /* 0x114 */
    char pad118[8];
    Vec4 cliffNormal;      /* 0x120 */
    float wallFloorHeight; /* 0x130 */
    float wallTopHeight;   /* 0x134 */
    float wallDist;        /* 0x138 */
    char pad13C[4];
    Vec4 wallDir;        /* 0x140 */
    Vec4 wallNormal;     /* 0x150 */
    Vec4 sideWallNormal; /* 0x160 */
    float upperWallDist; /* 0x170 */
    float sideWallDist;  /* 0x174 */
    float cliffDepth;    /* 0x178 */
    int pureWallAttr;    /* 0x17C */
    int pureCliffAttr;   /* 0x180 */
    int wallAttr;        /* 0x184 */
    int floorAttr;       /* 0x188 */
    char pad18C[4];
    int frameFlag1;    /* 0x190 */
    int frameFlag2;    /* 0x194 */
    int trigger1;      /* 0x198 */
    int trigger1Done;  /* 0x19C */
    int trigger2;      /* 0x1A0 */
    int trigger2Done;  /* 0x1A4 */
    float ropeHangPos; /* 0x1A8 */
    int seGroup[2];    /* 0x1AC */
    int slipFlags;     /* 0x1B4 */
    int lastSlipFlags; /* 0x1B8 */
    int slipOn;        /* 0x1BC */
    int pickedWeapon;  /* 0x1C0 */
    int keepWall;      /* 0x1C4 */
    int keepStand;     /* 0x1C8 */
    int landed;        /* 0x1CC */
    float waterY;      /* 0x1D0 */
    float waterDepth;  /* 0x1D4 */
    GObj *pool;        /* 0x1D8 */
    int contactFlags;  /* 0x1DC */
} MotionStateInfo;     /* derived name */

/* the record InitMotionStateInfo copies over every new actor's motion
   state: 480 bytes in this build (its copy loop ends at 0x1E0), with the
   step at -1, the shift frame at 1 and the slip off */
static MotionStateInfo motionStateInfoTemplate = {
    -1,
    -1,
    -1,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1,
    0,
    0,
    0,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    -1,
    0,
    0,
    0,
    1,
    0,
    0,
    {0},
    {{0.0f, 0.0f, 1.0f, 0.0f}},
    {{0.0f, 0.0f, 1.0f, 0.0f}},
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    0.0f,
    0.0f,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1.5e+02f,
    0.0f,
    {0},
    {{0.0f, 0.0f, 1.0f, 1.0f}},
    0.0f,
    0.0f,
    7e+02f,
    {0},
    {{0.0f, 0.0f, 1.0f, 1.0f}},
    {{0.0f, 0.0f, 1.0f, 1.0f}},
    {{0.0f, 0.0f, 1.0f, 1.0f}},
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0,
    0,
    {0},
    0,
    0,
    0,
    0,
    0,
    0,
    1e+02f,
    {-1, -1},
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0,
    0,
}; /* derived name */

INCLUDE_ASM(InitMotionGeoInfo);

/* The skeleton-display state DispSkelton hands to dispSkeltonHierarchy
   through file scope: the object, the motion and the nodes.  Nothing reads
   skelMotion back.  The motion is held as a word: typed void *, the three
   stores in DispSkelton reorder (measured). */
static void *skelGObj; /* derived name */

static int skelMotion; /* derived name */

static SkelNode *skelNodes; /* derived name */

/* a file static; ico2/sugipon/src/motionManager.c has its own of the same
   name */
static void dispSkeltonHierarchy(int node);

INCLUDE_ASM(dispSkeltonHierarchy);

INCLUDE_ASM_LIT(GetPureVerticalPlaneOfCurrentPosition);

/* SetSkeltonDispSwitch's switch for DispSkelton's debug draw */
static int skeltonDispSwitch = 0; /* derived name */

void DispSkelton(GObj *self, void *motion)
{
    /* the skeleton, read as a void * word */
    skelNodes = *(void **)((char *)GOBJ_SUB(self) + 0x8C);
    skelMotion = (int)motion;
    skelGObj = self;

    if (skeltonDispSwitch) {
        gif_StartPacketPri(11);
        gif_SetAlpha(1, 5, 128);
        MatrixDrive_PushMatrix();
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        dispSkeltonHierarchy(0);
        MatrixDrive_PopMatrix();
        gif_EndPacket();
    }
}

/* the motion record table SlopeIKControl indexes by the IK block's 0x30
   word; the two slope rates are the only fields this file reaches.  Declared
   here: motionOrientManager.h reaches ico2/fumi's files through typedef.h,
   and commonact.c declares the table char []. */
extern const MotionDef motionKind[];

/* SlopeIKControl's two slope helpers */
static inline float getSlopeDifference(GObj *self, char *arg, Sub15C *p) /* derived name */
{
    char *q = arg + 0x10;
    float v[4];
    Vec4 up = {{0.0f, 1.0f, 0.0f, 1.0f}};
    float y0;
    float y1;

    GetRootMatrix(MatrixDrive_GetMatrix(), self);
    MultiMatrixByQuaternion(q);
    CopyVector(v, MatrixDrive_GetMatrix()[3]);
    MatrixDrive_TransMatrixV(&up);
    y0 = GetYProjectionOfPlane(p->root.plane.f, v);
    y1 = GetYProjectionOfPlane(p->root.plane.f, MatrixDrive_GetMatrix()[3]);
    return y1 - y0;
}

static inline float getSlopeRatio(float d, float rate) /* derived name */
{
    float t = d * rate;
    float r = 1.0f;

    if (t > 0.0f) {
        if (t < 0.5f) {
            r = r + t * 0.2f;
        } else {
            r = 1.1f - (t - 0.5f) * 0.45f;
        }
    } else {
        r = r + t * 0.3f;
    }
    return (r > 0.3f) ? r : 0.3f;
}

INCLUDE_ASM(SlopeIKControl);

/* the four wall corners in edge order, closed back onto corner 0, so a walk of
   i = 0..3 takes the pair (corner[i], corner[i+1]) */
static int wallLineCorner[8] = {0, 1, 3, 2, 0, 0, 0, 0}; /* derived name */

/* the colour DebugDisp1Collision draws a wall outline in: white, half alpha */
static int wallLineColor[4] = {255, 255, 255, 128}; /* derived name */

/* the same closed corner walk, used to pick the wall edge a position sits on */
static int wallEdgeCorner[8] = {0, 1, 3, 2, 0, 0, 0, 0}; /* derived name */

INCLUDE_ASM(GetPureVerticalPlaneOfCurrentPosition);

static void getVerticalElementOfWallNormal(int *self, int *p, WallCfg *cfg);

INCLUDE_ASM(GetPureVerticalPlane);

typedef struct { /* field names derived */
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4f; /* derived name */

typedef struct { /* field names derived */
    unsigned char n;
    signed char adj : 7;
    unsigned char neg : 1;
} MotS16Hdr; /* derived name */

/* 2^e as a float, built by repeated multiply/divide so the exponent can
   exceed a single shift's range */
static inline float motPow2(int e) /* derived name */
{
    float s = 1.0f;

    if (e > 0) {
        while (e >= 31) {
            s *= (float)(1 << 31);
            e -= 31;
        }
        s *= (float)(1 << e);
    } else {
        e = -e;
        while (e >= 31) {
            s /= (float)(1 << 31);
            e -= 31;
        }
        s /= (float)(1 << e);
    }
    return s;
}

/* one 16-bit mini-float (sign:1 exp:5 mantissa:10) */
static inline float motDecodeS16(int h) /* derived name */
{
    float m = (float)(h & 0x3FF) + 1024.0f;
    float s = motPow2(-((h >> 10) & 0x1F) - 10);

    if ((h >> 15) & 1) {
        m = -m;
    }
    return m * s;
}

/* the VU0 square root split in two so the Q-pipeline latency is covered by
   the vector copy in between */
static inline void motSqrtStart(float d) /* derived name */
{
    float t = 1.0f - d;

    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $6, %0\n"
                         "qmtc2.ni $6, $vf1\n"
                         ".set reorder\n"
                         :
                         : "f"(t));
    VU0_WORD(0x4A0103BD);
}

static inline float motSqrtEnd(void) /* derived name */
{
    float r;

    VU0_WAIT();
    __asm__ __volatile__(".set noreorder\n"
                         "cfc2.ni $7, $vi22\n"
                         "mtc1 $7, %0\n"
                         ".set reorder\n"
                         : "=f"(r));
    return r;
}

void _getS16MotRotElem(void *dst, void *src);

INCLUDE_ASM(_getS16MotRotElem);

INCLUDE_ASM(func_00108860);

INCLUDE_ASM(func_00109228);

typedef struct { /* field names derived */
    unsigned char n;
    unsigned char s;
    float x, y, z;
} MotElemF; /* derived name */

typedef struct { /* field names derived */
    unsigned char n;
    unsigned char s;
    unsigned short a, b, c;
} MotElemS; /* derived name */

/* the body of _getMotRotElem, which _getMotion inlines and _getMotRotElem
   calls */
static inline void getMotRotElem(char *dst, char *src) /* derived name */
{
    float sum;

    sum = *(float *)(src + 0x4) * *(float *)(src + 0x4) +
          *(float *)(src + 0x8) * *(float *)(src + 0x8) +
          *(float *)(src + 0xC) * *(float *)(src + 0xC);
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

void _getMotion(void *dst, void *m, int node, int frame);

/* the root-position copy GetMotionRootPos and GetStreamMotion both
   expand */
static inline void getRootPos(float *dst, float *src) /* derived name */
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = 1.0f;

    dst[0] = -dst[0];
    dst[1] = -dst[1];
}

int GetStreamMotion(StreamElem *dst, float *out, char *node, SkelNode *skel)
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
            _getS16MotRotElem(&dst[i], node + 0x10 + i * 8);
            if (skel[i].parent == -1) {
                MultiQuaternion(dst[i].q, quat, dst[i].q);
            }
            *(int *)&dst[i] = 0;
        }
        return 1;
    }
    for (i = 0; i < n; i++) {
        CopyVector(out, ZeroPoint);
        *(int *)&dst[i] = 0;
        CopyQuaternion(dst[i].q, quat);
    }
    return 0;
}

/* copyMotionWithNodeHrc is a nested function inside CopyMotionWithNodeHrc:
 * the parent passes it a static chain, through which it reaches
 * dst/src/flag/hrc. */
void CopyMotionWithNodeHrc(StreamElem *dst, StreamElem *src, SkelNode *hrc, int node, int flag)
{
    inline void copyMotionWithNodeHrc(int n)
    {
        dst[n] = src[n];
        if (flag == 0) {
            *(int *)&dst[n] = 250;
        }
        if (hrc[n].child != -1) {
            copyMotionWithNodeHrc(hrc[n].child);
        }
        if (hrc[n].sibling != -1) {
            copyMotionWithNodeHrc(hrc[n].sibling);
        }
    }

    dst[node] = src[node];
    if (flag == 0) {
        *(int *)&dst[node] = 250;
    }
    if (hrc[node].child != -1) {
        copyMotionWithNodeHrc(hrc[node].child);
    }
}

/* the bodies of GetMotionRootPos and GetBlendedMotionRootPos, which their
   callers inline and the two exported functions call */
static inline void getMotionRootPos(float *dst, void *motion, int idx) /* derived name */
{
    float *src = (float *)(*(int *)((char *)motion + 4) + idx * 0xC);
    getRootPos(dst, src);
}

static inline void getBlendedMotionRootPos(float *dst, float *a, float *b,
                                           float t) /* derived name */
{
    float u = 1.0f - t;
    dst[0] = a[0] * t + b[0] * u;
    dst[1] = a[1] * t + b[1] * u;
    dst[2] = a[2] * t + b[2] * u;
}

/* the bodies of GetMotion (five sites) and GetBlendedMotion (one), which
   GetFloatingMotion inlines and the two exported functions call; this
   build's turns no node about Z (GetFloatingMotion reads no file static) */
static inline void getMotion(char *dst, float *root, void *motion, int idx, unsigned char *mask,
                             int count, SkelNode *hrc) /* derived name */
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

    if (root != 0) {
        getMotionRootPos(root, motion, idx);
    }
}

static inline void getBlendedMotion(StreamElem *dst, float *root, StreamElem *a, float *rootA,
                                    StreamElem *b, float *rootB, float t, unsigned char *mask,
                                    int count) /* derived name */
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

INCLUDE_ASM(GetFloatingMotion);

void MakeMirrorMotion(StreamElem *a, SkelNode *b)
{
    int i;
    int n;
    float buf[4];
    StreamElem tmp;

    for (i = 0; b[i].mirror != -1; i++) {
        n = b[i].mirror;
        if (i < n) {
            continue;
        }
        if (i != n) {
            goto swap;
        }
        GetInverseQuaternion(buf, b[i].quat);
        MultiQuaternion(buf, buf, a[i].q);
        GetMirrorQuaternion(buf, buf, 4);
        MultiQuaternion(a[i].q, b[i].quat, buf);
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
        GetMirrorQuaternion(a[b[i].mirror].q, a[b[i].mirror].q, 4);
    }
}

/* the body of GetShapeMotion, which GetFloatingShapeMotion inlines and
   GetShapeMotion calls */
static inline void getShapeMotion(float *dst, char *motion, int idx, int count) /* derived name */
{
    int i = 0;
    int m = *(int *)motion - 1;
    idx = idx - m * (idx / m);
    for (; i < count; i++) {
        char *t = *(char **)(motion + 0x10);
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

typedef struct { /* field names derived */
    int a;
    int b;
    int c;
} WallWork; /* derived name */

INCLUDE_ASM(FeedbackWallWorkInfoToBrainSystem);

INCLUDE_ASM(GetMotionPointer);

INCLUDE_ASM(GetCollisionOfLastActiveField);

/* the body of DebugDisp1CollisionWithColor, which the next function
   inlines and DebugDisp1CollisionWithColor calls */
static inline void debugDisp1CollisionWithColor(WallCfg *cfg, void *color) /* derived name */
{
    float pts[5][4];
    int i;
    GObj *obj = cfg->o.obj;
    int sh = cfg->o.node << 6;
    int *p15c = (int *)obj->dobj;
    int v_c = p15c[0xC / 4];

    GetWallGlobalInfo(pts, pts[4], cfg->elem, (void *)(v_c + sh));
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < 4; i++) {
        DrawLineG(pts[wallLineCorner[i]], color, pts[wallLineCorner[i + 1]], color, -1);
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

void DebugDisp1Collision(WallCfg *cfg)
{
    debugDisp1CollisionWithColor(cfg, wallLineColor);
}

void DebugDisp1CollisionWithColor(WallCfg *cfg, void *color)
{
    debugDisp1CollisionWithColor(cfg, color);
}

/* the body of GetSkeltonFocusNode, which SetMotionBlendlessNode, the two
   GetDifferenceFromWall*Plane and the node fix mode setter inline and
   GetSkeltonFocusNode calls */
static inline int getSkeltonFocusNode(GObj *self, int focus) /* derived name */
{
    return GOBJ_SUB(self)->focusNodes[focus];
}

INCLUDE_ASM(SetMotionBlendlessNode);

INCLUDE_ASM(ClearMotionBlendlessNode);

INCLUDE_ASM(InitMotionStateInfo);

INCLUDE_ASM(GetSkeltonFocusNode);

INCLUDE_ASM(GetLowerPlaneCollision);

INCLUDE_ASM(SetRootUpdateMode);

INCLUDE_ASM(ForMotionViewer_GetCurrentAnimationFrame);

INCLUDE_ASM(ForMotionViewer_GetCurrentMotion);

INCLUDE_ASM(EnableMotionOrientUpdate);

INCLUDE_ASM(DisableMotionOrientUpdate);

INCLUDE_ASM(CheckFloorAttribute);

INCLUDE_ASM(CheckWallAttribute);

INCLUDE_ASM(CheckPureWallAttribute);

INCLUDE_ASM(CheckPureCliffAttribute);

int GetStreamShapeMotion(float *dst, StreamShapeHdr *hdr)
{
    int i, n, skip;
    float *src, *p;
    if (hdr->shapeMode == 0 && (skip = hdr->skipNum, (n = hdr->shapeNum)) != 0) {
        int o = skip * 8 + 0x10;
        src = (float *)o;
        p = (float *)((char *)hdr + (int)src);
        src = p;
        for (i = 0; i < n; i++)
            *dst++ = *src++;
        return 1;
    }
    return 0;
}

INCLUDE_ASM(GetDifferenceFromWallUpperField);

INCLUDE_ASM(GetDifferenceFromLastField);

INCLUDE_ASM(GetDifferenceFromLowerField);

INCLUDE_ASM(GetDifferenceFromWallLowerPlane);

INCLUDE_ASM(GetDifferenceFromWallUpperPlane);

INCLUDE_ASM(DisableChangeRootUpdateMode);

INCLUDE_ASM(EnableChangeRootUpdateMode);

INCLUDE_ASM(GetRopeHangablePos);

INCLUDE_ASM(GetMotionFrameFlag1);

INCLUDE_ASM(GetMotionFrameFlag2);

INCLUDE_ASM(GetHeightOfFieldPlaneDifference);

INCLUDE_ASM(GetHeightOfWallFromGObj);

INCLUDE_ASM(GetHeightOfCliffFromGObj);

void InitMotionRotElem(int *elem, int count)
{
    int *p;
    int i;
    if (count <= 0)
        return;
    p = elem;
    i = count;
loop:
    p[0] = 0;
    {
        int *call_arg = p + 4;
        p += 8;
        SetIdentityQuaternion(call_arg);
    }
    --i;
    if (i != 0)
        goto loop;
}

INCLUDE_ASM(SetMotionNodeFixModeParameter);

INCLUDE_ASM(GetRootProjectionPosOfGObj);

INCLUDE_ASM(SetMotionPlaySpeedRatio);

INCLUDE_ASM(ClearMotionGeometryInfo);

void SetSkeltonDispSwitch(int val)
{
    skeltonDispSwitch = val;
}

void CopyMotion(StreamElem *dst, StreamElem *src, int n)
{
    if (n <= 0)
        return;
    do {
        *dst = *src;
        n--;
        src++;
        dst++;
    } while (n != 0);
}

void GetMotionRootPos(float *dst, void *motion, int idx)
{
    getMotionRootPos(dst, motion, idx);
}

void GetBlendedMotion(StreamElem *dst, float *root, StreamElem *a, float *rootA, StreamElem *b,
                      float *rootB, float t, unsigned char *mask, int count)
{
    getBlendedMotion(dst, root, a, rootA, b, rootB, t, mask, count);
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

void GetShapeMotion(float *dst, char *motion, int idx, int count)
{
    getShapeMotion(dst, motion, idx, count);
}

/* the release bodies are empty; every call site passes the actor's GObj */
void LockForceGroundParent(GObj *gobj) {}

void UnlockForceGroundParent(GObj *gobj) {}

INCLUDE_ASM(GetOutOutsideOfWall);

void fitYToPlane(long long *src, float *dest)
{
    Vec4 buf;
    buf.ll[0] = src[0];
    buf.ll[1] = src[1];
    dest[1] = GetYProjectionOfPlane(buf.f, dest);
}

void GetBlendedMotionRootPos(float *dst, float *a, float *b,
                             float t) /* same note as GetMotionRootPos */
{
    getBlendedMotionRootPos(dst, a, b, t);
}

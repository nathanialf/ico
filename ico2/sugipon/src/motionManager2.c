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
#include <libvu0.h>
#include <assert.h>

struct Pack32 { /* field names derived */
    long long a, b, c, d;
};

typedef struct { /* field names derived */
    char _0;
    signed char f1;
    unsigned char f2;
    unsigned char f3;
} FloorAttr; /* derived name */

typedef struct { /* field names derived */
    long long d[2];
    float q[4];
} StreamElem; /* derived name */

typedef struct { /* field names derived */
    int idx;
    char pad[28];
    float q[4];
    char pad2[16];
} StreamNode; /* derived name */

int GetWaterReaction(float *outH, int *outFlag, ClipBuf *info, float *pos, float *vel, float h0,
                     float h1, float h2, float scaleIn, float amp)
{
    float drain[4];
    float waterH;
    float scale;
    float r;
    GObj *pool;

    if (outFlag != 0) {
        *outFlag = 0;
    }
    if (info->floor.n != 0) {
        if (CompareAttribute(GetFloorAttribute(info), 0x50) != 0) {
            scale = scaleIn;
            pool = info->floor.o.obj;
            waterH = GetPoolGlobalHeightDetail(pool, pos);
            GetPoolGlobalDrainVector(drain, pool);
            if (outFlag != 0) {
                if (1.0000001e-06f < VectorLengthSquare(drain)) {
                    *outFlag = 1;
                }
            }
            if (waterH < h0) {
                vel[1] = vel[1] + amp;
            } else if (waterH < h1) {
                vel[1] = vel[1] + amp * (h1 - waterH) / (h1 - h0);
            } else if (waterH < h2) {
                r = (waterH - h1) / (h2 - h1);
                vel[1] = vel[1] +
                         (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f *
                              (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1])) +
                          amp * (1.0f - r)) *
                             r;
            } else {
                vel[1] =
                    vel[1] + 60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f *
                                 (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
                scale = 1.0f;
                CopyVector(drain, ZeroVector);
            }
            vel[0] = vel[0] * scale;
            vel[1] = vel[1] * scale;
            vel[2] = vel[2] * scale;
            sceVu0AddVector(vel, vel, drain);
            AddVectorXYZ(pos, pos, vel);
            if (outH != 0) {
                *outH = waterH;
            }
            return 1;
        }
    }
    return 0;
}

#define ABSF(x) ((x) < 0.0f ? -(x) : (x)) /* derived name */

/* a one-line by-value wrapper: each of the six call sites copies the plane
   into its own frame slot and passes that address */
static inline float getPlaneY(Vec4 pl, float *p) /* derived name */
{
    return GetYProjectionOfPlane(&pl, p);
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

void GetOrientOfWallOfGObj(float *dir, GObj *obj)
{
    CopyVector(dir, obj->dobj->ctrl.wallNormal);
}

void GetOrientOfCliffOfGObj(float *dir, GObj *obj)
{
    CopyVector(dir, obj->dobj->ctrl.cliffNormal);
}

void SetMotionDirection(GObj *a0, float *a1)
{
    Sub15C *base = a0->dobj;
    struct MotCtrl *s2 = &base->ctrl;
    char *m;
    Sub15C *ctrl;
    if (a1[0] == 0.0f && a1[2] == 0.0f) {
        return;
    }
    m = (char *)base + 0x520;
    CopyVector(m, a1);
    s2->dir[1] = 0.0f;
    s2->dir[3] = 1.0f;
    sceVu0Normalize(m, m);
    ctrl = a0->dobj;
    if (*(int *)ctrl == 0) {
        return;
    }
    LocalizeDirectionOrient(a0, (int *)ctrl);
}

void _GetMotionDirection(float *dir, GObj *obj)
{
    GetGlobalDirectionOrient(dir, obj, obj->dobj->ctrl.dir);
}

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

void GetRootPosOfNextFrame(float *pos, GObj *obj)
{
    struct MotRoot *sub = &obj->dobj->root;
    CopyVector(pos, sub->move);
    SubVectorXYZ(pos, pos, sub);
}

void AdjustMotionHeightToField(GObj *obj)
{
    struct MotRoot *sub = &obj->dobj->root;
    sub->footPos[1] = GetYProjectionOfPlane(sub->plane.f, sub->footPos);
    debug_StdPrintfDummy("Adjust Motion Height To Field. --------------\n");
}

void GetLowerPlaneCollision(ClipBuf *w, float *pos)
{
    CopyVector(w->pt[0], pos);
    CopyVector(w->pt[1], w->pt[0]);
    w->pt[1][1] = w->pt[1][1] + 10000.0f;
    ClipFloor(w);
}

void getLowerPlaneCollisionE(ClipBuf *w, float *pos)
{
    CopyVector(w->pt[0], pos);
    CopyVector(w->pt[1], w->pt[0]);
    w->pt[1][1] = w->pt[1][1] + 10000.0f;
    ClipFloorE(w);
}

/* inlined into AdjustMotionHeightToNearestField and InitMotionGeoInfo */
static inline int adjustMotionHeightToNearestField(char *o, float *pos) /* derived name */
{
    ClipBuf buf;
    float p[4];
    struct MotRoot *sub = (struct MotRoot *)(o + 0xA0);

    CopyVector(p, pos);
    p[1] = p[1] - 100.0f;
    if (sub->filter.o.obj != 0) {
        buf.filter = sub->filter;
        getLowerPlaneCollisionE(&buf, p);
    } else {
        GetLowerPlaneCollision(&buf, p);
    }
    if (buf.floor.n == 0) {
        return 0;
    }
    CopyVector((&sub->plane), (&buf.normal));
    sceVu0CopyVector(sub->footPos, buf.pt[2]);
    sub->footPos[3] = 1.0f;
    return 1;
}

/* RotQuaternionZ's second parameter is `int`, not `short`: calcFootIK's dev line
   1035 passes the raw GetTableArcSin result with no sign extension, and its 1040
   site sign-extends explicitly.  InitMotionGeoInfo's site carries the (short). */

int calcFootIK(SkelNode *skel, char *arg, int node, float scale, float ratio)
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
        MultiQuaternion(qb, arg + i * 0x20 + 0x10, qb);
        MultiQuaternion(qc, skel[i].quat, qc);
        i = skel[i].parent;
    }
    MultiQuaternion(qc, qi, qc);

    i = skel[node].parent;
    while (i != -1) {
        MultiQuaternion(qa, arg + i * 0x20 + 0x10, qa);
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
        MultiMatrixByQuaternion(arg + j * 0x20 + 0x10);
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

    dstq = arg + node * 0x20 + 0x10;
    CopyQuaternion(dstq, q0);
    RotQuaternionZ(dstq, (short)((float)ang * ratio));
    RotQuaternionY(dstq, ang2);
    MultiQuaternion(dstq, dstq, qt);

    CopyQuaternion(qv, qb);
    k = node;
    for (n = 1; n >= 0; n--) {
        k = skel[k].child;
        qk = arg + k * 0x20 + 0x10;
        MultiQuaternion(qv, qv, qk);
    }
    CopyQuaternion(qu, qa);
    MultiQuaternion(qu, qu, arg + node * 0x20 + 0x10);
    MultiQuaternion(qu, qu, arg + skel[node].child * 0x20 + 0x10);
    DivQuaternion(qk, qv, qu);
    return ang;
}

/* The motion geometry record the actor sub-object carries at its own +0xA0,
   and the default every actor starts from.  InitMotionGeoInfo writes the
   position at 0x0 and the root quaternion at 0x30, SetSimplePlane builds the
   field plane at 0x130, GetRootPosOfNextFrame reads the next-frame position
   at 0x90 and AdjustMotionHeightToField projects the field position at 0x1B0
   onto that plane; the offsets with no reader keep offset names. */
typedef struct { /* field names derived */
    int f_0;     /* 0x0 */
    int node;    /* 0x4, skeleton node index, -1 when the slot has none */
} MotionGeoNode; /* derived name */

typedef struct { /* field names derived */
    int f_0;     /* 0x0 */
    int f_4;     /* 0x4 */
    int node;    /* 0x8, skeleton node index, -1 when the limb has none */
    int f_C;     /* 0xC */
    Vec4 f_10;   /* 0x10 */
    Vec4 f_20;   /* 0x20 */
    Vec4 f_30;   /* 0x30 */
    Vec4 f_40;   /* 0x40 */
    float ratio; /* 0x50 */
    float f_54;  /* 0x54 */
    float f_58;  /* 0x58 */
    float f_5C;  /* 0x5C */
} MotionGeoLimb; /* derived name */

typedef struct { /* field names derived */
    Vec4 pos;    /* 0x0, the position InitMotionGeoInfo is handed */
    Vec4 f_10;
    Vec4 f_20;
    Vec4 rot; /* 0x30, the root quaternion */
    Vec4 f_40;
    Vec4 f_50;
    Vec4 f_60;
    Vec4 f_70; /* takes a copy of the initial position */
    int f_80;
    int f_84;
    int f_88;
    int f_8C;
    Vec4 nextPos; /* 0x90, the root position of the next frame */
    Vec4 f_A0;
    Vec4 f_B0;
    Vec4 f_C0;
    Vec4 f_D0;
    MotionGeoNode nodes[9]; /* 0xE0 */
    int f_128;
    int f_12C;
    Vec4 plane; /* 0x130, the field plane under the actor */
    Vec4 f_140;
    Vec4 f_150; /* takes a copy of the initial position */
    Vec4 f_160; /* takes a copy of the initial position */
    Vec4 f_170;
    int f_180;
    int f_184;
    int f_188;
    int f_18C;
    Vec4 f_190;
    Vec4 f_1A0;
    Vec4 fieldPos; /* 0x1B0, the position projected onto the field plane */
    Vec4 f_1C0;
    Vec4 f_1D0;
    Vec4 f_1E0;
    Vec4 f_1F0;
    int f_200;
    int f_204;
    int f_208;
    int f_20C;
    MotionGeoLimb limbs[2]; /* 0x210 and 0x270 */
    Vec4 f_2D0;
    Vec4 f_2E0;
    Vec4 f_2F0;
    Vec4 f_300;
    Vec4 f_310;
    Vec4 f_320;
    Vec4 f_330;
    Vec4 f_340;
    Vec4 f_350;
    int f_360;
    int f_364;
    int f_368;
    int f_36C;
    Vec4 f_370;
    Vec4 f_380;
    Vec4 f_390;
    Vec4 f_3A0;
    float f_3B0;
    float f_3B4;
    float f_3B8;
    float f_3BC;
    float f_3C0;
    float f_3C4;
    float f_3C8;
    float f_3CC;
} MotionGeoInfo; /* derived name */

/* the record InitMotionGeoInfo copies over every new actor's geometry
   state */
static MotionGeoInfo motionGeoInfoTemplate = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 1.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    0,
    -1,
    0,
    0,
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0, -1}, {0, -1}, {0, -1}, {0, -1}, {0, -1}, {0, -1}, {0, -1}, {0, -1}, {0, -1}},
    0,
    0,
    {{0.0f, -1.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    -1,
    0,
    0,
    0,
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, -1.0f, 0.0f, 0.0f}},
    {{0.0f, -1.0f, 0.0f, 0.0f}},
    1,
    0,
    0,
    0,
    {{0,
      0,
      -1,
      0,
      {{0.0f, 0.0f, 0.0f, 1.0f}},
      {{0.0f, 0.0f, 0.0f, 0.0f}},
      {{0.0f, 0.0f, 0.0f, 1.0f}},
      {{0.0f, 0.0f, 0.0f, 1.0f}},
      0.5f,
      0.0f,
      0.0f,
      0.0f},
     {0,
      0,
      -1,
      0,
      {{0.0f, 0.0f, 0.0f, 1.0f}},
      {{0.0f, 0.0f, 0.0f, 0.0f}},
      {{0.0f, 0.0f, 0.0f, 1.0f}},
      {{0.0f, 0.0f, 0.0f, 1.0f}},
      0.5f,
      0.0f,
      0.0f,
      0.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, -1.0f, 0.0f, 0.0f}},
    1,
    0,
    0,
    0,
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, 0.0f, 1.0f}},
    0.0f,
    0.0f,
    1.0f,
    0.09f,
    0.15f,
    0.1f,
    0.1f,
    0.0f,
}; /* derived name */

/* The motion state record the actor sub-object carries at its own +0x470,
   and the default every actor starts from.  SetMotionDirection writes the
   direction at 0xB0, SetMotionPlaySpeedRatio the ratio at 0x48,
   ForMotionViewer_GetCurrentMotion and ForMotionViewer_GetCurrentAnimationFrame
   read the motion at 0x30 and the frame at 0x3C, CheckPureWallAttribute,
   CheckPureCliffAttribute, CheckWallAttribute and CheckFloorAttribute the four
   attributes at 0x17C to 0x188, GetHeightOfCliffFromGObj and
   GetOrientOfCliffOfGObj the cliff pair at 0x110 and 0x120,
   GetHeightOfWallFromGObj and GetOrientOfWallOfGObj the wall pair at 0x130 and
   0x150, GetMotionFrameFlag1 and GetMotionFrameFlag2 the flags at 0x190 and
   0x194, GetRopeHangablePos the height at 0x1A8, and InitMotionStateInfo itself
   writes the two sound groups at 0x1AC and 0x1B0; the offsets with no reader
   keep offset names. */
typedef struct { /* field names derived */
    int f_0;
    int f_4;
    int f_8;
    int f_C;
    int f_10;
    int f_14;
    int f_18;
    int f_1C;
    int f_20;
    int f_24;
    int f_28;
    int f_2C;
    int currentMotion; /* 0x30 */
    int f_34;
    int f_38;
    float currentFrame; /* 0x3C */
    float f_40;
    float f_44;
    float playSpeedRatio; /* 0x48 */
    float f_4C;
    int f_50;
    int f_54;
    int f_58;
    int f_5C;
    int rootUpdateFixed; /* 0x60, set by DisableChangeRootUpdateMode */
    int f_64;
    int f_68;
    int f_6C;
    int f_70;
    int orientUpdateFixed; /* 0x74, set by DisableMotionOrientUpdate */
    int f_78;
    int f_7C;
    int f_80;
    int f_84;
    int f_88;
    int f_8C;
    int f_90;
    int f_94;
    int f_98;
    int f_9C;
    int f_A0;
    int f_A4;
    int f_A8;
    int f_AC;
    Vec4 direction; /* 0xB0, the motion direction */
    Vec4 f_C0;
    int f_D0;
    int f_D4;
    int f_D8;
    int f_DC;
    int f_E0;
    int f_E4;
    int f_E8;
    int f_EC;
    int f_F0;
    int f_F4;
    int f_F8;
    int f_FC;
    int f_100;
    int f_104;
    int f_108;
    int f_10C;
    float cliffHeight; /* 0x110 */
    float f_114;
    float f_118;
    float f_11C;
    Vec4 cliffOrient; /* 0x120 */
    float wallHeight; /* 0x130 */
    float f_134;
    float f_138;
    float f_13C;
    Vec4 f_140;
    Vec4 wallOrient; /* 0x150 */
    Vec4 f_160;
    int f_170;
    int f_174;
    int f_178;
    int pureWallAttr;  /* 0x17C */
    int pureCliffAttr; /* 0x180 */
    int wallAttr;      /* 0x184 */
    int floorAttr;     /* 0x188 */
    int f_18C;
    int motionFrameFlag1; /* 0x190 */
    int motionFrameFlag2; /* 0x194 */
    int f_198;
    int f_19C;
    int f_1A0;
    int f_1A4;
    float ropeHangablePos; /* 0x1A8 */
    int seGroup0;          /* 0x1AC */
    int seGroup1;          /* 0x1B0 */
    int f_1B4;
    int f_1B8;
    int f_1BC;
    int f_1C0;
    int f_1C4;
    int f_1C8;
    int f_1CC;
    int f_1D0;
    int f_1D4;
    int f_1D8;
    int f_1DC;
    int f_1E0;
    int f_1E4;
    int f_1E8;
    int f_1EC;
} MotionStateInfo; /* derived name */

/* the record InitMotionStateInfo copies over every new actor's motion
   state */
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
    0,
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
    0,
    -1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    {{0.0f, 0.0f, 1.0f, 0.0f}},
    {{0.0f, 0.0f, 1.0f, 0.0f}},
    0,
    1,
    1,
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
    0,
    0,
    0,
    150.0f,
    0.0f,
    0.0f,
    0.0f,
    {{0.0f, 0.0f, 1.0f, 1.0f}},
    0.0f,
    0.0f,
    700.0f,
    0.0f,
    {{0.0f, 0.0f, 1.0f, 1.0f}},
    {{0.0f, 0.0f, 1.0f, 1.0f}},
    {{0.0f, 0.0f, 1.0f, 1.0f}},
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
    0,
    0,
    100.0f,
    -1,
    -1,
    0,
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
    0,
    0,
}; /* derived name */

void InitMotionGeoInfo(char *self, float x, float y, float z, float rx, float ry, float rz)
{
    *(MotionGeoInfo *)self = motionGeoInfoTemplate;
    *(float *)(self + 0x0) = x;
    *(float *)(self + 0x4) = y;
    *(float *)(self + 0x8) = z;
    CopyVector((self + 0x150), self);
    CopyVector((self + 0x70), self);
    CopyVector((self + 0x160), self);
    RotQuaternionY(self + 0x30, -(int)(ry * 10430.378f));
    RotQuaternionX(self + 0x30, -(int)(rx * 10430.378f));
    RotQuaternionZ(self + 0x30, (short)-(int)(rz * 10430.378f));
    RegularizeQuaternion(self + 0x30);
    adjustMotionHeightToNearestField(self - 0xA0, (float *)self);
    SetSimplePlane(self + 0x130, 0.0f, -1.0f, 0.0f, y);
    CopyVector((self + 0x1B0), self);
}

/* The skeleton-display state DispSkelton hands to dispSkeltonHierarchy
   through file scope: the object, the flag and the nodes.  Nothing reads
   skelDispFlag back. */
static void *skelGObj; /* derived name */

static int skelDispFlag; /* derived name */

static SkelNode *skelNodes; /* derived name */

/* a file static; ico2/sugipon/src/motionManager.c has its own of the same
   name */
static void dispSkeltonHierarchy(int node)
{
    if (skelNodes[node].parent != -1) {
        float o[3] = {0.0f, 0.0f, 0.0f};
        float p[3] = {skelNodes[node].pos[0], skelNodes[node].pos[1], skelNodes[node].pos[2]};
        float ax[3] = {0.0f, 5.0f, 0.0f};
        float ay[3] = {0.0f, 0.0f, 5.0f};
        float az[3] = {5.0f, 0.0f, 0.0f};
        Col4 c0 = {{0x40, 0x40, 0x40, 0x80}};
        Col4 c1 = {{0x00, 0xFF, 0x00, 0x80}};
        Col4 c2 = {{0x00, 0x80, 0xFF, 0x80}};
        Col4 c3 = {{0xFF, 0x00, 0x00, 0x80}};

        DrawLineG(o, &c0, p, &c0, -1);
        DrawLineG(o, &c0, ax, &c1, -1);
        DrawLineG(o, &c0, ay, &c2, -1);
        DrawLineG(o, &c0, az, &c3, -1);
    }
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), (char *)((GObj *)skelGObj)->dobj->nodeMtx + node * 64);
    if (skelNodes[node].child == -1) {
        float o2[3] = {0.0f, 0.0f, 0.0f};
        float e[3] = {10.0f, 0.0f, 0.0f};
        Col4 c = {{0xFF, 0xFF, 0xFF, 0x80}};

        DrawLineG(o2, &c, e, &c, -1);
    }
    if (skelNodes[node].child != -1) {
        dispSkeltonHierarchy(skelNodes[node].child);
    }
    MatrixDrive_PopMatrix();
    if (skelNodes[node].sibling != -1) {
        dispSkeltonHierarchy(skelNodes[node].sibling);
    }
}

/* SetSkeltonDispSwitch's switch for DispSkelton's debug draw */
static int skeltonDispSwitch = 0; /* derived name */

void DispSkelton(GObj *self, int a1)
{
    /* the skeleton, read as a void * word */
    skelNodes = *(void **)((char *)GOBJ_SUB(self) + 0x8C);
    skelDispFlag = a1;
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
static inline float getSlopeDifference(GObj *self, char *arg, char *p) /* derived name */
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
    y0 = GetYProjectionOfPlane(p + 0x1D0, v);
    y1 = GetYProjectionOfPlane(p + 0x1D0, MatrixDrive_GetMatrix()[3]);
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

void SlopeIKControl(GObj *self, char *arg, int a2, Vec4 *vel)
{
    struct MotCtrl *ik;
    struct MotRoot *sub;
    int n0;
    int n1;
    int rec;
    float d;
    float r0 = 1.0f;
    float r1 = 1.0f;

    ik = &GOBJ_SUB(self)->ctrl;
    sub = &GOBJ_SUB(self)->root;
    if (ik->rootUpdateMode < 3) {
        if (ik->rootUpdateMode > 0) {
            if (sub->slopeIK != 0) {
                n0 = GOBJ_SUB(self)->focusNodes[49];
                n1 = GOBJ_SUB(self)->focusNodes[45];
                if (n0 != -1 && n1 != -1) {
                    SkelNode *skel = GOBJ_SUB(self)->skel;

                    calcFootIK(skel, arg, n0, GOBJ_SUB(self)->nodes->scale[0], sub->footIKRate);
                    calcFootIK(skel, arg, n1, GOBJ_SUB(self)->nodes->scale[0], sub->footIKRate);
                    vel->f[0] = vel->f[0] * sub->footIKRate;
                    vel->f[2] = vel->f[2] * sub->footIKRate;
                }
                d = getSlopeDifference(self, arg, (char *)GOBJ_SUB(self));
                rec = ik->motion;
                r1 = getSlopeRatio(d, motionKind[rec].rate0);
                r0 = getSlopeRatio(d, motionKind[rec].rate1);
            }
        }
    }
    sub->footIKRate = sub->footIKRate +
                      (r1 - sub->footIKRate) *
                          (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.1f);
    ik->playRate = (r0 > 1.0f) ? 1.0f : r0;
}

static const char motMan2File[] = __FILE__; /* derived name */

/* AdjustRootPositionToVerticalSidePlaneOfWall was about to push into the
   wall, so the position was clipped */
static const char adjustRootClippedMsg[] =
    "AdjustRootPositionToVerticalSidePlaneOfWallが壁の中に突入させようとしたのでクリップしました\n"; /* derived name */

/* AdjustVerticalSidePlaneOfWall: the vertical walls are close together, so
   the corrected position was set to their midpoint */
static const char adjustWallMidpointMsg[] =
    "AdjustVerticalSidePlaneOfWall:垂直壁が近接しているので補正位置をその中点としました\n"; /* derived name */

static const char illegalCompressMsg[] =
    "Illegal compress formatID(%d) appeard... ignore.\n"; /* derived name */

/* the four wall corners in edge order, closed back onto corner 0, so a walk of
   i = 0..3 takes the pair (corner[i], corner[i+1]) */
static int wallLineCorner[8] = {0, 1, 3, 2, 0, 0, 0, 0}; /* derived name */

/* the colour DebugDisp1Collision draws a wall outline in: white, half alpha */
static int wallLineColor[4] = {255, 255, 255, 128}; /* derived name */

/* the same closed corner walk, used to pick the wall edge a position sits on */
static int wallEdgeCorner[8] = {0, 1, 3, 2, 0, 0, 0, 0}; /* derived name */

/* the matrix that turns a wall into the XY plane: the identity with the wall
   normal's X and Z written into the four rotation slots before every use */
static float wallAlignMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
}; /* derived name */

/* the half turn about Z every motion node's quaternion is multiplied by */
static float nodeFlipQuaternion[4] = {0.0f, 0.0f, -1.0f, 0.0f}; /* derived name */

int GetPureVerticalPlaneOfCurrentPosition(void *plane0, void *plane1, float *ptsIn, WallCfg *cfg,
                                          int flip, float *pos)
{
    float local[4][4];
    float nrm[4];
    float best[4];
    float bestNrm[4];
    float plane[4];
    float work[4];
    float *pts;
    int i;
    int bestIdx;
    int *t;
    int *tbl;
    float bestDist;
    float d;
    GObj *obj;
    int sh;
    Sub15C *p15c;
    int v_c;

    tbl = wallEdgeCorner;
    pts = (ptsIn != 0) ? ptsIn : (float *)local;
    bestIdx = -1;

    bestDist = 3.40282347e+38f;

    obj = cfg->o.obj;
    sh = cfg->o.node << 6;
    p15c = obj->dobj;
    v_c = p15c->nodeMtx;
    GetWallGlobalInfo(pts, nrm, cfg->n, v_c + sh);
    nrm[1] = 0;
    sceVu0Normalize((int *)nrm, (int *)nrm);
    t = tbl;
    for (i = 0; i < 4; i++, t++) {
        sceVu0SubVector(work, pts + t[1] * 4, pts + t[0] * 4);
        sceVu0Normalize((int *)work, (int *)work);
        sceVu0OuterProduct(work, work, nrm);
        if (flip != 0) {
            sceVu0ScaleVectorXYZ(work, work, -1.0f);
        }
        if (work[1] < -0.1f) {
            SetSimplePlane(plane, work[0], work[1], work[2],
                           -sceVu0InnerProduct(work, pts + t[0] * 4));
            d = GetYDistanceFromPlane(plane, pos);
            if (d < 0.0f) {
                d = -d;
            }
            if (d < bestDist) {
                bestIdx = i;
                CopyVector(best, work);
                CopyVector(bestNrm, nrm);
                bestDist = d;
            }
        }
    }
    if (bestIdx == -1) {
        debug_assertMessage(motMan2File, 1360, "!!");
        __assert(motMan2File, 1360, "e");
    }
    if (plane0 != 0) {
        SetSimplePlane(plane0, best[0], best[1], best[2],
                       -sceVu0InnerProduct(best, pts + tbl[bestIdx] * 4));
    }
    if (plane1 != 0) {
        SetSimplePlane(plane1, bestNrm[0], bestNrm[1], bestNrm[2],
                       -sceVu0InnerProduct(bestNrm, pts + tbl[bestIdx] * 4));
    }
    return bestIdx;
}

void getVerticalElementOfWallNormal(int *self, int *p, WallCfg *cfg)
{
    GObj *obj = cfg->o.obj;
    int sh = cfg->o.node << 6;
    Sub15C *p15c = obj->dobj;
    int v_c = p15c->nodeMtx;

    GetWallGlobalInfo(self, p, cfg->n, v_c + sh);
    p[1] = 0;
    _NormalizeVector(p, p);
}

void AdjustVerticalSidePlaneOfWall(float *out, WallCfg *cfg, float *pos, float t)
{
    float pts[4][4];
    float nrm[4];
    float v[4];
    float pa[4];
    float pb[4];
    float p0[4];
    float p1[4];
    int maxIdx;
    int minIdx;
    int i;
    float minV;
    float maxV;
    float d;
    float t2;
    float d0;
    float d1;

    t2 = t + t;
    minIdx = 0;
    maxIdx = 0;
    getVerticalElementOfWallNormal((int *)pts, (int *)nrm, cfg);
    wallAlignMatrix[0] = wallAlignMatrix[10] = nrm[2];
    wallAlignMatrix[2] = nrm[0];
    wallAlignMatrix[8] = -nrm[0];
    _SetCurrentMatrix(wallAlignMatrix);
    _ApplyCurrentMatrix(v, pts);
    maxV = minV = v[0];
    for (i = 1; i < 4; i++) {
        _ApplyCurrentMatrix(v, pts[i]);
        if (maxV < v[0]) {
            maxV = v[0];
            maxIdx = i;
        }
        if (v[0] < minV) {
            minV = v[0];
            minIdx = i;
        }
    }
    _OuterProduct(pa, YUnitVector, nrm);
    pa[3] = -_InnerProduct(pa, pts[minIdx]);
    _OuterProduct(pb, nrm, YUnitVector);
    pb[3] = -_InnerProduct(pb, pts[maxIdx]);
    d0 = plane_distance(pos, pa);
    d1 = plane_distance(pos, pb);
    d = pa[3] + pb[3];
    if (((d < 0.0f) ? -d : d) < t2) {
        GetProjectionOfPlane(p0, pa, pos);
        GetProjectionOfPlane(p1, pb, pos);
        _InterVectorXYZ(out, p0, p1, 0.5f);
        debug_StdPrintfDummy(adjustWallMidpointMsg);
    } else if (d0 < t) {
        GetProjectionOfPlaneWithKeepAway(out, pa, pos, t);
    } else if (d1 < t) {
        GetProjectionOfPlaneWithKeepAway(out, pb, pos, t);
    } else {
        CopyVector(out, pos);
    }
    out[3] = 1.0f;
}

int GetPureVerticalPlane(void *plane0, void *plane1, float *ptsIn, WallCfg *cfg, int flip)
{
    float local[4][4];
    float up[4];
    float best[4];
    float bestUp[4];
    float work[4];
    float *pts;
    int i;
    int bestIdx;
    int *t;
    int *tbl;

    tbl = wallEdgeCorner;
    pts = (ptsIn != 0) ? ptsIn : (float *)local;
    bestIdx = 0;
    getVerticalElementOfWallNormal((int *)pts, (int *)up, cfg);
    for (i = 0, t = tbl; i < 4; i++, t++) {
        sceVu0SubVector(work, pts + t[1] * 4, pts + t[0] * 4);
        sceVu0Normalize((int *)work, (int *)work);
        sceVu0OuterProduct(work, work, up);
        if (flip != 0) {
            sceVu0ScaleVectorXYZ(work, work, -1.0f);
        }
        if (i == 0 || work[1] < best[1]) {
            CopyVector(best, work);
            bestIdx = i;
            CopyVector(bestUp, up);
        }
    }
    if (plane0 != 0) {
        SetSimplePlane(plane0, best[0], best[1], best[2],
                       -sceVu0InnerProduct(best, pts + tbl[bestIdx] * 4));
    }
    if (plane1 != 0) {
        SetSimplePlane(plane1, bestUp[0], bestUp[1], bestUp[2],
                       -sceVu0InnerProduct(bestUp, pts + tbl[bestIdx] * 4));
    }
    return bestIdx;
}

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

void _getS16MotRotElem(void *dst, void *src)
{
    Vec4f v = {motDecodeS16(*(unsigned short *)((char *)src + 2)),
               motDecodeS16(*(unsigned short *)((char *)src + 4)),
               motDecodeS16(*(unsigned short *)((char *)src + 6)), 1.0f};
    float d = _InnerProduct((float *)&v, (float *)&v);
    if (d > 1.0f) {
        d = 1.0f;
    }
    motSqrtStart(d);

    *(int *)dst = *(unsigned char *)src;
    sceVu0CopyVector((char *)dst + 0x10, &v);
    *(float *)((char *)dst + 0x1C) = motSqrtEnd();
    if (*(signed char *)((char *)src + 1) < 0) {
        *(float *)((char *)dst + 0x1C) = -*(float *)((char *)dst + 0x1C);
    }
    *(float *)((char *)dst + 0x1C) += (float)((MotS16Hdr *)src)->adj * 0.001f;
}

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

/* a file-static copy of _getMotRotElem, which _getMotion inlines */
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

void _getMotion(void *dst, void *m, int node, int frame)
{
    int type;

    char *mm = (char *)m;

    type = ((unsigned char *)*(int *)(mm + 8))[node];
    switch (type) {
    default:
        debug_StdPrintfDummy(illegalCompressMsg, type);
        SetIdentityQuaternion((char *)dst + 0x10);
        break;
    case 1: {
        int off = frame * 0x10;
        getMotRotElem((char *)dst, (char *)((int *)*(int *)(mm + 0xC))[node] + off);
        break;
    }
    case 2: {
        char *p = (char *)((int *)*(int *)(mm + 0xC))[node];
        MotElemF e = {((unsigned char *)*(int *)p)[frame], *(unsigned char *)(p + 4),
                      *(float *)(p + 8), *(float *)(p + 0xC), *(float *)(p + 0x10)};
        getMotRotElem((char *)dst, (char *)&e);
        break;
    }
    case 3: {
        char *p = (char *)((int *)*(int *)(mm + 0xC))[node];
        MotElemF e = {((unsigned char *)*(int *)p)[frame], *(unsigned char *)(p + 8),
                      *(float *)(p + 0xC), *(float *)(p + 0x10), ((float *)*(int *)(p + 4))[frame]};
        getMotRotElem((char *)dst, (char *)&e);
        break;
    }
    case 4: {
        char *p = (char *)((int *)*(int *)(mm + 0xC))[node];
        _getS16MotRotElem(dst, &((MotElemS *)p)[frame]);
        break;
    }
    case 5: {
        char *p = (char *)((int *)*(int *)(mm + 0xC))[node];
        MotElemS e = {((unsigned char *)*(int *)p)[frame], *(unsigned char *)(p + 4),
                      *(unsigned short *)(p + 6), *(unsigned short *)(p + 8),
                      *(unsigned short *)(p + 0xA)};
        _getS16MotRotElem(dst, &e);
        break;
    }
    case 6: {
        char *p = (char *)((int *)*(int *)(mm + 0xC))[node];
        MotElemS e = {((unsigned char *)*(int *)p)[frame], *(unsigned char *)(p + 8),
                      *(unsigned short *)(p + 0xA), *(unsigned short *)(p + 0xC),
                      ((unsigned short *)*(int *)(p + 4))[frame]};
        _getS16MotRotElem(dst, &e);
        break;
    }
    }
}

/* a file-static copy of the root-position helper GetMotionRootPos and
   GetStreamMotion both expand */
static inline void getRootPos(float *dst, float *src) /* derived name */
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = 1.0f;

    dst[0] = -dst[0];
    dst[1] = -dst[1];
}

int GetStreamMotion(char *dst, float *out, char *node, char *info)
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
            _getS16MotRotElem(dst + i * 0x20, node + 0x10 + i * 8);
            if (*(int *)(info + 0x38 + i * 0x40) == -1) {
                MultiQuaternion(dst + i * 0x20 + 0x10, quat, dst + i * 0x20 + 0x10);
            }
            *(int *)(dst + i * 0x20) = 0;
        }
        return 1;
    }
    for (i = 0; i < n; i++) {
        CopyVector(out, ZeroPoint);
        *(int *)(dst + i * 0x20) = 0;
        CopyQuaternion(dst + i * 0x20 + 0x10, quat);
    }
    return 0;
}

/* copyMotionWithNodeHrc is a nested function inside CopyMotionWithNodeHrc:
 * the parent passes it a static chain, through which it reaches
 * dst/src/flag/hrc. */
void CopyMotionWithNodeHrc(struct Pack32 *dst, struct Pack32 *src, char *hrc, int node, int flag)
{
    inline void copyMotionWithNodeHrc(int n)
    {
        dst[n] = src[n];
        if (flag == 0) {
            *(int *)&dst[n] = 250;
        }
        if (*(int *)(hrc + n * 64 + 0x30) != -1) {
            copyMotionWithNodeHrc(*(int *)(hrc + n * 64 + 0x30));
        }
        if (*(int *)(hrc + n * 64 + 0x34) != -1) {
            copyMotionWithNodeHrc(*(int *)(hrc + n * 64 + 0x34));
        }
    }

    dst[node] = src[node];
    if (flag == 0) {
        *(int *)&dst[node] = 250;
    }
    if (*(int *)(hrc + node * 64 + 0x30) != -1) {
        copyMotionWithNodeHrc(*(int *)(hrc + node * 64 + 0x30));
    }
}

/* file-static copies of GetMotionRootPos and GetBlendedMotionRootPos, which
   their callers inline */
static inline void getMotionRootPos(float *dst, void *a1, int idx) /* derived name */
{
    float *src = (float *)(*(int *)((char *)a1 + 4) + idx * 0xC);
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

/* file-static copies of GetMotion (five sites) and GetBlendedMotion (one),
   which GetFloatingMotion inlines */
static inline void getMotion(char *dst, float *root, void *motion, int idx, unsigned char *mask,
                             int count, char *hrc) /* derived name */
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

    if (hrc != 0) {
        i = 0;
        do {
            MultiQuaternion(dst + i * 0x20 + 0x10, nodeFlipQuaternion, dst + i * 0x20 + 0x10);
            i = *(int *)(hrc + i * 0x40 + 0x34);
        } while (i != -1);
    } else {
        for (i = 0; i < count; i++) {
            MultiQuaternion(dst + i * 0x20 + 0x10, nodeFlipQuaternion, dst + i * 0x20 + 0x10);
        }
    }
    if (root != 0) {
        getMotionRootPos(root, motion, idx);
    }
}

static inline void getBlendedMotion(StreamElem *dst, float *root, StreamElem *a, float *rootA,
                                    StreamElem *b, float *rootB, unsigned char *mask, int count,
                                    float t) /* derived name */
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

void GetFloatingMotion(StreamElem *dst, float *root, void *motion, int count, unsigned char *mask,
                       char *hrc, float t)
{
    float rootA[4];
    float rootB[4];
    StreamElem buf0[count];
    StreamElem buf1[count];
    int idx;
    int idx1;
    float frac;

    t = t - (*(int *)motion - 1) * (int)(t / (*(int *)motion - 1));
    idx = (int)t;
    idx1 = idx + 1;
    frac = t - (float)idx;
    if (frac == 0.0f) {
        getMotion((char *)dst, root, motion, idx, 0, count, hrc);
        return;
    }
    if (frac < 0.5f) {
        getMotion((char *)buf0, rootA, motion, idx, 0, count, hrc);
        getMotion((char *)buf1, rootB, motion, idx1, mask, count, hrc);
        getBlendedMotion(dst, root, buf0, rootA, buf1, rootB, mask, count, 1.0f - frac);
    } else {
        getMotion((char *)buf0, rootA, motion, idx, mask, count, hrc);
        getMotion((char *)buf1, rootB, motion, idx1, 0, count, hrc);
        getBlendedMotion(dst, root, buf1, rootB, buf0, rootA, mask, count, frac);
    }
}

int MakeMirrorMotion(StreamElem *a, StreamNode *b)
{
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

/* a file-static copy of GetShapeMotion, which GetFloatingShapeMotion
   inlines */
static inline void getShapeMotion(float *dst, char *a1, int idx, int count) /* derived name */
{
    int i = 0;
    int m = *(int *)a1 - 1;
    idx = idx - m * (idx / m);
    for (; i < count; i++) {
        char *t = *(char **)(a1 + 0x10);
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

void FeedbackWallWorkInfoToBrainSystem(GObj *a0)
{
    Sub15C *p = a0->dobj;
    char *d = (char *)a0->act;
    *(WallWork *)((char *)p + 0x180) = *(WallWork *)((char *)p + 0x1A0);
    *(WallWork *)(d + 0x620) = *(WallWork *)((char *)p + 0x1A0);
}

void *GetMotionPointer(GObj *self)
{
    return (char *)self->dobj + 0x680;
}

int GetCollisionOfLastActiveField(GObj *self)
{
    return self->dobj->root.lastField;
}

int CheckFieldContact(ClipBuf *info, GObj *self, float *pos, float lim)
{
    float h;
    float dy;
    float ph;
    float d;

    if (info->floor.n != 0) {
        h = GOBJ_SUB(self)->root.move[1];
        dy = info->pt[2][1] - pos[1];
        if (CompareAttribute(GetFloorAttribute(info), 0x50) != 0) {
            if (h >= 0.0f) {
                ph = GetPoolGlobalHeight(info->floor.o.obj);
                d = info->pt[2][1] - ph;
                if (dy < lim) {
                    if (d > 0.0f) {
                        if ((GOBJ_SUB(self)->ctrl.contactFlags & 1) == 0 && h > 5.0f) {
                            SetFallDownSplash(info->floor.o.obj, self);
                            GOBJ_SUB(self)->ctrl.contactFlags |= 1;
                        }
                    }
                    return 1;
                }
                if (d > 0.0f) {
                    if (ph - pos[1] < lim * 0.8f) {
                        if ((GOBJ_SUB(self)->ctrl.contactFlags & 1) == 0 && h > 5.0f) {
                            SetFallDownSplash(info->floor.o.obj, self);
                            GOBJ_SUB(self)->ctrl.contactFlags |= 1;
                        }
                        return 2;
                    }
                }
            }
        } else {
            if (dy < lim) {
                return 1;
            }
        }
    }
    return 0;
}

/* a file-static copy of DebugDisp1CollisionWithColor, which this caller
   inlines */
static inline void debugDisp1CollisionWithColor(int *cfg, void *color) /* derived name */
{
    float pts[5][4];
    int i;
    int *obj = (int *)cfg[0];
    int sh = cfg[1] << 6;
    int *p15c = (int *)((GObj *)(obj))->dobj;
    int v_c = p15c[0xC / 4];

    GetWallGlobalInfo(pts, pts[4], cfg[2], v_c + sh);
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

void DebugDisp1Collision(int *cfg)
{
    debugDisp1CollisionWithColor(cfg, wallLineColor);
}

void DebugDisp1CollisionWithColor(int *cfg, void *color)
{
    float pts[5][4];
    int i;
    int *obj = (int *)cfg[0];
    int sh = cfg[1] << 6;
    int *p15c = (int *)((GObj *)(obj))->dobj;
    int v_c = p15c[0xC / 4];

    GetWallGlobalInfo(pts, pts[4], cfg[2], v_c + sh);
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

/* a file-static copy of GetSkeltonFocusNode, which SetMotionBlendlessNode,
   the two GetDifferenceFromWall*Plane and the node fix mode setter inline */
static inline int getSkeltonFocusNode(GObj *a0, int a1) /* derived name */
{
    return GOBJ_SUB(a0)->focusNodes[a1];
}

/* declared here: motionManager2.h does not compile in this file (conflicting types for `CopyMotionWithNodeHrc') */
extern void ClearMotionBlendlessNode(GObj *a0);

void SetMotionBlendlessNode(GObj *self, int *node)
{
    char *blend;
    int i;

    blend = self->dobj->blendless;
    ClearMotionBlendlessNode(self);
    for (i = 0; node[i] != -1; i++) {
        int idx = getSkeltonFocusNode(self, node[i]);
        if (idx != -1) {
            blend[idx] = 1;
        }
    }
}

void ClearMotionBlendlessNode(GObj *a0)
{
    int i = 0;
    char *arr = a0->dobj->blendless;
    while (i < GOBJ_SUB(a0)->skelNodeNum) {
        arr[i] = 0;
        i++;
    }
}

void InitMotionStateInfo(MotionStateInfo *self)
{
    *self = motionStateInfoTemplate;
    self->seGroup0 = soundSeGroupGet();
    self->seGroup1 = soundSeGroupGet();
}

int GetSkeltonFocusNode(GObj *a0, int a1)
{
    return GOBJ_SUB(a0)->focusNodes[a1];
}

int AdjustMotionHeightToNearestField(GObj *self)
{
    float pos[4];
    char *o = (char *)self->dobj;

    GetRootPosition(pos, self);
    return adjustMotionHeightToNearestField(o, pos);
}

void SetRootUpdateMode(GObj *self, int val)
{
    self->dobj->ctrl.rootUpdateMode = val;
}

float ForMotionViewer_GetCurrentAnimationFrame(GObj *self)
{
    return GOBJ_SUB(self)->ctrl.animFrame;
}

int ForMotionViewer_GetCurrentMotion(GObj *self)
{
    return self->dobj->ctrl.motion;
}

void EnableMotionOrientUpdate(GObj *self)
{
    self->dobj->ctrl.orientUpdateOff = 0;
}

void DisableMotionOrientUpdate(GObj *self)
{
    self->dobj->ctrl.orientUpdateOff = 1;
}

int CheckFloorAttribute(GObj *self, int attr)
{
    Sub15C *sub = self->dobj;
    return CompareAttribute(sub->ctrl.floorAttr, attr);
}

int CheckWallAttribute(GObj *self, int attr)
{
    Sub15C *sub = self->dobj;
    return CompareAttribute(sub->ctrl.wallAttr, attr);
}

int CheckPureWallAttribute(GObj *self, int attr)
{
    Sub15C *sub = self->dobj;
    return CompareAttribute(sub->ctrl.pureWallAttr, attr);
}

int CheckPureCliffAttribute(GObj *self, int attr)
{
    Sub15C *sub = self->dobj;
    return CompareAttribute(sub->ctrl.pureCliffAttr, attr);
}

int GetStreamShapeMotion(float *dst, FloorAttr *a1)
{
    int i, n, f2;
    float *src, *p;
    if (a1->f1 == 0 && (f2 = a1->f2, (n = a1->f3)) != 0) {
        int o = f2 * 8 + 0x10;
        src = (float *)o;
        p = (float *)((char *)a1 + (int)src);
        src = p;
        for (i = 0; i < n; i++)
            *dst++ = *src++;
        return 1;
    }
    return 0;
}

float GetDifferenceFromWallUpperField(GObj *a0, int a1)
{
    Sub15C *e = a0->dobj;
    int idx = (e->focusNodes)[a1];
    return GetYDistanceFromPlane(e->root.cliffPlane, (char *)e->nodeMtx + idx * 0x40 + 0x30);
}

float GetDifferenceFromLastField(GObj *a0, int a1)
{
    Sub15C *e = a0->dobj;
    int idx = (e->focusNodes)[a1];
    return GetYDistanceFromPlane(e->root.plane.f, (char *)e->nodeMtx + idx * 0x40 + 0x30);
}

float GetDifferenceFromLowerField(GObj *a0, int a1)
{
    ClipBuf buf;
    Sub15C *ctrl;
    int idx;
    ctrl = a0->dobj;
    idx = ((signed char *)ctrl->focusNodes)[a1];
    GetLowerPlaneCollision(&buf, ctrl->nodeMtx + (idx << 6) + 0x30);
    if (buf.floor.n == 0) {
        return 3.40282347e+38f;
    }
    return buf.pt[2][1] - buf.pt[0][1];
}

float GetDifferenceFromWallLowerPlane(GObj *self, int node)
{
    float pos[4];
    float pts[4][4];
    int idx;

    idx = getSkeltonFocusNode(self, node);
    GetPureVerticalPlane(pos, 0, pts, &self->dobj->root.wall, 1);
    return GetYDistanceFromPlane(pos, (char *)GOBJ_SUB(self)->nodeMtx + idx * 0x40 + 0x30);
}

float GetDifferenceFromWallUpperPlane(GObj *self, int node)
{
    float pos[4];
    float pts[4][4];
    int idx;

    idx = getSkeltonFocusNode(self, node);
    GetPureVerticalPlane(pos, 0, pts, &self->dobj->root.wall, 0);
    return GetYDistanceFromPlane(pos, (char *)GOBJ_SUB(self)->nodeMtx + idx * 0x40 + 0x30);
}

void DisableChangeRootUpdateMode(GObj *self)
{
    Sub15C *sub = self->dobj;
    sub->ctrl.keepUpdateMode = 1;
}

void EnableChangeRootUpdateMode(GObj *self)
{
    Sub15C *sub = self->dobj;
    sub->ctrl.keepUpdateMode = 0;
}

float GetRopeHangablePos(GObj *self)
{
    Sub15C *sub = self->dobj;
    return *(float *)((char *)sub + 0x618);
}

int GetMotionFrameFlag1(GObj *self)
{
    Sub15C *sub = self->dobj;
    return sub->ctrl.frameFlag1;
}

int GetMotionFrameFlag2(GObj *self)
{
    Sub15C *sub = self->dobj;
    return sub->ctrl.frameFlag2;
}

float GetHeightOfFieldPlaneDifference(GObj *a, GObj *b)
{
    Sub15C *pa;
    Sub15C *pb;
    float r1;
    float r2;
    pa = a->dobj;
    r1 = GetYProjectionOfPlane(pa->root.plane.f, pa->root.pos);
    pb = b->dobj;
    r2 = GetYProjectionOfPlane(pb->root.plane.f, pb->root.pos);
    return r1 - r2;
}

float GetHeightOfWallFromGObj(GObj *self)
{
    Sub15C *sub = self->dobj;
    return sub->ctrl.wallFloorHeight;
}

float GetHeightOfCliffFromGObj(GObj *self)
{
    Sub15C *sub = self->dobj;
    return sub->ctrl.cliffHeight;
}

void InitMotionRotElem(int *a0, int count)
{
    int *p;
    int i;
    if (count <= 0)
        return;
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
    if (i != 0)
        goto loop;
}

void SetMotionNodeFixModeParameter(GObj *self, GObj *obj, int mode, int node, void *quat, float x,
                                   float y, float z, float w)
{
    float vec[4] = {x, y, z, 1.0f};

    GOBJ_SUB(self)->root.fixObj = (int)obj;
    GOBJ_SUB(self)->root.fixNode = getSkeltonFocusNode(obj, node);
    GOBJ_SUB(self)->root.fixMode = mode;
    CopyVector(GOBJ_SUB(self)->root.fixPos, vec);
    CopyQuaternion(GOBJ_SUB(self)->root.fixQuat, quat);
    GOBJ_SUB(self)->root.fixWeight = w;
}

void GetRootProjectionPosOfGObj(float *pos, GObj *obj)
{
    GetRootPosition(pos, obj);
    pos[1] += obj->dobj->root.projHeight;
}

void SetMotionPlaySpeedRatio(GObj *self, float val)
{
    GOBJ_SUB(self)->ctrl.speedRatio = val;
}

void ClearMotionGeometryInfo(GObj *self)
{
    Sub15C *p = self->dobj;
    float *p1 = p->root.focusPos;
    struct MotRoot *p2 = &p->root;
    int ret;
    CopyVector(p1, ZeroVector);
    sceVu0AddVector(p->root.footPos, p2->pos, p1);
    ret = -1;
    p2->standNode = ret;
    return ret;
}

void SetSkeltonDispSwitch(int val)
{
    skeltonDispSwitch = val;
}

void CopyMotion(struct Pack32 *dst, struct Pack32 *src, int n)
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

void GetMotionRootPos(float *dst, void *a1, int idx)
{
    float *src = (float *)(*(int *)((char *)a1 + 4) + idx * 0xC);
    getRootPos(dst, src);
}

void GetMotion(char *dst, float *root, void *motion, int idx, unsigned char *mask, int count,
               char *hrc)
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

    if (hrc != 0) {
        i = 0;
        do {
            MultiQuaternion(dst + i * 0x20 + 0x10, nodeFlipQuaternion, dst + i * 0x20 + 0x10);
            i = *(int *)(hrc + i * 0x40 + 0x34);
        } while (i != -1);
    } else {
        for (i = 0; i < count; i++) {
            MultiQuaternion(dst + i * 0x20 + 0x10, nodeFlipQuaternion, dst + i * 0x20 + 0x10);
        }
    }
    if (root != 0) {
        getMotionRootPos(root, motion, idx);
    }
}

void GetBlendedMotion(StreamElem *dst, float *root, StreamElem *a, float *rootA, StreamElem *b,
                      float *rootB, unsigned char *mask, int count, float t)
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

void GetShapeMotion(float *dst, char *a1, int idx, int count)
{
    int i = 0;
    int m = *(int *)a1 - 1;
    idx = idx - m * (idx / m);
    for (; i < count; i++) {
        char *t = *(char **)(a1 + 0x10);
        int *elem = *(int **)(*(char **)(t + 4) + i * 4);
        if (elem != 0) {
            dst[i] = ((float *)elem)[idx];
        } else {
            dst[i] = 0;
        }
    }
}

/* the release bodies are empty; every call site passes the actor's GObj */
void LockForceGroundParent(GObj *gobj) {}

void UnlockForceGroundParent(GObj *gobj) {}

void GetOutOutsideOfWall(GObj *obj, float threshold)
{
    int buf0[4];
    int buf1[4];
    if (GOBJ_SUB(obj)->root.wall.n != 0) {
        float dot;
        GetRootPosition(buf0, obj);
        GetGlobalWallPlane(buf1, &obj->dobj->root.wall);
        /* sugiCommon.h's plane_distance */
        dot = plane_distance(buf0, buf1);
        if (dot < threshold) {
            GetProjectionOfPlaneWithKeepAway(buf0, buf1, buf0, threshold);
        }
        SetDirectRootPosition(obj, buf0);
    }
}

void AdjustRootPositionToVerticalSidePlaneOfWall(void *a0, void *a1, float f)
{
    ClipBuf buf;
    memset(&buf, 0, 0xC0);
    GetRootPosition(&buf, a0);
    AdjustVerticalSidePlaneOfWall(buf.pt[1], a1, &buf, f);
    ClipWall(&buf);
    if (buf.wall.n != 0) {
        SetDirectRootPosition(a0, buf.pt[2]);
        debug_StdPrintfDummy(adjustRootClippedMsg);
    } else {
        SetDirectRootPosition(a0, buf.pt[1]);
    }
}

void fitYToPlane(long long *src, int *dest)
{
    long long buf[2];
    buf[0] = src[0];
    buf[1] = src[1];
    *(float *)((char *)dest + 4) = GetYProjectionOfPlane((int *)buf, dest);
}

void GetBlendedMotionRootPos(float *dst, float *a, float *b,
                             float t) /* same note as GetMotionRootPos */
{
    float u = 1.0f - t;
    dst[0] = a[0] * t + b[0] * u;
    dst[1] = a[1] * t + b[1] * u;
    dst[2] = a[2] * t + b[2] * u;
}

void _getMotRotElem(char *dst, char *src)
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

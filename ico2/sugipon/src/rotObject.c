#include "rotObject.h"
#include "gamesys.h"
#include "memory.h"
#include "fieldCollision.h"
#include "DisplayP2O.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "motionManager2.h"
#include "tableSin.h"
#include "debug.h"
#include <math.h>
#include <libvu0.h>
#include "ios.h"
#include "Matrix.h"
#include "matrixDrive.h"
#include "sceneManager.h"

/* the name every iosMallocDebug in this file reports itself under */
static const char rotObjectFile[] = "src/rotObject.c"; /* derived name */

/* the phase the next rotating object's uniq-data save counter starts at,
   cycling through 30 so the objects' saves fall on different frames */
static unsigned char rotObjectPhase = 0; /* derived name */

/* the 64-byte work block InitRotObjectGeo allocates for a rotating object */
typedef struct RotObjWork { /* field names derived */
    int kind;               /* 0x00, the layout's object word: 3 for a turn limited to a range */
    char pad04[12];
    float pos[4]; /* 0x10, the layout position */
    short angle;  /* 0x20, the drive turn */
    short pad22;
    int turnCount;  /* 0x24, the turn summed over the moves, 65536 a revolution */
    float limitMax; /* 0x28, kind 3: the largest turn, from the layout's scale z */
    float limitMin; /* 0x2C, kind 3: the smallest turn, from the layout's scale x */
    int saveCount;  /* 0x30, the frame counter of the uniq-data save */
    int lock;       /* 0x34, SetRotObjectLockFlag: no move while set */
    float rate;     /* 0x38, the turn per push, the layout's scale y (1 below 0.05) */
    float armScale; /* 0x3C, 100 over the arm radius */
} RotObjWork;       /* derived name */

/* the two words MemoryRotObject saves in the object's gamesys info record and
   RestoreRotObjectExtGeo and GetRotObjectGameSysObjInfoExtData read back */
typedef struct {          /* field names derived */
    unsigned short angle; /* 0x0 */
    short pad02;
    int turnCount; /* 0x4 */
} RotObjMemory;    /* derived name */

void moveStartSE(GObj *a0, int a1, int a2, int a3)
{
    ExecuteSEPackage(a0, 0x35);
}

void moveEndSE(GObj *a0, int a1, int a2, int a3)
{
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x3A);
}

void RotObjectGeo(GObj *a0)
{
    RotObjWork *p = GOBJ_SUB(a0)->work;
    if (p->saveCount++ >= 0x1F) {
        p->saveCount = 0;
        gamesysObjInfoUniqDataSet(a0);
    }
}

static inline void getRotObjectDriveMatrix(GObj *gobj, void *dst) /* derived name */
{
    float v[4];
    Sub15C *sub = GOBJ_SUB(gobj);
    RotObjWork *w = sub->work;

    GetRootMatrix(MatrixDrive_GetMatrix(), gobj);
    MatrixDrive_RotMatrixY(w->angle);
    _ApplyMatrix(v, MatrixDrive_GetMatrix(), ZUnitVector);
    v[1] = 0.0f;
    _NormalizeVector(v, v);
    UnitRotation(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixY(atan2f(v[0], v[2]) * 10430.378f);
    CopyMatrix(dst, MatrixDrive_GetMatrix());
}

void GetRotObjectHoldPoint(void *a0, void *a1, void *a2, void *a3)
{
    char buf[96];

    GetRootPosition(buf + 0x10, a3);
    GetGlobalWallPlane(buf, a2);
    sceVu0ScaleVectorXYZ(a1, buf, -1.0f);
    *(int *)((char *)a1 + 0xC) = 0;
    AdjustVerticalSidePlaneOfWall(a0, a2, buf + 0x10, 10.0f);
    GetProjectionPosOfPlane(a0, buf, a0);
    /* the hold point trace, switched off */
    if (0) {
        debug_StdPrintfDummy("%s\n", "GetRotObjectHoldPoint");
        debug_StdPrintfDummy("\t%f, %f, %f\n", ((float *)a0)[0], ((float *)a0)[1],
                             ((float *)a0)[2]);
    }
    MatrixDrive_SetTransposeMatrix(buf + 0x20, *(int *)(*(char **)(*(int *)a2 + 0x15C) + 0xC) +
                                                   (*(int *)((char *)a2 + 4) << 6));
    sceVu0ApplyMatrix(a0, buf + 0x20, a0);
    sceVu0ApplyMatrix(a1, buf + 0x20, a1);
    *(float *)((char *)a0 + 4) = -50.0f;
    sceVu0Normalize(a1, a1);
}

int MoveRotObjectWithHoldPoint(GObj *bar, void *hold, void *self, void *dir, void *up)
{
    RotObjWork *w = GOBJ_SUB(bar)->work;
    char *gobj = (char *)bar;
    float *a1 = (float *)hold;
    float *a3 = (float *)dir;
    float *a4 = (float *)up;
    float q[4];
    float m[16];
    float tm[16];
    float p[4];
    char *h;
    float vy;
    float len;
    float sl;
    float ang;
    float k;

    if (w->lock != 0)
        return 0;
    if (*(int *)(gobj + 0x16C) == 0) {
        w->turnCount = 0;
        return 0;
    }
    getRotObjectDriveMatrix(gobj, m);
    {
        float v[4];
        float o[4];
        MatrixDrive_SetTransposeMatrix(tm, m);
        sceVu0ApplyMatrix(q, tm, a3);
        CopyVector(p, a4);
        p[1] = 0.0f;
        p[3] = 0.0f;
        _ApplyMatrix(p, tm, p);
        _OuterProduct(v, p, a1);
        vy = v[1];
        len = FSqrt(a1[0] * a1[0] + a1[2] * a1[2]);
        sceVu0ScaleVector(q, q, len / FSqrt(q[0] * q[0] + q[2] * q[2]));
        sceVu0OuterProduct(o, q, a1);
        sl = _GetLengthXZ(q, a1);
        if (o[1] < 0.0f)
            sl = -sl;
        if (sl * vy < 0.0f)
            return 0;
    }
    ang = -atan2f(sl, len);
    ang *= w->rate;
    k = len * 0.01f * w->armScale;
    if (k > 1.0f)
        k = 1.0f;
    k *= k;
    k *= k;
    ang *= k;
    switch (w->kind) {
    case 2:
        if (0.0f <= ang)
            return 0;
        break;
    case 3:
        if (*(int *)*(char **)(gobj + 0x15C) != 0) {
            float r;

            h = *(char **)(*(char **)(*(int *)*(char **)(gobj + 0x15C) + 0x15C) + 0xC);
            ((Vec4 *)(h + 0x30))->f[1] += ang * 31.83098793f;
            CopyVector(*(char **)(*(int *)*(char **)(gobj + 0x15C) + 0x15C) + 0xA0,
                       *(char **)(*(char **)(*(int *)*(char **)(gobj + 0x15C) + 0x15C) + 0xC) +
                           0x30);
            r = -((Vec4 *)(h + 0x30))->f[1];
            if (w->limitMax < r) {
                ((Vec4 *)(h + 0x30))->f[1] = -w->limitMax;
                CopyVector(*(char **)(*(int *)*(char **)(gobj + 0x15C) + 0x15C) + 0xA0,
                           *(char **)(*(char **)(*(int *)*(char **)(gobj + 0x15C) + 0x15C) + 0xC) +
                               0x30);
                return 0;
            } else if (r < w->limitMin) {
                ((Vec4 *)(h + 0x30))->f[1] = -w->limitMin;
                CopyVector(*(char **)(*(int *)*(char **)(gobj + 0x15C) + 0x15C) + 0xA0,
                           *(char **)(*(char **)(*(int *)*(char **)(gobj + 0x15C) + 0x15C) + 0xC) +
                               0x30);
                return 0;
            }
        }
        break;
    }
    /* the function's name trace, switched off */
    if (0) {
        debug_StdPrintfDummy("%s\n", "MoveRotObjectWithHoldPoint");
    }
    w->turnCount += ang * 10430.378f;
    w->angle += ang * 10430.378f;
    return 1;
}

void ExecRotObjectMoveStartReaction(GObj *a0, int a1, int a2, int a3)
{
    moveStartSE(a0, a1, a2, a3);
}

void ExecRotObjectMoveEndReaction(GObj *a0, int a1, int a2, int a3)
{
    moveEndSE(a0, a1, a2, a3);
}

void SetRotObjectArmRadius(GObj *a0, float f)
{
    RotObjWork *w = GOBJ_SUB(a0)->work;

    w->armScale = 100.0f / f;
}

void GetRotObjectGlobalHoldGeometry(void *pos, void *dir, void *gobj, void *posMtx, void *dirMtx)
{
    float m[16];

    getRotObjectDriveMatrix(gobj, m);
    sceVu0ApplyMatrix(pos, m, posMtx);
    sceVu0ApplyMatrix(dir, m, dirMtx);
    /* the function's name trace, switched off */
    if (0) {
        debug_StdPrintfDummy("%s\n", "GetRotObjectGlobalHoldGeometry");
    }
}

/* a GObj slot read as an int but written elsewhere as a float */
typedef union RotObjWord { /* field names derived */
    int i;
    float f;
} RotObjWord; /* derived name */

RotObjWork *InitRotObjectGeo(GObj *gobj, SObjSimpleSetting *src)
{
    RotObjWork *p = iosMallocDebug(ios_partition_sugipon, 64, (void *)rotObjectFile, 57);

    p->saveCount = rotObjectPhase;
    rotObjectPhase = (rotObjectPhase + 1) % 30;

    CopyVector(p->pos, src->pos);
    p->kind = src->obj;
    p->pos[3] = 1.0f;
    p->angle = src->rot[1] * 32768.0f / 180.0f;
    p->turnCount = 0;
    p->limitMax = p->limitMin = 0.0f;
    p->lock = 0;
    p->rate = src->scale[1] < 0.05f ? 1.0f : src->scale[1];
    p->armScale = 1.0f;

    if (p->kind == 3) {
        p->limitMax = src->scale[2];
        p->limitMin = src->scale[0];
        CopyVector((char *)((RotObjWord *)&gobj->dobj)->i + 0xA0, ZeroPoint);
    }
    {
        struct DObjNode *q = GOBJ_SUB(gobj)->nodes;
        q->scale[0] = q->scale[1] = q->scale[2] = 1.0f;
    }
    return p;
}

void GetRotObjectGameSysObjInfoExtData(short *a0, int *a1, GamesysObjInfo *a2)
{
    RotObjMemory *m = (RotObjMemory *)a2->work;

    *a0 = m->angle;
    *a1 = m->turnCount;
}

void RotObjectDL(GObj *gobj)
{
    getRotObjectDriveMatrix(gobj, (void *)GOBJ_SUB(gobj)->nodeMtx);
    p2o_DispVU1(gobj);
}

float GetRotObjectRotCount(GObj *a0)
{
    RotObjWork *w = GOBJ_SUB(a0)->work;

    return (float)w->turnCount * (1.0f / 65536.0f);
}

/* the +Z unit vector the drive matrix is applied to */
static float zPlusVector[4] = {0.0f, 0.0f, 1.0f, 0.0f}; /* derived name */

int GetRotObjectZPlusDirection(void *gobj)
{
    float m[16];
    float v[4];

    getRotObjectDriveMatrix(gobj, m);
    sceVu0ApplyMatrix(v, m, zPlusVector);
    v[1] = 0.0f;
    sceVu0Normalize(v, v);
    return GetTableArcTan2(v[0], v[2]);
}

int RestoreRotObjectGeo(void)
{
    return 1;
}

int RestoreRotObjectExtGeo(GObj *a0, GamesysObjInfo *a1)
{
    RotObjWork *p = GOBJ_SUB(a0)->work;
    RotObjMemory *m = (RotObjMemory *)a1->work;

    p->angle = m->angle;
    p->turnCount = m->turnCount;
    return 1;
}

int MemoryRotObject(RotObjMemory *a0, GObj *a1)
{
    RotObjWork *p = GOBJ_SUB(a1)->work;
    a0->angle = p->angle;
    a0->turnCount = p->turnCount;
    return 1;
}

void SetRotObjectLockFlag(GObj *a0, int a1)
{
    RotObjWork *w = GOBJ_SUB(a0)->work;

    w->lock = a1;
}

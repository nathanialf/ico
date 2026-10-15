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
#include "include_asm.h"

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
typedef struct RotObjMemory { /* field names derived */
    unsigned short angle;     /* 0x0 */
    short pad02;
    int turnCount; /* 0x4 */
} RotObjMemory;    /* derived name */

static void moveStartSE(GObj *self)
{
    ExecuteSEPackage(self, 51);
}

INCLUDE_ASM(moveEndSE);

void RotObjectGeo(GObj *self)
{
    RotObjWork *p = GOBJ_SUB(self)->work;
    if (p->saveCount++ >= 31) {
        p->saveCount = 0;
        gamesysObjInfoUniqDataSet(self);
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

void GetRotObjectHoldPoint(void *pos, void *dir, WallCfg *wall, GObj *holder)
{
    struct { /* field names derived */
        float plane[4];
        float pos[4];
        float mtx[4][4];
    } buf;

    GetRootPosition(buf.pos, holder);
    GetGlobalWallPlane(buf.plane, wall);
    sceVu0ScaleVectorXYZ(dir, buf.plane, -1.0f);
    *(int *)((char *)dir + 0xC) = 0;
    AdjustVerticalSidePlaneOfWall(pos, wall, buf.pos, 10.0f);
    GetProjectionPosOfPlane(pos, buf.plane, pos);
    /* the hold point trace, switched off */
    if (0) {
        debug_StdPrintfDummy("%s\n", "GetRotObjectHoldPoint");
        debug_StdPrintfDummy("\t%f, %f, %f\n", ((float *)pos)[0], ((float *)pos)[1],
                             ((float *)pos)[2]);
    }
    MatrixDrive_SetTransposeMatrix(buf.mtx,
                                   (char *)GOBJ_SUB(wall->o.obj)->nodeMtx + (wall->o.node << 6));
    sceVu0ApplyMatrix(pos, buf.mtx, pos);
    sceVu0ApplyMatrix(dir, buf.mtx, dir);
    *(float *)((char *)pos + 4) = -50.0f;
    sceVu0Normalize(dir, dir);
}

INCLUDE_ASM(MoveRotObjectWithHoldPoint);

INCLUDE_ASM(ExecRotObjectMoveStartReaction);

INCLUDE_ASM(ExecRotObjectMoveEndReaction);

INCLUDE_ASM(GetRotObjectGlobalHoldGeometry);

INCLUDE_ASM(InitRotObjectGeo);

void RotObjectDL(GObj *gobj)
{
    getRotObjectDriveMatrix(gobj, (void *)GOBJ_SUB(gobj)->nodeMtx);
    p2o_DispVU1(gobj);
}

float GetRotObjectRotCount(GObj *self)
{
    RotObjWork *w = GOBJ_SUB(self)->work;

    return (float)w->turnCount * (1.0f / 65536.0f);
}

/* the +Z unit vector the drive matrix is applied to */
static float zPlusVector[4] = {0.0f, 0.0f, 1.0f, 0.0f}; /* derived name */

int GetRotObjectZPlusDirection(GObj *gobj)
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

INCLUDE_ASM(RestoreRotObjectExtGeo);

INCLUDE_ASM(MemoryRotObject);

void SetRotObjectLockFlag(GObj *self, int lock)
{
    RotObjWork *w = GOBJ_SUB(self)->work;

    w->lock = lock;
}

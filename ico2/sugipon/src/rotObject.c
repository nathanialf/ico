#include "common.h"
#include "rotObject.h"
#include "gamesys.h"
#include "memory.h"
#include "fieldCollision.h"
#include "DisplayP2O.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "motionManager2.h"
#include "tableSin.h"
#include <math.h>
#include <libvu0.h>

void moveStartSE(int a0, int a1, int a2, int a3)
{
    ExecuteSEPackage(a0, 0x35);
}

void moveEndSE(int a0, int a1, int a2, int a3)
{
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x3A);
}

void RotObjectGeo(char *a0)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    if ((*(int *)(p + 0x30))++ >= 0x1F) {
        *(int *)(p + 0x30) = 0;
        gamesysObjInfoUniqDataSet(a0);
    }
}

/* kept local: this TU's uses of MatrixDrive_GetMatrix do not fit the prototype in matrixDrive.h */
extern void *MatrixDrive_GetMatrix(void);
/* kept local: this TU's uses of MatrixDrive_RotMatrixY do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_RotMatrixY(short a0);
/* kept local: this TU's uses of UnitRotation do not fit the prototype in matrixDrive.h */
extern void UnitRotation(void *m);
/* kept local: this TU's uses of CopyMatrix do not fit the prototype in matrixDrive.h */
extern void CopyMatrix(void *dst, void *src);
/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(void *dst, void *m, void *src);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *dst, void *src);
/* kept local: this TU's uses of ZUnitVector do not fit the prototype in matrixDrive.h */
extern char ZUnitVector[];

static inline void getRotObjectDriveMatrix(void *gobj, void *dst)
{
    float v[4];
    Sub15C *sub = GOBJ_SUB(gobj);
    char *w = *(char **)((char *)sub + 0x830);

    GetRootMatrix(MatrixDrive_GetMatrix(), gobj);
    MatrixDrive_RotMatrixY(*(short *)(w + 0x20));
    _ApplyMatrix(v, MatrixDrive_GetMatrix(), ZUnitVector);
    v[1] = 0.0f;
    _NormalizeVector(v, v);
    UnitRotation(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixY(atan2f(v[0], v[2]) * 10430.378f);
    CopyMatrix(dst, MatrixDrive_GetMatrix());
}

/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *a0, int a1);

void GetRotObjectHoldPoint(void *a0, void *a1, void *a2, void *a3)
{
    char buf[0x60];

    GetRootPosition(buf + 0x10, a3);
    GetGlobalWallPlane(buf, a2);
    sceVu0ScaleVectorXYZ(a1, buf, -1.0f);
    *(int *)((char *)a1 + 0xC) = 0;
    AdjustVerticalSidePlaneOfWall(a0, a2, buf + 0x10, 10.0f);
    GetProjectionPosOfPlane(a0, buf, a0);
    MatrixDrive_SetTransposeMatrix(buf + 0x20, *(int *)(*(char **)(*(int *)a2 + 0x15C) + 0xC) +
                                                   (*(int *)((char *)a2 + 4) << 6));
    sceVu0ApplyMatrix(a0, buf + 0x20, a0);
    sceVu0ApplyMatrix(a1, buf + 0x20, a1);
    *(float *)((char *)a0 + 4) = -50.0f;
    sceVu0Normalize(a1, a1);
}

/* MoveRotObjectWithHoldPoint owns the first four words of this TU's .lit4 run
 * (VMA 0x639680..0x63968C); reserve them until it lands in C. */
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/rotObject", MoveRotObjectWithHoldPoint);

void ExecRotObjectMoveStartReaction(int a0, int a1, int a2, int a3)
{
    moveStartSE(a0, a1, a2, a3);
}

void ExecRotObjectMoveEndReaction(int a0, int a1, int a2, int a3)
{
    moveEndSE(a0, a1, a2, a3);
}

void SetRotObjectArmRadius(char *a0, float f)
{
    *(float *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x3C) = 100.0f / f;
}

void GetRotObjectGlobalHoldGeometry(void *pos, void *dir, void *gobj, void *posMtx, void *dirMtx)
{
    float m[16];

    getRotObjectDriveMatrix(gobj, m);
    sceVu0ApplyMatrix(pos, m, posMtx);
    sceVu0ApplyMatrix(dir, m, dirMtx);
}

/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector(void *dst, void *src);
extern int D_0063A438;
extern const char D_00620AE8[];
extern unsigned char D_0063BAB0;
/* kept local: this TU's uses of ZeroPoint do not fit the prototype in matrixDrive.h */
extern char ZeroPoint[];

/* A GObj slot read as an int but written elsewhere as a float: reading it
 * through the union keeps both views in one alias set, so the reload of
 * gobj->_15C stays behind the float stores it follows (COOKBOOK 8.26/8.32). */
typedef union RotObjWord {
    int i;
    float f;
} RotObjWord;

char *InitRotObjectGeo(char *gobj, char *src)
{
    char *p = iosMallocDebug(D_0063A438, 0x40, (void *)D_00620AE8, 57);

    *(int *)(p + 0x30) = D_0063BAB0;
    D_0063BAB0 = (D_0063BAB0 + 1) % 30;

    CopyVector(p + 0x10, src);
    *(int *)p = *(int *)(src + 0x30);
    *(float *)(p + 0x1C) = 1.0f;
    *(short *)(p + 0x20) = *(float *)(src + 0x14) * 32768.0f / 180.0f;
    *(int *)(p + 0x24) = 0;
    *(float *)(p + 0x28) = *(float *)(p + 0x2C) = 0.0f;
    *(int *)(p + 0x34) = 0;
    *(float *)(p + 0x38) = *(float *)(src + 0x24) < 0.05f ? 1.0f : *(float *)(src + 0x24);
    *(float *)(p + 0x3C) = 1.0f;

    if (*(int *)p == 3) {
        *(float *)(p + 0x28) = *(float *)(src + 0x28);
        *(float *)(p + 0x2C) = *(float *)(src + 0x20);
        CopyVector((char *)((RotObjWord *)(gobj + 0x15C))->i + 0xA0, ZeroPoint);
    }
    {
        char *q = (char *)GOBJ_SUB(gobj)->p_870;
        *(float *)(q + 0x20) = *(float *)(q + 0x24) = *(float *)(q + 0x28) = 1.0f;
    }
    return p;
}

void GetRotObjectGameSysObjInfoExtData(short *a0, int *a1, char *a2)
{
    *a0 = *(unsigned short *)(a2 + 0x30);
    *a1 = *(int *)(a2 + 0x34);
}

void RotObjectDL(void *gobj)
{
    getRotObjectDriveMatrix(gobj, *(void **)((char *)GOBJ_SUB(gobj) + 0xC));
    p2o_DispVU1(gobj);
}

float GetRotObjectRotCount(char *a0)
{
    return (float)*(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x24) * (1.0f / 65536.0f);
}

extern char D_004ECF90[];

int GetRotObjectZPlusDirection(void *gobj)
{
    float m[16];
    float v[4];

    getRotObjectDriveMatrix(gobj, m);
    sceVu0ApplyMatrix(v, m, D_004ECF90);
    v[1] = 0.0f;
    sceVu0Normalize(v, v);
    return GetTableArcTan2(v[0], v[2]);
}

int RestoreRotObjectGeo(void)
{
    return 1;
}

int RestoreRotObjectExtGeo(char *a0, char *a1)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    *(short *)(p + 0x20) = *(unsigned short *)(a1 + 0x30);
    *(int *)(p + 0x24) = *(int *)(a1 + 0x34);
    return 1;
}

int MemoryRotObject(char *a0, char *a1)
{
    char *p = *(char **)((char *)GOBJ_SUB(a1) + 0x830);
    *(short *)a0 = *(unsigned short *)(p + 0x20);
    *(int *)(a0 + 4) = *(int *)(p + 0x24);
    return 1;
}

void SetRotObjectLockFlag(char *a0, int a1)
{
    *(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x34) = a1;
}

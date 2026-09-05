#include "common.h"

extern void ExecuteSEPackage(int a0, int a1);
void moveStartSE(int a0, int a1, int a2, int a3) {
    ExecuteSEPackage(a0, 0x35);
}
extern void StopSEPackage(int a0);
extern void ExecuteSEPackage(int a0, int a1);
void moveEndSE(int a0, int a1, int a2, int a3) {
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x3A);
}
extern void gamesysObjInfoUniqDataSet(void *a0);
void RotObjectGeo(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if ((*(int *)(p + 0x30))++ >= 0x1F) {
        *(int *)(p + 0x30) = 0;
        gamesysObjInfoUniqDataSet(a0);
    }
}
extern void *MatrixDrive_GetMatrix(void);
extern void GetRootMatrix(void *m, void *gobj);
extern void MatrixDrive_RotMatrixY(short a0);
extern void UnitRotation(void *m);
extern void CopyMatrix(void *dst, void *src);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern void _NormalizeVector(void *dst, void *src);
extern void p2o_DispVU1(void *gobj);
extern float atan2f(float y, float x);
extern char D_0028FF30[];

static inline void getRotObjectDriveMatrix(void *gobj, void *dst)
{
    float v[4];
    char *sub = *(char **)((char *)gobj + 0x15C);
    char *w = *(char **)(sub + 0x830);

    GetRootMatrix(MatrixDrive_GetMatrix(), gobj);
    MatrixDrive_RotMatrixY(*(short *)(w + 0x20));
    _ApplyMatrix(v, MatrixDrive_GetMatrix(), D_0028FF30);
    v[1] = 0.0f;
    _NormalizeVector(v, v);
    UnitRotation(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixY(atan2f(v[0], v[2]) * 10430.378f);
    CopyMatrix(dst, MatrixDrive_GetMatrix());
}

extern void AdjustVerticalSidePlaneOfWall(void *a0, void *a1, void *a2, float a3);
extern void GetGlobalWallPlane(void *a0, void *a1);
extern void GetProjectionPosOfPlane(void *a0, void *a1, void *a2);
extern void GetRootPosition(void *a0, void *a1);
extern void MatrixDrive_SetTransposeMatrix(void *a0, int a1);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);

void GetRotObjectHoldPoint(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x60];

    GetRootPosition(buf + 0x10, a3);
    GetGlobalWallPlane(buf, a2);
    sceVu0ScaleVectorXYZ(a1, buf, -1.0f);
    *(int *)((char *)a1 + 0xC) = 0;
    AdjustVerticalSidePlaneOfWall(a0, a2, buf + 0x10, 10.0f);
    GetProjectionPosOfPlane(a0, buf, a0);
    MatrixDrive_SetTransposeMatrix(buf + 0x20,
        *(int *)(*(char **)(*(int *)a2 + 0x15C) + 0xC) + (*(int *)((char *)a2 + 4) << 6));
    sceVu0ApplyMatrix(a0, buf + 0x20, a0);
    sceVu0ApplyMatrix(a1, buf + 0x20, a1);
    *(float *)((char *)a0 + 4) = -50.0f;
    sceVu0Normalize(a1, a1);
}
/* MoveRotObjectWithHoldPoint owns the first four words of this TU's .lit4 run
 * (VMA 0x639680..0x63968C); reserve them until it lands in C. */
ASM_LIT4_SLOT(D_00639680, 10430.378f);
ASM_LIT4_SLOT(D_00639684, 0.01f);
ASM_LIT4_SLOT(D_00639688, 31.83098793f);
ASM_LIT4_SLOT(D_0063968C, 10430.378f);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", MoveRotObjectWithHoldPoint);
extern void moveStartSE();

void ExecRotObjectMoveStartReaction(int a0, int a1, int a2, int a3)
{
    moveStartSE(a0, a1, a2, a3);
}
extern void moveEndSE();

void ExecRotObjectMoveEndReaction(int a0, int a1, int a2, int a3)
{
    moveEndSE(a0, a1, a2, a3);
}
void SetRotObjectArmRadius(char *a0, float f) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x3C) = 100.0f / f;
}
void GetRotObjectGlobalHoldGeometry(void *pos, void *dir, void *gobj, void *posMtx, void *dirMtx)
{
    float m[16];

    getRotObjectDriveMatrix(gobj, m);
    sceVu0ApplyMatrix(pos, m, posMtx);
    sceVu0ApplyMatrix(dir, m, dirMtx);
}
extern void *iosMallocDebug(int handle, int size, void *file, int line);
extern void CopyVector(void *dst, void *src);
extern int D_0063A438;
extern const char D_00620AE8[];
extern unsigned char D_0063BAB0;
extern char D_0028FF00[];

/* A GObj slot read as an int but written elsewhere as a float: reading it
 * through the union keeps both views in one alias set, so the reload of
 * gobj->_15C stays behind the float stores it follows (COOKBOOK 8.26/8.32). */
typedef union RotObjWord { int i; float f; } RotObjWord;

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
        CopyVector((char *)((RotObjWord *)(gobj + 0x15C))->i + 0xA0, D_0028FF00);
    }
    {
        char *q = *(char **)(*(char **)(gobj + 0x15C) + 0x870);
        *(float *)(q + 0x20) = *(float *)(q + 0x24) = *(float *)(q + 0x28) = 1.0f;
    }
    return p;
}
void GetRotObjectGameSysObjInfoExtData(short *a0, int *a1, char *a2) {
    *a0 = *(unsigned short *)(a2 + 0x30);
    *a1 = *(int *)(a2 + 0x34);
}
void RotObjectDL(void *gobj)
{
    getRotObjectDriveMatrix(gobj, *(void **)(*(char **)((char *)gobj + 0x15C) + 0xC));
    p2o_DispVU1(gobj);
}
float GetRotObjectRotCount(char *a0) {
    return (float)*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x24) * (1.0f / 65536.0f);
}
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);
extern void sceVu0Normalize(void *dst, void *src);
extern int GetTableArcTan2(float f12, float f13);
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
int RestoreRotObjectExtGeo(char *a0, char *a1) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(short *)(p + 0x20) = *(unsigned short *)(a1 + 0x30);
    *(int *)(p + 0x24) = *(int *)(a1 + 0x34);
    return 1;
}
int MemoryRotObject(char *a0, char *a1) {
    char *p = *(char **)(*(char **)(a1 + 0x15C) + 0x830);
    *(short *)a0 = *(unsigned short *)(p + 0x20);
    *(int *)(a0 + 4) = *(int *)(p + 0x24);
    return 1;
}
void SetRotObjectLockFlag(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x34) = a1;
}

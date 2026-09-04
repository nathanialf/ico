#include "common.h"

/* rotObject 0x7F0 view (local) */
typedef struct { char _0[0x24]; int f_24; } RotGeo;

extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void GetGlobalWallPlane(void *a0, void *a1);
extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);
extern void SlopeIKControl(void *a0, void *a1, void *a2, float a3);
extern void GetProjectionPosOfPlane(void *a0, void *a1, void *a2);
extern void MatrixDrive_TransMatrix(void *a0, int a1);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);

void moveStartSE(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x60];

    GetRootMatrixByDObj(buf + 0x10, a3);
    GetGlobalWallPlane(buf, a2);
    sceVu0ScaleVectorXYZ(a1, buf, -1.0f);
    *(int *)((char *)a1 + 0xC) = 0;
    SlopeIKControl(a0, a2, buf + 0x10, 10.0f);
    GetProjectionPosOfPlane(a0, buf, a0);
    MatrixDrive_TransMatrix(buf + 0x20,
        *(int *)(*(char **)(*(int *)a2 + 0x15C) + 0xC) + (*(int *)((char *)a2 + 4) << 6));
    sceVu0ApplyMatrix(a0, buf + 0x20, a0);
    sceVu0ApplyMatrix(a1, buf + 0x20, a1);
    *(float *)((char *)a0 + 4) = -50.0f;
    sceVu0Normalize(a1, a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", moveEndSE);

extern void func_001E6B78(int a0);

void RotObjectGeo(int a0) {
    func_001E6B78(a0);
}

extern void func_001E6B80(void);

void getRootMatrix(void) {
    func_001E6B80();
}

extern void func_001E6BE0();
extern void sceVu0ApplyMatrix();

void RotObjectDL(int a0, int a1, void *a2, int a3, int a4) {
    char buf[0x40];
    func_001E6BE0(buf, a2);
    sceVu0ApplyMatrix(a0, buf, a3);
    sceVu0ApplyMatrix(a1, buf, a4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", GetRotObjectHoldPoint);

float MoveRotObjectWithHoldPoint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    RotGeo *q = *(RotGeo **)((char *)p + 0x7F0);
    return (float)q->f_24 * (1.0f / 65536.0f);
}

extern void sceVu0Normalize(void *a0, void *a1);
extern int GetTableArcTan2(float f12, float f13);
extern char D_004C2190[];

void ExecRotObjectMoveStartReaction(void *a0) {
    char buf[0x50];
    func_001E6BE0(buf, a0);
    sceVu0ApplyMatrix(buf + 0x40, buf, D_004C2190);
    *(int *)(buf + 0x44) = 0;
    sceVu0Normalize(buf + 0x40, buf + 0x40);
    GetTableArcTan2(*(float *)(buf + 0x40), *(float *)(buf + 0x48));
}

int ExecRotObjectMoveEndReaction(void) {
    return 1;
}

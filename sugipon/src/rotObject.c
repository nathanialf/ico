#include "common.h"

/* rotObject 0x7F0 view (local) */
typedef struct { char _0[0x24]; int f_24; } RotGeo;

extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void func_00166AF8(void *a0, void *a1);
extern void func_00240968(void *a0, void *a1, float a2);
extern void SlopeIKControl(void *a0, void *a1, void *a2, float a3);
extern void func_001046C8(void *a0, void *a1, void *a2);
extern void MatrixDrive_TransMatrix(void *a0, int a1);
extern void func_0023FDD8(void *a0, void *a1, void *a2);
extern void func_0023FE98(void *a0, void *a1);

void moveStartSE(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x60];

    GetRootMatrixByDObj(buf + 0x10, a3);
    func_00166AF8(buf, a2);
    func_00240968(a1, buf, -1.0f);
    *(int *)((char *)a1 + 0xC) = 0;
    SlopeIKControl(a0, a2, buf + 0x10, 10.0f);
    func_001046C8(a0, buf, a0);
    MatrixDrive_TransMatrix(buf + 0x20,
        *(int *)(*(char **)(*(int *)a2 + 0x15C) + 0xC) + (*(int *)((char *)a2 + 4) << 6));
    func_0023FDD8(a0, buf + 0x20, a0);
    func_0023FDD8(a1, buf + 0x20, a1);
    *(float *)((char *)a0 + 4) = -50.0f;
    func_0023FE98(a1, a1);
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
extern void func_0023FDD8();

void RotObjectDL(int a0, int a1, void *a2, int a3, int a4) {
    char buf[0x40];
    func_001E6BE0(buf, a2);
    func_0023FDD8(a0, buf, a3);
    func_0023FDD8(a1, buf, a4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", GetRotObjectHoldPoint);

float MoveRotObjectWithHoldPoint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    RotGeo *q = *(RotGeo **)((char *)p + 0x7F0);
    return (float)q->f_24 * (1.0f / 65536.0f);
}

extern void func_0023FE98(void *a0, void *a1);
extern int func_0010EF98(float f12, float f13);
extern char D_004C2190[];

void ExecRotObjectMoveStartReaction(void *a0) {
    char buf[0x50];
    func_001E6BE0(buf, a0);
    func_0023FDD8(buf + 0x40, buf, D_004C2190);
    *(int *)(buf + 0x44) = 0;
    func_0023FE98(buf + 0x40, buf + 0x40);
    func_0010EF98(*(float *)(buf + 0x40), *(float *)(buf + 0x48));
}

int ExecRotObjectMoveEndReaction(void) {
    return 1;
}

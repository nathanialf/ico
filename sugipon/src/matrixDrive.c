#include "common.h"
#include "r5900.h"
#include "vu0.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", InitMatrixDrive);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_PushMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_RotMatrixX);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_RotMatrixY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_RotMatrixZ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_ScaleMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_TurnViewMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_PushMatrixWithNoCopy);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_PopMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetLastMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_TransMatrixV);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_TransMatrix);

void MatrixDrive_TurnObjectMatrix(void *a0, void *a1) {
    QCOPY16("$a2");
}

void MatrixDrive_TurnXObjectMatrixZY(void *a0, void *a1) {
    QCOPY16("$a2");
}

void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src) {
    QCOPY64_SERIAL("$6");
}

void MatrixDrive_TurnYObjectMatrixXZ(void *a0, void *a1) {
    MAP_A0_TO_SPR();
    QCOPY64_SERIAL("$a2");
}

void MatrixDrive_TurnZObjectMatrixXY(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, 4);
    VU0_NOP();
}

void MatrixDrive_GetTurnXAngleZY(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vsub.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, 4);
    VU0_NOP();
}

typedef int Qw128 __attribute__((mode(TI)));
typedef struct { char pad[0x30]; Qw128 q; } MatDrive;
extern void func_002400F8(void *);

void MatrixDrive_GetTurnXAngleYZ(MatDrive *a0) {
    Qw128 tmp[1];
    void *p = &a0->q;
    LQ16_FROM(p);
    SQ16_TO(tmp);
    func_002400F8(a0);
    LQ16_FROM(tmp);
    SQ16_TO(p);
}

float MatrixDrive_GetTurnYAngleXZ(float a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf4\n"
        ".word 0x4A0403BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2", "$8");
    return ret;
}

float MatrixDrive_GetTurnYEAngleXZ(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "vmul.xyz $vf4, $vf4, $vf4\n"
        "vaddy.x $vf4, $vf4, $vf4y\n"
        "vaddz.x $vf4, $vf4, $vf4z\n"
        ".word 0x4A0403BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

float MatrixDrive_GetTurnZAngleXY(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf3, 0x0($4)\n"
        "vmul.xyz $vf3, $vf3, $vf3\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        "qmfc2.ni $2, $vf3\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnZAngleYX);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnMinusZAngleXY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_SetTransposeMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", CopyVector);

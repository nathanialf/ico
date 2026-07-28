#include "common.h"




extern void func_00243AE8();
#include "vu0.h"
#include "r5900.h"
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", InitMatrixDrive);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_PushMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_RotMatrixX);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_RotMatrixY);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_RotMatrixZ);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_ScaleMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnViewMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_PushMatrixWithNoCopy);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_PopMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetLastMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TransMatrixV);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TransMatrix);

void MatrixDrive_TurnObjectMatrix(void *dst, void *src)
{
    QCOPY16("$a2");
}

void MatrixDrive_TurnXObjectMatrixZY(void *dst, void *src)
{
    QCOPY16("$a2");
}

void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src)
{
    QCOPY64_SERIAL("$a2");
}

void MatrixDrive_TurnYObjectMatrixXZ(void *dst, void *src)
{
    MAP_A0_TO_SPR();
    QCOPY64_SERIAL("$a2");
}

void MatrixDrive_TurnZObjectMatrixXY(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_NOP();
}

void MatrixDrive_GetTurnXAngleZY(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_V3OP(vsub.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_NOP();
}

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnXAngleYZ);

void MatrixDrive_GetTurnYAngleXZ(void)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 4);
    VU0_NOREORDER_END();
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void MatrixDrive_GetTurnYEAngleXZ(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xyz, 4, 4, 4);
    VU0_V3OP_BC(vaddy.x, 4, 4, 4, y);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void MatrixDrive_GetTurnZAngleXY(void *p0)
{
    VU0_LSV(lqc2, 3, 0x0, a0);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}

float MatrixDrive_GetTurnZAngleYX(void *a, void *b)
{
    int local[4];
    register float result __asm__("$f0");
    func_00243AE8(local, a, b);
    VU0_LSV(lqc2, 4, 0x0, sp);
    VU0_V3OP(vmul.xyz, 4, 4, 4);
    VU0_V3OP_BC(vaddy.x, 4, 4, 4, y);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);

    return result;
}

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnMinusZAngleXY);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_SetTransposeMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", CopyVector);


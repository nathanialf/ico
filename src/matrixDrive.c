#include "common.h"




extern void func_00243AE8();
#include "vu0.h"
#include "r5900.h"

typedef int Qw128 __attribute__((mode(TI)));
typedef struct { char pad[0x30]; Qw128 q; } MatDrive;
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", InitMatrixDrive);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_PushMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_RotMatrixX);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_RotMatrixY);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_RotMatrixZ);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_ScaleMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnViewMatrix);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_PushMatrixWithNoCopy);

extern float D_0063092C;
extern float MatrixDrive_GetTurnYAngleXZ__p4(float a0) __asm__("MatrixDrive_GetTurnYAngleXZ");
extern void func_00243978(void *a0, void *a1);

void MatrixDrive_PopMatrix(float *a0, float *a1, float x, float y, float z) {
    float v0[4];
    float v1[4];
    float t;

    v0[0] = x;
    v0[1] = y;
    v0[2] = z;
    v0[3] = 1.0f;
    v1[0] = 0.0f;
    v1[1] = y;
    v1[2] = z;
    v1[3] = 1.0f;
    func_00243978(v0, v0);
    t = MatrixDrive_GetTurnYAngleXZ__p4(y * y + z * z);
    if (D_0063092C < t) {
        func_00243978(v1, v1);
        a0[0] = v1[1];
        a0[1] = v1[2];
    } else {
        a0[0] = 1.0f;
        a0[1] = 0.0f;
    }
    a1[0] = MatrixDrive_GetTurnYAngleXZ__p4(v0[1] * v0[1] + v0[2] * v0[2]);
    a1[1] = v0[0];
}

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

extern void func_00243BD8(void *);

void MatrixDrive_GetTurnXAngleYZ(MatDrive *a0) {
    Qw128 tmp[1];
    void *p = &a0->q;
    LQ16_FROM(p);
    SQ16_TO(tmp);
    func_00243BD8(a0);
    LQ16_FROM(tmp);
    SQ16_TO(p);
}

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


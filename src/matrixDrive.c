#include "common.h"




extern void sceVu0SubVector();
#include "vu0.h"
#include "r5900.h"

typedef int Qw128 __attribute__((mode(TI)));
typedef struct { char pad[0x30]; Qw128 q; } MatDrive;
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", InitMatrixDrive);
ASM_LIT4_SLOT(D_0063090C, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_PushMatrix);
ASM_LIT4_SLOT(D_00630910, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnXObjectMatrixYZ);
ASM_LIT4_SLOT(D_00630914, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnYObjectMatrixXZ);
ASM_LIT4_SLOT(D_00630918, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnZObjectMatrixXY);
ASM_LIT4_SLOT(D_0063091C, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnXAngleZY);
ASM_LIT4_SLOT(D_00630920, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnXAngleYZ);
ASM_LIT4_SLOT(D_00630924, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnYAngleXZ);
ASM_LIT4_SLOT(D_00630928, 0.01f);

extern float FSqrt(float a0);
extern void sceVu0Normalize(void *a0, void *a1);

void MatrixDrive_GetTurnYEAngleXZ(float *a0, float *a1, float x, float y, float z) {
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
    sceVu0Normalize(v0, v0);
    t = FSqrt(y * y + z * z);
    if (0.01f < t) {
        sceVu0Normalize(v1, v1);
        a0[0] = v1[1];
        a0[1] = v1[2];
    } else {
        a0[0] = 1.0f;
        a0[1] = 0.0f;
    }
    a1[0] = FSqrt(v0[1] * v0[1] + v0[2] * v0[2]);
    a1[1] = v0[0];
}

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnZAngleXY);
ASM_LIT4_SLOT(D_00630930, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnZAngleYX);
ASM_LIT4_SLOT(D_00630934, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TransMatrixV);
ASM_LIT4_SLOT(D_00630938, 0.01f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TransMatrix);

void MatrixDrive_TurnObjectMatrix(void *dst, void *src)
{
    QCOPY16("$a2");
}

void MatrixDrive_TurnXObjectMatrixZY(void *dst, void *src)
{
    QCOPY16("$a2");
}

void CopyMatrix(void *dst, void *src)
{
    QCOPY64_SERIAL("$a2");
}

void CopyMatrixUncached(void *dst, void *src)
{
    MAP_A0_TO_SPR();
    QCOPY64_SERIAL("$a2");
}

void AddVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_NOP();
}

void SubVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_V3OP(vsub.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_NOP();
}

extern void sceVu0UnitMatrix(void *);

void UnitRotation(MatDrive *a0) {
    Qw128 tmp[1];
    void *p = &a0->q;
    LQ16_FROM(p);
    SQ16_TO(tmp);
    sceVu0UnitMatrix(a0);
    LQ16_FROM(tmp);
    SQ16_TO(p);
}

float FSqrt(float a0)
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

void VectorLength(void *p0)
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

void VectorLengthSquare(void *p0)
{
    VU0_LSV(lqc2, 3, 0x0, a0);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}

float GetPointDistance(void *a, void *b)
{
    int local[4];
    register float result __asm__("$f0");
    sceVu0SubVector(local, a, b);
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
ASM_LIT4_SLOT(D_0063093C, 1.00000011e-06f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_SetTransposeMatrix);
ASM_LIT4_SLOT(D_00630940, 0.8f);

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", CopyVector);


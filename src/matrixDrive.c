#include "common.h"

#include "ico/types.h"
#include "vu0.h"

#include "r5900.h"

typedef int Qw128 __attribute__((mode(TI)));
typedef struct { char pad[0x30]; Qw128 q; } MatDrive;

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", InitMatrixDrive);
extern void CopyMatrix(void *dst, void *src);
extern int D_00639F00;
extern char D_00668640[];

void MatrixDrive_PushMatrix(void)
{
    D_00639F00 += 1;
    CopyMatrix(&D_00668640[D_00639F00 * 0x40],
                                    &D_00668640[D_00639F00 * 0x40 - 0x40]);
}
extern float D_0028FF80[];
extern float GetTableCos(short a0);
extern float GetTableSin(short a0);
extern void func_0025D440();

void MatrixDrive_RotMatrixX(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    D_0028FF80[10] = c;
    D_0028FF80[9] = -s;
    D_0028FF80[6] = s;
    D_0028FF80[5] = c;
    func_0025D440(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40],
                  (int)D_0028FF80);
}
extern float D_0028FFC0[];

void MatrixDrive_RotMatrixY(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    D_0028FFC0[10] = c;
    D_0028FFC0[8] = s;
    D_0028FFC0[2] = -s;
    D_0028FFC0[0] = c;
    func_0025D440(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40],
                  (int)D_0028FFC0);
}
extern float D_00290000[];

void MatrixDrive_RotMatrixZ(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    D_00290000[5] = c;
    D_00290000[4] = -s;
    D_00290000[1] = s;
    D_00290000[0] = c;
    func_0025D440(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40],
                  (int)D_00290000);
}
extern float D_00290040[];

void MatrixDrive_ScaleMatrix(float x, float y, float z)
{
    D_00290040[0] = x;
    D_00290040[5] = y;
    D_00290040[10] = z;
    func_0025D440(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40],
                      (int)D_00290040);
}
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnViewMatrix);
void MatrixDrive_PushMatrixWithNoCopy(void)
{
    D_00639F00 += 1;
}
void MatrixDrive_PopMatrix(void)
{
    D_00639F00 -= 1;
}
void *MatrixDrive_GetMatrix(void) {
    return &D_00668640[D_00639F00 * 0x40];
}
extern char D_00668600[];

void *MatrixDrive_GetLastMatrix(void) {
    return &D_00668600[D_00639F00 * 0x40];
}
extern void CopyVector(void *dst, void *src);
extern void sceVu0ApplyMatrix(int *buf, char *p, int x);

void MatrixDrive_TransMatrixV(char *a0)
{
    float buf[4];
    sceVu0ApplyMatrix((int *)buf, &D_00668640[D_00639F00 * 0x40], (int)a0);
    buf[3] = 1.0f;
    CopyVector(&D_00668640[D_00639F00 * 0x40 + 0x30], buf);
}
void MatrixDrive_TransMatrix(float x, float y, float z)
{
    float v[4];
    float buf[4];
    float *m = buf;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
    sceVu0ApplyMatrix((int *)m, &D_00668640[D_00639F00 * 0x40], (int)v);
    m[3] = 1.0f;
    CopyVector(&D_00668640[D_00639F00 * 0x40 + 0x30], m);
}
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnObjectMatrix);
ASM_LIT4_SLOT(D_00638B0C, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnXObjectMatrixZY);
ASM_LIT4_SLOT(D_00638B10, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnXObjectMatrixYZ);
ASM_LIT4_SLOT(D_00638B14, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnYObjectMatrixXZ);
ASM_LIT4_SLOT(D_00638B18, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_TurnZObjectMatrixXY);
ASM_LIT4_SLOT(D_00638B1C, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnXAngleZY);
ASM_LIT4_SLOT(D_00638B20, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnXAngleYZ);
ASM_LIT4_SLOT(D_00638B24, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnYAngleXZ);
ASM_LIT4_SLOT(D_00638B28, 0.01f);
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
ASM_LIT4_SLOT(D_00638B30, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnZAngleYX);
ASM_LIT4_SLOT(D_00638B34, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_GetTurnMinusZAngleXY);
ASM_LIT4_SLOT(D_00638B38, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", MatrixDrive_SetTransposeMatrix);
void CopyVector(void *dst, void *src)
{
    QCOPY16("$a2");
}
void CopyIVector(void *dst, void *src)
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
extern void sceVu0SubVector();

INCLUDE_ASM("asm/nonmatchings/src/matrixDrive", GetPointDistance);

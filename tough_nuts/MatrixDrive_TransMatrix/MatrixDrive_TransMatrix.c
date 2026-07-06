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

extern void func_0023FE98(void *a0, void *a1);
extern float MatrixDrive_GetTurnYAngleXZ(float a0);
extern float D_00628C2C;

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
    func_0023FE98(v0, v0);
    t = MatrixDrive_GetTurnYAngleXZ(y * y + z * z);
    if (D_00628C2C < t) {
        func_0023FE98(v1, v1);
        a0[0] = v1[1];
        a0[1] = v1[2];
    } else {
        a0[0] = 1.0f;
        a0[1] = 0.0f;
    }
    a1[0] = MatrixDrive_GetTurnYAngleXZ(v0[1] * v0[1] + v0[2] * v0[2]);
    a1[1] = v0[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetLastMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_TransMatrixV);

extern void func_0023FED0(void *dst, void *src);
extern void func_0023FDD8(void *out, void *mat, void *vec);

void MatrixDrive_TransMatrix(float *dst, float *src) {
    struct { float x, y, z, w; } __attribute__((aligned(8))) v, t;

    t.x = -src[12];
    t.y = -src[13];
    t.w = 0.0f;
    t.z = -src[14];
    v = t;
    func_0023FED0(dst, src);
    dst[7] = dst[11] = 0.0f;
    dst[3] = 0.0f;
    func_0023FDD8(dst + 12, dst, &v);
    dst[15] = 1.0f;
}


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

extern void func_00240008(void *out, void *a0, void *a1);

float MatrixDrive_GetTurnZAngleYX(void *a0, void *a1) {
    Qw128 buf[1];
    register float ret __asm__("$f0");
    func_00240008(buf, a0, a1);
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($29)\n"
        "vmul.xyz $vf4, $vf4, $vf4\n"
        "vaddy.x $vf4, $vf4, $vf4y\n"
        "vaddz.x $vf4, $vf4, $vf4z\n"
        ".word 0x4A0403BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2", "memory");
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnMinusZAngleXY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_SetTransposeMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", CopyVector);

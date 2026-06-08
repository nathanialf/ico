#include "common.h"
#include "vu0.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RemakeNormal);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _Sqrt);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _InitCurrentMatrix);

void _UnitCurrentMatrix(void *a0) {
    VU0_LSV(sqc2, 4, 0x0, 4);
    VU0_LSV(sqc2, 5, 0x10, 4);
    VU0_LSV(sqc2, 6, 0x20, 4);
    VU0_LSV(sqc2, 7, 0x30, 4);
    VU0_NOP();
}

void _PushCurrentMatrix(void *a0) {
    VU0_LSV_R(sqc2, 7, 0x0, a0);
    VU0_NOP();
}

void _PopCurrentMatrix(void *a0) {
    VU0_LSV(lqc2, 4, 0x0, 4);
    VU0_LSV(lqc2, 5, 0x10, 4);
    VU0_LSV(lqc2, 6, 0x20, 4);
    VU0_LSV(lqc2, 7, 0x30, 4);
    VU0_NOP();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _TransCurrentMatrix);

void _SetTransCurrentMatrix(void *m)
{
    VU0_LSV(lqc2, 14, 0x0, a0);
    VU0_LSV(lqc2, 15, 0x10, a0);
    VU0_LSV(lqc2, 16, 0x20, a0);
    VU0_LSV(lqc2, 17, 0x30, a0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 4, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 4, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 4, z);
    VU0_V3OP_BC(vmaddw.xyzw, 4, 17, 4, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 5, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 5, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 5, z);
    VU0_V3OP_BC(vmaddw.xyzw, 5, 17, 5, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 6, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 6, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 6, z);
    VU0_V3OP_BC(vmaddw.xyzw, 6, 17, 6, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 7, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 7, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 7, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 17, 7, w);
    VU0_NOP();
}

void _ClearTransCurrentMatrix(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf8, 0x0($5)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf7, $vf8w\n"
        "sqc2 $vf10, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void _RotCurrentMatrixX(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf8, 0x0($5)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf7, $vf8w\n"
        "vdiv $Q, $vf0w, $vf10w\n"
        "vwaitq\n"
        "vmulq.xyz $vf10, $vf10, $Q\n"
        "sqc2 $vf10, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void _RotCurrentMatrixY(void)
{
    VU0_V3OP(vsub.xyzw, 1, 0, 0);
    VU0_V3OP_BC(vaddx.y, 14, 1, 5, x);
    VU0_V3OP_BC(vaddx.z, 14, 1, 6, x);
    VU0_V3OP_BC(vaddx.w, 14, 1, 7, x);
    VU0_V3OP_BC(vaddy.x, 15, 1, 4, y);
    VU0_V3OP_BC(vaddy.z, 15, 1, 6, y);
    VU0_V3OP_BC(vaddy.w, 15, 1, 7, y);
    VU0_V3OP_BC(vaddz.x, 16, 1, 4, z);
    VU0_V3OP_BC(vaddz.y, 16, 1, 5, z);
    VU0_V3OP_BC(vaddz.w, 16, 1, 7, z);
    VU0_V3OP_BC(vaddw.x, 17, 1, 4, w);
    VU0_V3OP_BC(vaddw.y, 17, 1, 5, w);
    VU0_V3OP_BC(vaddw.z, 17, 1, 6, w);
    VU0_V2OP(vmove.yzw, 4, 14);
    VU0_V2OP(vmove.xzw, 5, 15);
    VU0_V2OP(vmove.xyw, 6, 16);
    VU0_V2OP(vmove.xyz, 7, 17);
    VU0_NOP();
}

void _RotCurrentMatrixZ(void) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vsub.xyzw $vf1, $vf0, $vf0\n"
        "vaddx.y $vf14, $vf1, $vf5x\n"
        "vaddx.z $vf14, $vf1, $vf6x\n"
        "vaddy.x $vf15, $vf1, $vf4y\n"
        "vaddy.z $vf15, $vf1, $vf6y\n"
        "vaddz.x $vf16, $vf1, $vf4z\n"
        "vaddz.y $vf16, $vf1, $vf5z\n"
        "vmove.yz $vf4, $vf14\n"
        "vmove.xz $vf5, $vf15\n"
        "vmove.xy $vf6, $vf16\n"
        ".set reorder\n" : : : "memory");
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _ScaleCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _GetCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _GetCurrentMatrixTrans);

void _SetCurrentMatrix(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "vmul.xyz $vf3, $vf1, $vf1\n"
        "vmulax.w $ACC, $vf0, $vf3x\n"
        "vmadday.w $ACC, $vf0, $vf3y\n"
        "vmaddz.w $vf3, $vf0, $vf3z\n"
        "vrsqrt $Q, $vf0w, $vf3w\n"
        "vwaitq\n"
        "vmulq.xyz $vf1, $vf1, $Q\n"
        "sqc2 $vf1, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

float _MulCurrentMatrixR(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($4)\n"
        "lqc2 $vf2, 0x0($5)\n"
        "vaddw.x $vf3, $vf0, $vf0w\n"
        "vmul.xyz $vf2, $vf1, $vf2\n"
        "vaddax.x $ACC, $vf0, $vf2x\n"
        "vmadday.x $ACC, $vf3, $vf2y\n"
        "vmaddz.x $vf2, $vf3, $vf2z\n"
        "qmfc2.ni $2, $vf2\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

void _MulCurrentMatrixL(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vopmula.xyz $ACC, $vf1, $vf2\n"
        "vopmsub.xyz $vf3, $vf2, $vf1\n"
        "vsub.w $vf3, $vf3, $vf3\n"
        "sqc2 $vf3, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void _ApplyCurrentMatrix(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vadd.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, 4);
    VU0_NOP();
}

void _RotTransPersCurrentMatrix(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vadd.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, 4);
    VU0_NOP();
}

void _TransposeCurrentMatrix(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, 4);
    VU0_NOP();
}

void _TransposeRotationCurrentMatrix(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vsub.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, 4);
    VU0_NOP();
}

void _InverseCurrentMatrix(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf2\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyzw, 3, 1, 2, x);
    VU0_LSV(sqc2, 3, 0x0, 4);
    VU0_NOP();
}

void _PushVu0Registers(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf2\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyz, 1, 1, 2, x);
    VU0_LSV(sqc2, 1, 0x0, 4);
    VU0_NOP();
}

void _PopVu0Registers(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vmulx.x $vf1, $vf1, $vf2x\n"
        "vmuly.y $vf1, $vf1, $vf2y\n"
        "vmulz.z $vf1, $vf1, $vf2z\n"
        "sqc2 $vf1, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

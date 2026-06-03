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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _SetTransCurrentMatrix);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RotCurrentMatrixX);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RotCurrentMatrixY);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RotCurrentMatrixZ);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _ScaleCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _GetCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _GetCurrentMatrixTrans);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _SetCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _MulCurrentMatrixR);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _PopVu0Registers);

#include "common.h"
#include "vu0.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RemakeNormal);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _Sqrt);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _InitCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _UnitCurrentMatrix);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _ClearTransCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RotCurrentMatrixX);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RotCurrentMatrixY);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RotCurrentMatrixZ);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _ScaleCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _GetCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _GetCurrentMatrixTrans);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _SetCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _MulCurrentMatrixR);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _MulCurrentMatrixL);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _InverseCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _PushVu0Registers);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _PopVu0Registers);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _PopCurrentMatrix);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _ApplyCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _RotTransPersCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _TransposeCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _TransposeRotationCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _InverseCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _PushVu0Registers);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _PopVu0Registers);

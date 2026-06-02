#include "common.h"
#include "r5900.h"

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_TurnXObjectMatrixYZ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_TurnYObjectMatrixXZ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_TurnZObjectMatrixXY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnXAngleZY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnXAngleYZ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnYAngleXZ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnYEAngleXZ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnZAngleXY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnZAngleYX);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_GetTurnMinusZAngleXY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", MatrixDrive_SetTransposeMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/matrixDrive", CopyVector);

#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", moveStartSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", moveEndSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", RotObjectGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", getRootMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", RotObjectDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", GetRotObjectHoldPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", MoveRotObjectWithHoldPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", ExecRotObjectMoveStartReaction);

int ExecRotObjectMoveEndReaction(void) {
    return 1;
}

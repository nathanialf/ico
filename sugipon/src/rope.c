#include "common.h"

void InitRopeGeo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", SetRopeFixPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", HoldRope);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", ropeGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", RopeDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", CheckRopeUpperWallClimbable);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", ReleaseRope);

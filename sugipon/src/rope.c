#include "common.h"

void InitRopeGeo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", SetRopeFixPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", HoldRope);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", ropeGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", RopeDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", CheckRopeUpperWallClimbable);

int ReleaseRope(int a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[1];
}

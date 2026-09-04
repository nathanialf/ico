#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/rope", InitRopeGeo);
void SetRopeFixPoint(char *a0, void *a1) {
    CopyVector(**(char ***)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) + 0x20, a1);
}
INCLUDE_ASM("asm/nonmatchings/src/rope", HoldRope);
INCLUDE_ASM("asm/nonmatchings/src/rope", ropeGeo);
INCLUDE_ASM("asm/nonmatchings/src/rope", RopeDL);
int CheckRopeUpperWallClimbable(int a0, char *a1) {
    return *(int *)(*(char **)(*(char **)(a1 + 0x15C) + 0x830) + 4);
}
void ReleaseRope(void) {}
INCLUDE_ASM("asm/nonmatchings/src/rope", RopeGeo);

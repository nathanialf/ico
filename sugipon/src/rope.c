#include "common.h"

void InitRopeGeo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", SetRopeFixPoint);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void HoldRope(void *a0, void *a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int *r = *(int **)q;
    int *s = *(int **)r;
    MatrixDrive_TurnObjectMatrix((int)((char *)s + 0x20), a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", ropeGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", RopeDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", CheckRopeUpperWallClimbable);

int ReleaseRope(int a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[1];
}

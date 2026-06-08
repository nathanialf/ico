#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch", switchOnSE);

extern int *actInitialize(int *self);
extern void actInitialize_ext_charcter(int *self);
extern void _ACTWait(int x);

void switchReleaseSE(int *self)
{
    int *p = actInitialize(self);
    long long v;
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    v = *(long long *)((char *)p + 0x18);
    v |= 1LL << 32;
    *(long long *)((char *)p + 0x18) = v;
}

float GetFloorLeverGlobalHoldPoint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x830);
    return *(float *)((char *)q + 0x20);
}

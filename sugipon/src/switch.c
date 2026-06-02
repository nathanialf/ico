#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch", switchOnSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch", switchReleaseSE);

float GetFloorLeverGlobalHoldPoint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x830);
    return *(float *)((char *)q + 0x20);
}

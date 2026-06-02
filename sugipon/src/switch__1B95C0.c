#include "common.h"

void FloorLeverTriStateGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[2] = a1;
}

extern void playSEConditionID(int a0, int a1);

void FloorLeverGeo(int a0) {
    playSEConditionID(a0, 0x3D);
}

void FloorLeverDL(int a0) {
    playSEConditionID(a0, 0x3E);
}

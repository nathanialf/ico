#include "common.h"

/* switch__1B95C0 0x7F0 view (local) */
typedef struct { char _0[8]; int f_8; } SwGeo;

void FloorLeverTriStateGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    SwGeo *q = *(SwGeo **)((char *)p + 0x7F0);
    q->f_8 = a1;
}

extern void playSEConditionID(int a0, int a1);

void FloorLeverGeo(int a0) {
    playSEConditionID(a0, 0x3D);
}

void FloorLeverDL(int a0) {
    playSEConditionID(a0, 0x3E);
}

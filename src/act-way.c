#include "common.h"

typedef struct { float f0, f4, f8; } Vec3;

INCLUDE_ASM("asm/nonmatchings/src/act-way", DetourCheck);

INCLUDE_ASM("asm/nonmatchings/src/act-way", checkPositionIllegal);

INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayMove_BeginDetail);

INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayMove_NextDetail);

INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayExec_Position);

extern Vec3 *ContinueCorrectPosition(void *a0);
extern float RotateAccordingToStick_PatternThree(void *a0, void *a1);

int ACTWay_IsMustWalkFromWay(void *a0) {
    char *w = *(char **)(*(char **)((char *)a0 + 0x164) + 0x370);
    float f;
    if (w == 0) goto ret0;
    f = *(float *)(w + 0x2C);
    if (f == 0.0f) goto ret0;
    if (RotateAccordingToStick_PatternThree(w + 0x10, ContinueCorrectPosition(a0)) < f * f)
        return 1;
ret0:
    return 0;
}

void ACTWay_SetBeginPositionIllegal(char *self) {
    char *sub = *(char **)(self + 0x164);
    *(long long *)(sub + 0x428) |= 0x200000LL;
}


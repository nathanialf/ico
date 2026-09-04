#include "common.h"

#include "vu0.h"
typedef struct {
    float v[4];
} LVec;

extern void sceVu0CopyMatrix(void *a0, void *a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);

void scale_m34(LVec *a0, void *a1, float f) {
    sceVu0CopyMatrix(a0, a1);
    sceVu0ScaleVector(a0, a0, f);
    sceVu0ScaleVector(a0 + 1, a0 + 1, f);
    return sceVu0ScaleVector(a0 + 2, a0 + 2, f);
}
INCLUDE_ASM("asm/nonmatchings/src/queen", func_001A27D0);
INCLUDE_ASM("asm/nonmatchings/src/queen", queenBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_001A2A10);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_001A34D8);
INCLUDE_ASM("asm/nonmatchings/src/queen", InitQueenGeo);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenGeo);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenDL);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBarrierGeo);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBarrierDL);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBallGeo);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBallDL);
INCLUDE_ASM("asm/nonmatchings/src/queen", actQueenStart);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenStartAttack);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenInqDead);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBoysWeaponPower);
float QueenBarrierRadius(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14);
}
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBarrierInqBreakable);
INCLUDE_ASM("asm/nonmatchings/src/queen", queenBarrierBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/queen", InqQueenBarrierExist);
INCLUDE_ASM("asm/nonmatchings/src/queen", InitQueenBarrierGeo);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBallRadius);
float GetQueenBallThickness(void) {
    return 150.0f;
}
INCLUDE_ASM("asm/nonmatchings/src/queen", queenBallBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/queen", InitQueenBallGeo);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_001A4B18);

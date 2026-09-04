#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/cage", CageRideFunc);
INCLUDE_ASM("asm/nonmatchings/src/cage", SetCageFixGeometry);
INCLUDE_ASM("asm/nonmatchings/src/cage", InitCageGeo);
INCLUDE_ASM("asm/nonmatchings/src/cage", HotInitCageGeo);
INCLUDE_ASM("asm/nonmatchings/src/cage", CageGeo);
INCLUDE_ASM("asm/nonmatchings/src/cage", CageDL);
INCLUDE_ASM("asm/nonmatchings/src/cage", GetCageChainPoint);
void SetCageVelocityFriction(char *a0, float a1) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x3C) = a1;
}
INCLUDE_ASM("asm/nonmatchings/src/cage", StabilizeAllLayoutedCage);
void SetCageChainHangableFlag(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x40) = a1;
}

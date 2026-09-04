#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/worm", outerProcess);
INCLUDE_ASM("asm/nonmatchings/src/worm", simulate);
INCLUDE_ASM("asm/nonmatchings/src/worm", getAnimation);
INCLUDE_ASM("asm/nonmatchings/src/worm", disp);
INCLUDE_ASM("asm/nonmatchings/src/worm", GetWormRoute);
INCLUDE_ASM("asm/nonmatchings/src/worm", InitWormGeo);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *a0, void *a1);

void GetWormCaptureVector(void *a0, char *a1, float f12) {
    sceVu0SubVector(a0, (void *)(*(int *)(a1 + 0x15C) + 0x50));
    sceVu0Normalize(a0, a0);
    sceVu0ScaleVector(a0, a0, f12);
}
INCLUDE_ASM("asm/nonmatchings/src/worm", WormGeo);
extern void disp(void);

void WormDL(void) {
    disp();
}
INCLUDE_ASM("asm/nonmatchings/src/worm", SetDirectWormTargetPos);
INCLUDE_ASM("asm/nonmatchings/src/worm", SetWormReduceRatio);
INCLUDE_ASM("asm/nonmatchings/src/worm", TraceWormRoute);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/worm", outerProcess);

INCLUDE_ASM("asm/nonmatchings/src/worm", simulate);

INCLUDE_ASM("asm/nonmatchings/src/worm", getAnimation);

INCLUDE_ASM("asm/nonmatchings/src/worm", disp);

extern void func_00243978(void *a0, void *a1);
extern void func_00243AE8(void *a0, void *a1);
extern void func_00243B18(void *a0, void *a1, float a2);

void GetWormRoute(void *a0, char *a1, float f12) {
    func_00243AE8(a0, (void *)(*(int *)(a1 + 0x15C) + 0x50));
    func_00243978(a0, a0);
    func_00243B18(a0, a0, f12);
}

INCLUDE_ASM("asm/nonmatchings/src/worm", InitWormGeo);

extern void simulate(void);

void GetWormCaptureVector(void) {
    simulate();
}

INCLUDE_ASM("asm/nonmatchings/src/worm", WormGeo);

INCLUDE_ASM("asm/nonmatchings/src/worm", WormDL);


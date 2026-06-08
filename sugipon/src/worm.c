#include "common.h"

/* Worm 0x7F0 view (local) */
typedef struct { char _0[8]; float f_8; } WormGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", outerProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", simulate);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", getAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", disp);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", GetWormRoute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", InitWormGeo);

extern void simulate(void);

void GetWormCaptureVector(void) {
    simulate();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", WormGeo);

void WormDL(void *a0, float a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WormGeo *q = *(WormGeo **)((char *)p + 0x7F0);
    q->f_8 = a1;
}

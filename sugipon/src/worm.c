#include "common.h"

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", WormDL);

#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/lightning", set_vertex);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/lightning", DrawLightning2);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/lightning", DrawLightningN);

int apply_m34(int *a0, int *a1) {
    return a0[4] - a1[4];
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/lightning", DrawLightning);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlOutStage);
INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlInStage);
extern int D_0063AA68;

void warpGirlInit(void) {
    D_0063AA68 = 0;
}

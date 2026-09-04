#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlOutStage);
INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlInStage);
extern int warpGirlId;

void warpGirlInit(void) {
    warpGirlId = 0;
}

#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1B9EC8", WallLeverDL);

extern void playSEConditionID(int a0, int a1);

void CheckReadyAllSwitches(int a0) {
    playSEConditionID(a0, 0x24);
}

void InitBoxGeo(int a0) {
    playSEConditionID(a0, 0x4);
}

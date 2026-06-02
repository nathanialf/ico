#include "common.h"

extern void playSEConditionID(int a0, int a1);

void execAutoMove(int a0) {
    playSEConditionID(a0, 0xD);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1B9EE0", initWheels);

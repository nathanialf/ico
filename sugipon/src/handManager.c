#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/handManager", getBone);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/handManager", connectToTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/handManager", _handManager);

extern void playSEConditionID(int a0, int a1);

void HandManager(int a0) {
    playSEConditionID(a0, 0x30);
}

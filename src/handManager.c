#include "common.h"


extern void playSEConditionID(int a0, int a1);
INCLUDE_ASM("asm/nonmatchings/src/handManager", getBone);

INCLUDE_ASM("asm/nonmatchings/src/handManager", connectToTarget);

INCLUDE_ASM("asm/nonmatchings/src/handManager", _handManager);

void HandManager(int a0)
{
    playSEConditionID(a0, 0x30);
}


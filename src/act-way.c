#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/act-way", DetourCheck);

INCLUDE_ASM("asm/nonmatchings/src/act-way", checkPositionIllegal);

INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayMove_BeginDetail);

INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayMove_NextDetail);

INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayExec_Position);

INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWay_IsMustWalkFromWay);

void ACTWay_SetBeginPositionIllegal(char *self) {
    char *sub = *(char **)(self + 0x164);
    *(long long *)(sub + 0x428) |= 0x200000LL;
}


#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/act-way", DetourCheck);
INCLUDE_ASM("asm/nonmatchings/src/act-way", checkPositionIllegal);
INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayMove_BeginDetail);
INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayMove_NextDetail);
INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayExec_Position);
INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWay_IsMustWalkFromWay);
void ACTWay_SetBeginPositionIllegal(char *a0) {
    char *p = *(char **)(a0 + 0x164);
    *(long long *)(p + 0x438) |= 0x200000;
}
INCLUDE_ASM("asm/nonmatchings/src/act-way", WayMove_CheckCollis);

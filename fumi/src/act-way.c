#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", DetourCheck);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", checkPositionIllegal);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayMove_BeginDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayMove_NextDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayExec_Position);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWay_IsMustWalkFromWay);

void ACTWay_SetBeginPositionIllegal(void *a0) {
    long long *p = *(long long **)((char *)a0 + 0x164);
    *(long long *)((char *)p + 0x428) |= 0x200000;
}

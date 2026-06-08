#include "common.h"

/* act-way 0x164 actor-state view (local) */
typedef struct { char _0[0x428]; long long f_428; } AWayState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", DetourCheck);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", checkPositionIllegal);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayMove_BeginDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayMove_NextDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayExec_Position);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWay_IsMustWalkFromWay);

void ACTWay_SetBeginPositionIllegal(void *a0) {
    AWayState *p = *(AWayState **)((char *)a0 + 0x164);
    p->f_428 |= 0x200000;
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_004C6FD0;

/* end struct shapes */

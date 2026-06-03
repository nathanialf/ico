#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", scale_m34);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_001971B0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", queenBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_00197DE0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_00197EE0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", subQueenBrainMain);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_00198080);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", InitQueenGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenDL);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBarrierGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBarrierDL);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBallGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBallDL);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", actQueenStart);

float QueenStartAttack(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return *(float *)((char *)q + 0x14);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenInqDead);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBoysWeaponPower);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBarrierRadius);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBarrierInqBreakable);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", queenBarrierBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", InitQueenBarrierGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBallRadius);

extern int D_0062C0CC;
extern char D_005568E0[];
extern void debug_assertMessage(char *a0);

void queenBallBeforeFunc(void) {
    D_0062C0CC = 0x3C;
    debug_assertMessage(D_005568E0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", InitQueenBallGeo);

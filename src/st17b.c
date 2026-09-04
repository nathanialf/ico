#include "common.h"

extern void _ACTWait();
extern int actInitialize(int a0);

extern void _ACTWait__pn(int a0) __asm__("_ACTWait");

INCLUDE_ASM("asm/nonmatchings/src/st17b", actSt17bTest);
INCLUDE_ASM("asm/nonmatchings/src/st17b", actSt17bCheck);
INCLUDE_ASM("asm/nonmatchings/src/st17b", actSt17bCheckChk);

#include "common.h"

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
INCLUDE_ASM("asm/nonmatchings/src/act2", BeforeFunc2);
void actDummy(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

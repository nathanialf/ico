#include "common.h"


extern char D_0061B040[];
extern void debug_assertMessage();
INCLUDE_ASM("asm/nonmatchings/src/act2", BeforeFunc2);

void actDummy(char *self, int val) {
    char *sub = *(char **)(self + 0x164);
    if (sub != 0) {
        *(int *)(sub + 0x438) = val;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00203CD0);

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00203D90);

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00203EE8);

void func_00203F18(int a0, int *a1, int *a2)
{
    int v = *a2;
    if (v >= 0x10) {
        debug_assertMessage(D_0061B040);
        return;
    }
    *a2 = v + 1;
    a1[v] = a0;
}

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00203F48);

INCLUDE_ASM("asm/nonmatchings/src/act2", func_002040C0);

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00204160);

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00204200);

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00204410);


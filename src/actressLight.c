#include "common.h"



extern int SetAP1DeadStatus(int *self, int a1);
extern int D_004BEFA8[];
extern void debug_assertMessage();
INCLUDE_ASM("asm/nonmatchings/src/actressLight", SetActressLight);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BA928);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BA9B0);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BAB68);

void func_001BAEE0(int a0)
{
    int idx = *(int *)(*(int *)(a0 + 0x164) + 0x30);
    debug_assertMessage(D_004BEFA8[idx]);
}

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BAF00);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BAF48);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BAFD0);

void func_001BB390(int a0)
{
    SetAP1DeadStatus(a0, 5);
}

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BB398);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BB3E0);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BB6B0);

int func_001BB7E0(int *a0)
{
    int *v1 = (int *)a0[0x164 / 4];
    long x = *(unsigned int *)((char *)v1 + 0x1C);
    return (((int)x) & 1) ^ 1;
}

void func_001BB800(char *self, int val) {
    *(int *)(*(char **)(self + 0x164) + 0x98) = val;
}

void func_001BB810(char *self, int val) {
    *(int *)(*(char **)(self + 0x164) + 0x9C) = val;
}


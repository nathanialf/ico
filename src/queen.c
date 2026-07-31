#include "common.h"


extern int D_0055C720[];
extern int D_00633DE0;
extern void debug_assertMessage();
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A7E8);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A8F0);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A9A0);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AA20);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AE50);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AE98);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B660);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B7F8);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B888);

extern void *isysGObjSearchFromObjLayoutID(int id);

char func_0019B8E8(void)
{
    char *p = *(char **)(*(char **)((char *)isysGObjSearchFromObjLayoutID(0x2E) + 0x15C) + 0x800);

    return p[3];
}

int func_0019B910(void)
{
    char *p = *(char **)(*(char **)((char *)isysGObjSearchFromObjLayoutID(0x2E) + 0x15C) + 0x800);

    return *(int *)(p + 4);
}

float func_0019B938(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    char *q = *(char **)((char *)p + 0x800);
    return *(float *)(q + 0x14);
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B948);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B998);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BA60);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BAA8);

float func_0019BB40(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    char *q = *(char **)((char *)p + 0x800);
    return *(float *)(q + 0x14) * 100.0f;
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BB60);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BC58);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BCE0);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BD30);

void queenBallBeforeFunc(void)
{
    D_00633DE0 = 0x3C;
    debug_assertMessage(D_0055C720);
}

INCLUDE_ASM("asm/nonmatchings/src/queen", InitQueenBallGeo);


#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/spider", InitSpiderLayoutGeo);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA3E0);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA480);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA5E8);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA9C8);

extern char D_006335E0[];
extern void debug_StdPrintfDummy();
extern void gamesysObjInfoUniqDataSet(void *a0);

void func_001EACE8(void *a0)
{
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);

    *(int *)(p + 0x3C) = 1;
    gamesysObjInfoUniqDataSet(a0);
    return debug_StdPrintfDummy(D_006335E0, *(int *)((char *)a0 + 8));
}

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EAD28);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EADA0);

int func_001EAE70(void *a0, int a1)
{
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    int *slot = (int *)(a1 * 4 + *(int *)(p + 0x24));
    int old;

    old = *slot;
    *slot = 0;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EAE90);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EAFC0);

int func_001EB0B8(void)
{
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EB0C0);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EB178);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EB238);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EB310);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EB3A8);

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EB418);


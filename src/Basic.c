#include "common.h"





extern int iosMallocCheckLeak2();
extern unsigned int D_00633780;
extern void func_00264128();
extern void func_00118678(void *p0);
extern int  D_00631970;
INCLUDE_ASM("asm/nonmatchings/src/Basic", dma_init);

INCLUDE_ASM("asm/nonmatchings/src/Basic", matrix_init);

void malloc_MemCpy(void)
{
    D_00631970 = 0x70000000;
    func_00118678(0x70000000);
}

void malloc_SetPartition(int a0, int a1, int a2, int a3)
{
    func_00264128(a0, a1, a2, a3);
}

void malloc_GetPartition(int val) {
    D_00633780 = val;
}

int mallocseki(void)
{
    return D_00633780;
}

INCLUDE_ASM("asm/nonmatchings/src/Basic", freeseki);

int resetmallocseki(void *a0)
{
    if (a0 != 0)
    {
        return iosMallocCheckLeak2(a0);
    }
}

void mallocsekistage(void) {}

INCLUDE_ASM("asm/nonmatchings/src/Basic", reallocseki);

INCLUDE_ASM("asm/nonmatchings/src/Basic", func_001F6E00);


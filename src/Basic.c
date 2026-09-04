#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/Basic", dma_init);
extern int D_00639CF0;
extern void _UnitMatrix(void *p0);

void matrix_init(void)
{
    D_00639CF0 = 0x70000000;
    _UnitMatrix(0x70000000);
}
extern void memcpy();

void malloc_MemCpy(int a0, int a1, int a2, int a3)
{
    memcpy(a0, a1, a2, a3);
}
extern unsigned int D_0063BC88;

void malloc_SetPartition(int val) {
    D_0063BC88 = val;
}
int malloc_GetPartition(void)
{
    return D_0063BC88;
}
INCLUDE_ASM("asm/nonmatchings/src/Basic", mallocseki);
extern int iosFree();

int freeseki(void *a0)
{
    if (a0 != 0)
    {
        return iosFree(a0);
    }
}
void resetmallocseki(void) {}
extern const char D_00621568[];
extern int D_0063A44C;
extern unsigned int D_0063BC88;
extern int iosMallocDebug(int heap, int size, const char *file, int line);

int mallocsekistage(int size)
{
    unsigned int save = D_0063BC88;
    int r;

    D_0063BC88 = 1;
    r = iosMallocDebug(D_0063A44C, size, D_00621568, 0x17E);
    D_0063BC88 = save;
    return r;
}
extern int iosReallocDebug(int size, int align, const char *file, int line);

INCLUDE_ASM("asm/nonmatchings/src/Basic", reallocseki);

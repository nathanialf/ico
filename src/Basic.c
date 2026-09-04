#include "common.h"

#include "ico/types.h"

struct DmaArec {
    void *p0;   /* 0x0 */
    int count;  /* 0x4 */
    void *p8;   /* 0x8 */
};





extern int iosMallocCheckLeak2();
extern unsigned int D_00633780;
extern void memcpy();
extern void _UnitMatrix(void *p0);
extern int  D_00631970;
extern void sceVu0InterVectorXYZ(void *a0, void *a1, void *a2, float a3);

void dma_init(void *gobj, float t) {
    Obj7F0 *o7 = *(Obj7F0 **)((char *)GOBJ_SUB(gobj) + 0x800);
    struct DmaArec *A = (struct DmaArec *)o7->p_0;
    int i;
    float f20 = t * 8.99999f;
    int rowcount, j, dn, k;
    float fj, frac;
    char *cp, *node;
    for (i = 0; i < A->count; i++) {
        rowcount = *(int *)((char *)A->p0 + i * 0x50);
        for (j = 1; j < rowcount; j++) {
            dn = rowcount - 1;
            fj = f20 * (float)j / dn;
            k = (int)fj;
            frac = fj - (float)k;
            cp = (char *)((void **)o7->f_4)[i];
            node = *(char **)((char *)A->p8 + i * 0x1A0) + j * 16;
            sceVu0InterVectorXYZ(node, cp + (k * 16 + 0x10), cp + k * 16, frac);
            node = *(char **)((char *)A->p8 + i * 0x1A0);
            *(float *)(node + j * 16 + 0xC) = 1.0f;
        }
    }
}

extern int *D_0063378C;
extern int *D_00633790;
extern int *D_00633794;
extern void debug_SetDmaCallback(void);
extern int *sceDmaGetChan(int a0);
extern void sceDmaReset(int a0);

void matrix_init(void) {
    union U { int i; } *p;
    sceDmaReset(1);
    D_0063378C = sceDmaGetChan(1);
    p = (union U *)D_0063378C;
    p->i |= 0x40;
    D_00633790 = sceDmaGetChan(2);
    p = (union U *)D_00633790;
    p->i |= 0x40;
    D_00633794 = sceDmaGetChan(8);
    p = (union U *)D_00633794;
    p->i |= 0x40;
    debug_SetDmaCallback();
}

void malloc_MemCpy(void)
{
    D_00631970 = 0x70000000;
    _UnitMatrix(0x70000000);
}

void malloc_SetPartition(int a0, int a1, int a2, int a3)
{
    memcpy(a0, a1, a2, a3);
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

extern int D_00632024;
extern const char D_0061A8A8[];
extern int func_0013A0F8(int heap, int size, const char *file, int line);

int reallocseki(int size)
{
    unsigned int save = D_00633780;
    int r;

    D_00633780 = 1;
    r = func_0013A0F8(D_00632024, size, D_0061A8A8, 0x17E);
    D_00633780 = save;
    return r;
}

extern int iosMallocAlignDebug(int size, int align, const char *file, int line);

int func_001F6E00(int size, int align)
{
    return iosMallocAlignDebug(size, align, D_0061A8A8, 0x1A8);
}


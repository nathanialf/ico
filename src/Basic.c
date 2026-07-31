#include "common.h"

#include "ico/types.h"

struct DmaArec {
    void *p0;   /* 0x0 */
    int count;  /* 0x4 */
    void *p8;   /* 0x8 */
};





extern int iosMallocCheckLeak2();
extern unsigned int D_00633780;
extern void func_00264128();
extern void func_00118678(void *p0);
extern int  D_00631970;
extern float D_0063142C;
extern void func_00244418(void *a0, void *a1, void *a2, float a3);

void dma_init(void *gobj, float t) {
    Obj7F0 *o7 = *(Obj7F0 **)((char *)GOBJ_SUB(gobj) + 0x800);
    struct DmaArec *A = (struct DmaArec *)o7->p_0;
    int i;
    float f20 = t * D_0063142C;
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
            func_00244418(node, cp + (k * 16 + 0x10), cp + k * 16, frac);
            node = *(char **)((char *)A->p8 + i * 0x1A0);
            *(float *)(node + j * 16 + 0xC) = 1.0f;
        }
    }
}

extern int *D_0063378C;
extern int *D_00633790;
extern int *D_00633794;
extern void debug_VariableInit(void);
extern int *func_00244630(int a0);
extern void func_00244658(int a0);

void matrix_init(void) {
    union U { int i; } *p;
    func_00244658(1);
    D_0063378C = func_00244630(1);
    p = (union U *)D_0063378C;
    p->i |= 0x40;
    D_00633790 = func_00244630(2);
    p = (union U *)D_00633790;
    p->i |= 0x40;
    D_00633794 = func_00244630(8);
    p = (union U *)D_00633794;
    p->i |= 0x40;
    debug_VariableInit();
}

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

extern int iosMallocAlignDebug(int size, int align, const char *file, int line);
extern const char D_0061A8A8[];

int func_001F6E00(int size, int align)
{
    return iosMallocAlignDebug(size, align, D_0061A8A8, 0x1A8);
}


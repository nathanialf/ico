#include "common.h"
#include "ico/types.h"

const char D_00613260[0x18] = "set partition first!\n";
const char D_00613278[0x18] = "src/Basic.c";

extern float D_0062970C;
extern void func_00240938(void *a0, void *a1, void *a2, float a3);

struct DmaArec {
    void *p0;   /* 0x0 */
    int count;  /* 0x4 */
    void *p8;   /* 0x8 */
};

void dma_init(void *gobj, float t) {
    Obj7F0 *o7 = GOBJ_SUB(gobj)->p_7F0;
    struct DmaArec *A = (struct DmaArec *)o7->p_0;
    int i;
    float f20 = t * D_0062970C;
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
            func_00240938(node, cp + (k * 16 + 0x10), cp + k * 16, frac);
            node = *(char **)((char *)A->p8 + i * 0x1A0);
            *(float *)(node + j * 16 + 0xC) = 1.0f;
        }
    }
}

extern void func_00240B78(int a0);
extern int *func_00240B50(int a0);
extern void debug_VariableInit(void);
extern int *D_0062BA6C;
extern int *D_0062BA70;
extern int *D_0062BA74;

void matrix_init(void) {
    union U { int i; } *p;
    func_00240B78(1);
    D_0062BA6C = func_00240B50(1);
    p = (union U *)D_0062BA6C;
    p->i |= 0x40;
    D_0062BA70 = func_00240B50(2);
    p = (union U *)D_0062BA70;
    p->i |= 0x40;
    D_0062BA74 = func_00240B50(8);
    p = (union U *)D_0062BA74;
    p->i |= 0x40;
    debug_VariableInit();
}

extern void *D_00629C70;
extern void func_00118AA0(void *a0);

void malloc_MemCpy(void) {
    D_00629C70 = (void *)0x70000000;
    func_00118AA0((void *)0x70000000);
}

extern void func_002604B8(void);

void malloc_SetPartition(void) {
    func_002604B8();
}

extern int D_0062BA60;

void malloc_GetPartition(int a0) {
    D_0062BA60 = a0;
}

int mallocseki(void) {
    return D_0062BA60;
}

extern int D_0062BA64;
extern int D_0062A314;
extern int D_0062A324;
extern unsigned int D_0062D8E8[];
extern void debug_assertMessage(char *p);
extern int func_001AAD00(const char *, int);
extern int func_00260380(const char *, int, void *);
extern int iosFree(int a0, int a1, char *file, int line);

int freeseki(int a0) {
    int rv = 0;
    if (D_0062BA60 == -1) {
        debug_assertMessage(D_00613260);
        func_001AAD00(D_00613278, 0x174);
        func_00260380(D_00613278, 0x174, D_0062D8E8);
    }
    switch (D_0062BA60) {
    case 0:
        {
            int t = D_0062BA64 + 0x30;
            D_0062BA64 = t + a0;
        }
        rv = iosFree(D_0062A314, a0, D_00613278, 0x17B);
        break;
    case 1:
        rv = iosFree(D_0062A324, a0, D_00613278, 0x17E);
        break;
    }
    return rv;
}

extern int iosMallocCheckLeak2(int a0);
int resetmallocseki(int a0) {
    if (a0) {
        return iosMallocCheckLeak2(a0);
    }
}

void mallocsekistage(void) {
}

extern int   D_0062A324;
extern int   iosFree(int a0, int a1, char *file, int line);

int reallocseki(int a0)
{
    int saved = D_0062BA60;
    int rv;
    D_0062BA60 = 1;
    rv = iosFree(D_0062A324, a0, D_00613278, 0x17E);
    D_0062BA60 = saved;
    return rv;
}

extern void *iosMallocAlignDebug(int a0, int a1, char *a2, int a3);

void *func_001F3DF0(int a0, int a1) {
    return iosMallocAlignDebug(a0, a1, D_00613278, 0x1A8);
}

extern int D_0062C254;
extern int D_0070A4B0[];
extern void _ScaleCurrentMatrix(void);
extern void _UnitCurrentMatrix(void *a0);

void func_001F3E18(void) {
    if (D_0062C254 != 0) {
        _ScaleCurrentMatrix();
        _UnitCurrentMatrix(D_0070A4B0);
    }
}

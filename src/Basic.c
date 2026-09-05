#include "common.h"

#include "ico/types.h"

extern int *dmaVif;
extern int *dmaGif;
extern int *dmaFSp;
extern void debug_SetDmaCallback(void);
extern int *sceDmaGetChan(int a0);
extern void sceDmaReset(int a0);
extern int matrixptr;
extern void _UnitMatrix(void *p0);
extern void memcpy();
extern int D_0063BC88;
extern char D_00621550[];
extern const char D_00621568[];
extern char D_0063BC90[];
extern int D_0063BC8C;
extern int D_0063A43C;
extern int D_0063A44C;
extern void debug_StdPrintfDummy();
extern void debug_assert(const char *file, int line);
extern void __assert(const char *file, int line, char *expr);
extern int iosMallocDebug(int heap, int size, const char *file, int line);
extern int iosFree();
extern int iosReallocDebug(int size, int align, const char *file, int line);
/* prototypes: their order is the inline tail's emission order */
void malloc_SetPartition(int val);
int malloc_GetPartition(void);
int mallocseki(int size);
int freeseki(void *a0);
void resetmallocseki(void);
int mallocsekistage(int size);
int reallocseki(int size, int align);
void dma_init(void) {
    union U { int i; } *p;
    sceDmaReset(1);
    dmaVif = sceDmaGetChan(1);
    p = (union U *)dmaVif;
    p->i |= 0x40;
    dmaGif = sceDmaGetChan(2);
    p = (union U *)dmaGif;
    p->i |= 0x40;
    dmaFSp = sceDmaGetChan(8);
    p = (union U *)dmaFSp;
    p->i |= 0x40;
    debug_SetDmaCallback();
}
void matrix_init(void)
{
    matrixptr = 0x70000000;
    _UnitMatrix(0x70000000);
}
inline void malloc_SetPartition(int val) {
    D_0063BC88 = val;
}
inline int malloc_GetPartition(void)
{
    return D_0063BC88;
}
inline void resetmallocseki(void) {}
inline int mallocseki(int size)
{
    int ptr = 0;

    if (D_0063BC88 == -1) {
        debug_StdPrintfDummy(D_00621550);
        debug_assert(D_00621568, 0x174);
        __assert(D_00621568, 0x174, D_0063BC90);
    }

    switch (D_0063BC88) {
    case 0:
        D_0063BC8C += size + 0x30;
        ptr = iosMallocDebug(D_0063A43C, size, D_00621568, 0x17B);
        break;
    case 1:
        ptr = iosMallocDebug(D_0063A44C, size, D_00621568, 0x17E);
        break;
    }
    return ptr;
}
inline int mallocsekistage(int size)
{
    int save = D_0063BC88;
    int r;

    D_0063BC88 = 1;
    r = mallocseki(size);
    D_0063BC88 = save;
    return r;
}
inline int reallocseki(int size, int align)
{
    return iosReallocDebug(size, align, D_00621568, 0x1A8);
}
inline int freeseki(void *a0)
{
    if (a0 != 0)
    {
        return iosFree(a0);
    }
}
void malloc_MemCpy(int a0, int a1, int a2, int a3)
{
    memcpy(a0, a1, a2, a3);
}

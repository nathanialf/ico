#include "common.h"
#include "debug.h"
#include "Matrix.h"

extern int *dmaVif;
extern int *dmaGif;
extern int *dmaFSp;
extern int *sceDmaGetChan(int a0);
extern void sceDmaReset(int a0);
extern int matrixptr;
extern void memcpy();
extern int D_0063BC88;
extern char D_0063BC90[];
extern int D_0063BC8C;
extern int D_0063A43C;
extern int D_0063A44C;
extern void debug_assert(const char *file, int line);
extern void __assert(const char *file, int line, char *expr);
/* kept local: this TU's uses of iosMallocDebug do not fit the prototype in memory.h */
extern int iosMallocDebug(int heap, int size, const char *file, int line);
/* kept local: this TU's uses of iosFree do not fit the prototype in memory.h */
extern int iosFree();
/* kept local: this TU's uses of iosReallocDebug do not fit the prototype in memory.h */
extern int iosReallocDebug(int size, int align, const char *file, int line);

#include "Basic.h"

void dma_init(void)
{
    union U {
        int i;
    } *p;

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

inline void malloc_SetPartition(int val)
{
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
        debug_StdPrintfDummy("set partition first!\n");
        debug_assert("src/Basic.c", 372);
        __assert("src/Basic.c", 372, D_0063BC90);
    }

    switch (D_0063BC88) {
    case 0:
        D_0063BC8C += size + 0x30;
        ptr = iosMallocDebug(D_0063A43C, size, "src/Basic.c", 379);
        break;
    case 1:
        ptr = iosMallocDebug(D_0063A44C, size, "src/Basic.c", 382);
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
    return iosReallocDebug(size, align, "src/Basic.c", 424);
}

inline int freeseki(void *a0)
{
    if (a0 != 0) {
        return iosFree(a0);
    }
}

void malloc_MemCpy(int a0, int a1, int a2, int a3)
{
    memcpy(a0, a1, a2, a3);
}

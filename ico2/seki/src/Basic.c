#include "debug.h"
#include "Matrix.h"

/* kept local: int * (int) here, int (unsigned int) in libdma.h */
extern int *sceDmaGetChan(int a0);
/* kept local: void (int) here, int (int) in libdma.h */
extern void sceDmaReset(int a0);
/* kept local: declaring it only through string.h moves this TU's bytes */
extern void memcpy();

/* The TU's .sdata opens with the allocator's partition (none selected yet)
   and the running total of what partition 0 has handed out. */
static int mallocPartition = -1; /* derived name */

static int mallocTotal = 0; /* derived name */

extern void __assert(const char *file, int line, char *expr);
/* kept local: int (int, int, const char *, int) here, void * (IosMemPart *, int, char *, int) in memory.h */
extern int iosMallocDebug(int heap, int size, const char *file, int line);
/* kept local: int () here, void * (void *) in memory.h */
extern int iosFree();
/* kept local: int (int, int, const char *, int) here, void * (void *, unsigned int) in memory.h */
extern int iosReallocDebug(int size, int align, const char *file, int line);

#include "Basic.h"
#include "ios.h"
#include "main.h"
#include "debug_exception.h"

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
    mallocPartition = val;
}

inline int malloc_GetPartition(void)
{
    return mallocPartition;
}

inline void resetmallocseki(void) {}

inline int mallocseki(int size)
{
    int ptr = 0;

    if (mallocPartition == -1) {
        debug_StdPrintfDummy("set partition first!\n");
        debug_assert("src/Basic.c", 372);
        __assert("src/Basic.c", 372, "0");
    }

    switch (mallocPartition) {
    case 0:
        mallocTotal += size + 0x30;
        ptr = iosMallocDebug(ios_partition_common, size, "src/Basic.c", 379);
        break;
    case 1:
        ptr = iosMallocDebug(ios_partition_seki, size, "src/Basic.c", 382);
        break;
    }
    return ptr;
}

inline int mallocsekistage(int size)
{
    int save = mallocPartition;
    int r;

    mallocPartition = 1;
    r = mallocseki(size);
    mallocPartition = save;
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

/* The DMA channel handles and the screen fade state (MAIN.MAP globals). The
   ROM's .sdata has them after mallocseki's assert text, so they are defined
   after the allocator. */
int *dmaVif = 0;

int *dmaGif = 0;

int *dmaFSp = 0;

int fadeStatus = 0;

float fadeSpeed = 0.0f;

int fadeContinue = 0;

unsigned char fadeColor[4] = {0};

#include "debug.h"
#include "Matrix.h"
#include <assert.h>
#include <string.h>

/* The allocator's partition (none selected yet) and the running total of
   what partition 0 has handed out. */
static int mallocPartition = -1; /* derived name */

static int mallocTotal = 0; /* derived name */

/* memory.h is not included: its iosFree and iosReallocDebug disagree with
   the calls below (see them); iosMallocDebug as memory.h declares it */
struct IosMemPart;

extern void *iosMallocDebug(struct IosMemPart *part, int size, const char *file, int line);
/* int () here, void * (void *) in memory.h */
extern int iosFree();
/* int (int, int, const char *, int) here, void * (void *, unsigned int) in memory.h */
extern int iosReallocDebug(int size, int align, const char *file, int line);

#include "Basic.h"
#include "ios.h"
#include "main.h"
#include "debug_exception.h"
#include <libdma.h>
#include "include_asm.h"

void dma_init(void)
{
    union U { /* field names derived */
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
    matrixptr = (char *)0x70000000;
    _UnitMatrix(matrixptr);
}

INCLUDE_ASM_LIT(mallocseki);

void malloc_MemCpy(void *dst, void *src, int size)
{
    memcpy(dst, src, size);
}

/* The DMA channel handles and the screen fade state. */
DmaChan *dmaVif = 0;

DmaChan *dmaGif = 0;

DmaChan *dmaFSp = 0;

int fadeStatus = 0;

float fadeSpeed = 0.0f;

int fadeContinue = 0;

unsigned char fadeColor[4] = {0};

INCLUDE_ASM(malloc_SetPartition);

INCLUDE_ASM(malloc_GetPartition);

INCLUDE_ASM(mallocseki);

INCLUDE_ASM(freeseki);

INCLUDE_ASM(resetmallocseki);

INCLUDE_ASM(mallocsekistage);

INCLUDE_ASM(reallocseki);

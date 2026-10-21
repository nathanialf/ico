#include "debug.h"
#include "memory.h"
#include "DmaPacket.h"
#include "GifPacket.h"
#include "MicroCode.h"
#include "DisplayList.h"
#include <eekernel.h>
#include <libdma.h>
#include "GsBase.h"
#include "ios.h"
#include "debug_exception.h"
#include "Basic.h"
#include <assert.h>

#define DL_DEBUG 0 /* derived name */

/* One priority's display list: whether a DMA tag is open, where the open tag
   is, the address and quadword count it refers to and its tag id, a VIF tag's
   open flag and position (dl_Debug's "dlvif" count) and one more word the
   reset clears, the start of the list's buffer and the write pointer.  0x60
   bytes in this build. */
typedef struct {           /* field names derived */
    int open;              /* 0x00 */
    int tag;               /* 0x04 */
    long long addr;        /* 0x08 */
    unsigned int qwc;      /* 0x10 */
    int pad14;             /* 0x14 */
    unsigned long long id; /* 0x18 */
    int vifOpen;           /* 0x20, cleared with open */
    int vifTag;            /* 0x24, the VIF tag dl_Debug counts from */
    int pad28[2];
    int word30; /* 0x30, cleared with open; no other reader */
    int pad34[9];
    int start; /* 0x58 */
    int cur;   /* 0x5C */
} DlEntry;     /* derived name */

/* The bank the list is built into and the priority it is building at, then the 13
   list entries, the two banks of 13 buffer heads they are reloaded from, and
   the eight-deep priority stack. */
static int dlBank; /* derived name */

static int dlPriority; /* derived name */

static DlEntry dlEntries[13]; /* derived name */

static int dlBufferHead[2][13]; /* derived name */

/* The depth of the priority stack below. */
static int dlStackDepth = 0; /* derived name */

static int dlPriorityStack[8]; /* derived name */

/* The size of each priority's list buffer. */
static const int dlBufferSize[13] = {
    /* derived name */
    98304, 16384, 32768, 4096, 16384, 49152, 49152, 16384, 28672, 16384, 4096, 12288, 24576,
};

void dl_Init(void)
{
    int i;
    int j;
    dlPriority = 0;
    dlStackDepth = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 13; j++) {
            dlBufferHead[i][j] =
                (int)iosMallocDebug(ios_partition_common, dlBufferSize[j], __FILE__, 428);
        }
    }
    dlBank = 0;
    for (i = 0; i < 13; i++) {
        dlEntries[i].word30 = 0;
        dlEntries[i].start = dlEntries[i].cur = dlBufferHead[0][i];
        dlEntries[i].vifOpen = 0;
        dlEntries[i].open = 0;
    }
    dpk_Init();
    dl_Clear();
}

inline void dl_Out(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        int *p = dlBufferHead[i];
        int j;
        for (j = 12; j >= 0; j--) {
            iosFree((void *)*p);
            p++;
        }
    }
}

void dl_Clear(void)
{
    int flag = dlBank ^ 1;
    int *src = dlBufferHead[flag];
    DlEntry *dst = dlEntries;
    int i;
    dlBank = flag;
    dlPriority = 0;
    for (i = 12; i >= 0; i--) {
        int v = *src;
        dst->word30 = 0;
        src++;
        dst->cur = v;
        dst->start = v;
        dst->vifOpen = 0;
        dst->open = 0;
        dst++;
    }
    dpk_SwapBuffer();
    gif_Init();
    mc_Reset();
}

inline void dl_SetDLPriority(int pri);
inline void dl_OpenDma(int id, void *addr, int qwc);

void dl_Swap(void)
{
    int i;
    int j;
    for (i = 0; i < 13; i++) {
        if (dlEntries[i].open) {
            debug_StdPrintfDummy("dma not close dl priority:%d\n", i);
            dl_CloseDma();
        }
    }
    dl_SetDLPriority(0xC);
    dl_OpenDma(7, 0, 0);
    dl_CloseDma();
    i = 0;
    do {
        dl_SetDLPriority(i);
        j = i + 1;
        dl_OpenDma(1, (void *)(dlEntries[j].start & 0xFFFFFFF), 0);
        dl_CloseDma();
        i = j;
    } while (j < 0xC);
    FlushCache(0);
    if (fbKeep) {
        sceDmaSend(dmaVif, dlEntries[11].start);
    } else {
        sceDmaSend(dmaVif, dlEntries[0].start);
    }
    dl_Clear();
}

inline void dl_SetDLPriority(int pri)
{
    DlEntry *entry = &dlEntries[dlPriority];

    if (entry->open) {
        dl_CloseDma();
    }
    if (pri < 0) {
        dlPriority = 0;
    } else if (pri >= 0xD) {
        dlPriority = 0xC;
    } else {
        dlPriority = pri;
    }
}

void dl_PushPriority(void)
{
    if (dlStackDepth < 7) {
        dlStackDepth = dlStackDepth + 1;
        dlPriorityStack[dlStackDepth - 1] = dlPriority;
    } else {
        debug_StdPrintfDummy("dl_PushPriority:Stack Overflow.\n");
        debug_assert(__FILE__, 575);
        __assert(__FILE__, 575, "FALSE");
    }
}

void dl_PopPriority(void)
{
    DlEntry *entry = &dlEntries[dlPriority];

    if (entry->open) {
        debug_StdPrintfDummy("dl_PushPriority:dma is now open.\n");
        dl_CloseDma();
    }
    if (dlStackDepth > 0) {
        dlPriority = dlPriorityStack[dlStackDepth - 1];
        dlStackDepth--;
    } else {
        debug_StdPrintfDummy("dl_PopPriority:Stack Underflow.\n");
        debug_assert(__FILE__, 597);
        __assert(__FILE__, 597, "FALSE");
    }
}

inline int dl_GetPri(void)
{
    return dlPriority;
}

void dl_Debug(void)
{
    DlEntry *entry = &dlEntries[dlPriority];

    debug_StdPrintfDummy("dldma %d\n", ((unsigned int)(entry->cur - entry->tag) >> 4) - 1);
    debug_StdPrintfDummy("dlvif %d\n", ((unsigned int)(entry->cur - entry->vifTag) >> 4) - 1);
}

inline void dl_OpenDma(int id, void *addr, int qwc)
{
    DlEntry *entry = &dlEntries[dlPriority];

    /* the buffer overflow check, compiled out (DL_DEBUG is 0); the
       message-assert form this programmer writes in Packet.c and
       BgAnimation.c */
    if (DL_DEBUG) {
        debug_StdPrintfDummy("dl_CheckDLOverflow:Display List Buffer [%d] Full.\n", dlPriority);
        __assert(__FILE__, 613, "e");
    }
    if (entry->open) {
        dl_CloseDma();
    }
    entry->id = id;
    entry->qwc = qwc;
    entry->tag = entry->cur;
    entry->cur += 0x10;
    entry->addr = (unsigned int)addr;
    entry->open = 1;
}

void dl_CloseDma(void)
{
    DlEntry *e = &dlEntries[dlPriority];
    long long addr = (e->addr & 0x7FFFFFFF) << 32;
    long long qwc;
    long long *p;

    switch (e->id) {
    case 0:
    case 6:
        qwc = ((unsigned int)(e->cur - e->tag) >> 4) - 1;
        if (qwc == 0) {
            e->cur = e->cur - 0x10;
            e->open = 0;
            return;
        }
        break;
    case 7:
        qwc = ((unsigned int)(e->cur - e->tag) >> 4) - 1;
        break;
    default:
        qwc = e->qwc;
        break;
    }
    p = (long long *)e->tag;
    switch (e->id) {
    case 0:
        p[0] = qwc | 0x10000000;
        break;
    case 1:
        p[0] = qwc | 0x20000000 | addr;
        break;
    case 2:
        p[0] = qwc | 0x30000000 | addr;
        break;
    case 3:
        p[0] = qwc | 0x40000000 | addr;
        break;
    case 4:
        p[0] = qwc | addr;
        break;
    case 5:
        p[0] = qwc | 0x50000000 | addr;
        break;
    case 6:
        p[0] = qwc | 0x60000000;
        break;
    case 7:
        p[0] = qwc | 0x70000000;
        break;
    }
    p[1] = 0;
    e->open = 0;
}

#include "common.h"
#include "debug.h"
#include "memory.h"
#include "DmaPacket.h"
#include "GifPacket.h"
#include "MicroCode.h"
#include "DisplayList.h"
#include <eekernel.h>
#include <libdma.h>

typedef struct {
    int f_0;                 /* 0x00 */
    int f_4;                 /* 0x04 */
    long long f_8;           /* 0x08 */
    unsigned int f_10;       /* 0x10 */
    int pad_14;              /* 0x14 */
    unsigned long long f_18; /* 0x18 */
    int pad_20;              /* 0x20 */
    int f_24;                /* 0x24 */
} DlEntry;

/* .sbss and .bss, owned by DisplayList.o and reached only from this file
   (MAIN.MAP names no symbol in either run), each in the ROM's run order: the
   bank the list is built into and the priority it is building at, then the 13
   list entries, the two banks of 13 buffer heads they are reloaded from, and
   the eight-deep priority stack. */
static int dlBank;

static int dlPriority;

static DlEntry dlEntries[13];

static int dlBufferHead[2][13];

extern int fbKeep;
extern int dmaVif;
extern int D_006218E0[];
extern int D_00621840[];
extern int D_0063A43C;
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern int D_0063BD20;

static int dlPriorityStack[8];

extern char D_00621878[];
extern char D_00621890[];
extern char D_006218B8[];
extern char D_0063BD28[];
void dl_Clear(void);

void dl_Init(void)
{
    int i;
    int j;
    dlPriority = 0;
    D_0063BD20 = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 13; j++) {
            dlBufferHead[i][j] =
                (int)iosMallocDebug(D_0063A43C, D_00621840[j], D_00621878, 393) | 0x30000000;
        }
    }
    dlBank = 0;
    for (i = 0; i < 13; i++) {
        dlEntries[i].pad_20 = dlEntries[i].f_24 = dlBufferHead[0][i];
        dlEntries[i].f_0 = 0;
    }
    dpk_Init();
    dl_Clear();
}

inline void dl_Out(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        int *p = (int *)((char *)dlBufferHead + i * 0x34);
        int j;
        for (j = 0xC; j >= 0; j--) {
            iosFree(*p);
            p++;
        }
    }
}

void dl_Clear(void)
{
    int flag = dlBank ^ 1;
    int *src = (int *)((char *)dlBufferHead + flag * 0x34);
    char *dst = (char *)dlEntries;
    int i;
    dlBank = flag;
    dlPriority = 0;
    for (i = 0xC; i >= 0; i--) {
        int v = *src;
        *(int *)dst = 0;
        src++;
        *(int *)(dst + 0x24) = v;
        *(int *)(dst + 0x20) = v;
        dst += 0x28;
    }
    dpk_SwapBuffer();
    gif_Init();
    mc_Reset();
}

void dl_Swap(void)
{
    int i;
    int j;
    int stride = 0x28;
    dl_SetDLPriority(0xC);
    dl_OpenDma(7, 0, 0);
    dl_CloseDma();
    i = 0;
    do {
        DlEntry *e;
        dl_SetDLPriority(i);
        j = i + 1;
        e = (DlEntry *)((char *)dlEntries + j * stride);
        dl_OpenDma(1, e->pad_20 & 0xFFFFFFF, 0);
        dl_CloseDma();
        i = j;
    } while (j < 0xC);
    FlushCache(0);
    if (fbKeep) {
        sceDmaSend(dmaVif, dlEntries[11].pad_20 & 0xFFFFFFF);
    } else {
        sceDmaSend(dmaVif, dlEntries[0].pad_20 & 0xFFFFFFF);
    }
    dl_Clear();
}

inline void dl_SetDLPriority(int a0)
{
    if (a0 < 0) {
        dlPriority = 0;
    } else if (a0 >= 0xD) {
        dlPriority = 0xC;
    } else {
        dlPriority = a0;
    }
}

void dl_PushPriority(void)
{
    if (D_0063BD20 < 7) {
        D_0063BD20 = D_0063BD20 + 1;
        dlPriorityStack[D_0063BD20 - 1] = dlPriority;
    } else {
        debug_StdPrintfDummy(D_00621890);
        debug_assert(D_00621878, 0x216);
        __assert(D_00621878, 0x216, D_0063BD28);
    }
}

void dl_PopPriority(void)
{
    if (D_0063BD20 > 0) {
        dlPriority = dlPriorityStack[D_0063BD20 - 1];
        D_0063BD20--;
    } else {
        debug_StdPrintfDummy(D_006218B8);
        debug_assert(D_00621878, 0x228);
        __assert(D_00621878, 0x228, D_0063BD28);
    }
}

inline int dl_GetPri(void)
{
    return dlPriority;
}

void dl_Debug(void)
{
    int *entry = (int *)dlEntries + dlPriority * 10;
    unsigned int end = entry[9];
    unsigned int start = entry[1];
    unsigned int count = (end - start) >> 4;
    return debug_StdPrintfDummy(D_006218E0, count - 1);
}

inline void dl_OpenDma(int a0, int a1, int a2)
{
    int *entry = (int *)&dlEntries[dlPriority];
    int old;
    if (entry[0]) {
        dl_CloseDma();
    }
    old = entry[9];
    *(long long *)(entry + 6) = a0;
    entry[4] = a2;
    entry[0] = 1;
    *(long long *)(entry + 2) = (long long)a1 & 0xFFFFFFFLL;
    entry[1] = old;
    entry[9] = old + 0x10;
}

void dl_CloseDma(void)
{
    DlEntry *e = &dlEntries[dlPriority];
    long long addr = (e->f_8 & 0x7FFFFFFF) << 32;
    long long qwc;
    long long *p;

    switch (e->f_18) {
    case 0:
    case 6:
        qwc = ((unsigned int)(e->f_24 - e->f_4) >> 4) - 1;
        if (qwc == 0) {
            e->f_24 = e->f_24 - 0x10;
            e->f_0 = 0;
            return;
        }
        break;
    case 7:
        qwc = ((unsigned int)(e->f_24 - e->f_4) >> 4) - 1;
        break;
    default:
        qwc = e->f_10;
        break;
    }
    p = (long long *)e->f_4;
    switch (e->f_18) {
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
    e->f_0 = 0;
}

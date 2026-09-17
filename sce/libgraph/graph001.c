/* libgraph.a member graph001.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <libgraph.h>

/* RECONSTRUCTION: the record sceGsGetGParam hands back, read off the offsets
   this function writes.  The name follows the accessor's; MAIN.MAP names no
   symbol in the run.  It stays local to this file until another TU reaches the
   record by field. */
typedef struct {
    short inter;   /* 0x0 */
    short omode;   /* 0x2 */
    short ffmd;    /* 0x4 */
    short version; /* 0x6, the GS revision out of CSR bits 16..23 */
    int intcUsed;  /* 0x8, set while this member owns the INTC 2 handler */
    int handler;   /* 0xC, the handler id RemoveIntcHandler takes */
} sceGsGParam;

/* syscall 113 (sce/libkernl/klib.c): it returns the previous IMR, which the
   ROM proves by keeping $2 live across the call here */
extern int GsPutIMR(int a0);
extern void DisableIntc(int a0);
extern void RemoveIntcHandler(int a0, int a1);
extern void SetGsCrt(int a0, int a1, int a2);

void sceGsResetGraph(short mode, short inter, short omode, short ffmd)
{
    sceGsGParam *g;

    switch (mode) {
    case 0:
        g = (sceGsGParam *)sceGsGetGParam();
        *(volatile long *)0x12001000 = 0x200;
        g->inter = inter;
        g->omode = omode;
        g->version = (*(volatile unsigned long *)0x12001000 >> 16) & 0xFF;
        GsPutIMR(0xFF00);
        g->ffmd = ffmd != 0;
        if (g->intcUsed != 0) {
            DisableIntc(2);
            RemoveIntcHandler(2, g->handler);
            g->intcUsed = 0;
            g->handler = 0;
        }
        SetGsCrt(inter & 1, omode & 0xFF, ffmd & 1);
        break;
    case 1:
        *(volatile long *)0x12001000 = 0x100;
        break;
    }
}

extern int D_0054A2B0[];

void *sceGsGetGParam(void)
{
    return D_0054A2B0;
}

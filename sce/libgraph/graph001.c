/* libgraph.a member graph001.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <libgraph.h>
#include <eeregs.h>
#include <eekernel.h>

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

/* the member's .data: its build stamp and the record, interlaced NTSC frame
   mode until sceGsResetGraph sets it.  The stamp is 16-aligned in Sony's
   object: the shipped link starts this member's .data at 0x54A2A0, 12 bytes
   past vobj.o's run end at 0x54A294, where an 8-aligned section would sit at
   0x54A298.  The stamp is the run's first object, so its alignment is the
   section's. */
static char sceGsVersion[16] __attribute__((aligned(16))) = "PsIIlibgraph2200"; /* derived name */

static sceGsGParam gsGParam = {1, 2, 1, 3, 0, 0}; /* derived name */

void sceGsResetGraph(short mode, short inter, short omode, short ffmd)
{
    sceGsGParam *g;

    switch (mode) {
    case 0:
        g = (sceGsGParam *)sceGsGetGParam();
        *GS_CSR = 0x200;
        g->inter = inter;
        g->omode = omode;
        g->version = (*GS_CSR >> 16) & 0xFF;
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
        *GS_CSR = 0x100;
        break;
    }
}

void *sceGsGetGParam(void)
{
    return &gsGParam;
}

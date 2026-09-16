/* libgraph.a member graph017.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern void printf(void *a0, ...);

int sceGsExecLoadImage(void *pkt, void *img)
{
    unsigned int i = 0;

    while (*(volatile int *)0x1000A000 & 0x100) {
        if (i++ > 0x1000000) {
            printf("sceGsExecLoadImage: DMA Ch.2 does not terminate\r\n");
            return -1;
        }
    }
    *(volatile int *)0x1000A020 = 6;
    if (((unsigned int)pkt & 0x70000000) == 0x70000000) {
        *(volatile int *)0x1000A010 = ((unsigned int)pkt & 0x0FFFFFFF) | 0x80000000;
    } else {
        *(volatile int *)0x1000A010 = (unsigned int)pkt & 0x0FFFFFFF;
    }
    *(volatile int *)0x1000A000 = 0x101;
    while (*(volatile int *)0x1000A000 & 0x100) {
        if (i++ > 0x1000000) {
            printf("sceGsExecLoadImage: DMA Ch.2 does not terminate\r\n");
            return -1;
        }
    }
    *(volatile int *)0x1000A020 = (int)(*(long *)((char *)pkt + 0x50) & 0x7FFF);
    if (((unsigned int)img & 0x70000000) == 0x70000000) {
        *(volatile int *)0x1000A010 = ((unsigned int)img & 0x0FFFFFFF) | 0x80000000;
    } else {
        *(volatile int *)0x1000A010 = (unsigned int)img & 0x0FFFFFFF;
    }
    *(volatile int *)0x1000A000 = 0x101;
    return 0;
}

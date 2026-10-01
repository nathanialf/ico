/* libgraph.a member graph017.o */
#include <stdio.h>
#include <eeregs.h>

int sceGsExecLoadImage(void *pkt, void *img)
{
    unsigned int i = 0;

    while (*D2_CHCR & 0x100) {
        if (i++ > 0x1000000) {
            printf("sceGsExecLoadImage: DMA Ch.2 does not terminate\r\n");
            return -1;
        }
    }
    *D2_QWC = 6;
    if (((unsigned int)pkt & 0x70000000) == 0x70000000) {
        *D2_MADR = ((unsigned int)pkt & 0x0FFFFFFF) | 0x80000000;
    } else {
        *D2_MADR = (unsigned int)pkt & 0x0FFFFFFF;
    }
    *D2_CHCR = 0x101;
    while (*D2_CHCR & 0x100) {
        if (i++ > 0x1000000) {
            printf("sceGsExecLoadImage: DMA Ch.2 does not terminate\r\n");
            return -1;
        }
    }
    *D2_QWC = (int)(*(long *)((char *)pkt + 0x50) & 0x7FFF);
    if (((unsigned int)img & 0x70000000) == 0x70000000) {
        *D2_MADR = ((unsigned int)img & 0x0FFFFFFF) | 0x80000000;
    } else {
        *D2_MADR = (unsigned int)img & 0x0FFFFFFF;
    }
    *D2_CHCR = 0x101;
    return 0;
}

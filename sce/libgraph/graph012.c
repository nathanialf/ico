/* libgraph.a member graph012.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int printf(const char *fmt, ...);

#define GS_SYNCPATH_DUMP()                                                                         \
    printf("\t<D1_CHCR=%08x:", *(volatile int *)0x10009000);                                       \
    printf("D1_TADR=%08x:", *(volatile int *)0x10009030);                                          \
    printf("D1_MADR=%08x:", *(volatile int *)0x10009010);                                          \
    printf("D1_QWC=%08x>\r\n", *(volatile int *)0x10009020);                                       \
    printf("\t<D2_CHCR=%08x:", *(volatile int *)0x1000A000);                                       \
    printf("D2_TADR=%08x:", *(volatile int *)0x1000A030);                                          \
    printf("D2_MADR=%08x:", *(volatile int *)0x1000A010);                                          \
    printf("D2_QWC=%08x>\r\n", *(volatile int *)0x1000A020);                                       \
    printf("\t<VIF1_STAT=%08x:", *(volatile int *)0x10003C00);                                     \
    printf("GIF_STAT=%08x>\r\n", *(volatile int *)0x10003020);                                     \
    return -1

int sceGsSyncPath(int mode)
{
    unsigned int i = 0;
    int r;
    int v;

    if (mode == 0) {
        while (*(volatile int *)0x10009000 & 0x100) {
            if (i++ > 0x1000000) {
                printf("sceGsSyncPath: DMA Ch.1 does not terminate\r\n");
                GS_SYNCPATH_DUMP();
            }
        }
        while (*(volatile int *)0x1000A000 & 0x100) {
            if (i++ > 0x1000000) {
                printf("sceGsSyncPath: DMA Ch.2 does not terminate\r\n");
                GS_SYNCPATH_DUMP();
            }
        }
        while (*(volatile int *)0x10003C00 & 0x1F000003) {
            if (i++ > 0x1000000) {
                printf("sceGsSyncPath: VIF1 does not terminate\r\n");
                GS_SYNCPATH_DUMP();
            }
        }
        __asm__ __volatile__("cfc2.ni %0, $vi29" : "=r"(v));
        while (v & 0x100) {
            if (i++ > 0x1000000) {
                printf("sceGsSyncPath: VU1 does not terminate\r\n");
                GS_SYNCPATH_DUMP();
            }
            __asm__ __volatile__("cfc2.ni %0, $vi29" : "=r"(v));
        }
        while (*(volatile int *)0x10003020 & 0xC00) {
            if (i++ > 0x1000000) {
                printf("sceGsSyncPath: GIF does not terminate\r\n");
                GS_SYNCPATH_DUMP();
            }
        }
        return 0;
    }
    r = 0;
    if (*(volatile int *)0x10009000 & 0x100) {
        r |= 1;
    }
    if (*(volatile int *)0x1000A000 & 0x100) {
        r |= 2;
    }
    if (*(volatile int *)0x10003C00 & 0x1F000003) {
        r |= 4;
    }
    __asm__ __volatile__("cfc2.ni %0, $vi29" : "=r"(v));
    if (v & 0x100) {
        r |= 8;
    }
    if (*(volatile int *)0x10003020 & 0xC00) {
        r |= 0x10;
    }
    return r;
}

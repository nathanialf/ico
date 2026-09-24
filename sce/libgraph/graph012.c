/* libgraph.a member graph012.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int printf(const char *fmt, ...);
extern char D_00636150[];
extern char D_00636180[];
extern char D_00636190[];
extern char D_006361A0[];
extern char D_006361B0[];
extern char D_006361C0[];
extern char D_006361D0[];
extern char D_006361E0[];
extern char D_006361F0[];
extern char D_00636200[];
extern char D_00636218[];
extern char D_00636230[];
extern char D_00636260[];
extern char D_00636290[];
extern char D_006362B8[];

#define GS_SYNCPATH_DUMP()                                                                         \
    printf(D_00636180, *(volatile int *)0x10009000);                                               \
    printf(D_00636190, *(volatile int *)0x10009030);                                               \
    printf(D_006361A0, *(volatile int *)0x10009010);                                               \
    printf(D_006361B0, *(volatile int *)0x10009020);                                               \
    printf(D_006361C0, *(volatile int *)0x1000A000);                                               \
    printf(D_006361D0, *(volatile int *)0x1000A030);                                               \
    printf(D_006361E0, *(volatile int *)0x1000A010);                                               \
    printf(D_006361F0, *(volatile int *)0x1000A020);                                               \
    printf(D_00636200, *(volatile int *)0x10003C00);                                               \
    printf(D_00636218, *(volatile int *)0x10003020);                                               \
    return -1

int sceGsSyncPath(int mode)
{
    unsigned int i = 0;
    int r;
    int v;

    if (mode == 0) {
        while (*(volatile int *)0x10009000 & 0x100) {
            if (i++ > 0x1000000) {
                printf(D_00636150);
                GS_SYNCPATH_DUMP();
            }
        }
        while (*(volatile int *)0x1000A000 & 0x100) {
            if (i++ > 0x1000000) {
                printf(D_00636230);
                GS_SYNCPATH_DUMP();
            }
        }
        while (*(volatile int *)0x10003C00 & 0x1F000003) {
            if (i++ > 0x1000000) {
                printf(D_00636260);
                GS_SYNCPATH_DUMP();
            }
        }
        __asm__ __volatile__("cfc2.ni %0, $vi29" : "=r"(v));
        while (v & 0x100) {
            if (i++ > 0x1000000) {
                printf(D_00636290);
                GS_SYNCPATH_DUMP();
            }
            __asm__ __volatile__("cfc2.ni %0, $vi29" : "=r"(v));
        }
        while (*(volatile int *)0x10003020 & 0xC00) {
            if (i++ > 0x1000000) {
                printf(D_006362B8);
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

/* libgraph.a member graph008.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern char D_00636120[];
extern void printf(char *fmt);

int sceGsPutDrawEnv(void *a0)
{
    unsigned int count;
    int qwc;

    count = 0;
    while (*(volatile int *)0x1000A000 & 0x100) {
        if (count++ > 0x1000000) {
            printf(D_00636120);
            return -1;
        }
    }
    qwc = *(long long *)a0 & 0x7FFF;
    *(volatile int *)0x1000A020 = qwc + 1;
    if (((unsigned int)a0 & 0x70000000) == 0x70000000)
        *(volatile int *)0x1000A010 = ((unsigned int)a0 & 0xFFFFFFF) | 0x80000000;
    else
        *(volatile int *)0x1000A010 = (unsigned int)a0 & 0xFFFFFFF;
    *(volatile int *)0x1000A000 = 0x101;
    return 0;
}

extern int sceGsPutDrawEnv();

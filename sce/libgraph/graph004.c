/* libgraph.a member graph004.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern void *sceGsGetGParam(void);

void sceGsPutDispEnv(void *a0)
{
    long *s = (long *)a0;
    if (*(short *)((char *)sceGsGetGParam() + 6) == 1) {
        *(volatile long *)0x12000000 = s[0];
        *(volatile long *)0x12000070 = s[2];
        *(volatile long *)0x12000080 = s[3];
        *(volatile long *)0x120000C0 = s[4];
    } else {
        *(volatile long *)0x12000000 = s[0];
        *(volatile long *)0x12000020 = s[1];
        *(volatile long *)0x12000090 = s[2];
        *(volatile long *)0x120000A0 = s[3];
        *(volatile long *)0x120000E0 = s[4];
    }
}

/* libgraph.a member graph011.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern void *sceGsGetGParam(void);
extern void VSync(void);
extern long VSync2(void);

int sceGsSyncV(void)
{
    char *p = (char *)sceGsGetGParam();
    long c;

    if (*(int *)(p + 8) == 0) {
        VSync();
        if (*(short *)p != 1) {
            return 1;
        }
        return (int)((*(volatile unsigned long *)0x12001000 >> 13) & 1);
    }
    c = VSync2();
    c = (c >> 13) & 1;
    if (*(short *)p != 1) {
        return 1;
    }
    return (int)c;
}

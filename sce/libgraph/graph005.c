/* libgraph.a member graph005.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <libgraph.h>

typedef struct {
    unsigned short f0;     /* 0x0 */
    unsigned short f2;     /* 0x2 */
    unsigned short f4;     /* 0x4 */
    unsigned short f6;     /* 0x6 */
    unsigned long long f8; /* 0x8 */
} GParam;

short sceGszbufaddr(short a0, short a1, short a2)
{
    GParam *gp;
    int h;
    int w;

    gp = (GParam *)sceGsGetGParam();
    h = (a1 + 0x3F) / 0x40;
    if (a0 & 2)
        w = (a2 + 0x3F) / 0x40;
    else
        w = (a2 + 0x1F) / 0x20;
    if (gp->f0 == 1 && gp->f4 == 0)
        return h * w;
    return h * w * 2;
}

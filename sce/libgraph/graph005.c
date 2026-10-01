/* libgraph.a member graph005.o */
#include <libgraph.h>

/* libgraph.h's sceGsGParam as this member reads it: the modes unsigned
   (lhu), and the INTC pair as one doubleword, whose 8-byte alignment the
   member's code shows. */
typedef struct {
    unsigned short inter;    /* 0x0 */
    unsigned short omode;    /* 0x2 */
    unsigned short ffmd;     /* 0x4 */
    unsigned short version;  /* 0x6 */
    unsigned long long intc; /* 0x8, intcUsed and handler */
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
    if (gp->inter == 1 && gp->ffmd == 0)
        return h * w;
    return h * w * 2;
}

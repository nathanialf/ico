/* libgraph.a member graph020.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int GsGetIMR(void);
extern int GsPutIMR(int a0);

int sceGsPutIMR(void *a0)
{
    int r = GsGetIMR();
    GsPutIMR((int)a0);
    return r;
}

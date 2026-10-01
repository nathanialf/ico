/* libgraph.a member graph020.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <libgraph.h>
#include <eekernel.h>

unsigned long sceGsPutIMR(unsigned long imr)
{
    unsigned long r = GsGetIMR();
    GsPutIMR(imr);
    return r;
}

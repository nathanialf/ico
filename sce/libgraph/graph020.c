/* libgraph.a member graph020.o */
#include <libgraph.h>
#include <eekernel.h>

unsigned long sceGsPutIMR(unsigned long imr)
{
    unsigned long r = GsGetIMR();
    GsPutIMR(imr);
    return r;
}

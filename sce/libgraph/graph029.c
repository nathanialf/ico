/* libgraph.a member graph029.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <libgraph.h>
#include <eekernel.h>

int sceGsGetIMR(void)
{
    return GsGetIMR();
}

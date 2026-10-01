/* libgraph.a member graph011.o */
#include <libgraph.h>
#include <eeregs.h>
#include <eekernel.h>

int sceGsSyncV(int mode)
{
    sceGsGParam *gp = sceGsGetGParam();
    long c;

    if (gp->intcUsed == 0) {
        VSync();
        if (gp->inter != 1) {
            return 1;
        }
        return (int)((*GS_CSR >> 13) & 1);
    }
    c = VSync2();
    c = (c >> 13) & 1;
    if (gp->inter != 1) {
        return 1;
    }
    return (int)c;
}

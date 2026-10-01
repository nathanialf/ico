/* libgraph.a member graph011.o */
#include <libgraph.h>
#include <eeregs.h>
#include <eekernel.h>

int sceGsSyncV(int mode)
{
    char *p = (char *)sceGsGetGParam();
    long c;

    if (*(int *)(p + 8) == 0) {
        VSync();
        if (*(short *)p != 1) {
            return 1;
        }
        return (int)((*GS_CSR >> 13) & 1);
    }
    c = VSync2();
    c = (c >> 13) & 1;
    if (*(short *)p != 1) {
        return 1;
    }
    return (int)c;
}

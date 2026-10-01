/* libpkt.a member vifpk026.o */
#include <libpkt.h>

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

int sceVif1PkReset(int *a0)
{
    int v = a0[1];
    a0[2] = 0;
    a0[0] = v;
    return v;
}

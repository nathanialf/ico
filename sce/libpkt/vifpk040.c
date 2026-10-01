/* libpkt.a member vifpk040.o */

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

int sceVif1PkCloseDirectCode(Pool241748 *a0)
{
    int n = (int)a0->end - 4;
    int *p = a0->cur;
    a0->cur = 0;
    n -= (int)p;
    n = (unsigned)(n >> 2) >> 2;
    *p = *p + n;
    return n;
}

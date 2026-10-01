/* libpkt.a member vifpk025.o */
#include <libpkt.h>

/* the member's .data: the library's build stamp */
static char scePktVersion[16] = "PsIIlibpkt  2200"; /* derived name */

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

void sceVif1PkInit(int *a0, int a1)
{
    a0[1] = a1;
    a0[0] = a1;
    a0[2] = 0;
}

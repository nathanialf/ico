/* libgraph.a member graph014.o */
#include <libgraph.h>

/* R5900 opcodes with no C spelling.  Defined in this member. */
#define SYNC() __asm__ __volatile__("sync" : : : "memory")

int sceGsSetDefAlphaEnv(long long *a0, int a1)
{
    short t = a1;
    a0[1] = 0x42;
    a0[0] = 0x44;
    a0[3] = 0x49;
    a0[2] = t;
    a0[5] = 0x3B;
    a0[4] = 0x000000810000807FLL;
    a0[7] = 0x4A;
    a0[6] = 0;
    SYNC();
    return 4;
}

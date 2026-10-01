/* libgraph.a member graph014.o */
#include <libgraph.h>

/* R5900 opcodes with no C spelling.  Defined in this member. */
#define SYNC() __asm__ __volatile__("sync" : : : "memory")

int sceGsSetDefAlphaEnv(long long *pkt, int pabe)
{
    short t = pabe;
    pkt[1] = 0x42;
    pkt[0] = 0x44;
    pkt[3] = 0x49;
    pkt[2] = t;
    pkt[5] = 0x3B;
    pkt[4] = 0x000000810000807FLL;
    pkt[7] = 0x4A;
    pkt[6] = 0;
    SYNC();
    return 4;
}

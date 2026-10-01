/* libpkt.a member vifpk044.o */
#include <libpkt.h>

void sceVif1PkAlign(sceVif1Packet *pkt, int bit, int pos)
{
    unsigned int m = 0xFFFFFFFF >> (32 - ((bit + 2) & 31));
    unsigned int *p = pkt->cur;
    unsigned int *q;
    unsigned int a = ((unsigned int)p & ~m) + pos * 4;

    if (a < (unsigned int)p) {
        /* one past the wrapped address, then up by the block mask */
        unsigned int t = a + 1;
        a = t + m;
    }
    /* clear the words up to a, advancing the packet pointer */
    if ((unsigned int)p < a) {
        goto fill;
        do {
            p = q;
        fill:
            q = p + 1;
            *p = 0;
            pkt->cur = q;
        } while ((unsigned int)q < a);
    }
}

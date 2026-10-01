/* libpkt.a member vifpk027.o */
#include <libpkt.h>

unsigned int *sceVif1PkTerminate(sceVif1Packet *pkt)
{
    unsigned int *p = pkt->cur;
    unsigned int *q = pkt->dmaTag;
    while ((int)p & 0xC) {
        *p = 0;
        p++;
    }
    if (q) {
        int n = (((char *)p - (char *)q) >> 4) - 1;
        *q += n;
    }
    pkt->cur = p;
    pkt->dmaTag = 0;
    return p;
}

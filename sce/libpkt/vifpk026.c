/* libpkt.a member vifpk026.o */
#include <libpkt.h>

unsigned int *sceVif1PkReset(sceVif1Packet *pkt)
{
    unsigned int *v = pkt->base;
    pkt->dmaTag = 0;
    pkt->cur = v;
    return v;
}

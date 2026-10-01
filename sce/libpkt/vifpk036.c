/* libpkt.a member vifpk036.o */
#include <libpkt.h>

void sceVif1PkEnd(sceVif1Packet *pkt, int code)
{
    unsigned int *p;
    pkt->dmaTag = sceVif1PkTerminate(pkt);
    p = pkt->cur;
    *p++ = code | 0x70000000;
    pkt->vifCode = 0;
    pkt->cur = p + 1;
    *p = 0;
}

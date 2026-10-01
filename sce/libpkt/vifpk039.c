/* libpkt.a member vifpk039.o */
#include <libpkt.h>

void sceVif1PkOpenDirectCode(sceVif1Packet *pkt, int irq)
{
    unsigned int *v;
    unsigned int w;
    sceVif1PkAlign(pkt, 2, 3);
    v = pkt->cur;
    w = irq ? 0xD0000000 : 0x50000000;
    *v = w;
    pkt->vifCode = v;
    pkt->cur = v + 1;
}

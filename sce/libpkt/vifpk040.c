/* libpkt.a member vifpk040.o */
#include <libpkt.h>

int sceVif1PkCloseDirectCode(sceVif1Packet *pkt)
{
    int n = (int)pkt->cur - 4;
    unsigned int *p = pkt->vifCode;
    pkt->vifCode = 0;
    n -= (int)p;
    n = (unsigned)(n >> 2) >> 2;
    *p = *p + n;
    return n;
}

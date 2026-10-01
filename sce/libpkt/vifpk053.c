/* libpkt.a member vifpk053.o */
#include <libpkt.h>

void sceVif1PkAddGsData(sceVif1Packet *pkt, long long data)
{
    unsigned int *p = pkt->cur;
    *p++ = (int)data;
    pkt->cur = p + 1;
    *p = (int)(data >> 32);
}

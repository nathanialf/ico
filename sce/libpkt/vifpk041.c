/* libpkt.a member vifpk041.o */
#include <libpkt.h>

void sceVif1PkOpenGifTag(sceVif1Packet *pkt, u_long128 tag)
{
    unsigned int *p = pkt->cur;
    *(u_long128 *)p = tag;
    pkt->gifTag = p;
    pkt->cur = p + 4;
}

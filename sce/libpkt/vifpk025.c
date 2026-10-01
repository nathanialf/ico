/* libpkt.a member vifpk025.o */
#include <libpkt.h>

/* the member's .data: the library's build stamp */
static char scePktVersion[16] = "PsIIlibpkt  2200"; /* derived name */

void sceVif1PkInit(sceVif1Packet *pkt, unsigned int *buf)
{
    pkt->base = buf;
    pkt->cur = buf;
    pkt->dmaTag = 0;
}

/* libpkt.a member vifpk042.o */
#include <libpkt.h>

void sceVif1PkCloseGifTag(sceVif1Packet *pkt)
{
    unsigned long long tag;
    unsigned int *p;
    unsigned int *cur;
    unsigned int *q;
    unsigned int n;
    unsigned long long flg;
    unsigned int nreg;

    p = pkt->gifTag;
    cur = pkt->cur;
    tag = *(unsigned long long *)p;
    n = (((int)cur - (int)p) >> 3) - 2;
    flg = (tag >> 58) & 3;
    if (flg != 1)
        n >>= 1;
    if (flg != 2) {
        nreg = tag >> 60;
        if (nreg == 0)
            nreg = 16;
        n = (n + nreg - 1) / nreg;
    }
    pkt->gifTag = 0;
    *(unsigned long long *)p = tag + n;
    q = cur;
    while ((int)q & 0xC) {
        *q = 0;
        q++;
    }
    pkt->cur = q;
}

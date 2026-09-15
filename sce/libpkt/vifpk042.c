/* libpkt.a member vifpk042.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

void sceVif1PkCloseGifTag(void *a0)
{
    unsigned long long tag;
    unsigned int *p;
    unsigned int *cur;
    unsigned int *q;
    unsigned int n;
    unsigned long long flg;
    unsigned int nreg;

    p = *(unsigned int **)((char *)a0 + 0x14);
    cur = *(unsigned int **)a0;
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
    *(unsigned int **)((char *)a0 + 0x14) = 0;
    *(unsigned long long *)p = tag + n;
    q = cur;
    while ((int)q & 0xC) {
        *q = 0;
        q++;
    }
    *(unsigned int **)a0 = q;
}

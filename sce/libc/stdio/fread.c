/* libc.a member fread.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);
extern int __srefill(StreamBuf *s);

int fread(char *dst, int size, int count, StreamBuf *s)
{
    unsigned int total = count * size;
    int len;
    unsigned int avail;
    unsigned int total_orig;
    char *p;

    if (total == 0) {
        return 0;
    }
    len = s->len;
    if (len < 0) {
        s->len = 0;
        len = 0;
    }
    avail = len;
    total_orig = total;
    p = dst;
    if (avail < total) {
        do {
            memcpy(p, s->pos, avail);
            total -= avail;
            p += avail;
            s->pos += avail;
            if (__srefill(s) != 0) {
                return (total_orig - total) / size;
            }
            avail = s->len;
        } while (avail < total);
    }
    memcpy(p, s->pos, total);
    s->len -= total;
    s->pos += total;
    return count;
}

/* libc.a member strtok_r.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int strtok_r(int a0, int a1, int a2)
{
    char *s = (char *)a0;
    char *delim = (char *)a1;
    char **last = (char **)a2;
    char *spanp;
    char *tok;
    int c;
    int sc;

    if (s == 0 && (s = *last) == 0) {
        return 0;
    }

cont:
    c = *s++;
    for (spanp = delim; (sc = *spanp++) != 0;) {
        if (c == sc) {
            goto cont;
        }
    }

    if (c == 0) {
        *last = 0;
        return 0;
    }
    tok = s - 1;

    for (;;) {
        c = *s++;
        spanp = delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0) {
                    s = 0;
                } else {
                    s[-1] = 0;
                }
                *last = s;
                return (int)tok;
            }
        } while (sc != 0);
    }
}

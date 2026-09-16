/* libc.a member vfscanf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdio/vfscanf", __svfscanf);

char *__sccl(char *tab, char *fmt)
{
    int c;
    int n;
    int v;

    c = *fmt++;
    if (c == '^') {
        v = 1;
        c = *fmt++;
    } else {
        v = 0;
    }

    for (n = 0; n < 256; n++) {
        tab[n] = v;
    }
    if (c == 0) {
        return fmt - 1;
    }

    v = 1 - v;
    for (;;) {
        tab[c] = v;
    doswitch:
        n = *fmt++;
        switch (n) {
        case 0:
            return fmt - 1;

        case '-':
            n = *fmt;
            if (n == ']' || n < c) {
                c = '-';
                break;
            }
            fmt++;
            do {
                tab[++c] = v;
            } while (c < n);
            goto doswitch;

        case ']':
            return fmt;

        default:
            c = n;
            break;
        }
    }
}

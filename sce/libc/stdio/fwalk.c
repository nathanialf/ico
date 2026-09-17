/* libc.a member fwalk.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);

typedef struct _glue {
    struct _glue *next; /* 0x0 */
    int niobs;          /* 0x4 */
    char *iobs;         /* 0x8 */
} Glue;

int _fwalk(char *ptr, int (*function)())
{
    char *fp;
    int n, ret = 0;
    Glue *g;

    for (g = (Glue *)(ptr + 0x1D8); g != 0; g = g->next)
        for (fp = g->iobs, n = g->niobs; --n >= 0; fp += 0x58)
            if (*(short *)(fp + 0xC) != 0)
                ret |= function(fp);

    return ret;
}

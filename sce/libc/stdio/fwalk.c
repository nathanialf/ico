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

int _fwalk(Reent *ptr, int (*function)())
{
    Fil *fp;
    int n, ret = 0;
    Glue *g;

    for (g = &ptr->glue; g != 0; g = g->next)
        for (fp = g->iobs, n = g->niobs; --n >= 0; fp++)
            if (fp->flags != 0)
                ret |= function(fp);

    return ret;
}

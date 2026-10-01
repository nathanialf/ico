/* libc.a member fwalk.o */
#include <reent.h>
#include <libc_internal.h>

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

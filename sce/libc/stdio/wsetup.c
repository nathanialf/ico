/* libc.a member wsetup.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>
#include <stdlib.h>
#include <libc_internal.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int __swsetup(Fil *fp)
{
    do {
        if (fp->data == 0) {
            fp->data = _impure_ptr;
        }
        if (!fp->data->sdidinit) {
            __sinit(fp->data);
        }
    } while (0);

    if ((fp->flags & 8) == 0) {
        if ((fp->flags & 0x10) == 0) {
            return -1;
        }
        if (fp->flags & 4) {
            if (fp->ub.base != 0) {
                if (fp->ub.base != fp->ubuf) {
                    _free_r(fp->data, fp->ub.base);
                }
                fp->ub.base = 0;
            }
            fp->flags &= ~0x24;
            fp->r = 0;
            fp->p = fp->bf.base;
        }
        fp->flags |= 8;
    }

    if (fp->bf.base == 0) {
        __smakebuf(fp);
    }
    if (fp->flags & 1) {
        fp->w = 0;
        fp->lbfsize = -fp->bf.size;
    } else {
        fp->w = (fp->flags & 2) ? 0 : fp->bf.size;
    }
    return 0;
}

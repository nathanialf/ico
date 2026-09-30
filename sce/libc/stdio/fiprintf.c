/* libc.a member fiprintf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern char D_00637E38[];
extern int fiprintf(void *fp, void *fmt, ...);
extern void abort(void);
extern int vfiprintf(void *fp, void *fmt, void *args);

int fiprintf(void *fp, void *fmt, ...)
{
    void *args = (char *)__builtin_next_arg(fmt) - 0x30;
    return vfiprintf(fp, fmt, args);
}

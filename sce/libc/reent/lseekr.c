/* libc.a member lseekr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <unistd.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

/* kept local: errno.h declares it as `int errno` */
extern int errno[];

int _lseek_r(int *self, int a1, int a2, int a3)
{
    int ret;
    errno[0] = 0;
    ret = lseek(a1, a2, a3);
    if (ret == -1) {
        if (errno[0] != 0) {
            self[0] = errno[0];
        }
    }
    return ret;
}

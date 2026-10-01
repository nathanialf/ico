/* libc.a member signalr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <signal.h>
#include <unistd.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

/* kept local: errno.h declares it as `int errno` */
extern int errno[];

int _kill_r(int *self, int a1, int a2)
{
    int ret;
    errno[0] = 0;
    ret = kill(a1, a2);
    if (ret == -1) {
        if (errno[0] != 0) {
            self[0] = errno[0];
        }
    }
    return ret;
}

int _getpid_r(void)
{
    return getpid();
}

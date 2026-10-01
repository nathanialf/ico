/* libc.a member sbrkr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <unistd.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

/* We use the errno variable used by the system dependent layer.  Common,
 * so the linker puts it in the small common section (MAIN.MAP line 7658). */
int errno;

int _sbrk_r(int *self, int a1)
{
    unsigned int ret;
    errno = 0;
    ret = sbrk(a1);
    if (ret == 0xFFFFFFFF) {
        if (errno != 0) {
            self[0] = errno;
        }
    }
    return ret;
}

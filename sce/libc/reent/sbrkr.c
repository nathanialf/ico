/* libc.a member sbrkr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <unistd.h>

/* We use the errno variable used by the system dependent layer.  Common,
 * so the linker puts it in the small common section (MAIN.MAP line 7658). */
int errno;

int _sbrk_r(Reent *ptr, int incr)
{
    unsigned int ret;
    errno = 0;
    ret = sbrk(incr);
    if (ret == 0xFFFFFFFF) {
        if (errno != 0) {
            ptr->err = errno;
        }
    }
    return ret;
}

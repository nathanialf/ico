/* libc.a member closer.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <errno.h>
#include <unistd.h>

int _close_r(Reent *ptr, int fd)
{
    int ret;
    errno = 0;
    ret = close(fd);
    if (ret == -1) {
        if (errno != 0) {
            ptr->err = errno;
        }
    }
    return ret;
}

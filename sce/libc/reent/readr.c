/* libc.a member readr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <unistd.h>
#include <errno.h>

long _read_r(Reent *ptr, int fd, void *buf, int cnt)
{
    long ret;
    errno = 0;
    ret = read(fd, buf, cnt);
    if (ret == -1) {
        if (errno != 0) {
            ptr->err = errno;
        }
    }
    return ret;
}

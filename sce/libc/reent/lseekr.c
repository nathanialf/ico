/* libc.a member lseekr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <errno.h>
#include <unistd.h>

long _lseek_r(Reent *ptr, int fd, long pos, int whence)
{
    long ret;
    errno = 0;
    ret = lseek(fd, pos, whence);
    if (ret == -1) {
        if (errno != 0) {
            ptr->err = errno;
        }
    }
    return ret;
}

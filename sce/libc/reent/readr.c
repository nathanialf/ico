/* libc.a member readr.o */
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

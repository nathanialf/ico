/* libc.a member writer.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <unistd.h>
#include <errno.h>

long _write_r(Reent *ptr, int fd, const void *buf, int cnt)
{
    long ret;
    errno = 0;
    ret = write(fd, buf, cnt);
    if (ret == -1) {
        if (errno != 0) {
            ptr->err = errno;
        }
    }
    return ret;
}

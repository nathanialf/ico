/* libc.a member closer.o */
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

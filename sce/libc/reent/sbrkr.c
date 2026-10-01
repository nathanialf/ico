/* libc.a member sbrkr.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <unistd.h>

/* We use the errno variable used by the system dependent layer.  Common,
 * so the linker puts it in the small common section. */
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

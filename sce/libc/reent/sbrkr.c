/* libc.a member sbrkr.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <unistd.h>

/* We use the errno variable used by the system dependent layer.  Common,
 * so the linker puts it in the small common section. */
int errno;

void *_sbrk_r(Reent *ptr, int incr)
{
    char *ret;
    errno = 0;
    ret = sbrk(incr);
    if (ret == (void *)-1) {
        if (errno != 0) {
            ptr->err = errno;
        }
    }
    return ret;
}

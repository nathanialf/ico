/* libc.a member errno.o */
#include <reent.h>
#include <errno.h>

int *__errno(void)
{
    return &_impure_ptr->err;
}

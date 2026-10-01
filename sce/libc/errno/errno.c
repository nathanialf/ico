/* libc.a member errno.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>
#include <errno.h>

int *__errno(void)
{
    return &_impure_ptr->err;
}

/* libc.a member printf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <reent.h>
#include <libc_internal.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int _printf_r(int *self, int b, ...)
{
    void *args = (char *)__builtin_next_arg(b) - 0x30;
    return _vfprintf_r(self, self[2], b, args);
}

int printf(const char *fmt, ...)
{
    void *args = (char *)__builtin_next_arg(fmt) - 0x38;
    int s = (int)_impure_ptr;
    *(int *)(*(int *)(s + 8) + 0x54) = s;
    return vfprintf(*(int *)(s + 8), fmt, args);
}

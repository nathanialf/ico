/* libc.a member printf.o */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <reent.h>
#include <libc_internal.h>

int _printf_r(Reent *ptr, const char *fmt, ...)
{
    char *ap = (char *)__builtin_next_arg(fmt) - 0x30;
    return _vfprintf_r(ptr, ptr->out, fmt, ap);
}

int printf(const char *fmt, ...)
{
    void *args = (char *)__builtin_next_arg(fmt) - 0x38;
    int s = (int)_impure_ptr;
    *(int *)(*(int *)(s + 8) + 0x54) = s;
    return vfprintf(*(int *)(s + 8), fmt, args);
}

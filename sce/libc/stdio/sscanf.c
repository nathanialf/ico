/* libc.a member sscanf.o */
#include <string.h>
#include <reent.h>
#include <libc_internal.h>
#include <stdio.h>

int eofread(void *cookie, char *buf, int len)
{
    return 0;
}

int sscanf(const char *str, const char *fmt, ...)
{
    Fil f;
    char *va;
    f.flags = 4;
    f.bf.base = f.p = (unsigned char *)str;
    f.bf.size = f.r = strlen(str);
    f.read = eofread;
    f.ub.base = 0;
    f.lb.base = 0;
    f.data = _impure_ptr;
    va = (char *)__builtin_next_arg(fmt) - 48;
    return __svfscanf(&f, fmt, va);
}

/* libc.a member vsprintf.o */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <reent.h>

int vsprintf(char *out, const char *fmt, char *ap)
{
    char s[0x60];
    int n;
    *(void **)(s + 0x0) = out;
    *(int *)(s + 0x8) = 0x7FFFFFFF;
    *(short *)(s + 0xC) = 0x208;
    *(void **)(s + 0x10) = out;
    *(int *)(s + 0x14) = 0x7FFFFFFF;
    *(int *)(s + 0x54) = (int)_impure_ptr;
    n = vfprintf(s, fmt, ap);
    *(char *)(*(void **)(s + 0x0)) = 0;
    return n;
}

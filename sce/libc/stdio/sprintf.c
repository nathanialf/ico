/* libc.a member sprintf.o */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <reent.h>

int _sprintf_r(void *ptr, int str, int fmt, ...)
{
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(fmt) - 40;
    int n;
    *(int *)(buf + 0x0) = str;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = str;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = (int)ptr;
    n = vfprintf(buf, fmt, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
    return n;
}

int sprintf(char *str, const char *fmt, ...)
{
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(fmt) - 48;
    int n;
    *(int *)(buf + 0x0) = (int)str;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = (int)str;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = (int)_impure_ptr;
    n = vfprintf(buf, fmt, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
    return n;
}

/* libc.a member sprintf.o */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <reent.h>

int _sprintf_r(void *a0, int a1, int a2, ...)
{
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(a2) - 40;
    int n;
    *(int *)(buf + 0x0) = a1;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = a1;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = (int)a0;
    n = vfprintf(buf, a2, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
    return n;
}

int sprintf(void *a0, int a1, ...)
{
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(a1) - 48;
    int n;
    *(int *)(buf + 0x0) = (int)a0;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = (int)a0;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = (int)_impure_ptr;
    n = vfprintf(buf, a1, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
    return n;
}

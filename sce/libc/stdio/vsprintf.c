/* libc.a member vsprintf.o */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int vsprintf(void *out, void *a1, void *a2)
{
    char s[0x60];
    int n;
    *(void **)(s + 0x0) = out;
    *(int *)(s + 0x8) = 0x7FFFFFFF;
    *(short *)(s + 0xC) = 0x208;
    *(void **)(s + 0x10) = out;
    *(int *)(s + 0x14) = 0x7FFFFFFF;
    *(int *)(s + 0x54) = (int)_impure_ptr;
    n = vfprintf(s, a1, a2);
    *(char *)(*(void **)(s + 0x0)) = 0;
    return n;
}

#include "matching.h"

extern int func_00268DA0(void *out, int x, void *args);
extern void func_001A40C8(int *a, int *b, int *c, void *p);

void func_001A6AA0(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    func_00268DA0(buf, x, args);
    func_001A40C8(a, b, c, buf);
}

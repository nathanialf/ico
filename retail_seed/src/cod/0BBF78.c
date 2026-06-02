#include "matching.h"

extern int *func_00202208(int *self);
extern void func_00202148(int *self);
extern void func_00203AA0(int x);

void func_001BBF78(int *self)
{
    int *p = func_00202208(self);
    long long v;
    func_00202148(self);
    func_00203AA0(1);
    v = *(long long *)((char *)p + 0x18);
    v |= 1LL << 32;
    *(long long *)((char *)p + 0x18) = v;
}

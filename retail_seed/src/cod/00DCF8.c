#include "matching.h"

extern void func_001182F0(void *out, int *p);
extern float func_0010E950(int x);
extern float func_001183D0(int *self, void *p, float arg);
extern float func_0010E9A0(int x);

void func_0010DCF8(int *self, int a1, int *p)
{
    char buf[0x10];
    int half_pre = a1 << 16;
    int half;
    float f;
    func_001182F0(buf, p);
    half = half_pre >> 17;
    f = func_0010E950(half);
    func_001183D0(self, buf, f);
    *(float *)((char *)self + 0xC) = func_0010E9A0(half);
}

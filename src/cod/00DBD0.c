#include "matching.h"

extern float func_0010E950(int x);
extern float func_001183D0(int *self, float *p, float arg);
extern float func_0010E9A0(int x);

void func_0010DBD0(int *self, int a1, float x, float y, float z)
{
    float buf[4];
    int half_pre = a1 << 16;
    int half;
    float f;
    half = half_pre >> 17;
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    buf[3] = 0;
    f = func_0010E950(half);
    func_001183D0(self, buf, f);
    *(float *)((char *)self + 0xC) = func_0010E9A0(half);
}

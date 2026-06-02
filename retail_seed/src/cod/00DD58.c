#include "matching.h"

extern float func_0010E950(int x);
extern float func_001183D0(int *self, int *param, float arg);
extern float func_0010E9A0(int x);

void func_0010DD58(int *self, int a1, int *param)
{
    int half = ((int)(short)a1) >> 1;
    float f = func_0010E950(half);
    func_001183D0(self, param, f);
    *(float *)((char *)self + 0xC) = func_0010E9A0(half);
}

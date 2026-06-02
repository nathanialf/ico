#include "matching.h"

extern float D_006D0680[];
extern int D_00632D30;

void func_0018CF80(void *dst, float *out) {
    long long *s = (long long *)D_006D0680;
    long long *d = (long long *)dst;
    float val = (float)D_00632D30 / 100.0f;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[3];
    __asm__ __volatile__("" : "+f"(val));
    *out = val;
}

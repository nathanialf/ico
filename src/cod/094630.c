#include "matching.h"

extern int func_00243978(float *a, float *b);
extern void func_0025E5D8(float a, float b);

void func_00194630(float *a0)
{
    float local[3];
    local[0] = a0[0];
    local[1] = 0.0f;
    local[2] = a0[2];
    func_00243978(local, local);
    func_0025E5D8(local[0], local[2]);
}

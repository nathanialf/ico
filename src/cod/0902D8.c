#include "matching.h"

void func_001902D8(int *self, float *out1, volatile float *out2, float *out3)
{
    int *p = (int *)((int *)self[0x15C/4])[0x800/4];
    *out1 = *(float *)((char *)p + 0x30);
    *out2 = *(float *)((char *)p + 0x34);
    if (*(float *)((char *)p + 0x48) < *(float *)((char *)p + 0x34)) {
        *out2 = *(float *)((char *)p + 0x48);
    }
    *out3 = *(float *)((char *)p + 0x40);
}

#include "matching.h"

void func_001902D8(int *a0, float *a1, float *a2, float *a3)
{
    int *sub = (int *)((int *)a0[0x15C / 4])[0x800 / 4];
    *a1 = *(float *)((char *)sub + 0x30);
    *a2 = *(float *)((char *)sub + 0x34);
    if (*(float *)((char *)sub + 0x48) < *(float *)((char *)sub + 0x34)) {
        *a2 = *(float *)((char *)sub + 0x48);
    }
    *a3 = *(float *)((char *)sub + 0x40);
}

TRAILING_PAD_NOP();

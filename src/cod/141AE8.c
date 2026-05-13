#include "matching.h"

extern void *func_00105278(int a0);
extern int func_00243BD8(void *p);
extern void func_001052A8(void *a0);

void func_00241AE8(int a0, void *a1)
{
    void *p = func_00105278(a0);
    func_00243BD8(p);
    *(float *)((char *)a1 + 0xC) = 1.0f;
    func_001052A8(a1);
}

TRAILING_PAD_NOP();

#include "matching.h"

extern int *func_0013EB50(int x);
extern void func_00193848(int *p);
extern int *func_0013EBE0(int *p);

void func_0017DE98(void)
{
    int *p = func_0013EB50(0x21);
    while (p != 0) {
        func_00193848(p);
        p = func_0013EBE0(p);
    }
}

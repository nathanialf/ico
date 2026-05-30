#include "matching.h"

extern void func_00203AA0(int);
extern int func_0017B230(int);
extern void func_00205B30(int, int);

void func_00223E50(int a0)
{
    int s;

    s = a0;
    __asm__ volatile("" : : "r"(&s), "r"(s) : "memory");
    NOP();
    while (func_0017B230(0xEA) == 0) {
        func_00203AA0(1);
    }
    func_00205B30(3, 1);

}

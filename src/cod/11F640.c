#include "matching.h"

extern void func_00203AA0(int);
extern int func_0017D230(int);
extern void func_0017B258(int);

void func_0021F640(int a0)
{
    int s;
    DEFEAT_TCO();
    s = a0;
    __asm__ volatile("" : : "r"(&s), "r"(s) : "memory");
    NOP();
    while (func_0017D230(0x454) == 0) {
        func_00203AA0(1);
    }
    func_0017B258(0xBA);
    DEFEAT_TCO();
}

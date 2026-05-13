#include "matching.h"

extern void func_001297A0(int a, int b, int c);
extern void func_0018CED0(void);
extern void func_00203AA0(int a);
extern int func_0012AA80(int a);
extern int D_00633FAC;

void func_00229E48(volatile int unused)
{
    func_001297A0(0x143, 1, 0);
    func_001297A0(0x144, 1, 0);
    func_0018CED0();
    while (func_0012AA80(0x144) == 0) {
        func_00203AA0(1);
    }
    func_00203AA0(1);
    D_00633FAC = 1;
    func_00203AA0(0);
    DEFEAT_TCO();
}

TRAILING_PAD_NOP();

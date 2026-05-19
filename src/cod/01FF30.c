#include "matching.h"

extern void func_001FBA80(int a0);
extern void func_001FBAA8(int a0, char *a1, int a2);
extern void func_001FB8B8(void);
extern char D_00555830[];

void func_0011FF30(int a0)
{
    func_001FBA80(a0);
    func_001FBAA8(2, D_00555830, 4);
    func_001FB8B8();
}

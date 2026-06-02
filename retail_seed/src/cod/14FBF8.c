#include "matching.h"
#include "regpin.h"

extern int func_00100410(void);
extern int func_001002A0(int a0, int a1, int a2);
extern void func_00100440(void);
extern void func_0024FBD0(void);

void func_0024FBF8(unsigned int a0)
{
    int s0 = (int)&func_0024FBD0;
    int s1 = a0 & 0xFFFF;
    int v;
    v = func_00100410();
    func_001002A0(s1, s0, v);
    func_00100440();
}

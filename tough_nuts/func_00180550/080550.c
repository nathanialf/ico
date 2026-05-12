#include "regpin.h"
extern char D_0055A380[];
extern float D_00630EAC;
extern void func_0012FFF0(char *a0, int a1, float f12, float f13, float f14, float f15, float f16, float f17);

void func_00180550(void)
{
    register int a1 REG("$5");
    a1 = 1;
    func_0012FFF0(D_0055A380, a1, 0.0f, 0.0f, 0.0f, D_00630EAC, 0.0f, 0.5f);
}

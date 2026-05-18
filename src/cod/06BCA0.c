#include "matching.h"

extern void func_00104508(int *dst, int *src);
extern void func_0010A498(int *dst, int *src);
extern int *D_00631AE4;
extern int *D_00631AE8;
extern int D_002882D0[];

void func_0016BCA0(void)
{
    func_00104508(&D_002882D0[0], D_00631AE8);
    func_00104508(&D_002882D0[8], D_00631AE4);
    func_0010A498(&D_002882D0[4], D_00631AE8);
    func_0010A498(&D_002882D0[12], D_00631AE4);
}

#include "matching.h"
#include "regpin.h"

extern int D_0055266C[];
extern void func_002521C0(void);
extern void func_00252058(void);

void func_00252180(void)
{
    int v = D_0055266C[0];
    if (v != 3) {
        func_002521C0();
        DEFEAT_TCO();
    } else {
        func_00252058();
        DEFEAT_TCO();
    }
}

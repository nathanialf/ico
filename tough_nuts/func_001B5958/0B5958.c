#include "regpin.h"

extern int func_00192098(void);
extern void func_0019FF98(int a0, float f1, float f2);
extern float D_0063110C;
extern int D_00633044;

int func_001B5958(void)
{
    if (func_00192098() == 0) {
        register float f12 REG("$f12") = D_0063110C;
        func_0019FF98(D_00633044, f12, 4.0f);
    }
    return -1;
}

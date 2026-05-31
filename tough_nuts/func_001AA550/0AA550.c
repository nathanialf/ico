#include "matching.h"

extern int D_00632C80;
extern void func_00247608(void);

void func_001AA550(int a0)
{
    if (a0 == D_00632C80) {
        D_00632C80 = -1;
    }
    func_00247608();
    DEFEAT_TCO();
}

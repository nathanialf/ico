#include "r5900.h"

extern int  D_00633B8C;
extern char D_0028CA30[];
extern void func_0019E628(char *p);

int func_0023EFF8(void)
{
    if (D_00633B8C != 0) {
        func_0019E628(D_0028CA30);
        D_00633B8C = 0;
    }
    SYNC();
    EI();
    return 0;
}

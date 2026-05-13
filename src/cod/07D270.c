#include "matching.h"

extern int *func_0013EB50(int x);
extern int func_001D3D98(int *p);
extern int *func_0013EBE0(int *p);

int *func_0017D270(int x)
{
    int *p = func_0013EB50(x);
    if (p != 0) {
        do {
            if (func_001D3D98(p) != 0) {
                return p;
            }
            p = func_0013EBE0(p);
        } while (p != 0);
    }
    return 0;
}

TRAILING_PAD_NOP();

#include "regpin.h"

extern char *D_005524A4[];
extern void func_00251CF8(int p, int *args);
extern void func_00252550(int *a0);

void func_00252590(int *a0)
{
    char *p = D_005524A4[0];
    if (p != 0) {
        register int q = *(int *)(p + 0x40);
        if (q != 0) {
            register int r = *(int *)(q + 0xC);
            if (r != 0) {
                int local[2];
                local[0] = 0;
                local[1] = (int)a0;
                func_00251CF8((int)p, local);
                return;
            }
        }
    }
    func_00252550(a0);
}

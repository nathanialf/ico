#include "regpin.h"
#include "matching.h"

extern int D_00552370[];
extern char D_00717BD8[];
extern void func_0024DD30(int a0, int a1, int a2, int a3);

void func_0024DA80(void)
{
    D_00552370[0] = 0;
    {
        register char *t0 REG("$8") = D_00717BD8;
        KEEP_LIVE(t0);
    func_0024DD30(0, 0, 0, 3);
    DEFEAT_TCO();
    }
}

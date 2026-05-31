#include "regpin.h"
#include "matching.h"

extern char D_00717BD8[];
extern void func_0024DD30(int a0, int a1, int a2, int a3);

void func_0024DA50(int a0)
{
    register char *t0 REG("$8");
    LA_SPLIT(t0, D_00717BD8);
    KEEP_LIVE(t0);
    func_0024DD30(a0, 0, 0, 4);
    DEFEAT_TCO();
}

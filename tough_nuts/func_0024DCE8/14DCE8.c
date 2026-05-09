#include "regpin.h"
#include "matching.h"

extern int D_00550910[];
extern char D_00717BD8[];
extern char D_0062E9F0[];
extern void func_001019E0(char *fmt);
extern void func_0024DD30(int a0, int a1, int a2, int a3);

void func_0024DCE8(void)
{
    int v;
    register char *t0 REG("$8");
    v = D_00550910[0];
    if (v > 0) {
        func_001019E0(D_0062E9F0);
    }
    t0 = D_00717BD8;
    KEEP_LIVE(t0);
    func_0024DD30(0, 0, 0, 6);
    DEFEAT_TCO();
}

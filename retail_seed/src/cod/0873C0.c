#include "matching.h"

extern int D_006326D0;
extern int D_00632CBC;
extern unsigned char D_006326D8;
extern void func_001869F8(void);
extern void func_00186978(void);
extern void func_0018CC00(int x);
extern void func_00187308(void);

int func_001873C0(void)
{
    D_00632CBC = 1;
    if (D_006326D0 == 0) {
        func_001869F8();
    }
    func_00186978();
    func_0018CC00(1);
    if (D_006326D8 != 0) {
        D_006326D8 = 0;
        func_00187308();
        return -1;
    }
    return 0;
}

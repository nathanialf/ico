#include "matching.h"

extern void func_0020BF88(void);
extern void func_0020D7E0(void);
extern void func_00203B78(void (*a0)(void), int a1);

void func_0020D7A8(int a0)
{
    int local = a0;
    func_00203B78(func_0020BF88, 0x15);
    func_00203B78(func_0020D7E0, 0x15);
    KEEP_LIVE(&local);
}

#include "matching.h"

extern char D_0061A8A8[];
extern void func_00139D78(int a0, int a1, char *a2, int a3);

void func_001F6E00(int a0, int a1)
{
    func_00139D78(a0, a1, D_0061A8A8, 0x1A8);
    DEFEAT_TCO();
}

#include "matching.h"

extern char D_0061A8A8[];
extern void func_00139D78(int x, int y, char *p, int line);

void func_001F6E00(int x, int y)
{
    func_00139D78(x, y, D_0061A8A8, 0x1A8);
    DEFEAT_TCO();
}

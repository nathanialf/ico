#include "matching.h"

extern void func_001118B8(int x);
extern void func_00111FA8(int x, int y, int z);
extern void func_001114D0(int a, int b, int c, int d);
extern void func_0010F630(void);

int func_001CF8D0(int *self)
{
    func_001118B8(self[0]);
    func_00111FA8(1, self[0xD], 0x80);
    func_001114D0(self[3], self[4], self[1] * 2, 1);
    func_0010F630();
    return 1;
}

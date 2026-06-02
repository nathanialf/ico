#include "matching.h"

extern int func_0025E198(int a, int b);
extern int func_0025E1E8(int a, int b, int c);
extern int func_0025E118(int a);

void func_0023E298(int *self)
{
    func_0025E198(0, 0);
    func_0025E198(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        func_0025E1E8(3, half, half);
    } else {
        func_0025E1E8(1, 0, self[0x5C / 4]);
        func_0025E1E8(2, self[0x5C / 4], 0);
    }
    func_0025E118(3);
    self[0] = 2;
}

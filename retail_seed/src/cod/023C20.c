#include "matching.h"

extern int *D_00631970;
extern void func_00118460(int *self, int p);
extern void func_00117FE8(int p);
extern void func_00117CE0(void);
extern void func_001180C0(int *a, int *b);
extern void func_001182F0(int *a, int *b);

void func_00123C20(int *self, int p)
{
    func_00118460(self, p + 0x830);
    func_00117FE8((int)D_00631970 + 0x80);
    func_00117CE0();
    func_001180C0(self, self);
    func_001182F0(self, self);
}

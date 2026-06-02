#include "common.h"

extern void func_00104F20(void);
extern int func_00105278(void);
extern void func_00118678(int a0);
extern void func_001118B8(int a0);
extern void func_001052A8(void *a0);
extern void func_0011E220(void *a0, int a1, int a2, float f);
extern void func_0010F630(void);
extern void func_00105268(void);

void func_00159C38(void *a0, void *a1, float f)
{
    func_00104F20();
    func_00118678(func_00105278());
    func_001118B8(0xB);
    func_001052A8(a0);
    func_0011E220(a1, 4, 4, f);
    func_0010F630();
    func_00105268();
}

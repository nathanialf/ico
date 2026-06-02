#include "matching.h"

extern void func_0010D540(void *out, void *src);
extern void *func_00105278(void);
extern void func_001185D0(void *a, void *b, void *p);

void func_0010DF70(void *src)
{
    int local[16];
    void *r1, *r2;
    func_0010D540(local, src);
    r1 = func_00105278();
    r2 = func_00105278();
    func_001185D0(r1, r2, local);
}

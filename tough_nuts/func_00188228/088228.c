#include "matching.h"

extern void *D_00632744;
extern int D_00632748;
extern void *func_0018B300(void);
extern void func_001897A8(void);

void func_00188228(void)
{
    char *d;
    int n;
    char *limit;
    char *p;
    int i;
    d = (char *)func_0018B300();
    n = *(int *)(d + 8);
    D_00632744 = d;
    D_00632748 = n;
    limit = d + 0x10 + n * 0x4C;
    if (n > 0) {
        p = d + 0x58;
        i = n;
        do {
            *(int *)p = (int)limit;
            i--;
            p += 0x4C;
        } while (i != 0);
    }
    func_001897A8();
}

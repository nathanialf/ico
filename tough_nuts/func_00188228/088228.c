#include "matching.h"

extern void *D_00632744;
extern int D_00632748;
extern char *func_0018B300(void);
extern void func_001897A8(void);

void func_00188228(void)
{
    char *d = func_0018B300();
    int n = *(int *)(d + 8);
    char *limit;
    D_00632744 = d;
    D_00632748 = n;
    limit = (d + 0x10) + n * 0x4C;
    if (n > 0) {
        char *p = d + 0x58;
        int i = n;
        NOP();
        do {
            *(char **)p = limit;
            i--;
            p += 0x4C;
            NOP();
            NOP();
        } while (i != 0);
    }
    func_001897A8();
}

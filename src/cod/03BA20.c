#include "matching.h"

extern void func_0013A250(int *a, int *b, int c);
extern void func_0013A6C0(int *a, void *b, int c);
extern void func_0013AF88(void);
extern int D_00281630[];
extern int D_006A6D90[];

void func_0013BA20(void)
{
    int local_buf;
    func_0013A250(D_00281630, D_006A6D90, 8);
    while (1) {
        func_0013A6C0(D_00281630, &local_buf, 1);
        func_0013AF88();
    }
}

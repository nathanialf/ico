#include "matching.h"

extern int D_00558C38[];
extern void func_001A6E28(int *a0);
extern void func_00203AA0(int a0);

void func_0015EA80(int a0)
{
    int local = a0;
    func_001A6E28(D_00558C38);
    func_00203AA0(0);
    KEEP_LIVE(&local);
}

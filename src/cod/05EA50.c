#include "matching.h"

extern int D_00558C18[];
extern void func_001A6E28(int *a0);
extern void func_00203AA0(int a0);

void func_0015EA50(int a0)
{
    int local = a0;
    func_001A6E28(D_00558C18);
    func_00203AA0(0);
    KEEP_LIVE(&local);
}

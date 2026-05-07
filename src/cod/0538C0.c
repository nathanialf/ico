#include "matching.h"

extern void func_00203C40(int *a0);
extern void func_00194508(int *a0, int a1);

void func_001538C0(int a0)
{
    int buf[4];
    func_00203C40(buf);
    func_00194508(buf, a0);
    KEEP_LIVE(buf);
}

#include "matching.h"
extern void func_0023D468(int *p);
extern char D_00633B60[];
extern int D_005F3038[];

void func_0023D420(int idx)
{
    int dummy[64];
    int *p;
    if (idx == -1) {
        p = (int *)D_00633B60;
    } else {
        p = (int *)((char *)D_005F3038 + idx * 0x194);
    }
    func_0023D468(p);


}

#include "regpin.h"
extern int func_0018CF60(int x);
extern float func_001F5298(int x);
extern float D_00633B48;
extern int D_00633B4C;
extern int D_00631960;

int func_0023D170(int *self)
{
    register int *self_save REG("$16");
    float f;
    int v0, v1;
    self_save = self;
    v0 = D_00633B4C;
    v1 = D_00631960;
    if (v0 != v1) goto fresh;
    f = D_00633B48;
    goto out;
fresh:
    D_00633B4C = v1;
    v0 = func_0018CF60((int)self_save);
    f = func_001F5298(v0);
    f = f * 0.5f + 0.5f;
    D_00633B48 = f;
out:
    *(float *)((char *)self_save + 0x18) = f;
    return -1;
}

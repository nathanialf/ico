#include "ico/types.h"
extern int func_001CD9B0(int a0, int a1, int a2);

int func_001CEBC0(int a0)
{
    int v0 = (int)((GObj *)(a0))->p_15C;
    int *a2 = ((Sub15C *)(v0))->p_800;
    int v1 = *(int *)(v0 + 0x840);
    int a1 = a2[0];
    *(int *)(v1 + 0x30) = 0;
    return func_001CD9B0(a0, a1, (int)(a2 + 1));
}

#include "matching.h"
#include "regpin.h"
extern int *func_001E29E8();

int func_0015EF50(int *self)
{
    register int a2_val REG("$6");
    int *v;
    char *s = (char *)self[0x164/4];
    a2_val = (int)(s + 0x610);
    KEEP_LIVE(a2_val);
    v = func_001E29E8();
    *(int **)(s + 0x120) = v;
    return v[3] != 0;
}

#include "matching.h"
#include "regpin.h"

extern int *func_001E29E8(int *a0, int a1, char *arg);

int func_0015EF50(int *a0, int a1)
{
    char *sub = (char *)a0[0x164 / 4];
    int *p = func_001E29E8(a0, a1, sub + 0x610);
    register int v REG("$3");
    *(int *)(sub + 0x120) = (int)p;
    KEEP_LIVE(sub);
    v = p[0xC / 4];
    return v != 0;
}

TRAILING_PAD_NOP();

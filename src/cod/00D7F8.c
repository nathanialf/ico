#include "regpin.h"
#include "matching.h"

extern void func_001186C8(int *buf);
extern int func_0010D5C8(int a0, int *buf);

int func_0010D7F8(int a0)
{
    int buf[16];
    func_001186C8(buf);
    {
        register int aa REG("$4") = a0;
        DEAD_DADDU_V0_SP(aa);
        return func_0010D5C8(aa, buf);
    }
}

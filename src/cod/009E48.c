#include "matching.h"
#include "ico/types.h"
#include "regpin.h"

void func_00109E48(char *self)
{
    register int i REG("$5") = 0;
    char *sub = ((GObj *)(self))->p_15C;
    int count;
    char *p;
    KEEP_LIVE(i);
    count = *(int *)(sub + 0x88);
    if (count > 0) {
        p = *(char **)(sub + 0x7F0);
        do {
            p[i] = 0;
            i++;
            sub = *(char * volatile *)(self + 0x15C);
            count = *(int *)(sub + 0x88);
        } while (i < count);
    }
}

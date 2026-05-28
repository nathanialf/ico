#include "matching.h"
#include "regpin.h"

int func_00194960(int a0)
{
    register int c REG("$2") = 360;
    if (a0 > 0) {
        a0 = a0 % c;
    } else {
        int a = a0 < 0 ? -a0 : a0;
        int t = a / c * c + c;
        a0 = a0 + t;
    }
    return (a0 < 181) ? a0 : a0 - 360;
}

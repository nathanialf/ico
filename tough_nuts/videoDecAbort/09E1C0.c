#include "regpin.h"
int videoDecAbort(int *self)
{
    register int v REG("$2") = 1;
    self[46] = v;
    return v;
}

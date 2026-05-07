#include "regpin.h"
extern int D_0070D4D8[];

/* See 0E8D30.c for the explicit-register-vars rationale. Write variant:
 * stride goes to $v1, base to $v0 so the sw uses $v0 for its base. */
void func_001F1148(int idx, int val)
{
    register int s REG("$3") = 0x18;
    register int *b REG("$2") = D_0070D4D8;
    register int prod REG("$4") = idx * s;
    b = (int *)((char *)b + prod);
    *(int *)((char *)b + 0x14) = val;
}

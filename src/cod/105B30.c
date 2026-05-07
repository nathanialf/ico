#include "regpin.h"
extern int D_004CAEC0[];

/* See 0E8D30.c for the explicit-register-vars rationale. */
void func_00205B30(int idx, int val)
{
    register int s REG("$3") = 0x34;
    register int *b REG("$2") = D_004CAEC0;
    register int prod REG("$4") = idx * s;
    b = (int *)((char *)b + prod);
    *(int *)((char *)b + 0x28) = val;
}

#include "regpin.h"
extern int D_00292540[];

/* See 0E8D30.c for the explicit-register-vars rationale. */
void func_0015F228(int idx, int val)
{
    register int s REG("$3") = 0x18;
    register int *b REG("$2") = D_00292540;
    register int prod REG("$4") = idx * s;
    b = (int *)((char *)b + prod);
    *(int *)((char *)b + 8) = val;
}

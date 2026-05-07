#include "regpin.h"
extern int D_004CAEC0[];

/* See 0E8D30.c for the explicit-register-vars rationale. */
int func_00205A78(int idx)
{
    register int s REG("$2") = 0x34;
    register int *b REG("$3") = D_004CAEC0;
    register int prod REG("$4") = idx * s;
    b = (int *)((char *)b + prod);
    return *(int *)((char *)b + 8);
}

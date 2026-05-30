#include "matching.h"
extern int D_004CAEC0[];

/* See 0E8D30.c for the explicit-register-vars + ADDU_RS rationale (drops
 * the swap_addu postprocess; COOKBOOK §8.11). */
void func_00205B30(int idx, int val)
{
    register int s REG("$3") = 0x34;
    register int prod REG("$4") = idx * s;
    register int *b REG("$2") = D_004CAEC0;
    ADDU_RS(b, prod);
    *(int *)((char *)b + 0x28) = val;
}

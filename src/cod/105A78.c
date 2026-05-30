#include "matching.h"
extern int D_004CAEC0[];

/* See 0E8D30.c for the explicit-register-vars + ADDU_RS rationale (drops
 * the swap_addu postprocess; COOKBOOK §8.11). */
int func_00205A78(int idx)
{
    register int s REG("$2") = 0x34;
    register int prod REG("$4") = idx * s;
    register int *b REG("$3") = D_004CAEC0;
    ADDU_RS(b, prod);
    return *(int *)((char *)b + 8);
}

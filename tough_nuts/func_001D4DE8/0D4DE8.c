#include "regpin.h"
extern int D_00565060[];
extern int D_004C49A8[];
extern int D_00633F1C;

void func_001D4DE8(void)
{
    register int *D_base REG("$2");  /* v0 - holds D_00565060 */
    register int *base REG("$5");    /* a1 */
    register int *out REG("$3");     /* v1 */
    register int target REG("$6");   /* a2 */
    register int i REG("$4");        /* a0 */
    
    D_base = D_00565060;
    out = D_004C49A8;
    base = (int *)((char *)D_base + 0x134);
    target = 4;
    i = 0x43D;
    do {
        if (*base == target) {
            *out = 0;
        }
        out = (int *)((char *)out + 4);
        base = (int *)((char *)base + 0x190);
    } while (--i >= 0);
    D_00633F1C = 0;
}

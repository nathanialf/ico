#include "regpin.h"
extern int D_004C7710[];

void func_001FBBE0(void)
{
    D_004C7710[0] ^= 1;
    D_004C7710[4] = (D_004C7710 + D_004C7710[0])[1];
    D_004C7710[7] = 0;
    D_004C7710[5] = 0;
    D_004C7710[6] = 0;
}

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/gflag", gflagInit);
INCLUDE_ASM("asm/nonmatchings/src/gflag", gflagSave);
INCLUDE_ASM("asm/nonmatchings/src/gflag", gflagLoad);
extern unsigned char D_002A50C0[];

int gflagChk(int bit_idx)
{
    return (D_002A50C0[bit_idx >> 3] >> (bit_idx & 7)) & 1;
}
void gflagOn(int bit_idx)
{
    D_002A50C0[bit_idx >> 3] |= 1 << (bit_idx & 7);
}
void gflagOff(int bit_idx)
{
    D_002A50C0[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
}

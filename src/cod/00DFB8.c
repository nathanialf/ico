#include "matching.h"
#include "include_asm.h"

extern void func_0010D830(float *vec);

void func_0010DFB8(float *vec, int a1, int flip)
{
    func_0010D830(vec);
    switch (flip) {
        case 0: vec[0] = -vec[0]; break;
        case 1: vec[1] = -vec[1]; break;
        case 2: vec[2] = -vec[2]; break;
        case 4: vec[0] = -vec[0]; vec[1] = -vec[1]; break;
        case 3: vec[0] = -vec[0]; vec[2] = -vec[2]; break;
        case 5: vec[1] = -vec[1]; vec[2] = -vec[2]; break;
        case 6:
        default: vec[0] = -vec[0]; vec[1] = -vec[1]; vec[2] = -vec[2]; break;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E0B8);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E158);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E1F8);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E298);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E398);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E498);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E528);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E5B8);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E648);

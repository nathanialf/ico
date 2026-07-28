#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"


extern int D_00712CC0[];
INCLUDE_ASM("asm/nonmatchings/src/PObj", MakeBoundingBox);

INCLUDE_ASM("asm/nonmatchings/src/PObj", MakePacket);

int AllocPObj(int idx)
{
    return D_00712CC0[idx];
}

extern int D_00633B98;

int InitPObj(int a0) {
    int i;
    for (i = 0; i < D_00633B98; i++) {
        if (a0 == D_00712CC0[i]) {
            return i;
        }
    }
    return -1;
}

extern char D_00633BA0[];
extern void debug_assertMessage();

void FreePObj(int a0) {
    int i;
    for (i = 0; i < D_00633B98; i++) {
        if (a0 == D_00712CC0[i]) {
            debug_assertMessage(D_00633BA0, i);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240C50);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240D40);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240EA0);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240FC8);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_002412D8);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_002413F0);


#include "common.h"


extern int EnableMotionOrientUpdate();
extern int ForMotionViewer_GetCurrentMotion();
extern int D_00631990;
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC6C8);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC780);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FCA20);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_00200848);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_00200970);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_002009F0);

int func_00200A98(int a0)
{
    unsigned char v0;
    if (D_00631990 == 4) {
        v0 = EnableMotionOrientUpdate(a0, 0x1000);
    } else {
        v0 = ForMotionViewer_GetCurrentMotion(a0, 0x1000);
    }
    return v0 & 0xFF;
}


#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", MakeRefractTexture);

INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", queen_barrier_set_damage);

extern unsigned short D_006327FC;
extern int D_00633DE0;
extern int D_00633DE4;

void makeRefractST(void) {
    D_006327FC += 0x7D0;
    D_00633DE4 += 0x1000;
    if (D_00633DE0 > 0) {
        if (--D_00633DE0 < 0) {
            D_00633DE0 = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", queen_barrier_disp_proc);

INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", queen_barrier_disp_init);

INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", queen_barrier_anim);

INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", func_0019CD50);

INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", func_0019CE40);


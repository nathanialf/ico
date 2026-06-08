#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen_barrier_disp", MakeRefractTexture);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen_barrier_disp", queen_barrier_set_damage);

extern unsigned short D_0062AACC;
extern int D_0062C0D0;
extern int D_0062C0CC;

void makeRefractST(void) {
    D_0062AACC += 0x7D0;
    D_0062C0D0 += 0x1000;
    if (D_0062C0CC > 0) {
        if (--D_0062C0CC < 0) {
            D_0062C0CC = 0;
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen_barrier_disp", queen_barrier_disp_proc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen_barrier_disp", queen_barrier_disp_init);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen_barrier_disp", queen_barrier_anim);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen_barrier_disp", func_0019A3C8);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen_barrier_disp", func_0019A4B8);


/* recovered struct shapes */
typedef struct {
    short              f_0;  /* 0x00 */
} S_006CDC20;  /* stride 0x2 */

/* end struct shapes */

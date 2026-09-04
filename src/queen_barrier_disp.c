#include "common.h"

/* header prototypes (order fixes the inline tail) */
void queen_barrier_anim(void);
extern int D_00556E10[];
extern int D_0063C308;
extern void debug_StdPrintfDummy();
extern unsigned short D_0063AC64;
extern int D_0063C30C;
void queen_barrier_set_damage(void)
{
    D_0063C308 = 0x3C;
    debug_StdPrintfDummy(D_00556E10);
}
inline void queen_barrier_anim(void) {
    D_0063AC64 += 0x7D0;
    D_0063C30C += 0x1000;
    if (D_0063C308 > 0) {
        if (--D_0063C308 < 0) {
            D_0063C308 = 0;
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", makeRefractST);
INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", queen_barrier_disp_proc);
INCLUDE_ASM("asm/nonmatchings/src/queen_barrier_disp", queen_barrier_disp_init);

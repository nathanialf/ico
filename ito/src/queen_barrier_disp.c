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

extern int sscanf(void *a0, void *a1, void *a2);
extern int strcmp(void *a0, void *a1);
extern char D_005EBC68[];
extern char D_0062C950[];
extern short D_006CDC20[];
extern char D_00556920[];

void func_0019A3C8(void)
{
    char buf[0x40];
    int i;
    for (i = 0; i < 0x68; i++) {
        sscanf(&D_005EBC68[i * 0x190], &D_0062C950, buf);
        D_006CDC20[i] = -1;
        {
            unsigned int j = 0;
            while (j < 0x23) {
                if (strcmp(buf, &D_00556920[j * 0x2C]) == 0) {
                    D_006CDC20[i] = j;
                    break;
                }
                j++;
            }
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen_barrier_disp", func_0019A4B8);


/* recovered struct shapes */
typedef struct {
    short              f_0;  /* 0x00 */
} S_006CDC20;  /* stride 0x2 */

/* end struct shapes */

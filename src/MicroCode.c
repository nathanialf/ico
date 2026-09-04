#include "common.h"

#include "vu0.h"

INCLUDE_ASM("asm/nonmatchings/src/MicroCode", mc_setBaseOffset);
INCLUDE_ASM("asm/nonmatchings/src/MicroCode", mc_SetMicroCode);
extern int D_00290B20[];
extern int D_0063C140;
extern int D_0067BFD0[];
extern int dl_CloseDma(void);
extern void dl_OpenDma(int a0, int a1, int a2);
extern int dl_SetDLPriority(int a0);
extern void mc_setBaseOffset(int a0, int a1);

void mc_TransMicroCode(int a0, int a1) {
    int *q = &D_00290B20[a0];
    int i;
    for (i = 0; i < 0xD; i++) {
        if ((a1 >> i) & 1) {
            if (a0 != D_0067BFD0[i]) {
                D_0063C140++;
                mc_setBaseOffset(a0, i);
                dl_SetDLPriority(i);
                dl_OpenDma(5, *q, 0);
                dl_CloseDma();
                D_0067BFD0[i] = a0;
            }
        }
    }
}
void mc_Reset(void)
{
    int *p = D_0067BFD0;
    int i = 0xC;
    D_0063C140 = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}
void mc_Init(void)
{
    int *p = D_0067BFD0;
    int i = 0xC;
    D_0063C140 = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

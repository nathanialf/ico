#include "common.h"


extern int D_00633EDC;
extern float D_00633EE4;
extern int D_004BD980[];   /* defined as unsigned char[16] in box_data.c */;
extern float D_00633EE0;
extern int D_00633EE8;
extern int D_006331B4;
void InitAP1(void)
{
    register int a __asm__("$3") = D_004BD980[0] + 0x1400;
    register int one __asm__("$2") = 1;
    register int b4 __asm__("$6") = 0xFF;
    int b;
    D_00633EE8 = one;
    D_00633EE0 = (float)(a / 30);
    b = D_00633EDC - 0x280;
    D_00633EE4 = (float)(b / 30);
    D_006331B4 = b4;
}

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", yAxisRotFitting);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", zAxisRotFitting);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", fitToCol);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", walkMot);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", rolling);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", calcSubMission);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", updateMatrix);


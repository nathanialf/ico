#include "common.h"



extern int D_006337B4;
extern int D_006337BC;
extern int D_006337B8;
extern int D_00274EC0[];

int font_CheckAlign(void *a0) {
    int n = (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1];
    float f1 = (float)*(int *)((char *)a0 + 4);
    float f2 = *(float *)((char *)a0 + 8);
    return f1 * ((float)n / 30.0f) <= f2;
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FA910);

int font_Print(void *a0, int a1, int a2) {
    int n = 0x3C - D_00274EC0[0] * 0xA;
    return (float)a1 * ((float)(n / D_00274EC0[1]) / 30.0f) <= *(float *)((char *)a0 + 8)
        && *(float *)((char *)a0 + 8) < (float)a2 * ((float)(n / D_00274EC0[1]) / 30.0f);
}

void font_GetWidth(void) {
    D_006337B8 = 1;
}

void font_GetHeight(void)
{
    D_006337B8 = 0;
    D_006337BC = 0;
}

void font_Init(int val) {
    D_006337B4 = val;
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FAA58);

extern float D_006337B0;

float func_001FAAA8(void)
{
    return D_006337B0;
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FAAB0);

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FAE98);


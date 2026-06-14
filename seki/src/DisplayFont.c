#include "common.h"

extern int D_00271240[];

int font_CheckAlign(void *a0) {
    int n = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
    float f1 = (float)*(int *)((char *)a0 + 4);
    float f2 = *(float *)((char *)a0 + 8);
    return f1 * ((float)n / 30.0f) <= f2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F7578);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", font_Print);

extern int D_0062BAA0;
extern int D_0062BAA4;

void font_GetWidth(void) {
    D_0062BAA0 = 1;
}

void font_GetHeight(void) {
    D_0062BAA0 = 0;
    D_0062BAA4 = 0;
}

extern int D_0062BA9C;

void font_Init(int a0) {
    D_0062BA9C = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F76C0);

extern float D_0062BA98;

float func_001F7710(void) {
    return D_0062BA98;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F7718);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F7B00);

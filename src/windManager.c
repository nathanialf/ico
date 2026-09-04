#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/windManager", ExecWindManager);
INCLUDE_ASM("asm/nonmatchings/src/windManager", ReinitWindManager);
extern float D_0063BC64;
extern float D_0063BC68;
extern float D_0063BC6C;
extern float D_0063BC70;
extern float D_0063BC74;
extern float D_0063BC78;
extern void InitWindField(int a0, float *a1, float *a2, float a3);

void SetWindManager(float a, float b, float c, float d, float e, float f, float g, float h) {
    float buf1[4] = {a, b, c, 1.0f};
    float buf2[4] = {d, e, f, 0.0f};

    D_0063BC64 = g;
    D_0063BC68 = 1.0f / g;
    D_0063BC6C = h;
    D_0063BC70 = 1.0f / h;
    D_0063BC74 = g;
    D_0063BC78 = g;
    InitWindField(1, buf1, buf2, g);
}
INCLUDE_ASM("asm/nonmatchings/src/windManager", InitWindManager);
INCLUDE_ASM("asm/nonmatchings/src/windManager", GetRegularizedWindSpeed);

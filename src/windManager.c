#include "common.h"

extern int D_0063BC7C;
extern float D_0063BC74;
extern float D_0063BC78;
extern float D_0063BC64;
extern float D_0063BC6C;
extern float D_00639708;
extern float _GetRandom(void);
extern void ExecWindField(float f);
void ExecWindManager(void) {
    D_0063BC7C++;
    if (D_0063BC7C >= 0x33) {
        float r = _GetRandom();
        D_0063BC7C = 0;
        D_0063BC74 = D_0063BC64 * ((r + r - 1.0f) * D_0063BC6C + 1.0f);
    }
    D_0063BC78 = D_0063BC78 + (D_0063BC74 - D_0063BC78) * D_00639708;
    ExecWindField(D_0063BC78);
}
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

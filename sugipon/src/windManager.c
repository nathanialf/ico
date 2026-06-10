#include "common.h"

extern float D_004C24A0[];
extern float D_004C2490[];
extern void func_001D1DF0(void *a0, void *a1, void *a2, void *a3, int a4);

void ExecWindManager(void) {
    float *p;
    for (p = D_004C24A0; -1000.0f < *p; p += 8) {
        func_001D1DF0(p, D_004C2490, p + 4, D_004C2490, -1);
    }
}

extern float D_004C2600[];

void ReinitWindManager(void) {
    float *p;
    for (p = D_004C2600; -1000.0f < *p; p += 8) {
        func_001D1DF0(p, D_004C2490, p + 4, D_004C2490, -1);
    }
}

extern float D_004C27A0[];

void SetWindManager(void) {
    float *p;
    for (p = D_004C27A0; -1000.0f < *p; p += 8) {
        func_001D1DF0(p, D_004C2490, p + 4, D_004C2490, -1);
    }
}

extern int D_0062BA54;
extern float D_0062BA3C;
extern float D_0062BA44;
extern float D_0062BA4C;
extern float D_0062BA50;
extern float D_006296F4;
extern float pac_DispQW(void);
extern void drawSenpuukiHaneUnit(float a0);

void InitWindManager(void) {
    float v;
    if (++D_0062BA54 >= 0x33) {
        D_0062BA4C = D_0062BA3C * ((pac_DispQW() * 2.0f - 1.0f) * D_0062BA44 + 1.0f);
        D_0062BA54 = 0;
    }
    v = D_0062BA50 + (D_0062BA4C - D_0062BA50) * D_006296F4;
    D_0062BA50 = v;
    drawSenpuukiHaneUnit(v);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", GetRegularizedWindSpeed);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", func_001F2130);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", func_001F21B0);

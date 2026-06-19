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

extern float D_005EBD14[];
extern int D_0062BA38;
extern float D_0062BA40;
extern float D_0062BA48;
extern void LightTorchOnOfWeaponWithNoSE(int a0, float *a1, float *a2, float a3);

static inline void windApply(float a, float b, float c, float d, float e, float f, float g, float h) {
    float buf1[4] = {a, b, c, 1.0f};
    float buf2[4] = {d, e, f, 0.0f};

    D_0062BA3C = g;
    D_0062BA40 = 1.0f / g;
    D_0062BA44 = h;
    D_0062BA48 = 1.0f / h;
    D_0062BA4C = g;
    D_0062BA50 = g;
    LightTorchOnOfWeaponWithNoSE(1, buf1, buf2, g);
}

void GetRegularizedWindSpeed(void) {
    int idx = D_0062BA38;
    float *p = &D_005EBD14[idx * 100];
    float *q = &D_005EBD14[idx * 100 - 3];
    float g = (idx * 100 + 45)[D_005EBD14];
    float h = (idx * 100 + 35)[D_005EBD14];

    windApply(p[0], p[1], p[2], q[0], q[1], q[2], g, h);
    D_0062BA38 = idx;
}

void func_001F2130(float a, float b, float c, float d, float e, float f, float g, float h) {
    float buf1[4] = {a, b, c, 1.0f};
    float buf2[4] = {d, e, f, 0.0f};

    D_0062BA3C = g;
    D_0062BA40 = 1.0f / g;
    D_0062BA44 = h;
    D_0062BA48 = 1.0f / h;
    D_0062BA4C = g;
    D_0062BA50 = g;
    LightTorchOnOfWeaponWithNoSE(1, buf1, buf2, g);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", func_001F21B0);

#include "common.h"

extern float D_004C63A0[];
extern float D_004C63B0[];
extern void func_001D4A58(void *a0, void *a1, void *a2, void *a3, int a4);

void ExecWindManager(void) {
    float *p;
    for (p = D_004C63B0; -1000.0f < *p; p += 8) {
        func_001D4A58(p, D_004C63A0, p + 4, D_004C63A0, -1);
    }
}

extern float D_004C6510[];

void ReinitWindManager(void) {
    float *p;
    for (p = D_004C6510; -1000.0f < *p; p += 8) {
        func_001D4A58(p, D_004C63A0, p + 4, D_004C63A0, -1);
    }
}

extern float D_004C66B0[];

void SetWindManager(void) {
    float *p;
    for (p = D_004C66B0; -1000.0f < *p; p += 8) {
        func_001D4A58(p, D_004C63A0, p + 4, D_004C63A0, -1);
    }
}

extern float D_0063375C;
extern float D_00633764;
extern float D_0063376C;
extern float D_00633770;
extern int D_00633774;
extern void drawSenpuukiHaneUnit(float a0);
extern float pac_DispQW(void);

void InitWindManager(void) {
    float v;
    if (++D_00633774 >= 0x33) {
        D_0063376C = D_0063375C * ((pac_DispQW() * 2.0f - 1.0f) * D_00633764 + 1.0f);
        D_00633774 = 0;
    }
    v = D_00633770 + (D_0063376C - D_00633770) * 0.1f;
    D_00633770 = v;
    drawSenpuukiHaneUnit(v);
}

extern float D_005F3084[];
extern int D_00633758;
extern float D_00633760;
extern float D_00633768;
extern void LightTorchOnOfWeaponWithNoSE(int a0, float *a1, float *a2, float a3);

static inline void windApply(float a, float b, float c, float d, float e, float f, float g, float h) {
    float buf1[4] = {a, b, c, 1.0f};
    float buf2[4] = {d, e, f, 0.0f};

    D_0063375C = g;
    D_00633760 = 1.0f / g;
    D_00633764 = h;
    D_00633768 = 1.0f / h;
    D_0063376C = g;
    D_00633770 = g;
    LightTorchOnOfWeaponWithNoSE(1, buf1, buf2, g);
}

void GetRegularizedWindSpeed(void) {
    int idx = D_00633758;
    float *p = &D_005F3084[idx * 101];
    float *q = &D_005F3084[idx * 101 - 3];
    float g = (idx * 101 + 36)[D_005F3084];
    float h = (idx * 101 + 35)[D_005F3084];

    windApply(p[0], p[1], p[2], q[0], q[1], q[2], g, h);
    D_00633758 = idx;
}

INCLUDE_ASM("asm/nonmatchings/src/windManager", func_001F5140);

INCLUDE_ASM("asm/nonmatchings/src/windManager", func_001F51C0);


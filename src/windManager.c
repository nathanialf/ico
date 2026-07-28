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

extern float D_00631414;
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
    v = D_00633770 + (D_0063376C - D_00633770) * D_00631414;
    D_00633770 = v;
    drawSenpuukiHaneUnit(v);
}

INCLUDE_ASM("asm/nonmatchings/src/windManager", GetRegularizedWindSpeed);

INCLUDE_ASM("asm/nonmatchings/src/windManager", func_001F5140);

INCLUDE_ASM("asm/nonmatchings/src/windManager", func_001F51C0);


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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", ReinitWindManager);

extern float D_004C27A0[];

void SetWindManager(void) {
    float *p;
    for (p = D_004C27A0; -1000.0f < *p; p += 8) {
        func_001D1DF0(p, D_004C2490, p + 4, D_004C2490, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", InitWindManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", GetRegularizedWindSpeed);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", func_001F2130);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windManager", func_001F21B0);

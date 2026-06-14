#include "common.h"

extern int D_00271BD0[];

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", InitWindField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", drawSenpuukiHaneUnit);

extern int (*D_0062BA30)(void);

int drawSenpuuki(void) {
    return D_0062BA30();
}

void *ExecWindField(int *a0) {
    if (a0) {
        *a0 = 0;
    }
    return D_00271BD0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", GetWindVector);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", dummyGetWindVector);

extern int (*D_0062BA30)(void);

void getParallelWindVector(void) {
    D_0062BA30 = ExecWindField;
}

extern void func_001D1DF0();
extern char D_004C2490[];

void getRadiateWindVector(char *a0) {
    char *cur = a0;
    if (-1000.0f < *(float *)cur) {
        do {
            func_001D1DF0(cur, D_004C2490, cur + 0x10, D_004C2490, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
}

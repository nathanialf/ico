#include "common.h"


extern char D_00275850[];
INCLUDE_ASM("asm/nonmatchings/src/windField", InitWindField);

INCLUDE_ASM("asm/nonmatchings/src/windField", drawSenpuukiHaneUnit);

extern int (*D_00633750)(void);

int drawSenpuuki(void) {
    return D_00633750();
}

int *ExecWindField(int *a0)
{
    if (a0) *a0 = 0;
    return D_00275850;
}

INCLUDE_ASM("asm/nonmatchings/src/windField", GetWindVector);

INCLUDE_ASM("asm/nonmatchings/src/windField", dummyGetWindVector);

INCLUDE_ASM("asm/nonmatchings/src/windField", getParallelWindVector);

extern char D_004C63A0[];
extern void func_001D4A58();

void getRadiateWindVector(char *a0) {
    char *cur = a0;
    if (-1000.0f < *(float *)cur) {
        do {
            func_001D4A58(cur, D_004C63A0, cur + 0x10, D_004C63A0, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
}


#include "common.h"


extern char D_00275850[];
INCLUDE_ASM("asm/nonmatchings/src/windField", drawSenpuuki);

INCLUDE_ASM("asm/nonmatchings/src/windField", drawSenpuukiHaneUnit);

extern int (*D_00633750)(void);

int GetWindVector(void) {
    return D_00633750();
}

int *dummyGetWindVector(int *a0)
{
    if (a0) *a0 = 0;
    return D_00275850;
}

INCLUDE_ASM("asm/nonmatchings/src/windField", getParallelWindVector);

INCLUDE_ASM("asm/nonmatchings/src/windField", getRadiateWindVector);

void StopWindField(void)
{
    D_00633750 = (int (*)(void))dummyGetWindVector;
}

extern char D_004C63A0[];
extern void func_001D4A58();

void drawLines(char *a0) {
    char *cur = a0;
    if (-1000.0f < *(float *)cur) {
        do {
            func_001D4A58(cur, D_004C63A0, cur + 0x10, D_004C63A0, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
}


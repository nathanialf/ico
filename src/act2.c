#include "common.h"

extern void _ACTWait(int a0);
extern int actInitialize(int a0);

typedef union { float f[4]; long long ll[2]; } Vec4;


extern char D_0061B040[];
extern void debug_StdPrintfDummy();
extern int D_00631970;
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0TransposeMatrix(void *a0, void *a1);

void BeforeFunc2(void *a0, float *a1) {
    Vec4 v = {{ a1[3], 0.0f, -a1[4], 0.0f }};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)(D_00631970 + 0x80));
    sceVu0ApplyMatrix(a0, m, &v);
}

void actDummy(char *self, int val) {
    char *sub = *(char **)(self + 0x164);
    if (sub != 0) {
        *(int *)(sub + 0x438) = val;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/act2", actWaitCondition);

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00203D90);


void func_00203EE8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

void func_00203F18(int a0, int *a1, int *a2)
{
    int v = *a2;
    if (v >= 0x10) {
        debug_StdPrintfDummy(D_0061B040);
        return;
    }
    *a2 = v + 1;
    a1[v] = a0;
}

INCLUDE_ASM("asm/nonmatchings/src/act2", func_00203F48);

INCLUDE_ASM("asm/nonmatchings/src/act2", func_002040C0);

INCLUDE_ASM("asm/nonmatchings/src/act2", add_wp_pos);

INCLUDE_ASM("asm/nonmatchings/src/act2", WayLengthOfPos_Pos);

INCLUDE_ASM("asm/nonmatchings/src/act2", WayPointWithRangeFromPos);


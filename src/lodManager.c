#include "common.h"




extern int D_00633F18;
extern int D_00633F1C;
extern void func_001D4228();
extern void _FTOI4Vector();
extern void gif_SetGsReg();
extern int D_00633428;
void SetLodLevel(void)
{
    gif_SetGsReg(0, D_00633428);
}

INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4358);

INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D43F8);

INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D45B0);

void func_001D49C0(int *p1, int *p2, int a2, int a3)
{
    int t0[4];
    int t1[4];
    int t2[4];
    int t3[4];
    if (func_001D45B0(t0, t1, p1, p2) < 0) return;
    _FTOI4Vector(t2, t0);
    _FTOI4Vector(t3, t1);
    func_001D4228(t2, t3, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4A58);

INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4B40);

INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4BD0);

INCLUDE_ASM("asm/nonmatchings/src/lodManager", InitMotionFile);

void func_001D4D98(void) {
    D_00633F18 = 0;
    D_00633F1C = 0;
}

int AddMotionMemorySize(int a0, int a1)
{
    int v0;
    if (a1 != 0) {
        v0 = D_00633F1C + a0;
        D_00633F1C = v0;
    } else {
        v0 = D_00633F18 + a0;
        D_00633F18 = v0;
    }
    return v0;
}

int GetMotionMemorySize(int a0)
{
    return a0 ? D_00633F1C : D_00633F18;
}

INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4DE8);


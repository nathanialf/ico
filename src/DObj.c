#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/DObj", initGeometryState);

int initMatrixDObj(volatile int *self) {
    if (self[3] != 0) {
        int e = self[2] - self[3];
        int d = self[4];
        return self[1] + (e + d) % d * 0xA0A40;
    }
    return 0;
}

void allocObjectData(int *p) {
    if (*(volatile int *)(p + 3) > 0) {
        --(*(volatile int *)(p + 3));
    }
}

INCLUDE_ASM("asm/nonmatchings/src/DObj", initInitialInverseMatrix);

INCLUDE_ASM("asm/nonmatchings/src/DObj", initPolygonState);

INCLUDE_ASM("asm/nonmatchings/src/DObj", CSVSYSTEM_InitDObj);

extern char D_00612620[];
extern int D_00632010;
extern void func_00103120(int v, int *self);
extern int func_0013A0F8(int a0, int a1, int *a2, int a3);

void FreeDObj(int *self) {
    int v = func_0013A0F8(D_00632010, self[0x88/4] << 6, (int*)D_00612620, 0x14C);
    self[0x90/4] = v;
    func_00103120(v, self);
}

INCLUDE_ASM("asm/nonmatchings/src/DObj", LinkParentOfDObj);

INCLUDE_ASM("asm/nonmatchings/src/DObj", UnlinkParentOfDObj);

void func_0019F4E0(void) {}

INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019F4E8);

INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019F530);

INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019F568);


#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/DObj", initGeometryState);

INCLUDE_ASM("asm/nonmatchings/src/DObj", initMatrixDObj);

void allocObjectData(int *p) {
    if (*(volatile int *)(p + 3) > 0) {
        --(*(volatile int *)(p + 3));
    }
}

INCLUDE_ASM("asm/nonmatchings/src/DObj", initInitialInverseMatrix);

INCLUDE_ASM("asm/nonmatchings/src/DObj", initPolygonState);

INCLUDE_ASM("asm/nonmatchings/src/DObj", CSVSYSTEM_InitDObj);

INCLUDE_ASM("asm/nonmatchings/src/DObj", FreeDObj);

INCLUDE_ASM("asm/nonmatchings/src/DObj", LinkParentOfDObj);

INCLUDE_ASM("asm/nonmatchings/src/DObj", UnlinkParentOfDObj);

void func_0019F4E0(void) {}

INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019F4E8);

INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019F530);

INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019F568);


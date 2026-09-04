#include "common.h"

typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } DObjBlk8;

INCLUDE_ASM("asm/nonmatchings/src/DObj", initGeometryState);
INCLUDE_ASM("asm/nonmatchings/src/DObj", initMatrixDObj);
INCLUDE_ASM("asm/nonmatchings/src/DObj", allocObjectData);
INCLUDE_ASM("asm/nonmatchings/src/DObj", initInitialInverseMatrix);
INCLUDE_ASM("asm/nonmatchings/src/DObj", initPolygonState);
INCLUDE_ASM("asm/nonmatchings/src/DObj", CSVSYSTEM_InitDObj);
void FreeDObj(void) {}
INCLUDE_ASM("asm/nonmatchings/src/DObj", LinkParentOfDObj);
extern DObjBlk8 D_0063A810;
extern void GlobalizeGeometry(void *a0);

void UnlinkParentOfDObj(void *a0)
{
    GlobalizeGeometry(a0);
    *(DObjBlk8 *)(*(char **)((char *)a0 + 0x15C)) = D_0063A810;
}

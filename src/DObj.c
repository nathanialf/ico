#include "common.h"

typedef struct { long long x; } __attribute__((packed, aligned(4))) PackedLL_19CAF0;

typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } DObjBlk8;

INCLUDE_ASM("asm/nonmatchings/src/DObj", initGeometryState);
INCLUDE_ASM("asm/nonmatchings/src/DObj", initMatrixDObj);
INCLUDE_ASM("asm/nonmatchings/src/DObj", allocObjectData);
INCLUDE_ASM("asm/nonmatchings/src/DObj", initInitialInverseMatrix);
INCLUDE_ASM("asm/nonmatchings/src/DObj", initPolygonState);
INCLUDE_ASM("asm/nonmatchings/src/DObj", CSVSYSTEM_InitDObj);
void FreeDObj(void) {}
extern void LocalizeGeometry();

void LinkParentOfDObj(void *a0, PackedLL_19CAF0 *a1) {
    PackedLL_19CAF0 *p;
    LocalizeGeometry(a0, a1);
    p = *(PackedLL_19CAF0 **)((char *)a0 + 0x15C);
    *p = *a1;
}
extern DObjBlk8 D_0063A810;
extern void GlobalizeGeometry(void *a0);

void UnlinkParentOfDObj(void *a0)
{
    GlobalizeGeometry(a0);
    *(DObjBlk8 *)(*(char **)((char *)a0 + 0x15C)) = D_0063A810;
}

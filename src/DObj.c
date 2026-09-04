#include "common.h"

typedef struct { long long x; } __attribute__((packed, aligned(4))) PackedLL_19CAF0;
typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } DObjBlk8;
extern char D_00618F30[];
extern int D_0063A438;
extern void LocalizeGeometry();
extern DObjBlk8 D_0063A810;
extern void GlobalizeGeometry(void *a0);
/* prototypes: their order is the inline tail's emission order */
void FreeDObj(void);
void LinkParentOfDObj(void *a0, PackedLL_19CAF0 *a1);
void UnlinkParentOfDObj(void *a0);
INCLUDE_ASM("asm/nonmatchings/src/DObj", initGeometryState);
INCLUDE_ASM("asm/nonmatchings/src/DObj", initMatrixDObj);
INCLUDE_ASM("asm/nonmatchings/src/DObj", allocObjectData);
void initInitialInverseMatrix(char *a0) {
    char *m = iosMallocDebug(D_0063A438, *(int *)(a0 + 0x88) << 6, D_00618F30, 0x14D);
    *(char **)(a0 + 0x90) = m;
    GetInitialInverseMatrixByDObj(m, a0);
}
INCLUDE_ASM("asm/nonmatchings/src/DObj", initPolygonState);
inline void FreeDObj(void) {}
INCLUDE_ASM("asm/nonmatchings/src/DObj", CSVSYSTEM_InitDObj);
inline void LinkParentOfDObj(void *a0, PackedLL_19CAF0 *a1) {
    PackedLL_19CAF0 *p;
    LocalizeGeometry(a0, a1);
    p = *(PackedLL_19CAF0 **)((char *)a0 + 0x15C);
    *p = *a1;
}
inline void UnlinkParentOfDObj(void *a0)
{
    GlobalizeGeometry(a0);
    *(DObjBlk8 *)(*(char **)((char *)a0 + 0x15C)) = D_0063A810;
}

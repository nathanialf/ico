#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(int a0);
extern void sceVu0UnitMatrix(void *a0);
INCLUDE_ASM("asm/nonmatchings/src/vobj", DrawVObj);
void SetVObjRT(int a0, void *a1) {
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    *(float *)((char *)a1 + 0xC) = 1.0f;
    MatrixDrive_TransMatrixV((int)a1);
}

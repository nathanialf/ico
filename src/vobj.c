#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

INCLUDE_ASM("asm/nonmatchings/src/vobj", DrawVObj);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(int a0);
extern void sceVu0UnitMatrix(void *a0);

INCLUDE_ASM("asm/nonmatchings/src/vobj", SetVObjRT);

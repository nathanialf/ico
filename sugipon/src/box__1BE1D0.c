#include "common.h"

extern void GetRootMatrixByDObj(void *dst, void *src);
extern void func_00240008(void *a0, void *a1, void *a2);
extern float func_0023FE70(void *a0, void *a1);
extern float MatrixDrive_GetTurnYAngleXZ(float a0);

struct vec4_BE1D0 { float x, y, z, w; } __attribute__((aligned(8)));

float BoxMemoryFunc(void *a0, void *a1) {
    struct vec4_BE1D0 buf1;
    struct vec4_BE1D0 buf2;
    GetRootMatrixByDObj(&buf1, a1);
    GetRootMatrixByDObj(&buf2, a0);
    func_00240008(&buf1, &buf1, &buf2);
    return MatrixDrive_GetTurnYAngleXZ(func_0023FE70(&buf1, &buf1));
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BE1D0", getAlign);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BE1D0", GetDistanceOfGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BE1D0", moveXPlus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BE1D0", moveXMinus);

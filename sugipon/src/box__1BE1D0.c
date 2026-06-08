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

int getAlign(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[0])) { rv = 0; goto end; }
    if (a0[0] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BE1D0", GetDistanceOfGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BE1D0", moveXPlus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BE1D0", moveXMinus);

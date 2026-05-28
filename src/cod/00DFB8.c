#include "matching.h"
#include "include_asm.h"

extern void func_0010D830(float *vec);

void func_0010DFB8(float *vec, int a1, int flip)
{
    func_0010D830(vec);
    switch (flip) {
        case 0: vec[0] = -vec[0]; break;
        case 1: vec[1] = -vec[1]; break;
        case 2: vec[2] = -vec[2]; break;
        case 4: vec[0] = -vec[0]; vec[1] = -vec[1]; break;
        case 3: vec[0] = -vec[0]; vec[2] = -vec[2]; break;
        case 5: vec[1] = -vec[1]; vec[2] = -vec[2]; break;
        case 6:
        default: vec[0] = -vec[0]; vec[1] = -vec[1]; vec[2] = -vec[2]; break;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E0B8);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E158);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E1F8);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E298);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E398);
extern void func_001183F0(void *a0, void *buf, float f);

void func_0010E498(float *a0, float *a1)
{
    float buf[4];
    register float *aa __asm__("$4") = a0;
    register float k __asm__("$f12") = 2.0f;
    register float z __asm__("$f5");
    register float y __asm__("$f3");
    register float w __asm__("$f4");
    register float x __asm__("$f0");
    register float zz __asm__("$f6");
    register float yy __asm__("$f2");
    register float wy __asm__("$f7");
    register float xz __asm__("$f1");
    z = a1[2];
    y = a1[1];
    w = a1[3];
    zz = z * z;
    KEEP_LIVE_FP(zz);
    x = a1[0];
    yy = y * y;
    wy = w * y;
    xz = x * z;
    buf[0] = -(yy + zz);
    buf[2] = xz + wy;
    buf[1] = x * y - w * z;
    buf[3] = 0.0f;
    func_001183F0(aa, buf, k);
    a0[0] += 1.0f;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E528);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E5B8);
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E648);

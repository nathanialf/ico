#include "matching.h"
#include "include_asm.h"
#include "vu0.h"

extern void func_0010D830(float *vec);

void GetMirrorQuaternion(float *vec, int a1, int flip)
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

extern float func_0010E950(int);
extern float GetTableCos(int);
extern void func_001183D0(int dst, int src, float f);
extern float D_00275870[];

void func_0010E0B8(int dst, short v)
{
    float buf[4];
    int angle = -(v << 16) >> 17;

    func_001183D0((int)buf, (int)D_00275870, func_0010E950(angle));
    buf[3] = GetTableCos(angle);
    VU0_LSV_R(lqc2, 11, 0x0, dst);
    VU0_LSV_R(lqc2, 12, 0x0, buf);
    VU0_V3OP(vmul.xyzw, 13, 11, 12);
    VU0_V3OP_BC(vaddy.x, 13, 13, 13, y);
    VU0_V3OP_BC(vaddz.x, 13, 13, 13, z);
    VU0_V3OP_BC(vsubx.w, 13, 13, 13, x);
    VU0_V3OP_BC(vmulw.xyz, 14, 12, 11, w);
    VU0_V3OP_BC(vmulw.xyz, 15, 11, 12, w);
    VU0_V3OP_ACC(vopmula.xyz, 12, 11);
    VU0_V3OP(vopmsub.xyz, 16, 11, 12);
    VU0_V3OP(vadd.xyz, 13, 14, 15);
    VU0_V3OP(vadd.xyz, 13, 13, 16);
    VU0_LSV_R(sqc2, 13, 0x0, dst);
}

extern float D_00275880[];

void func_0010E158(int dst, short v)
{
    float buf[4];
    int angle = -(v << 16) >> 17;

    func_001183D0((int)buf, (int)D_00275880, func_0010E950(angle));
    buf[3] = GetTableCos(angle);
    VU0_LSV_R(lqc2, 11, 0x0, dst);
    VU0_LSV_R(lqc2, 12, 0x0, buf);
    VU0_V3OP(vmul.xyzw, 13, 11, 12);
    VU0_V3OP_BC(vaddy.x, 13, 13, 13, y);
    VU0_V3OP_BC(vaddz.x, 13, 13, 13, z);
    VU0_V3OP_BC(vsubx.w, 13, 13, 13, x);
    VU0_V3OP_BC(vmulw.xyz, 14, 12, 11, w);
    VU0_V3OP_BC(vmulw.xyz, 15, 11, 12, w);
    VU0_V3OP_ACC(vopmula.xyz, 12, 11);
    VU0_V3OP(vopmsub.xyz, 16, 11, 12);
    VU0_V3OP(vadd.xyz, 13, 14, 15);
    VU0_V3OP(vadd.xyz, 13, 13, 16);
    VU0_LSV_R(sqc2, 13, 0x0, dst);
}

extern float D_00275890[];

void func_0010E1F8(int dst, short v)
{
    float buf[4];
    int angle = -(v << 16) >> 17;

    func_001183D0((int)buf, (int)D_00275890, func_0010E950(angle));
    buf[3] = GetTableCos(angle);
    VU0_LSV_R(lqc2, 11, 0x0, dst);
    VU0_LSV_R(lqc2, 12, 0x0, buf);
    VU0_V3OP(vmul.xyzw, 13, 11, 12);
    VU0_V3OP_BC(vaddy.x, 13, 13, 13, y);
    VU0_V3OP_BC(vaddz.x, 13, 13, 13, z);
    VU0_V3OP_BC(vsubx.w, 13, 13, 13, x);
    VU0_V3OP_BC(vmulw.xyz, 14, 12, 11, w);
    VU0_V3OP_BC(vmulw.xyz, 15, 11, 12, w);
    VU0_V3OP_ACC(vopmula.xyz, 12, 11);
    VU0_V3OP(vopmsub.xyz, 16, 11, 12);
    VU0_V3OP(vadd.xyz, 13, 14, 15);
    VU0_V3OP(vadd.xyz, 13, 13, 16);
    VU0_LSV_R(sqc2, 13, 0x0, dst);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", RotQuaternionEAX);
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
void func_0010E528(float *a0, float *a1)
{
    float buf[4];
    register float *aa __asm__("$4") = a0;
    register float k __asm__("$f12") = 2.0f;
    register float z __asm__("$f4");
    register float x __asm__("$f0");
    register float w __asm__("$f3");
    register float zz __asm__("$f6");
    register float xx __asm__("$f2");
    register float y __asm__("$f5");
    register float wx __asm__("$f7");
    register float yz __asm__("$f1");
    z = a1[2];
    x = a1[0];
    w = a1[3];
    zz = z * z;
    KEEP_LIVE_FP(zz);
    y = a1[1];
    xx = x * x;
    wx = w * x;
    yz = y * z;
    buf[1] = -(xx + zz);
    buf[2] = yz - wx;
    buf[0] = x * y + w * z;
    buf[3] = 0.0f;
    func_001183F0(aa, buf, k);
    a0[1] += 1.0f;
}
void func_0010E5B8(float *a0, float *a1)
{
    float buf[4];
    register float *aa __asm__("$4") = a0;
    register float k __asm__("$f12") = 2.0f;
    register float x __asm__("$f0");
    register float y __asm__("$f2");
    register float w __asm__("$f1");
    register float xx __asm__("$f3");
    register float yy __asm__("$f6");
    register float z __asm__("$f5");
    register float wx __asm__("$f7");
    register float yz __asm__("$f4");
    x = a1[0];
    y = a1[1];
    w = a1[3];
    xx = x * x;
    KEEP_LIVE_FP(xx);
    z = a1[2];
    yy = y * y;
    wx = w * x;
    yz = y * z;
    buf[2] = -(xx + yy);
    buf[1] = yz + wx;
    buf[0] = x * z - w * y;
    buf[3] = 0.0f;
    func_001183F0(aa, buf, k);
    a0[2] += 1.0f;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/00DFB8", func_0010E648);

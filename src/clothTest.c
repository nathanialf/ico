#include "common.h"


#include "vu0.h"
void InitClothTestGeo(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_QMFC2_NI(v0, 4);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}

void ClothTestGeo(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyzw, 4, 1, 2);
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void ClothTestDL(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 6);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyz, 5, 5, 6, x);
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_NOP();
}

void func_001C8ED8(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 5);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_NOP();
}

void func_001C8EF8(void *a0, void *a1, void *a2, float f12)
{
    int sp_buf[4];
    register float q __asm__("$f0");
    register float scaled __asm__("$f12") = f12;
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_REG("vsub.xyzw $vf4, $vf1, $vf2");
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    VU0_LSV(sqc2, 4, 0x0, sp);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_REG("mul.s $f12, $f12, $f0");
    VU0_NOREORDER_END();

    VU0_LSV(lqc2, 4, 0x0, a2);
    VU0_LSV(lqc2, 5, 0x0, sp);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 6);
    VU0_NOREORDER_END();
    VU0_REG("vmulx.xyz $vf5, $vf5, $vf6x");
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
}

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C8F50);

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C8FB8);

int func_001C9078(void *a0, void *a1)
{
    int bits;
    int v0 = 0;
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    VU0_QMFC2_NI(v0, 3);
    bits = v0;
    {
        register float f1 __asm__("$f1");
        register float f0 __asm__("$f0");
        VU0_MTC1(v0, 1);
        VU0_REG("mtc1 $0, $f0");
        if (f0 < f1) return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C90B8);

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C9128);

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C91B0);

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C92D8);

void func_001C9328(void) {}

void func_001C9330(void) {}

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C9338);

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C9640);

INCLUDE_ASM("asm/nonmatchings/src/clothTest", func_001C9B30);


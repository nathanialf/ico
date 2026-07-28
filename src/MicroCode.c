#include "common.h"



#include "r5900.h"
#include "vu0.h"
void mc_setBaseOffset(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_V2OP(vftoi4.xyzw, 2, 1);
    VU0_LSV(sqc2, 2, 0x0, a0);
    VU0_NOP();
}

void mc_SetMicroCode(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_V2OP(vftoi0.xyzw, 2, 1);
    VU0_LSV(sqc2, 2, 0x0, a0);
    VU0_NOP();
}

void mc_TransMicroCode(void *dst, void *src)
{
    QCOPY16("$t0");
}

void mc_Reset(void *dst, void *src)
{
    QCOPY16("$t0");
}

void mc_Init(void *p0)
{
    VU0_LSV(sqc2, 0, 0x0, a0);
    VU0_NOP();
}

void func_00118490(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 3);
    VU0_NOREORDER_END();
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vsubx.w, 8, 0, 3, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 1, 3, x);
    VU0_V3OP_BC(vmaddw.xyzw, 9, 2, 8, w);
    VU0_LSV(sqc2, 9, 0x0, a0);
    VU0_NOP();
}

void func_001184B8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 3);
    VU0_NOREORDER_END();
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vsubx.w, 8, 0, 3, x);
    VU0_V3OP_ACC_BC(vmulax.xyz, 1, 3, x);
    VU0_V3OP_BC(vmaddw.xyz, 1, 2, 8, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void func_001184E0(void *p0)
{
    VU0_LSV(lqc2, 3, 0x0, a0);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_ACC_BC(vmulax.w, 0, 3, x);
    VU0_V3OP_ACC_BC(vmadday.w, 0, 3, y);
    VU0_V3OP_BC(vmaddz.w, 3, 0, 3, z);
    VU0_WORD(0x4B8303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void func_00118510(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_ACC_BC(vmulax.w, 0, 3, x);
    VU0_V3OP_ACC_BC(vmadday.w, 0, 3, y);
    VU0_V3OP_BC(vmaddz.w, 3, 0, 3, z);
    VU0_WORD(0x4B8303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void func_00118548(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_V3OP(vmul.xy, 3, 3, 3);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_WORD(0x4A0303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void func_00118578(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_V3OP(vmul.xz, 3, 3, 3);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_WORD(0x4A0303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void func_001185A8(void *dst, void *src)
{
    QCOPY64_PARALLEL("$a2", "$a3", "$t0", "$t1");
}

void func_001185D0(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 14, 0x0, a1);
    VU0_LSV(lqc2, 15, 0x10, a1);
    VU0_LSV(lqc2, 16, 0x20, a1);
    VU0_LSV(lqc2, 17, 0x30, a1);
    VU0_LSV(lqc2, 24, 0x0, a2);
    VU0_LSV(lqc2, 25, 0x10, a2);
    VU0_LSV(lqc2, 26, 0x20, a2);
    VU0_LSV(lqc2, 27, 0x30, a2);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 24, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 24, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 24, z);
    VU0_V3OP_BC(vmaddw.xyzw, 24, 17, 24, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 25, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 25, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 25, z);
    VU0_V3OP_BC(vmaddw.xyzw, 25, 17, 25, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 26, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 26, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 26, z);
    VU0_V3OP_BC(vmaddw.xyzw, 26, 17, 26, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 27, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 27, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 27, z);
    VU0_V3OP_BC(vmaddw.xyzw, 27, 17, 27, w);
    VU0_LSV(sqc2, 24, 0x0, a0);
    VU0_LSV(sqc2, 25, 0x10, a0);
    VU0_LSV(sqc2, 26, 0x20, a0);
    VU0_LSV(sqc2, 27, 0x30, a0);
    VU0_NOP();
}

void func_00118648(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 8, 0x0, a2);
    VU0_LSV(lqc2, 14, 0x0, a1);
    VU0_LSV(lqc2, 15, 0x10, a1);
    VU0_LSV(lqc2, 16, 0x20, a1);
    VU0_LSV(lqc2, 17, 0x30, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 17, 8, w);
    VU0_LSV(sqc2, 10, 0x0, a0);
    VU0_NOP();
}

void func_00118678(void *p0)
{
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_LSV(sqc2, 14, 0x0, a0);
    VU0_LSV(sqc2, 15, 0x10, a0);
    VU0_LSV(sqc2, 16, 0x20, a0);
    VU0_LSV(sqc2, 17, 0x30, a0);
    VU0_NOP();
}

void func_001186A0(void *p0)
{
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_LSV(sqc2, 14, 0x0, a0);
    VU0_LSV(sqc2, 15, 0x10, a0);
    VU0_LSV(sqc2, 16, 0x20, a0);
    VU0_NOP();
}

INCLUDE_ASM("asm/nonmatchings/src/MicroCode", func_001186C8);

INCLUDE_ASM("asm/nonmatchings/src/MicroCode", func_00118710);

INCLUDE_ASM("asm/nonmatchings/src/MicroCode", func_00118780);

INCLUDE_ASM("asm/nonmatchings/src/MicroCode", func_00118818);

INCLUDE_ASM("asm/nonmatchings/src/MicroCode", func_00118940);

INCLUDE_ASM("asm/nonmatchings/src/MicroCode", func_00118A10);

void func_00118A48(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(a2, 12);
    VU0_QMTC2_NI(a2, 1);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vaddw.x, 2, 1, 0, w);
    VU0_V3OP(vadd.x, 1, 1, 1);
    VU0_REG("vrinit $R, $vf2x");
    VU0_REG("vrxor $R, $vf1x");
    VU0_NOP();
}


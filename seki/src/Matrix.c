#include "common.h"
#include "vu0.h"

extern float func_0010ED30(int x);
extern float p2o_SetDefaultEnviroment(int x);

void _RemakeNormal(short a0)
{
    float c = func_0010ED30(a0);
    float s = p2o_SetDefaultEnviroment(a0);
    __asm__ __volatile__("mfc1 $8, %0" : : "f"(c) : "$8");
    __asm__ __volatile__("mfc1 $9, %0" : : "f"(s) : "$9");
    VU0_QMTC2_NI(8, 1);
    VU0_QMTC2_NI(9, 2);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_V3OP_BC(vaddx.x, 14, 0, 1, x);
    VU0_V3OP_BC(vaddx.x, 16, 0, 2, x);
    VU0_V3OP_BC(vsubx.z, 14, 0, 2, x);
    VU0_V3OP_BC(vaddx.z, 16, 0, 1, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 14, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 15, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 16, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 17, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 14);
    VU0_V2OP(vmove.xyzw, 5, 15);
    VU0_V2OP(vmove.xyzw, 6, 16);
    VU0_V2OP(vmove.xyzw, 7, 17);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Matrix", _Sqrt);

void _InitCurrentMatrix(float a0, float a1, float a2)
{
    VU0_MFC1(6, 12);
    VU0_MFC1(7, 13);
    VU0_MFC1(8, 14);
    VU0_QMTC2_NI(6, 1);
    VU0_QMTC2_NI(7, 2);
    VU0_QMTC2_NI(8, 3);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_V3OP_BC(vaddx.x, 14, 0, 1, x);
    VU0_V3OP_BC(vaddx.y, 15, 0, 2, x);
    VU0_V3OP_BC(vaddx.z, 16, 0, 3, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 14, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 15, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 16, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 17, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 14);
    VU0_V2OP(vmove.xyzw, 5, 15);
    VU0_V2OP(vmove.xyzw, 6, 16);
    VU0_V2OP(vmove.xyzw, 7, 17);
    VU0_NOP();
}

void _UnitCurrentMatrix(void *a0) {
    VU0_LSV(sqc2, 4, 0x0, 4);
    VU0_LSV(sqc2, 5, 0x10, 4);
    VU0_LSV(sqc2, 6, 0x20, 4);
    VU0_LSV(sqc2, 7, 0x30, 4);
    VU0_NOP();
}

void _PushCurrentMatrix(void *a0) {
    VU0_LSV_R(sqc2, 7, 0x0, a0);
    VU0_NOP();
}

void _PopCurrentMatrix(void *a0) {
    VU0_LSV(lqc2, 4, 0x0, 4);
    VU0_LSV(lqc2, 5, 0x10, 4);
    VU0_LSV(lqc2, 6, 0x20, 4);
    VU0_LSV(lqc2, 7, 0x30, 4);
    VU0_NOP();
}

void _TransCurrentMatrix(void *a0)
{
    VU0_LSV(lqc2, 14, 0x0, 4);
    VU0_LSV(lqc2, 15, 0x10, 4);
    VU0_LSV(lqc2, 16, 0x20, 4);
    VU0_LSV(lqc2, 17, 0x30, 4);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 14, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 15, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 16, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 17, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 14);
    VU0_V2OP(vmove.xyzw, 5, 15);
    VU0_V2OP(vmove.xyzw, 6, 16);
    VU0_V2OP(vmove.xyzw, 7, 17);
    VU0_NOP();
}

void _SetTransCurrentMatrix(void *m)
{
    VU0_LSV(lqc2, 14, 0x0, a0);
    VU0_LSV(lqc2, 15, 0x10, a0);
    VU0_LSV(lqc2, 16, 0x20, a0);
    VU0_LSV(lqc2, 17, 0x30, a0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 4, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 4, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 4, z);
    VU0_V3OP_BC(vmaddw.xyzw, 4, 17, 4, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 5, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 5, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 5, z);
    VU0_V3OP_BC(vmaddw.xyzw, 5, 17, 5, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 6, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 6, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 6, z);
    VU0_V3OP_BC(vmaddw.xyzw, 6, 17, 6, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 7, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 7, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 7, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 17, 7, w);
    VU0_NOP();
}

void _ClearTransCurrentMatrix(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf8, 0x0($5)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf7, $vf8w\n"
        "sqc2 $vf10, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void _RotCurrentMatrixX(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf8, 0x0($5)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf7, $vf8w\n"
        "vdiv $Q, $vf0w, $vf10w\n"
        "vwaitq\n"
        "vmulq.xyz $vf10, $vf10, $Q\n"
        "sqc2 $vf10, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void _RotCurrentMatrixY(void)
{
    VU0_V3OP(vsub.xyzw, 1, 0, 0);
    VU0_V3OP_BC(vaddx.y, 14, 1, 5, x);
    VU0_V3OP_BC(vaddx.z, 14, 1, 6, x);
    VU0_V3OP_BC(vaddx.w, 14, 1, 7, x);
    VU0_V3OP_BC(vaddy.x, 15, 1, 4, y);
    VU0_V3OP_BC(vaddy.z, 15, 1, 6, y);
    VU0_V3OP_BC(vaddy.w, 15, 1, 7, y);
    VU0_V3OP_BC(vaddz.x, 16, 1, 4, z);
    VU0_V3OP_BC(vaddz.y, 16, 1, 5, z);
    VU0_V3OP_BC(vaddz.w, 16, 1, 7, z);
    VU0_V3OP_BC(vaddw.x, 17, 1, 4, w);
    VU0_V3OP_BC(vaddw.y, 17, 1, 5, w);
    VU0_V3OP_BC(vaddw.z, 17, 1, 6, w);
    VU0_V2OP(vmove.yzw, 4, 14);
    VU0_V2OP(vmove.xzw, 5, 15);
    VU0_V2OP(vmove.xyw, 6, 16);
    VU0_V2OP(vmove.xyz, 7, 17);
    VU0_NOP();
}

void _RotCurrentMatrixZ(void) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vsub.xyzw $vf1, $vf0, $vf0\n"
        "vaddx.y $vf14, $vf1, $vf5x\n"
        "vaddx.z $vf14, $vf1, $vf6x\n"
        "vaddy.x $vf15, $vf1, $vf4y\n"
        "vaddy.z $vf15, $vf1, $vf6y\n"
        "vaddz.x $vf16, $vf1, $vf4z\n"
        "vaddz.y $vf16, $vf1, $vf5z\n"
        "vmove.yz $vf4, $vf14\n"
        "vmove.xz $vf5, $vf15\n"
        "vmove.xy $vf6, $vf16\n"
        ".set reorder\n" : : : "memory");
}

void _ScaleCurrentMatrix(void)
{
    VU0_V3OP(vsub.xyzw, 1, 0, 0);
    VU0_V3OP_BC(vsubw.x, 2, 0, 0, w);
    VU0_V3OP_BC(vaddx.y, 14, 1, 5, x);
    VU0_V3OP_BC(vaddx.z, 14, 1, 6, x);
    VU0_V3OP_BC(vaddy.x, 15, 1, 4, y);
    VU0_V3OP_BC(vaddy.z, 15, 1, 6, y);
    VU0_V3OP_BC(vaddz.x, 16, 1, 4, z);
    VU0_V3OP_BC(vaddz.y, 16, 1, 5, z);
    VU0_V3OP_BC(vmulx.xyz, 17, 7, 2, x);
    VU0_V2OP(vmove.yz, 4, 14);
    VU0_V2OP(vmove.xz, 5, 15);
    VU0_V2OP(vmove.xy, 6, 16);
    VU0_V2OP(vmove.w, 17, 0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 0, 17, w);
    VU0_NOP();
}

void _GetCurrentMatrix(void)
{
    VU0_MEM("vsqi.xyzw $vf1, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf2, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf3, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf4, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf5, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf6, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf7, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf8, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf9, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf10, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf11, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf12, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf13, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf14, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf15, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf16, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf17, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf18, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf19, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf20, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf21, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf22, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf23, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf24, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf25, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf26, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf27, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf28, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf29, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf30, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf31, ($vi15++)");
    VU0_NOP();
}

void _GetCurrentMatrixTrans(void)
{
    VU0_MEM("vlqd.xyzw $vf31, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf30, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf29, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf28, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf27, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf26, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf25, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf24, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf23, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf22, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf21, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf20, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf19, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf18, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf17, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf16, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf15, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf14, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf13, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf12, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf11, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf10, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf9, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf8, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf7, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf6, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf5, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf4, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf3, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf2, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf1, (--$vi15)");
    VU0_NOP();
}

void _SetCurrentMatrix(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "vmul.xyz $vf3, $vf1, $vf1\n"
        "vmulax.w $ACC, $vf0, $vf3x\n"
        "vmadday.w $ACC, $vf0, $vf3y\n"
        "vmaddz.w $vf3, $vf0, $vf3z\n"
        "vrsqrt $Q, $vf0w, $vf3w\n"
        "vwaitq\n"
        "vmulq.xyz $vf1, $vf1, $Q\n"
        "sqc2 $vf1, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

float _MulCurrentMatrixR(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($4)\n"
        "lqc2 $vf2, 0x0($5)\n"
        "vaddw.x $vf3, $vf0, $vf0w\n"
        "vmul.xyz $vf2, $vf1, $vf2\n"
        "vaddax.x $ACC, $vf0, $vf2x\n"
        "vmadday.x $ACC, $vf3, $vf2y\n"
        "vmaddz.x $vf2, $vf3, $vf2z\n"
        "qmfc2.ni $2, $vf2\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

void _MulCurrentMatrixL(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vopmula.xyz $ACC, $vf1, $vf2\n"
        "vopmsub.xyz $vf3, $vf2, $vf1\n"
        "vsub.w $vf3, $vf3, $vf3\n"
        "sqc2 $vf3, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void _ApplyCurrentMatrix(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vadd.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, 4);
    VU0_NOP();
}

void _RotTransPersCurrentMatrix(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vadd.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, 4);
    VU0_NOP();
}

void _TransposeCurrentMatrix(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, 4);
    VU0_NOP();
}

void _TransposeRotationCurrentMatrix(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vsub.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, 4);
    VU0_NOP();
}

void _InverseCurrentMatrix(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf2\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyzw, 3, 1, 2, x);
    VU0_LSV(sqc2, 3, 0x0, 4);
    VU0_NOP();
}

void _PushVu0Registers(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf2\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyz, 1, 1, 2, x);
    VU0_LSV(sqc2, 1, 0x0, 4);
    VU0_NOP();
}

void _PopVu0Registers(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vmulx.x $vf1, $vf1, $vf2x\n"
        "vmuly.y $vf1, $vf1, $vf2y\n"
        "vmulz.z $vf1, $vf1, $vf2z\n"
        "sqc2 $vf1, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

#include "common.h"
#include "vu0.h"
#include "r5900.h"

void mc_setBaseOffset(void *a0, void *a1) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_V2OP(vftoi4.xyzw, 2, 1);
    VU0_LSV(sqc2, 2, 0x0, 4);
    VU0_NOP();
}

void mc_SetMicroCode(void *a0, void *a1) {
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_V2OP(vftoi0.xyzw, 2, 1);
    VU0_LSV(sqc2, 2, 0x0, 4);
    VU0_NOP();
}

void mc_TransMicroCode(void *a0, void *a1) {
    QCOPY16("$t0");
}

void mc_Reset(void *a0, void *a1) {
    QCOPY16("$t0");
}

void mc_Init(void *a0) {
    VU0_LSV_R(sqc2, 0, 0x0, a0);
    VU0_NOP();
}

void func_001188B8(void *a0, void *a1, void *a2, float t) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf3\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vsubx.w $vf8, $vf0, $vf3x\n"
        "vmulax.xyzw $ACC, $vf1, $vf3x\n"
        "vmaddw.xyzw $vf9, $vf2, $vf8w\n"
        "sqc2 $vf9, 0x0($4)\n"
        ".set reorder\n" : : : "$8", "memory");
}

void func_001188E0(void *a0, void *a1, void *a2, float t) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf3\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vsubx.w $vf8, $vf0, $vf3x\n"
        "vmulax.xyz $ACC, $vf1, $vf3x\n"
        "vmaddw.xyz $vf1, $vf2, $vf8w\n"
        "sqc2 $vf1, 0x0($4)\n"
        ".set reorder\n" : : : "$8", "memory");
}

float func_00118908(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf3, 0x0($4)\n"
        "vmul.xyz $vf3, $vf3, $vf3\n"
        "vmulax.w $ACC, $vf0, $vf3x\n"
        "vmadday.w $ACC, $vf0, $vf3y\n"
        "vmaddz.w $vf3, $vf0, $vf3z\n"
        ".word 0x4B8303BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

float func_00118938(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($4)\n"
        "lqc2 $vf2, 0x0($5)\n"
        "vsub.xyzw $vf3, $vf1, $vf2\n"
        "vmul.xyz $vf3, $vf3, $vf3\n"
        "vmulax.w $ACC, $vf0, $vf3x\n"
        "vmadday.w $ACC, $vf0, $vf3y\n"
        "vmaddz.w $vf3, $vf0, $vf3z\n"
        ".word 0x4B8303BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

float func_00118970(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($4)\n"
        "lqc2 $vf2, 0x0($5)\n"
        "vsub.xyzw $vf3, $vf1, $vf2\n"
        "vmul.xy $vf3, $vf3, $vf3\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        ".word 0x4A0303BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

float func_001189A0(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($4)\n"
        "lqc2 $vf2, 0x0($5)\n"
        "vsub.xyzw $vf3, $vf1, $vf2\n"
        "vmul.xz $vf3, $vf3, $vf3\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        ".word 0x4A0303BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

void func_001189D0(void *dst, void *src) {
    QCOPY64_PARALLEL("$6", "$7", "$8", "$9");
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001189F8);

void func_00118A70(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf8, 0x0($6)\n"
        "lqc2 $vf14, 0x0($5)\n"
        "lqc2 $vf15, 0x10($5)\n"
        "lqc2 $vf16, 0x20($5)\n"
        "lqc2 $vf17, 0x30($5)\n"
        "vmulax.xyzw $ACC, $vf14, $vf8x\n"
        "vmadday.xyzw $ACC, $vf15, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf17, $vf8w\n"
        "sqc2 $vf10, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void func_00118AA0(void *a0) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vmove.xyzw $vf17, $vf0\n"
        "vmr32.xyzw $vf16, $vf17\n"
        "vmr32.xyzw $vf15, $vf16\n"
        "vmr32.xyzw $vf14, $vf15\n"
        "sqc2 $vf14, 0x0($4)\n"
        "sqc2 $vf15, 0x10($4)\n"
        "sqc2 $vf16, 0x20($4)\n"
        "sqc2 $vf17, 0x30($4)\n"
        ".set reorder\n" : : : "memory");
}

void func_00118AC8(void *a0) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vmove.xyzw $vf17, $vf0\n"
        "vmr32.xyzw $vf16, $vf17\n"
        "vmr32.xyzw $vf15, $vf16\n"
        "vmr32.xyzw $vf14, $vf15\n"
        "sqc2 $vf14, 0x0($4)\n"
        "sqc2 $vf15, 0x10($4)\n"
        "sqc2 $vf16, 0x20($4)\n"
        ".set reorder\n" : : : "memory");
}

void func_00118AF0(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lq $8, 0x0($5)\n"
        "lq $9, 0x10($5)\n"
        "lq $10, 0x20($5)\n"
        "lq $11, 0x30($5)\n"
        "pextlw $12, $9, $8\n"
        "pextuw $13, $9, $8\n"
        "pextlw $14, $11, $10\n"
        "pextuw $15, $11, $10\n"
        "pcpyld $8, $14, $12\n"
        "pcpyud $9, $12, $14\n"
        "pcpyld $10, $15, $13\n"
        "pcpyud $11, $13, $15\n"
        "sq $8, 0x0($4)\n"
        "sq $9, 0x10($4)\n"
        "sq $10, 0x20($4)\n"
        "sq $11, 0x30($4)\n"
        ".set reorder\n" : : : "$8","$9","$10","$11","$12","$13","$14","$15","memory");
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118B38);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118C40);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118D68);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118E38);

void func_00118E70(float a0) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "mfc1 $6, $f12\n"
        "qmtc2.ni $6, $vf1\n"
        "vaddw.x $vf2, $vf1, $vf0w\n"
        "vadd.x $vf1, $vf1, $vf1\n"
        "vrinit $R, $vf2x\n"
        "vrxor $R, $vf1x\n"
        ".set reorder\n" : : : "$6", "memory");
}

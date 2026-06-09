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

void func_001189F8(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0($5)\n"
        "lqc2 $vf15, 0x10($5)\n"
        "lqc2 $vf16, 0x20($5)\n"
        "lqc2 $vf17, 0x30($5)\n"
        "lqc2 $vf24, 0x0($6)\n"
        "lqc2 $vf25, 0x10($6)\n"
        "lqc2 $vf26, 0x20($6)\n"
        "lqc2 $vf27, 0x30($6)\n"
        "vmulax.xyzw $ACC, $vf14, $vf24x\n"
        "vmadday.xyzw $ACC, $vf15, $vf24y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf24z\n"
        "vmaddw.xyzw $vf24, $vf17, $vf24w\n"
        "vmulax.xyzw $ACC, $vf14, $vf25x\n"
        "vmadday.xyzw $ACC, $vf15, $vf25y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf25z\n"
        "vmaddw.xyzw $vf25, $vf17, $vf25w\n"
        "vmulax.xyzw $ACC, $vf14, $vf26x\n"
        "vmadday.xyzw $ACC, $vf15, $vf26y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf26z\n"
        "vmaddw.xyzw $vf26, $vf17, $vf26w\n"
        "vmulax.xyzw $ACC, $vf14, $vf27x\n"
        "vmadday.xyzw $ACC, $vf15, $vf27y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf27z\n"
        "vmaddw.xyzw $vf27, $vf17, $vf27w\n"
        "sqc2 $vf24, 0x0($4)\n"
        "sqc2 $vf25, 0x10($4)\n"
        "sqc2 $vf26, 0x20($4)\n"
        "sqc2 $vf27, 0x30($4)\n"
        ".set reorder\n" : : : "memory");
}

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

void func_00118B38(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lq $8, 0x0($5)\n"
        "lq $9, 0x10($5)\n"
        "lq $10, 0x20($5)\n"
        "lqc2 $vf4, 0x30($5)\n"
        "vmove.xyzw $vf5, $vf4\n"
        "vsub.xyz $vf4, $vf4, $vf4\n"
        "vmove.xyzw $vf9, $vf4\n"
        "qmfc2.ni $11, $vf4\n"
        "pextlw $12, $9, $8\n"
        "pextuw $13, $9, $8\n"
        "pextlw $14, $11, $10\n"
        "pextuw $15, $11, $10\n"
        "pcpyld $8, $14, $12\n"
        "pcpyud $9, $12, $14\n"
        "pcpyld $10, $15, $13\n"
        "qmtc2.ni $8, $vf6\n"
        "qmtc2.ni $9, $vf7\n"
        "qmtc2.ni $10, $vf8\n"
        "vmulax.xyz $ACC, $vf6, $vf5x\n"
        "vmadday.xyz $ACC, $vf7, $vf5y\n"
        "vmaddz.xyz $vf4, $vf8, $vf5z\n"
        "vsub.xyz $vf4, $vf9, $vf4\n"
        "sq $8, 0x0($4)\n"
        "sq $9, 0x10($4)\n"
        "sq $10, 0x20($4)\n"
        "sqc2 $vf4, 0x30($4)\n"
        ".set reorder\n" : : : "$8","$9","$10","$11","$12","$13","$14","$15","memory");
}

float D_00272540[16] __attribute__((aligned(16))) = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

void func_00118BA8(void *a0, void *a1, float *a2) {
    D_00272540[0] = a2[0];
    D_00272540[5] = a2[1];
    D_00272540[10] = a2[2];
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0($5)\n"
        "lqc2 $vf15, 0x10($5)\n"
        "lqc2 $vf16, 0x20($5)\n"
        "lqc2 $vf17, 0x30($5)\n"
        "lqc2 $vf24, 0x0(%0)\n"
        "lqc2 $vf25, 0x10(%0)\n"
        "lqc2 $vf26, 0x20(%0)\n"
        "lqc2 $vf27, 0x30(%0)\n"
        "vmulax.xyzw $ACC, $vf14, $vf24x\n"
        "vmadday.xyzw $ACC, $vf15, $vf24y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf24z\n"
        "vmaddw.xyzw $vf24, $vf17, $vf24w\n"
        "vmulax.xyzw $ACC, $vf14, $vf25x\n"
        "vmadday.xyzw $ACC, $vf15, $vf25y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf25z\n"
        "vmaddw.xyzw $vf25, $vf17, $vf25w\n"
        "vmulax.xyzw $ACC, $vf14, $vf26x\n"
        "vmadday.xyzw $ACC, $vf15, $vf26y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf26z\n"
        "vmaddw.xyzw $vf26, $vf17, $vf26w\n"
        "vmulax.xyzw $ACC, $vf14, $vf27x\n"
        "vmadday.xyzw $ACC, $vf15, $vf27y\n"
        "vmaddaz.xyzw $ACC, $vf16, $vf27z\n"
        "vmaddw.xyzw $vf27, $vf17, $vf27w\n"
        "sqc2 $vf24, 0x0($4)\n"
        "sqc2 $vf25, 0x10($4)\n"
        "sqc2 $vf26, 0x20($4)\n"
        "sqc2 $vf27, 0x30($4)\n"
        ".set reorder\n" : : "r"(D_00272540) : "memory");
}

void func_00118C40(void *a0, void *a1, void *a2, void *a3) {
    int buf[20] __attribute__((aligned(16)));
    __asm__ __volatile__(
        ".set noreorder\n"
        "vmove.xyzw $vf17, $vf0\n"
        "vmr32.xyzw $vf16, $vf17\n"
        "vmr32.xyzw $vf15, $vf16\n"
        "vmr32.xyzw $vf14, $vf15\n"
        "sqc2 $vf14, 0x0($sp)\n"
        "sqc2 $vf15, 0x10($sp)\n"
        "sqc2 $vf16, 0x20($sp)\n"
        "sqc2 $vf17, 0x30($sp)\n"
        "addiu $2, $sp, 0x40\n"
        "lqc2 $vf1, 0x0($7)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vopmula.xyz $ACC, $vf1, $vf2\n"
        "vopmsub.xyz $vf3, $vf2, $vf1\n"
        "vsub.w $vf3, $vf3, $vf3\n"
        "sqc2 $vf3, 0x0($2)\n"
        "lqc2 $vf1, 0x0($2)\n"
        "vmul.xyz $vf3, $vf1, $vf1\n"
        "vmulax.w $ACC, $vf0, $vf3x\n"
        "vmadday.w $ACC, $vf0, $vf3y\n"
        "vmaddz.w $vf3, $vf0, $vf3z\n"
        "vrsqrt $Q, $vf0w, $vf3w\n"
        "vwaitq\n"
        "vmulq.xyz $vf1, $vf1, $Q\n"
        "sqc2 $vf1, 0x0($sp)\n"
        "addiu $7, $sp, 0x20\n"
        "lqc2 $vf1, 0x0($6)\n"
        "vmul.xyz $vf3, $vf1, $vf1\n"
        "vmulax.w $ACC, $vf0, $vf3x\n"
        "vmadday.w $ACC, $vf0, $vf3y\n"
        "vmaddz.w $vf3, $vf0, $vf3z\n"
        "vrsqrt $Q, $vf0w, $vf3w\n"
        "vwaitq\n"
        "vmulq.xyz $vf1, $vf1, $Q\n"
        "sqc2 $vf1, 0x0($7)\n"
        "addiu $2, $sp, 0x10\n"
        "lqc2 $vf1, 0x0($7)\n"
        "lqc2 $vf2, 0x0($sp)\n"
        "vopmula.xyz $ACC, $vf1, $vf2\n"
        "vopmsub.xyz $vf3, $vf2, $vf1\n"
        "vsub.w $vf3, $vf3, $vf3\n"
        "sqc2 $vf3, 0x0($2)\n"
        "addiu $3, $sp, 0x30\n"
        "lq $8, 0x0($5)\n"
        "sq $8, 0x0($3)\n"
        "lq $8, 0x0($sp)\n"
        "lq $9, 0x10($sp)\n"
        "lq $10, 0x20($sp)\n"
        "lqc2 $vf4, 0x30($sp)\n"
        "vmove.xyzw $vf5, $vf4\n"
        "vsub.xyz $vf4, $vf4, $vf4\n"
        "vmove.xyzw $vf9, $vf4\n"
        "qmfc2.ni $11, $vf4\n"
        "pextlw $12, $9, $8\n"
        "pextuw $13, $9, $8\n"
        "pextlw $14, $11, $10\n"
        "pextuw $15, $11, $10\n"
        "pcpyld $8, $14, $12\n"
        "pcpyud $9, $12, $14\n"
        "pcpyld $10, $15, $13\n"
        "qmtc2.ni $8, $vf6\n"
        "qmtc2.ni $9, $vf7\n"
        "qmtc2.ni $10, $vf8\n"
        "vmulax.xyz $ACC, $vf6, $vf5x\n"
        "vmadday.xyz $ACC, $vf7, $vf5y\n"
        "vmaddz.xyz $vf4, $vf8, $vf5z\n"
        "vsub.xyz $vf4, $vf9, $vf4\n"
        "sq $8, 0x0($4)\n"
        "sq $9, 0x10($4)\n"
        "sq $10, 0x20($4)\n"
        "sqc2 $vf4, 0x30($4)\n"
        ".set reorder\n"
        : "=m"(buf)
        :
        : "$2", "$3", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

void func_00118D68(void *a0, void *a1, void *a2, void *a3) {
    register void *p2 __asm__("$3") = a2;
    register void *p3 __asm__("$2") = a3;
    __asm__ __volatile__(
        ".set noreorder\n"
        "vsubw.x $vf1, $vf0, $vf0w\n"
        "lqc2 $vf24, 0x0(%1)\n"
        "lqc2 $vf25, 0x0(%2)\n"
        "lqc2 $vf26, 0x0(%3)\n"
        "vmulx.xyz $vf24, $vf24, $vf1x\n"
        "vmulx.xyz $vf25, $vf25, $vf1x\n"
        "vmulx.xyz $vf26, $vf26, $vf1x\n"
        "vmul.xyz $vf14, $vf24, $vf24\n"
        "vaddy.x $vf14, $vf14, $vf14y\n"
        "vaddz.x $vf14, $vf14, $vf14z\n"
        "vrsqrt $Q, $vf0w, $vf14x\n"
        "vmul.xyz $vf15, $vf25, $vf25\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vwaitq\n"
        "vmulq.xyz $vf24, $vf24, $Q\n"
        "vrsqrt $Q, $vf0w, $vf15x\n"
        "vmul.xyz $vf16, $vf26, $vf26\n"
        "vaddy.x $vf16, $vf16, $vf16y\n"
        "vaddz.x $vf16, $vf16, $vf16z\n"
        "vwaitq\n"
        "vmulq.xyz $vf25, $vf25, $Q\n"
        "vrsqrt $Q, $vf0w, $vf16x\n"
        "vwaitq\n"
        "vmulq.xyz $vf26, $vf26, $Q\n"
        "vmove.xyzw $vf27, $vf0\n"
        "vmove.xyzw $vf14, $vf24\n"
        "vmove.xyzw $vf15, $vf25\n"
        "vmove.xyzw $vf16, $vf26\n"
        "vmove.xyzw $vf17, $vf27\n"
        "vsub.xyzw $vf1, $vf0, $vf0\n"
        "vaddx.y $vf14, $vf1, $vf25x\n"
        "vaddx.z $vf14, $vf1, $vf26x\n"
        "vaddx.w $vf14, $vf1, $vf27x\n"
        "vaddy.x $vf15, $vf1, $vf24y\n"
        "vaddy.z $vf15, $vf1, $vf26y\n"
        "vaddy.w $vf15, $vf1, $vf27y\n"
        "vaddz.x $vf16, $vf1, $vf24z\n"
        "vaddz.y $vf16, $vf1, $vf25z\n"
        "vaddz.w $vf16, $vf1, $vf27z\n"
        "vaddw.x $vf17, $vf1, $vf24w\n"
        "vaddw.y $vf17, $vf1, $vf25w\n"
        "vaddw.z $vf17, $vf1, $vf26w\n"
        "sqc2 $vf14, 0x0(%0)\n"
        "sqc2 $vf15, 0x10(%0)\n"
        "sqc2 $vf16, 0x20(%0)\n"
        "sqc2 $vf17, 0x30(%0)\n"
        ".set reorder\n" : : "r"(a0), "r"(a1), "r"(p2), "r"(p3) : "memory");
}

void func_00118E38(void *a0, void *a1, void *a2, void *a3, void *a4) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "daddu $10, $6, $0\n"
        "daddu $3, $7, $0\n"
        "daddu $2, $8, $0\n"
        "lq $6, 0x0($5)\n"
        "lq $7, 0x0($10)\n"
        "lq $8, 0x0($3)\n"
        "lq $9, 0x0($2)\n"
        "sq $6, 0x0($4)\n"
        "sq $7, 0x10($4)\n"
        "sq $8, 0x20($4)\n"
        "sq $9, 0x30($4)\n"
        ".set reorder\n" : : : "$2","$3","$6","$7","$8","$9","$10","memory");
}

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

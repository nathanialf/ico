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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001188E0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118908);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118938);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118970);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001189A0);

void func_001189D0(void *dst, void *src) {
    QCOPY64_PARALLEL("$6", "$7", "$8", "$9");
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001189F8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118A70);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118AF0);

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

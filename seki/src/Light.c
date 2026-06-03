#include "common.h"
#include "vu0.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_killLinkLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_killLinkAmbient);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_AddLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_getNearLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_getAmbientLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_MakeLightMatrix);

extern float D_00629EC0;
extern float D_00629EC8;

void light_DispVolume(float a0, float a1) {
    D_00629EC0 = a0;
    D_00629EC8 = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_GetColorAnalog);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_DrawCursor);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_Tool);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_InitLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_KillAllFixLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_KillAllAmbient);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_AddAmbientObject);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_resetFlatLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00115CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00116308);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001163E8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001169D8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00116CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117038);

extern int D_0062BF30;
extern int D_0062BF34;
extern int D_00629F70;

void func_00117B80(void) {
    D_0062BF30 = 0;
    D_0062BF34 = 0;
    D_00629F70 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117B90);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117BF0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117C48);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117D78);

float func_00118048(float a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "mfc1 $6, $f12\n"
        "qmtc2.ni $6, $vf1\n"
        ".word 0x4A0103BD\n"
        "vwaitq\n"
        "cfc2.ni $7, $vi22\n"
        "mtc1 $7, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$6", "$7");
    return ret;
}

void func_00118068(void) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vmove.xyzw $vf7, $vf0\n"
        "vmr32.xyzw $vf6, $vf7\n"
        "vmr32.xyzw $vf5, $vf6\n"
        "vmr32.xyzw $vf4, $vf5\n"
        "viaddi $vi15, $vi0, 0x0\n"
        ".set reorder\n");
}

void func_00118088(void) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vmove.xyzw $vf7, $vf0\n"
        "vmr32.xyzw $vf6, $vf7\n"
        "vmr32.xyzw $vf5, $vf6\n"
        "vmr32.xyzw $vf4, $vf5\n"
        "viaddi $vi15, $vi0, 0x0\n"
        ".set reorder\n");
}

void func_001180A8(void) {
    VU0_MEM("vsqi.xyzw $vf4, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf5, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf6, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf7, ($vi15++)");
    VU0_NOP();
}

void func_001180C0(void) {
    VU0_MEM("vlqd.xyzw $vf7, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf6, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf5, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf4, (--$vi15)");
    VU0_NOP();
}

void func_001180D8(void *a0) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf8, 0x0($4)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf7, $vf7, $vf8w\n"
        ".set reorder\n" : : : "memory");
}

void func_001180F8(void *a0) {
    VU0_LSV_R(lqc2, 8, 0x0, a0);
    VU0_V2OP(vmove.xyzw, 7, 8);
    VU0_NOP();
}

void func_00118108(void) {
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_NOP();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00118118);

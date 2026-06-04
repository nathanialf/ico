#include "common.h"
#include "vu0.h"

float InitClothTestGeo(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "vmul.xz $vf4, $vf4, $vf4\n"
        "vaddz.x $vf4, $vf4, $vf4z\n"
        "qmfc2.ni $2, $vf4\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

float ClothTestGeo(void *a0, void *a1, void *a2) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vsub.xyzw $vf4, $vf1, $vf2\n"
        "vmul.xyz $vf3, $vf4, $vf4\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        "vrsqrt $Q, $vf0w, $vf3x\n"
        "sqc2 $vf4, 0x0($4)\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

void ClothTestDL(void *a0, void *a1, void *a2, float a3) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x0($6)\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "vadd.xyz $vf4, $vf4, $vf5\n"
        "sqc2 $vf4, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void func_001C6148(void *a0, void *a1, float a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($5)\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf5\n"
        "vmulx.xz $vf4, $vf4, $vf5x\n"
        "sqc2 $vf4, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6168);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C61C0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6228);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C62E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6328);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6398);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6420);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6548);

void func_001C6598(void) {
}

void func_001C65A0(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C65A8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C68B0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6DA0);

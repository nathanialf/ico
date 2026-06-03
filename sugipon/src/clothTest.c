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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", ClothTestGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", ClothTestDL);

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

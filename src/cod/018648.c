void func_00118648(void *dst, void *m, void *v) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0($a2)\n\t"
        "lqc2 $vf14, 0($a1)\n\t"
        "lqc2 $vf15, 16($a1)\n\t"
        "lqc2 $vf16, 32($a1)\n\t"
        "lqc2 $vf17, 48($a1)\n\t"
        "vmulax.xyzw $ACC, $vf14, $vf8x\n\t"
        "vmadday.xyzw $ACC, $vf15, $vf8y\n\t"
        "vmaddaz.xyzw $ACC, $vf16, $vf8z\n\t"
        "vmaddw.xyzw $vf10, $vf17, $vf8w\n\t"
        "sqc2 $vf10, 0($a0)\n\t"
        "nop"
        : : : "memory"
    );
}

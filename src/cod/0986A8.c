void func_001986A8(void *dst, void *m, void *v) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\t"
        "lqc2 $vf5, 16($a1)\n\t"
        "lqc2 $vf6, 32($a1)\n\t"
        "lqc2 $vf7, 48($a1)\n\t"
        "lqc2 $vf8, 0($a2)\n\t"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n\t"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n\t"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n\t"
        "vmaddw.xyzw $vf9, $vf7, $vf0w\n\t"
        "sqc2 $vf9, 0($a0)\n\t"
        "nop"
        : : : "memory"
    );
}

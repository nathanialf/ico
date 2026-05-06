void func_00243B30(void *dst, void *m, void *v) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a2)\n\t"
        "lqc2 $vf5, 48($a1)\n\t"
        "lq $a3, 0($a1)\n\t"
        "lq $t0, 16($a1)\n\t"
        "lq $t1, 32($a1)\n\t"
        "vadd.xyz $vf5, $vf5, $vf4\n\t"
        "sq $a3, 0($a0)\n\t"
        "sq $t0, 16($a0)\n\t"
        "sq $t1, 32($a0)\n\t"
        "sqc2 $vf5, 48($a0)"
        : : : "memory"
    );
}

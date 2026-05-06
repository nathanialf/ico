void func_00243930(void *dst, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\t"
        "lqc2 $vf5, 0($a2)\n\t"
        "vopmula.xyz $ACC, $vf4, $vf5\n\t"
        "vopmsub.xyz $vf6, $vf5, $vf4\n\t"
        "vsub.w $vf6, $vf6, $vf6\n\t"
        "sqc2 $vf6, 0($a0)"
        : : : "memory"
    );
}

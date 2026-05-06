void func_001C8EB0(void *dst, void *a, void *b, float k) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "lqc2 $vf4, 0($a1)\n\t"
        "lqc2 $vf5, 0($a2)\n\t"
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf6\n\t"
        "vmulx.xyz $vf5, $vf5, $vf6x\n\t"
        "vadd.xyz $vf4, $vf4, $vf5\n\t"
        "sqc2 $vf4, 0($a0)\n\t"
        ".set reorder"
        : : : "memory"
    );
}

void func_001C8ED8(void *dst, void *src, float k) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "lqc2 $vf4, 0($a1)\n\t"
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf5\n\t"
        "vmulx.xz $vf4, $vf4, $vf5x\n\t"
        "sqc2 $vf4, 0($a0)\n\t"
        ".set reorder"
        : : : "memory"
    );
}

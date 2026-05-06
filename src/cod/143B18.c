void func_00243B18(void *dst, void *src, float k) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\t"
        ".set noreorder\n\t"
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf5\n\t"
        ".set reorder\n\t"
        "vmulx.xyzw $vf6, $vf4, $vf5x\n\t"
        "sqc2 $vf6, 0($a0)"
        : : : "memory"
    );
}

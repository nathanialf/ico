void func_001183D0(void *dst, void *src, float k) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "lqc2 $vf1, 0($a1)\n\t"
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf2\n\t"
        "vmulx.xyzw $vf3, $vf1, $vf2x\n\t"
        "sqc2 $vf3, 0($a0)\n\t"
        ".set reorder"
        : : : "memory"
    );
}

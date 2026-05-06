void func_00243AA8(void *dst, void *a, void *b, float t) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\t"
        "lqc2 $vf5, 0($a2)\n\t"
        ".set noreorder\n\t"
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf6\n\t"
        ".set reorder\n\t"
        "vaddw.x $vf7, $vf0, $vf0w\n\t"
        "vsub.x $vf8, $vf7, $vf6\n\t"
        "vmulax.xyzw $ACC, $vf4, $vf6x\n\t"
        "vmaddx.xyzw $vf9, $vf5, $vf8x\n\t"
        "sqc2 $vf9, 0($a0)"
        : : : "memory"
    );
}

void func_00243EC0(void *dst, void *src, float minv, float maxv) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "mfc1 $t0, $f12\n\t"
        "mfc1 $t1, $f13\n\t"
        "lqc2 $vf6, 0($a1)\n\t"
        "qmtc2.ni $t0, $vf4\n\t"
        "qmtc2.ni $t1, $vf5\n\t"
        ".set reorder\n\t"
        "vmaxx.xyzw $vf6, $vf6, $vf4x\n\t"
        "vminix.xyzw $vf6, $vf6, $vf5x\n\t"
        "sqc2 $vf6, 0($a0)"
        : : : "memory"
    );
}

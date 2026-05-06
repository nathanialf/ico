void func_00118490(void *dst, void *a, void *b, float t) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf3\n\t"
        "lqc2 $vf1, 0($a1)\n\t"
        "lqc2 $vf2, 0($a2)\n\t"
        "vsubx.w $vf8, $vf0, $vf3x\n\t"
        "vmulax.xyzw $ACC, $vf1, $vf3x\n\t"
        "vmaddw.xyzw $vf9, $vf2, $vf8w\n\t"
        "sqc2 $vf9, 0($a0)\n\t"
        ".set reorder"
        : : : "memory"
    );
}

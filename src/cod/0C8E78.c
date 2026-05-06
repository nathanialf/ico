float func_001C8E78(void *dst, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0($a1)\n\t"
        "lqc2 $vf2, 0($a2)\n\t"
        "vsub.xyzw $vf4, $vf1, $vf2\n\t"
        "vmul.xyz $vf3, $vf4, $vf4\n\t"
        "vaddy.x $vf3, $vf3, $vf3y\n\t"
        "vaddz.x $vf3, $vf3, $vf3z\n\t"
        "vrsqrt $Q, $vf0w, $vf3x\n\t"
        "sqc2 $vf4, 0($a0)\n\t"
        "vwaitq\n\t"
        ".set noreorder\n\t"
        "cfc2.ni $v0, $vi22\n\t"
        "mtc1 $v0, $f0\n\t"
        ".set reorder"
        : : : "memory"
    );
}

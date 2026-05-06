float func_001C8E30(void *p) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a0)\n\t"
        "vmul.xz $vf4, $vf4, $vf4\n\t"
        "vaddz.x $vf4, $vf4, $vf4z\n\t"
        "vrsqrt $Q, $vf0w, $vf4x\n\t"
        "vwaitq\n\t"
        ".set noreorder\n\t"
        "cfc2.ni $v0, $vi22\n\t"
        "mtc1 $v0, $f0\n\t"
        ".set reorder"
        : : : "memory"
    );
}

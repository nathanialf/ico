void func_001182F0(void *dst, void *v) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0($a1)\n\t"
        "vmul.xyz $vf3, $vf1, $vf1\n\t"
        "vmulax.w $ACC, $vf0, $vf3x\n\t"
        "vmadday.w $ACC, $vf0, $vf3y\n\t"
        "vmaddz.w $vf3, $vf0, $vf3z\n\t"
        "vrsqrt $Q, $vf0w, $vf3w\n\t"
        "vwaitq\n\t"
        "vmulq.xyz $vf1, $vf1, $Q\n\t"
        "sqc2 $vf1, 0($a0)\n\t"
        "nop"
        : : : "memory"
    );
}

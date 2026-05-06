void func_001180E0(void *dst, void *v) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0($a1)\n\t"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n\t"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n\t"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n\t"
        "vmaddw.xyzw $vf10, $vf7, $vf8w\n\t"
        "vdiv $Q, $vf0w, $vf10w\n\t"
        "vwaitq\n\t"
        "vmulq.xyz $vf10, $vf10, $Q\n\t"
        "sqc2 $vf10, 0($a0)\n\t"
        "nop"
        : : : "memory"
    );
}

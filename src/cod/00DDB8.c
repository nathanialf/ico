void func_0010DDB8(void *dst, void *q1, void *q2) {
    __asm__ __volatile__(
        "lqc2 $vf11, 0($a1)\n\t"
        "lqc2 $vf12, 0($a2)\n\t"
        "vmul.xyzw $vf13, $vf11, $vf12\n\t"
        "vaddy.x $vf13, $vf13, $vf13y\n\t"
        "vaddz.x $vf13, $vf13, $vf13z\n\t"
        "vsubx.w $vf13, $vf13, $vf13x\n\t"
        "vmulw.xyz $vf14, $vf12, $vf11w\n\t"
        "vmulw.xyz $vf15, $vf11, $vf12w\n\t"
        "vopmula.xyz $ACC, $vf12, $vf11\n\t"
        "vopmsub.xyz $vf16, $vf11, $vf12\n\t"
        "vadd.xyz $vf13, $vf14, $vf15\n\t"
        "vadd.xyz $vf13, $vf13, $vf16\n\t"
        "sqc2 $vf13, 0($a0)\n\t"
        "nop"
        : : : "memory"
    );
}

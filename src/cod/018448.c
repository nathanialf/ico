void func_00118448(void *dst, void *src) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0($a1)\n\tvftoi0.xyzw $vf2, $vf1\n\tsqc2 $vf2, 0($a0)\n\tnop"
        : : : "memory"
    );
}

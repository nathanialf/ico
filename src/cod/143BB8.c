void func_00243BB8(void *dst, void *src) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\tvitof4.xyzw $vf5, $vf4\n\tsqc2 $vf5, 0($a0)"
        : : : "memory"
    );
}

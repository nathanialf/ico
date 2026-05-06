void func_00243BA8(void *dst, void *src) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\tvftoi0.xyzw $vf5, $vf4\n\tsqc2 $vf5, 0($a0)"
        : : : "memory"
    );
}

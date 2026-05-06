void func_00243B98(void *dst, void *src) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\tvftoi4.xyzw $vf5, $vf4\n\tsqc2 $vf5, 0($a0)"
        : : : "memory"
    );
}

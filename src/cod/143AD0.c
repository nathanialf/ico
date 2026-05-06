void func_00243AD0(void *dst, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\tlqc2 $vf5, 0($a2)\n\tvadd.xyzw $vf6, $vf4, $vf5\n\tsqc2 $vf6, 0($a0)"
        : : : "memory"
    );
}

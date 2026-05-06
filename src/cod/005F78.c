void func_00105F78(void *dst, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\tlqc2 $vf5, 0($a2)\n\tvadd.xyz $vf4, $vf4, $vf5\n\tsqc2 $vf4, 0($a0)\n\tnop"
        : : : "memory"
    );
}

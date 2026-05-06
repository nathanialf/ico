void func_001183B8(void *dst, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0($a1)\n\tlqc2 $vf2, 0($a2)\n\tvsub.xyz $vf1, $vf1, $vf2\n\tsqc2 $vf1, 0($a0)\n\tnop"
        : : : "memory"
    );
}

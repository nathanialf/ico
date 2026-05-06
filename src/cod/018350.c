void func_00118350(void *dst, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0($a1)\n\tlqc2 $vf2, 0($a2)\n\tvopmula.xyz $ACC, $vf1, $vf2\n\tvopmsub.xyz $vf3, $vf2, $vf1\n\tvsub.w $vf3, $vf3, $vf3\n\tsqc2 $vf3, 0($a0)\n\tnop"
        : : : "memory"
    );
}

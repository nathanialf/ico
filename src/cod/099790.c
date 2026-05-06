void func_00199790(void *dst, void *m, void *v) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0($a2)\n\tlqc2 $vf4, 0($a1)\n\tlqc2 $vf5, 16($a1)\n\tlqc2 $vf6, 32($a1)\n\tvmulax.xyzw $ACC, $vf4, $vf8x\n\tvmadday.xyzw $ACC, $vf5, $vf8y\n\tvmaddz.xyzw $vf12, $vf6, $vf8z\n\tsqc2 $vf12, 0($a0)\n\tnop"
        : : : "memory"
    );
}

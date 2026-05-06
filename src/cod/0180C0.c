void func_001180C0(void *dst, void *src) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0($a1)\n\tvmulax.xyzw $ACC, $vf4, $vf8x\n\tvmadday.xyzw $ACC, $vf5, $vf8y\n\tvmaddaz.xyzw $ACC, $vf6, $vf8z\n\tvmaddw.xyzw $vf10, $vf7, $vf8w\n\tsqc2 $vf10, 0($a0)\n\tnop"
        : : : "memory"
    );
}

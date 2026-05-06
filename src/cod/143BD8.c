void func_00243BD8(void *dst) {
    __asm__ __volatile__(
        "vsub.xyzw $vf4, $vf0, $vf0\n\tvadd.w $vf4, $vf4, $vf0\n\tvmr32.xyzw $vf5, $vf4\n\tvmr32.xyzw $vf6, $vf5\n\tvmr32.xyzw $vf7, $vf6\n\tsqc2 $vf4, 48($a0)\n\tsqc2 $vf5, 32($a0)\n\tsqc2 $vf6, 16($a0)\n\tsqc2 $vf7, 0($a0)"
        : : : "memory"
    );
}

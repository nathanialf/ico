void func_00117FC0(void *dst) {
    __asm__ __volatile__(
        "sqc2 $vf4, 0($a0)\n\tsqc2 $vf5, 16($a0)\n\tsqc2 $vf6, 32($a0)\n\tsqc2 $vf7, 48($a0)\n\tnop"
        : : : "memory"
    );
}

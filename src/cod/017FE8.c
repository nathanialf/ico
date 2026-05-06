void func_00117FE8(void *src) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a0)\n\tlqc2 $vf5, 16($a0)\n\tlqc2 $vf6, 32($a0)\n\tlqc2 $vf7, 48($a0)\n\tnop"
        : : : "memory"
    );
}

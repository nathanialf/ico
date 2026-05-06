void func_00117CD0(void *src) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0($a0)\n\tvmove.xyzw $vf7, $vf8\n\tnop"
        : : : "memory"
    );
}

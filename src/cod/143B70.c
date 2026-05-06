void func_00243B70(void *dst, void *src) {
    __asm__ __volatile__(
        "lq $a2, 0($a1)\n\t"
        "lq $a3, 0x10($a1)\n\t"
        "lq $t0, 0x20($a1)\n\t"
        "lq $t1, 0x30($a1)\n\t"
        "sq $a2, 0($a0)\n\t"
        "sq $a3, 0x10($a0)\n\t"
        "sq $t0, 0x20($a0)\n\t"
        "sq $t1, 0x30($a0)"
        : : : "memory"
    );
}

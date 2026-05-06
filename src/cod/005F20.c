void func_00105F20(void *dst, void *src) {
    __asm__ __volatile__(
        "lq $a2, 0($a1)\n\t"
        "sq $a2, 0($a0)\n\t"
        "lq $a2, 0x10($a1)\n\t"
        "sq $a2, 0x10($a0)\n\t"
        "lq $a2, 0x20($a1)\n\t"
        "sq $a2, 0x20($a0)\n\t"
        "lq $a2, 0x30($a1)\n\t"
        "sq $a2, 0x30($a0)\n\t"
        "nop"
        : : : "memory"
    );
}

void func_00105F10(void *dst, void *src) {
    __asm__ __volatile__("lq $a2, 0($a1)\n\tsq $a2, 0($a0)\n\tnop" : : : "memory");
}

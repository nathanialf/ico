void func_00118470(void *dst, void *src) {
    __asm__ __volatile__("lq $t0, 0($a1)\n\tsq $t0, 0($a0)\n\tnop" : : : "memory");
}

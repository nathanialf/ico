void func_001A6DE0(void) {
    char local[0x60];
    __asm__ __volatile__(
        "sd $t0, 0x40($sp)\n\t"
        "sd $t1, 0x48($sp)\n\t"
        "sd $t2, 0x50($sp)\n\t"
        "sd $t3, 0x58($sp)"
        : : "r"(local) : "memory"
    );
}

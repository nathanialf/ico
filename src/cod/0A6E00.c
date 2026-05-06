void func_001A6E00(void) {
    char local[0x70];
    __asm__ __volatile__(
        "sd $a2, 0x40($sp)\n\t"
        "sd $a3, 0x48($sp)\n\t"
        "sd $t0, 0x50($sp)\n\t"
        "sd $t1, 0x58($sp)\n\t"
        "sd $t2, 0x60($sp)\n\t"
        "sd $t3, 0x68($sp)"
        : : "r"(local) : "memory"
    );
}

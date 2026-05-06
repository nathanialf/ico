void func_001003D0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x2B\n\tsyscall 0" : : : "$3", "memory");
}

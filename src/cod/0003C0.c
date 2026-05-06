void func_001003C0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x2A\n\tsyscall 0" : : : "$3", "memory");
}

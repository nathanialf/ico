void func_001003B0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x29\n\tsyscall 0" : : : "$3", "memory");
}

void func_001001B0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0xB\n\tsyscall 0" : : : "$3", "memory");
}

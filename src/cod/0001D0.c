void func_001001D0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0xD\n\tsyscall 0" : : : "$3", "memory");
}

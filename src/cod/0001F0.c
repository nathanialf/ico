void func_001001F0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0xF\n\tsyscall 0" : : : "$3", "memory");
}

void func_001001E0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0xE\n\tsyscall 0" : : : "$3", "memory");
}

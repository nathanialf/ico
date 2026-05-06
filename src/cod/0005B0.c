void func_001005B0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x49\n\tsyscall 0" : : : "$3", "memory");
}

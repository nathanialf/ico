void func_001005E0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x4C\n\tsyscall 0" : : : "$3", "memory");
}

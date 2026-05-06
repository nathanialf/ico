void func_001008C0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x76\n\tsyscall 0" : : : "$3", "memory");
}

void func_00100330(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x21\n\tsyscall 0" : : : "$3", "memory");
}

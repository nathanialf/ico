void func_001005F0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x4D\n\tsyscall 0" : : : "$3", "memory");
}

void func_001004B0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x39\n\tsyscall 0" : : : "$3", "memory");
}

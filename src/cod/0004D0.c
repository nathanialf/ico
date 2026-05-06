void func_001004D0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x3B\n\tsyscall 0" : : : "$3", "memory");
}

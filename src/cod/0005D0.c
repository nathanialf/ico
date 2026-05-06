void func_001005D0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x4B\n\tsyscall 0" : : : "$3", "memory");
}

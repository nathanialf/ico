void func_00100C80(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x5B\n\tsyscall 0" : : : "$3", "memory");
}

void func_00100980(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x7F\n\tsyscall 0" : : : "$3", "memory");
}

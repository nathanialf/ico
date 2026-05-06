void func_00100350(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x23\n\tsyscall 0" : : : "$3", "memory");
}

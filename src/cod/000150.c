void func_00100150(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x5\n\tsyscall 0" : : : "$3", "memory");
}

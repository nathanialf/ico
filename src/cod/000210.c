void func_00100210(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x10\n\tsyscall 0" : : : "$3", "memory");
}

void func_00100560(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x44\n\tsyscall 0" : : : "$3", "memory");
}

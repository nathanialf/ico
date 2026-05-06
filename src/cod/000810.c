void func_00100810(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x6D\n\tsyscall 0" : : : "$3", "memory");
}

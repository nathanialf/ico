void func_00100310(void) {
    __asm__ __volatile__("addiu $3, $zero, -0xFF\n\tsyscall 0" : : : "$3", "memory");
}

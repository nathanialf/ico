void func_00100280(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x16\n\tsyscall 0" : : : "$3", "memory");
}

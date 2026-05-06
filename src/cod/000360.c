void func_00100360(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x24\n\tsyscall 0" : : : "$3", "memory");
}

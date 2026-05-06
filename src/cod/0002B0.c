void func_001002B0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0xFD\n\tsyscall 0" : : : "$3", "memory");
}

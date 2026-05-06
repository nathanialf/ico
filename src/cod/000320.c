void func_00100320(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x20\n\tsyscall 0" : : : "$3", "memory");
}

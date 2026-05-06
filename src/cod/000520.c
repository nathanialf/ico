void func_00100520(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x40\n\tsyscall 0" : : : "$3", "memory");
}

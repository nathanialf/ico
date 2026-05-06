void func_001002F0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x1D\n\tsyscall 0" : : : "$3", "memory");
}

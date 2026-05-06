void func_001007B0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x66\n\tsyscall 0" : : : "$3", "memory");
}

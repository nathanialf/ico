void func_001007F0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x6B\n\tsyscall 0" : : : "$3", "memory");
}

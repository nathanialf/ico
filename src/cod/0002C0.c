void func_001002C0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x1A\n\tsyscall 0" : : : "$3", "memory");
}

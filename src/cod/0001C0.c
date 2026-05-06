void func_001001C0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0xC\n\tsyscall 0" : : : "$3", "memory");
}

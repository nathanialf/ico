void func_001006A0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x58\n\tsyscall 0" : : : "$3", "memory");
}

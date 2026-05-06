void func_001006F0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x5C\n\tsyscall 0" : : : "$3", "memory");
}

void func_001006B0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x59\n\tsyscall 0" : : : "$3", "memory");
}

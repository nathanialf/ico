void func_001006C0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x5A\n\tsyscall 0" : : : "$3", "memory");
}

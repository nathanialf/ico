void func_001005C0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x4A\n\tsyscall 0" : : : "$3", "memory");
}

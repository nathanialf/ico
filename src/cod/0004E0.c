void func_001004E0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x3C\n\tsyscall 0" : : : "$3", "memory");
}

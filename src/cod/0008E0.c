void func_001008E0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x77\n\tsyscall 0" : : : "$3", "memory");
}

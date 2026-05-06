void func_001005A0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x48\n\tsyscall 0" : : : "$3", "memory");
}

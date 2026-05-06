void func_001002E0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x1C\n\tsyscall 0" : : : "$3", "memory");
}

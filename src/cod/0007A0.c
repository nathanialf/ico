void func_001007A0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x64\n\tsyscall 0" : : : "$3", "memory");
}

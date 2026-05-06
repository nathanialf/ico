void func_00100900(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x78\n\tsyscall 0" : : : "$3", "memory");
}

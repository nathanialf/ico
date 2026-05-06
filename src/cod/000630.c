void func_00100630(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x51\n\tsyscall 0" : : : "$3", "memory");
}

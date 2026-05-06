void func_00100830(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x6F\n\tsyscall 0" : : : "$3", "memory");
}

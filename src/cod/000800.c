void func_00100800(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x6C\n\tsyscall 0" : : : "$3", "memory");
}

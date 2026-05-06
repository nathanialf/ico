void func_00100670(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x55\n\tsyscall 0" : : : "$3", "memory");
}

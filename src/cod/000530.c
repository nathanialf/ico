void func_00100530(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x41\n\tsyscall 0" : : : "$3", "memory");
}

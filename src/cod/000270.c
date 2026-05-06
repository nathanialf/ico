void func_00100270(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x15\n\tsyscall 0" : : : "$3", "memory");
}

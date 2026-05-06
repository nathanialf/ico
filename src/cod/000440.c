void func_00100440(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x32\n\tsyscall 0" : : : "$3", "memory");
}

void func_00100190(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x9\n\tsyscall 0" : : : "$3", "memory");
}

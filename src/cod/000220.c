void func_00100220(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x11\n\tsyscall 0" : : : "$3", "memory");
}

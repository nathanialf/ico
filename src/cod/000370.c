void func_00100370(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x25\n\tsyscall 0" : : : "$3", "memory");
}

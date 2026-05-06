void func_00100760(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x60\n\tsyscall 0" : : : "$3", "memory");
}

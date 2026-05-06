void func_00100700(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x5D\n\tsyscall 0" : : : "$3", "memory");
}

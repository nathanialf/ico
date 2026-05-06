void func_00100260(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x14\n\tsyscall 0" : : : "$3", "memory");
}

void func_00100110(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x1\n\tsyscall 0" : : : "$3", "memory");
}

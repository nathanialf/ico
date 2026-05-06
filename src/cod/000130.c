void func_00100130(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x3\n\tsyscall 0" : : : "$3", "memory");
}

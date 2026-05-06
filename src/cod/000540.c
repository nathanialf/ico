void func_00100540(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x42\n\tsyscall 0" : : : "$3", "memory");
}

void func_00100880(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x72\n\tsyscall 0" : : : "$3", "memory");
}

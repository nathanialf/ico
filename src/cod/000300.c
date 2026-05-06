void func_00100300(void) {
    __asm__ __volatile__("addiu $3, $zero, -0xFE\n\tsyscall 0" : : : "$3", "memory");
}

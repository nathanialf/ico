void func_00100450(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x33\n\tsyscall 0" : : : "$3", "memory");
}

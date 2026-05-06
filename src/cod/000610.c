void func_00100610(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x4F\n\tsyscall 0" : : : "$3", "memory");
}

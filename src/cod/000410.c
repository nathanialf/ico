void func_00100410(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x2F\n\tsyscall 0" : : : "$3", "memory");
}

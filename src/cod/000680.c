void func_00100680(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x56\n\tsyscall 0" : : : "$3", "memory");
}

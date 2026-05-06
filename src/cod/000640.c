void func_00100640(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x52\n\tsyscall 0" : : : "$3", "memory");
}

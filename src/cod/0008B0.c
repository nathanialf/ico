void func_001008B0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x75\n\tsyscall 0" : : : "$3", "memory");
}

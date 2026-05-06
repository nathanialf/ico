void func_001002A0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0xFC\n\tsyscall 0" : : : "$3", "memory");
}

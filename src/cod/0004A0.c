void func_001004A0(void) {
    __asm__ __volatile__("addiu $3, $zero, -0x38\n\tsyscall 0" : : : "$3", "memory");
}

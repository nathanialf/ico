void func_001003A0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x28\n\tsyscall 0" : : : "$3", "memory");
}

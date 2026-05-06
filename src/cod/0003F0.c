void func_001003F0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x2D\n\tsyscall 0" : : : "$3", "memory");
}

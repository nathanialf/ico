void func_001004F0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x3D\n\tsyscall 0" : : : "$3", "memory");
}

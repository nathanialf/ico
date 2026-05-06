void func_00100570(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x45\n\tsyscall 0" : : : "$3", "memory");
}

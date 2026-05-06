void func_00100140(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x4\n\tsyscall 0" : : : "$3", "memory");
}

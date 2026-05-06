void func_001001A0(void) {
    __asm__ __volatile__("addiu $3, $zero, 0xA\n\tsyscall 0" : : : "$3", "memory");
}

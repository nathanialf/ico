void func_00100620(void) {
    __asm__ __volatile__("addiu $3, $zero, 0x50\n\tsyscall 0" : : : "$3", "memory");
}

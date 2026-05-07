void func_00100310(void)
{
    register int v1 __asm__("$3") = -0xFF;
    __asm__ __volatile__("syscall 0" : : "r"(v1) : "memory");
}

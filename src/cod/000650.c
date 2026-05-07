void func_00100650(void)
{
    register int v1 __asm__("$3") = -0x53;
    __asm__ __volatile__("syscall 0" : : "r"(v1) : "memory");
}

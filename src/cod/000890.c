void func_00100890(void)
{
    register int v1 __asm__("$3") = 0x73;
    __asm__ __volatile__("syscall 0" : : "r"(v1) : "memory");
}

__attribute__((noreturn)) void func_001AD748(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "b func_001AD748\n"
        " nop\n"
        ".set reorder\n"
    );
}

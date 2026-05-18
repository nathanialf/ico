extern int func_001013E0(char *fmt, void *args);

int func_001019A8(char *fmt, ...)
{
    /* va_list for ee-gcc 2.9 EE-EABI: 7 saved reg slots (a1-a3, t0-t3) of
       8 bytes each = 0x38 bytes preceding __builtin_next_arg's return. */
    void *args = (char *)__builtin_next_arg(fmt) - 0x38;
    return func_001013E0(fmt, args);
}

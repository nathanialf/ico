extern int func_00265C28(int a0, int a1, void *va);

int func_00264060(int a0, int a1, ...)
{
    return func_00265C28(a0, a1, (char *)__builtin_next_arg(a1) - 0x30);
}

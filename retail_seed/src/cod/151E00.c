void func_00251E00(int *self, long long a1)
{
    char *p = (char *)self[0x10];
    *(long long *)(p + 0xF0) = a1;
    *(int *)(p + 0xF8) = 1;
}

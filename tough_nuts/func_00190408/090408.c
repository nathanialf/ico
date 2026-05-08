void func_00190408(int *dst, int *self)
{
    int *p = (int *)((int *)self[0x15C/4])[0x800/4];
    *(long long *)dst = *(long long *)((char *)p + 0xA4);
    *(int *)((char *)dst + 8) = *(int *)((char *)p + 0xAC);
}

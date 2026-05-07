extern void func_0011B6D8(int a0, int a1, int a2);

void func_0011BF40(int a0)
{
    int v = *(int *)(a0 + 0x820);
    int p = *(int *)(a0 + 0x844);
    func_0011B6D8(v, *(int *)(p + 0xF0), *(signed char *)(v + 0x2F) > 0);
}

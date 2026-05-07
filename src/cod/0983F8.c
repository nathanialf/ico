extern int func_001E8D30(int a0);

int func_001983F8(int a0)
{
    int rc = func_001E8D30(a0);
    {
        register int v __asm__("$2") = 1;
        *(int *)*(int *)(rc + 0x60) = v;
        return v;
    }
}

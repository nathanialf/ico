int func_001D3DB0(int a0)
{
    int new_var2;
    int v1 = *((int *)((*((int *)(a0 + 0x15C))) + 0x800));
    int new_var;
    int new_var3;
    int new_var4;
    new_var2 = v1 + 0x4;
    new_var3 = *((int *)new_var2);
    new_var4 = new_var3 == 1;
    if (new_var4) {
        new_var = *((int *)(v1 + 0x40));
        return new_var;
    }
    return 0;
}

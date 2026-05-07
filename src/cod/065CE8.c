extern int func_00163D60(int a0);

int func_00165CE8(int a0)
{
    int v = *(int *)(*(int *)(a0 + 0x164) + 0x10);
    if (v < 0xC) return -1;
    return func_00163D60(a0);
}

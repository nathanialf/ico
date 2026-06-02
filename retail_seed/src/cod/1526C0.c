int func_002526C0(int a0, int a1, int a2)
{
    *(int *)(a0 + 0x4) = a1;
    *(int *)(a0 + 0x8) = a2;
    *(int *)(a0 + 0xC) = a1 >> 4;
    *(int *)(a0 + 0x10) = a2 >> 4;
    return 1;
}

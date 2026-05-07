int func_001D3DB0(int a0)
{
    int v1 = *(int *)(*(int *)(a0 + 0x15C) + 0x800);
    if (*(int *)(v1 + 0x4) == 1) {
        return *(int *)(v1 + 0x40);
    }
    return 0;
}

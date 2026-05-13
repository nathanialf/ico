int func_0013FF88(int *a0, int a1, int a2)
{
    int idx;
    if (a0[0x16] == 0x20) return -1;
    idx = a0[0x16];
    *(int *)((char *)a0 + idx * 8 + 0x5C) = a1;
    idx++;
    a0[0x16] = idx;
    *(int *)((char *)a0 + idx * 8 + 0x60) = a2;
    return 0;
}

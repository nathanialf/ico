int func_0013D0D0(int *a0, int *a1)
{
    register int *node __asm__("$5") = a1;
    int *next;
    if (node[0x30 / 4] != 0)
    {
        *(int *)(node[0x30 / 4] + 0x34) = node[0x34 / 4];
    }
    else
    {
        *a0 = node[0x34 / 4];
    }
    next = (int *) node[0x34 / 4];
    if (next != 0)
    {
        next[0x30 / 4] = node[0x30 / 4];
        next = (int *) node[0x34 / 4];
    }
    {
        void (*fn)(int *, int) = (void (*)(int *, int)) a0[0x8 / 4];
        if (fn != 0)
        {
            fn(node, a0[0xC / 4]);
        }
    }
    return (int) next;
}

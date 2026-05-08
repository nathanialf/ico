extern void func_001F19F0(int x);

void func_001F41C8(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    int i;
    for (i = 0; i < p[0x50 / 4]; i++) {
        int *arr = (int *)p[0x54 / 4];
        func_001F19F0(arr[i]);
    }
}

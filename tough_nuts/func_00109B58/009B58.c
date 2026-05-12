struct __attribute__((packed)) Pack8 { long long x; };

void func_00109B58(int *self)
{
    volatile char *base = (volatile char *)self[0x57];
    char *other = (char *)self[0x59];
    *(struct Pack8 *)(base + 0x180) = *(struct Pack8 *)(base + 0x1A0);
    *(int *)(base + 0x188) = *(int *)(base + 0x1A8);
    *(struct Pack8 *)(other + 0x610) = *(struct Pack8 *)(base + 0x1A0);
    *(int *)(other + 0x618) = *(int *)(base + 0x1A8);
}

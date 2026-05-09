extern void *func_001ADED8(int a, int b);

void *func_001AE420(int a0, int a1, int a2, int a3)
{
    void *r = func_001ADED8(a0, a3);
    *(int *)((char *)r + 0x30) = a1;
    *(int *)((char *)r + 0x34) = a2;
    return r;
}

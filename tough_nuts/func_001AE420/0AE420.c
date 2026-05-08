extern int *func_001ADED8(int a0, int a1);

void func_001AE420(int a0, int a1, int a2, int a3)
{
    int *p = func_001ADED8(a0, a3);
    *(int *)((char *)p + 0x30) = a1;
    *(int *)((char *)p + 0x34) = a2;
}

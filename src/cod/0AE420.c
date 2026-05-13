extern int *func_001ADED8(int a0, int a1);

void func_001AE420(int a0, int a1, int a2, int a3)
{
    int *p = func_001ADED8(a0, a3);
    p[0xC] = a1;
    p[0xD] = a2;
}

extern void func_001A6848(int *p, int a1);

void func_001AA210(int *a0)
{
    int *p = a0;
    int i;
    for (i = 3; i >= 0; i--) {
        func_001A6848(p, 0);
        p = (int *)((char *)p + 0x10);
    }
}

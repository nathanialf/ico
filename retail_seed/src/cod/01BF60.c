extern void func_00118FD8(int *p, int n);

void func_0011BF60(int *a0, int size)
{
    int *p = a0;
    int count;
    size >>= 4;
    if (size <= 0)
        return;
    count = size;
    do {
        int *arg = p;
        p += 4;
        func_00118FD8(arg, 4);
        count--;
    } while (count != 0);
}

extern void func_00136060(int *p);

void func_00136140(int *self)
{
    int *p = (int *)self[0];
    if (p != 0) {
        do {
            int *next = (int *)p[0xC / 4];
            func_00136060(p);
            p = next;
        } while (p != 0);
        ((volatile int *)self)[1] = 0;
        ((volatile int *)self)[0] = 0;
    }
}

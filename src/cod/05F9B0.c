extern void func_0015F800(int *self, int a1);

void func_0015F9B0(int *self, int a1)
{
    char *p;
    int i;
    p = (char *)((int *)self[0x59])[0x19C] + 0x360;
    i = 0;
    do {
        if (*(signed char *)(p + 0x1D) != 0) {
            if (*(int *)(p + 0x14) == a1) {
                return;
            }
        }
        i++;
        p += 0x20;
    } while (i < 5);
    func_0015F800(self, a1);
}

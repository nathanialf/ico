extern int func_00109F10(int a, int b);

void func_001F3F58(int *self, int *other, int a2)
{
    int *s1;
    int rv;
    s1 = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    s1[0x8 / 4] = (int)other;
    rv = func_00109F10((int)other, a2);
    s1[0xC / 4] = rv;
    ((int *)other[0x15C / 4])[0x630 / 4] = (int)self;
}

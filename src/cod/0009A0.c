extern void func_00100990(int a0, int a1);

void func_001009A0(void)
{
    int i;
    for (i = 0x80; i < 0x100; i++) {
        func_00100990(i, 0);
    }
}

extern int func_00100930(int a0);

int func_0024AE10(void)
{
    int v = func_00100930(4);
    int mask = 0x10000;
    return (v & mask) ? 1 : 0;
}

int func_0025C2C0(int a0, int a1, int a2, int a3)
{
    a0 &= 0xFF;
    a1 &= 0xFF;
    a3 &= 0xFF;
    a2 &= 0xFF;
    return (a0 + (a1 - a0) * a3 / a2) & 0xFF;
}

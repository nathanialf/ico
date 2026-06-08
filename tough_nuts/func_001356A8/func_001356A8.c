int func_001356A8(int a0, int a1)
{
    int g = *(int *) D_0062A328;
    int *s1;
    D_0062A33C = g;
    D_0062A348 = 0;
    s1 = (int *) iosFree(g, 0x180A8, D_00550EA0, 0x2E3);
    func_001350C8(s1);
    s1[0] = a1;
    if (a0 == 0)
    {
        debug_assertMessage(D_00550EF0);
    }
    else
    {
        s1[0x4 / 4] = a0;
    }
    return (int) s1;
}

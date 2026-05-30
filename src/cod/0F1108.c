extern unsigned int D_00633718;
extern unsigned int D_0063371C;

int func_001F1108(void)
{
    unsigned int p = D_00633718;
    unsigned int q = D_0063371C;
    unsigned int end = p + 0x1000;
    int r;
    if (q < p)
        q += 0x28000;
    r = 1;
    if (!(q < p) && (int)q < (int)end)
        r = 0;
    return r;
}

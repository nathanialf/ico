extern int D_00553244[];

int func_00264D60(void)
{
    int *p = (int *)D_00553244[0];
    int v = p[0x16] * 0x41C64E6D + 0x3039;
    p[0x16] = v;
    return v & 0x7FFFFFFF;
}

extern int D_0070A3F0[];

int func_001E8DE0(int a0)
{
    int *p;
    if (a0 < 0) {
        return -1;
    }
    p = (int *)((char *)D_0070A3F0 + a0 * 0xA0);
    return p[1] == 1;
}

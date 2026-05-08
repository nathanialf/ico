extern int *func_0013EB50(int a0);

int func_0019BA60(void)
{
    int ret = 0;
    int *p;
    int *q;
    int *r;
    p = func_0013EB50(0x35);
    if (p != 0) {
        q = (int *)p[0x15C / 4];
        r = (int *)q[0x800 / 4];
        ret = r[0x18 / 4] < 5;
    }
    return ret;
}

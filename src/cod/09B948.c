extern int *func_0013EB50(int x);

int func_0019B948(void)
{
    int *p;
    int ret = 0;
    p = (int *)((int *)func_0013EB50(0x2E)[0x15C / 4])[0x800 / 4];
    if (p[0x4 / 4] > 0 || p[0x8 / 4] > 0) {
        ret = 1;
    }
    return ret;
}

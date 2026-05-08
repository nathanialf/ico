extern int func_001B9638(int *a0);

int func_001BA838(int *a0)
{
    int *p = (int *)a0[0x15C / 4];
    int *s = (int *)p[0x800 / 4];
    int ret;
    ret = func_001B9638(a0);
    if (ret == -1) {
        s[0x1C8 / 4] = 0;
        s[0x1C0 / 4] = 0;
        s[0x1C4 / 4] = 0;
        return 2;
    }
    return ret;
}

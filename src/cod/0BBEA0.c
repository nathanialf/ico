void func_001BBEA0(int *a0)
{
    int *p = (int *)a0[0x15C / 4];
    int *q = (int *)p[0];
    if (q == 0) {
        return;
    }
    if (q[0x16C / 4] == 0) {
        a0[0x16C / 4] = 0;
    }
}

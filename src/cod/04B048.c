extern int func_001F40C8(int *q);

int func_0014B048(int *a0)
{
    int *q;
    int ret = 0;
    q = (int *)((int *)a0[0x164 / 4])[0x140 / 4];
    if (q == 0 || func_001F40C8(q) == 0) {
        ret = 1;
    }
    return ret;
}

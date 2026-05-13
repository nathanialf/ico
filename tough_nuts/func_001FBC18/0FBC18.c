extern int D_004C7710[];

int func_001FBC18(void)
{
    int idx;
    int *p;
    int end_off;
    int adj_cur;
    idx = D_004C7710[0];
    adj_cur = D_004C7710[4] - 0x80000;
    p = D_004C7710 + idx;
    end_off = p[1];
    return (end_off - adj_cur) >> 4;
}

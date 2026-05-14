extern int D_004C7710[];

int func_001FBC18(void)
{
    int idx = D_004C7710[0];
    int adj_cur = D_004C7710[4] - 0x80000;
    int end_off = (D_004C7710 + idx)[1];
    return (end_off - adj_cur) >> 4;
}

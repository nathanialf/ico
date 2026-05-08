extern int D_00275254[];
extern int D_0063304C;
extern int func_001B7288(int x);

int func_001B5728(void)
{
    int v;
    int ret;
    v = D_00275254[0];
    if ((v & 0x10) != 0) {
        func_001B7288(0);
        D_0063304C = 0;
        ret = 0x1A;
    } else {
        ret = -1;
    }
    return ret;
}

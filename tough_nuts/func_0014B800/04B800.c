extern int D_006325B4;

int func_0014B800(int *self)
{
    int *p;
    int *q;
    p = (int *)self[0x59];
    if (p[0xC] == 0x35) {
        return 1;
    }
    q = (int *)p[0x19E];
    if (q[0xE5] == 0) {
        return 0;
    }
    if (D_006325B4 == 0) {
        return 0;
    }
    return 1;
}

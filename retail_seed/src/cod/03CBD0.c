extern int *D_00632190;

int func_0013CBD0(unsigned idx) {
    int *base = (int *)D_00632190;
    if (idx >= (unsigned)base[0]) return 0;
    return ((int *)base[1])[idx];
}

extern unsigned int *D_00632190;

int func_0013CF08(unsigned int idx, int val) {
    int *base = (int *)D_00632190;
    if (idx < (unsigned)base[0]) {
        ((int *)base[1])[idx] = val;
    } else {
        idx = -1;
    }
    return idx;
}

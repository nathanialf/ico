extern int *D_00632190;

int func_0013CAA0(unsigned int idx, int val)
{
    int *base = (int *)D_00632190;
    if (idx >= (unsigned int)base[0]) return -1;
    ((int *)base[1])[idx] = val;
    return idx;
}

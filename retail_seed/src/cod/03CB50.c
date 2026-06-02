extern int *D_00632190;

int func_0013CB50(unsigned int idx)
{
    int *base = (int *)D_00632190;
    if (idx >= (unsigned int)base[0]) return -1;
    ((int *)base[1])[idx] = 0;
    return idx;
}

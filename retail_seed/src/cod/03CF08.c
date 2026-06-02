extern int *D_00632190;

int func_0013CF08(int idx, int val)
{
    int *base = (int *)D_00632190;
    int *array;
    if ((unsigned int)idx < (unsigned int)base[0]) goto store;
    idx = -1;
    goto end;
store:
    array = (int *)base[1];
    array[idx] = val;
end:
    return idx;
}

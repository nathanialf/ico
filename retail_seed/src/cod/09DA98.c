int func_0019DA98(int *a0, int *a1)
{
    int new_var;
    int diff = a0[1] - a0[3];
    if (diff != 0) {
        new_var = a0[2];
        a1[0] = a0[0] + new_var;
    }
    return diff;
}

int func_00187950(int *a0, int a1)
{
    int sum = 0;
    int i;
    if (a1 > 0) {
        int hi = a0[0xF];
        int lo = a0[0xE];
        i = 0;
        do {
            sum = sum + (hi - lo);
            i++;
        } while (i < a1);
    }
    return sum;
}

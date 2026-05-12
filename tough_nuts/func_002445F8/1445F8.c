void func_002445F8(char *p, int n)
{
    int i;
    int neg1;
    if (n == 0) return;
    i = n - 1;
    neg1 = -1;
    do {
        *p = 0;
        i--;
        p++;
    } while (i != neg1);
}

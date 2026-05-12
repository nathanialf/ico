extern int D_00633CB8[2];

int func_00140F20(void)
{
    int count = 0;
    int *p = D_00633CB8;
    int n = 1;
    do {
        int v = *p;
        int next = count + 1;
        p++;
        n--;
        if (v != 0) count = next;
    } while (n >= 0);
    return count;
}

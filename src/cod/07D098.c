extern int D_006CF910[];

int func_0017D098(void)
{
    int count = 0;
    int *p = D_006CF910;
    int *end = (int *)((char *)p + 0x28);
    do {
        int v = *p;
        int next = count + 1;
        p = (int *)((char *)p + 0x14);
        if (v != 0) count = next;
    } while ((int)p < (int)end);
    return count;
}

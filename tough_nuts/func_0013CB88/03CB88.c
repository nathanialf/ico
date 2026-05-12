extern int *D_00632190;

unsigned short func_0013CB88(unsigned int idx)
{
    int *p = (int *)D_00632190;
    int *q;
    if (idx < (unsigned int)p[0]) {
        q = (int *)((int *)p[1])[idx];
    } else {
        q = 0;
    }
    if (q == 0) return 0;
    return *(unsigned short *)((char *)(*q) + 8);
}

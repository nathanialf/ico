float func_00190658(int *self)
{
    int *p = (int *)self[0x15C/4];
    int *q = (int *)p[0x800/4];
    int n = q[0x74/4] - 1;
    return (float)n * 50.0f;
}

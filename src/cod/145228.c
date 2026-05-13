void func_00245228(int **a0)
{
    int *p1 = a0[0];
    int *p2 = a0[3];
    int t = (int)p1 - 4;
    int diff;
    a0[3] = 0;
    diff = t - (int)p2;
    *p2 += (unsigned int)(diff >> 2) >> 2;
}

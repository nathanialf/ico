extern float func_00168C18(int *p, int *q);

float func_0010A330(int *a, int *b)
{
    int *pa;
    int *pb;
    float r1;
    float r2;
    pa = (int *)a[0x15C/4];
    r1 = func_00168C18((int *)((char *)pa + 0x1D0), (int *)((char *)pa + 0xA0));
    pb = (int *)b[0x15C/4];
    r2 = func_00168C18((int *)((char *)pb + 0x1D0), (int *)((char *)pb + 0xA0));
    return r1 - r2;
}

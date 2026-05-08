extern int func_002450C8(int *self, int a1);

void func_00245120(int *self, int a1)
{
    int v0;
    int *p;
    int *q;
    v0 = func_002450C8(self, a1);
    p = (int *)self[0];
    self[2] = v0;
    p[0] = a1 | 0x10000000;
    q = p + 1;
    self[3] = 0;
    self[0] = (int)(q + 1);
    *q = 0;
}

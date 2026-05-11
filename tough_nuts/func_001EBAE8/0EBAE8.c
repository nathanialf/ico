extern int D_00633604;
extern int D_0063360C;
extern int D_0070C9C8[];

void func_001EBAE8(int a0, int a1)
{
    int idx = D_00633604;
    int *p;
    D_0063360C = a1;
    p = D_0070C9C8 + idx;
    *p = a0;
    D_00633604 = idx + 1;
}

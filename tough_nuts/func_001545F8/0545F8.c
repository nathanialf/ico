extern int D_00631AE4;
extern int D_00631AE8;

int func_001545F8(void)
{
    int *a = (int *)D_00631AE4;
    int *b = (int *)D_00631AE8;
    int *pa;
    int *pb;
    int *r;
    if (a == 0) return -1;
    if (b == 0) return -1;
    pa = (int *)a[0x164/4];
    if (pa[0x30/4] != 0x2D) return -1;
    pb = (int *)b[0x164/4];
    if (pb[0x30/4] != 0x2D) return -1;
    r = (int *)pa[0x150/4];
    return r[0x8/4];
}

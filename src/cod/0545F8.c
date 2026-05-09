extern int D_00631AE4;
extern int D_00631AE8;

int func_001545F8(void)
{
    int *a = (int *)D_00631AE4;
    int *b = (int *)D_00631AE8;
    int *pa, *pb, *r;
    int v;
    int ret;
    if (a == 0) goto err;
    if (b == 0) goto err;
    pa = (int *)a[0x164/4];
    v = pa[0x30/4];
    if (v != 0x2D) goto err;
    pb = (int *)b[0x164/4];
    if (pb[0x30/4] != v) goto err;
    r = (int *)pa[0x150/4];
    return r[2];
err:
    return -1;
}

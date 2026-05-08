extern int D_004BEA50[];

int func_001BA7C0(void *a0)
{
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x800);
    return D_004BEA50[q[0x8 / 4]];
}

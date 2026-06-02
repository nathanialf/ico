extern int D_00631990;

int func_00198110(void)
{
    int v = D_00631990;
    int r = 0;
    if (v == 0x54) goto yes;
    if (v == 3) goto yes;
    if (v != 0x2E) goto no;
yes:
    r = 1;
no:
    return r;
}

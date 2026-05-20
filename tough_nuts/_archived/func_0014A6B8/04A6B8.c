extern int *D_00631AE4;
extern unsigned char D_0055CFD8[];

int func_0014A6B8(int *a0)
{
    int *p;
    char *e;
    int v;
    if (a0 != D_00631AE4) return 0;
    p = (int *)a0[0x59];
    e = (char *)&D_0055CFD8[p[0xC] * 0x50];
    v = *(int *)(e + 0x4C);
    if (((unsigned)v >> 9 & 1) != 0) return p[0x60];
    return 0;
}

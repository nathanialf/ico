extern char *D_005524A4[];
extern int D_005525C4[];
extern unsigned char D_00552D40[16];

int func_00257850(void)
{
    char *p = (char *)D_005524A4[0];
    int *q = *(int **)(p + 0x40);
    if (q[2] != 2) {
        int v = D_005525C4[0];
        q[2] = 2;
        q[0x2B] = v;
    }
    *(int *)D_00552D40 = 1;
    return 1;
}

extern char D_00280F88[];
extern int func_0013A5B8(char *a0, void *a1, int a2, int a3);

int func_00138068(long long *a0)
{
    *(int *)((char *)a0 + 4) = 7;
    *a0 = *a0 & -2L;
    return func_0013A5B8(D_00280F88, a0, 0, -2);
}

extern int D_00631990;
extern char D_005F2FB8[];
extern int func_00188228(int a0);

int func_00188290(void)
{
    int idx = D_00631990;
    char *base = &D_005F2FB8[idx * 0x194];
    return func_00188228(*(int *)(base + 0x118));
}

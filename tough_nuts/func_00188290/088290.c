extern int D_00631990;
extern char D_005F2FB8[];
extern void func_00188228(int x);

void func_00188290(void)
{
    char *p = &D_005F2FB8[D_00631990 * 0x194];
    func_00188228(*(int *)(p + 0x118));
}

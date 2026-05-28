extern int *D_00631AE4;
extern char D_00558CB8[];
extern char D_00632310[];
extern char D_00632318[];
extern void func_001A6E28();

void func_0015B728(int *a0, int a1, int *a2)
{
    int *cur = D_00631AE4;
    int *p = (int *)a0[0x59];
    p[0x34] |= 0x10;
    func_001A6E28(D_00558CB8,
                  (a2 == cur) ? D_00632310 : D_00632318,
                  (a0 == cur) ? D_00632310 : D_00632318);
}

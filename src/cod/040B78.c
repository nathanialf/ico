extern int D_00633CC4;
extern int D_00633CB0;
extern char D_00557B78[];
extern int func_00135EB8(int x, char *p, int b);

void func_00140B78(void)
{
    int a;
    a = func_00135EB8(0xB8800, D_00557B78, 0x44);
    D_00633CC4 = a;
    if ((a & 0x7FF) != 0) {
        D_00633CB0 = (a / 0x800 + 1) * 0x800;
    } else {
        D_00633CB0 = a;
    }
}

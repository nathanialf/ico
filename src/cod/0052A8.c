extern void func_002438B8(int *buf, char *p, int x);
extern void func_00105F00(char *p, int *buf);
extern int D_00631B40;
extern char D_0065FA40[];

void func_001052A8(int a0)
{
    int buf[4];
    func_002438B8(buf, &D_0065FA40[D_00631B40 * 64], a0);
    *(float *)&buf[3] = 1.0f;
    func_00105F00(&D_0065FA40[D_00631B40 * 64 + 0x30], buf);
}
